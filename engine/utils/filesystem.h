#pragma once
#include "common.h"
#include "config.h"
#include <shobjidl.h>

namespace engine::utils
{
	class FileSystem
	{
	public:
		FileSystem() = delete;
		FileSystem(const FileSystem&) = delete;
		FileSystem& operator=(const FileSystem&) = delete;
		~FileSystem() = delete;

		static std::string getRootPath();
		static std::string openFile(const char* filter);
		static std::string saveFile(const char* filter);
		static std::string getFilenameInFilepath(const std::string& path);

		static std::string openFolder();
				
	private:
		std::string root;
	};
}