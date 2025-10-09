#include "./lib/Stream/Input/CFileInputStream.h"
#include "./lib/Stream/Input/Decorator/CDecompressInputStream.h"
#include "./lib/Stream/Input/Decorator/CDecryptInputStream.h"
#include "./lib/Stream/Output/CFileOutputStream.h"
#include "./lib/Stream/Output/Decorator/CCompressOutputStream.h"
#include "./lib/Stream/Output/Decorator/CEncryptOutputStream.h"
#include <iostream>
#include <memory>

template <typename Component, typename... Args>
auto Make(const Args&... args)
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

int main(const int argc, char* argv[])
{
	IOutputStreamPtr outputFile = std::make_unique<CFileOutputStream>("test.txt");
	outputFile = std::move(outputFile) << Make<CCompressOutputStream>();

	outputFile->WriteByte('5');
	outputFile->WriteByte('6');
	outputFile->Close();

	IInputStreamPtr inputFile = std::make_unique<CFileInputStream>("test.txt") << Make<CDecompressInputStream>();
	while (!inputFile->IsEOF())
	{
		std::cout << static_cast<char>(inputFile->ReadByte());
	}

	std::cout << std::endl;

	return 0;
}