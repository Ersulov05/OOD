#include "./Exception/EnoughtCountArgumentsException.h"
#include "./Exception/UnknownOptionException.h"
#include "./lib/Stream/Input/CFileInputStream.h"
#include "./lib/Stream/Input/Decorator/CDecompressInputStream.h"
#include "./lib/Stream/Input/Decorator/CDecryptInputStream.h"
#include "./lib/Stream/Output/CFileOutputStream.h"
#include "./lib/Stream/Output/Decorator/CCompressOutputStream.h"
#include "./lib/Stream/Output/Decorator/CEncryptOutputStream.h"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using InputStreamDecoratorFactoriesType = std::vector<std::function<IInputStreamPtr(IInputStreamPtr&&)>>;
using OutputStreamDecoratorFactoriesType = std::vector<std::function<IOutputStreamPtr(IOutputStreamPtr&&)>>;

const std::string ENCRYPT_OPTION_NAME = "--encrypt";
const std::string DECRYPT_OPTION_NAME = "--decrypt";
const std::string COMPRESS_OPTION_NAME = "--compress";
const std::string DECOMPRESS_OPTION_NAME = "--decompress";

template <typename Component, typename... Args>
auto MakeDecorator(const Args&... args)
{
	return [=](auto&& b) {
		return std::make_unique<Component>(std::forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(std::forward<Component>(component));
}

void AssertNextArgumentExists(int currentIndex, int argc, const std::string& optionName)
{
	if (currentIndex + 1 >= argc)
	{
		throw EnoughtCountArgumentsException(optionName);
	}
}

void InitDecoratorFactories(
	InputStreamDecoratorFactoriesType& inputDecoratorFactories,
	OutputStreamDecoratorFactoriesType& outputDecoratorFactories,
	const int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == COMPRESS_OPTION_NAME)
		{
			outputDecoratorFactories.insert(outputDecoratorFactories.begin(), MakeDecorator<CCompressOutputStream>());
		}
		else if (std::string(argv[i]) == DECOMPRESS_OPTION_NAME)
		{
			inputDecoratorFactories.push_back(MakeDecorator<CDecompressInputStream>());
		}
		else if (std::string(argv[i]) == ENCRYPT_OPTION_NAME)
		{
			AssertNextArgumentExists(i, argc, ENCRYPT_OPTION_NAME);
			int key = std::stoi(argv[++i]);
			outputDecoratorFactories.insert(outputDecoratorFactories.begin(), MakeDecorator<CEncryptOutputStream>(key));
		}
		else if (std::string(argv[i]) == DECRYPT_OPTION_NAME)
		{
			AssertNextArgumentExists(i, argc, DECRYPT_OPTION_NAME);
			int key = std::stoi(argv[++i]);
			inputDecoratorFactories.push_back(MakeDecorator<CDecryptInputStream>(key));
		}
		else
		{
			throw UnknownOptionException(argv[i]);
		}
	}
}

int main(const int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid count arguments\n";
		return 1;
	}
	std::string inputFileName = argv[argc - 2];
	std::string outputFileName = argv[argc - 1];

	InputStreamDecoratorFactoriesType inputDecoratorFactories;
	OutputStreamDecoratorFactoriesType outputDecoratorFactories;
	try
	{
		InitDecoratorFactories(inputDecoratorFactories, outputDecoratorFactories, argc - 2, argv);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}

	IInputStreamPtr inputFile = std::make_unique<CFileInputStream>(inputFileName);
	IOutputStreamPtr outputFile = std::make_unique<CFileOutputStream>(outputFileName);
	for (auto& factory : inputDecoratorFactories)
	{
		inputFile = factory(std::move(inputFile));
	}
	for (auto& factory : outputDecoratorFactories)
	{
		outputFile = factory(std::move(outputFile));
	}

	while (!inputFile->IsEOF())
	{
		outputFile->WriteByte(inputFile->ReadByte());
	}

	return 0;
}