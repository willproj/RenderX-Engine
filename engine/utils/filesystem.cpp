#include "filesystem.h"
#include <commdlg.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "openglcore/include/window.h"


namespace engine::utils
{
	std::string FileSystem::getRootPath()
	{
		return std::string(ROOT_DIR);
	}

	std::string FileSystem::openFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)openglcore::Window::getInstance()->getGLFWwinPtr());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}
	std::string FileSystem::saveFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)openglcore::Window::getInstance()->getGLFWwinPtr());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}

	std::string FileSystem::openFolder()
	{
        // Initialize COM
        HRESULT hr = CoInitialize(NULL);
        if (FAILED(hr))
        {
            printf("Failed to initialize COM.\n");
            return std::string();
        }

        // Create a new instance of the File Open dialog box
        IFileDialog* pfd;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (FAILED(hr))
        {
            printf("Failed to create instance of File Open dialog box.\n");
            CoUninitialize();
            return std::string();
        }

        // Set the options for the dialog box
        DWORD dwOptions;
        hr = pfd->GetOptions(&dwOptions);
        if (FAILED(hr))
        {
            printf("Failed to get options for File Open dialog box.\n");
            pfd->Release();
            CoUninitialize();
            return std::string();
        }
        hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);
        if (FAILED(hr))
        {
            printf("Failed to set options for File Open dialog box.\n");
            pfd->Release();
            CoUninitialize();
            return std::string();
        }

        // Show the dialog box
        hr = pfd->Show(NULL);
        if (FAILED(hr))
        {
            printf("Failed to show File Open dialog box.\n");
            pfd->Release();
            CoUninitialize();
            return std::string();
        }

        // Get the selected folder path
        IShellItem* psi;
        hr = pfd->GetResult(&psi);
        if (FAILED(hr))
        {
            printf("Failed to get selected folder from File Open dialog box.\n");
            pfd->Release();
            CoUninitialize();
            return std::string();
        }

        PWSTR pszFolderPath;
        hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);
        if (FAILED(hr))
        {
            printf("Failed to get selected folder path.\n");
            psi->Release();
            pfd->Release();
            CoUninitialize();
            return std::string();
        }
        
        std::wstring wstrFolderPath(pszFolderPath);
        CoTaskMemFree(pszFolderPath);

        // Release COM objects
        psi->Release();
        pfd->Release();
        CoUninitialize();

        return *(std::string*)&wstrFolderPath;
	}

	std::string FileSystem::getFilenameInFilepath(const std::string& path)
	{
		return path.substr(path.find_last_of("/\\") + 1);
	}
}