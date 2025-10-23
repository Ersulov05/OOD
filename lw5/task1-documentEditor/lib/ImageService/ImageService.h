#pragma once
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

class ImageService
{
public:
	std::string SaveImage(std::string path)
	{
		size_t dotPos = path.find_last_of('.');
		std::string extension = dotPos != std::string::npos
			? path.substr(dotPos)
			: "";
		std::string newFilename = GenerateName() + extension;
		std::string savePath = IMAGE_DIR + "/" + newFilename;
		std::filesystem::create_directories(IMAGE_DIR);

		try
		{
			std::filesystem::copy_file(path, savePath, std::filesystem::copy_options::overwrite_existing);
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			throw std::runtime_error("Failed to copy file: " + std::string(e.what()));
		}

		return savePath;
	}

	void DeleteImage(std::string path)
	{
		try
		{
			if (std::filesystem::exists(path))
			{
				std::filesystem::remove(path);
			}
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			throw std::runtime_error("Filesystem error while deleting: " + std::string(e.what()));
		}
	}

private:
	static inline const std::string IMAGE_DIR = "images";

	std::string GenerateName()
	{
		auto now = std::chrono::system_clock::now();
		auto time_t = std::chrono::system_clock::to_time_t(now);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

		std::ostringstream oss;
		oss << "file_"
			<< std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S_")
			<< std::setfill('0') << std::setw(3) << ms.count();

		return oss.str();
	}
};