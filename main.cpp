#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ShlObj.h>
#include <string>

void hideConsoleWindow() {
    // Get the console window handle
    HWND consoleHandle = GetConsoleWindow();

    // Hide the console window
    ShowWindow(consoleHandle, SW_HIDE);
}


int createShortcut(int count) {
    // Get the desktop folder path
    wchar_t desktop[MAX_PATH];
    SHGetFolderPathW(NULL, CSIDL_DESKTOP, NULL, SHGFP_TYPE_CURRENT, desktop);

    // Create the shortcut file path
    wchar_t shortcut[MAX_PATH];
    wcscpy_s(shortcut, desktop);

    std::wstring str = L"\\RickAstley";
    str = str + std::to_wstring(count) + L".lnk";
    // std::wcout << str << std::endl;
    wcscat_s(shortcut, str.c_str());

    // Open the shortcut file for writing
    HANDLE file = CreateFileW(shortcut, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        // An error occurred
    }

    // Write the shortcut data to the file
    const wchar_t* data =
        L"[Shell]\n"
        L"IconFile=D:\\Program Files (x86)\\Program Files\\Program\\Program\\c++\\RickTroll\\nggyu.mp4" // specify the correct path to the icon file here
        L"IconIndex=0\n"
        L"Target=D:\\Program Files (x86)\\Program Files\\Program\\Program\\c++\\RickTroll\\nggyu.mp4" // specify the correct path to the target file here
        L"Description=Rick is the best\n";
    DWORD bytesWritten;
    if (!WriteFile(file, data, wcslen(data) * sizeof(wchar_t), &bytesWritten, NULL)) {
        // An error occurred
        CloseHandle(file);
    }

    // Close the file
    CloseHandle(file);

    if (count > 0) {
        return createShortcut(count - 1);
    } else {
        return 0;
    }
}

// global variables
bool canModifyWindow = TRUE;
bool vlcInstalled = FALSE;

void createTray() {
    NOTIFYICONDATAA nid = {};
	AllocConsole();
	HWND h = FindWindowA("ConsoleWindowClass", NULL);
	
	nid.cbSize = sizeof(nid);
	nid.hWnd = h;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO;
	
    nid.hIcon = (HICON)LoadImage(NULL, "D:/Program Files (x86)/Program Files/Program/Program/c++/RickTroll/Rick.ico", IMAGE_ICON, 128, 128, LR_LOADFROMFILE | LR_SHARED);

	memcpy(nid.szTip, "Hi, I am Rick Astley", 128);
	memcpy(nid.szInfoTitle, "Hello!", 64);
	memcpy(nid.szInfo, "I'll never gonna give you up!", 256);
	
	Shell_NotifyIcon(NIM_ADD, &nid);
	// Shell_NotifyIcon(NIM_DELETE, &nid);
}

// Declare the window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void checkWNDMOD() {
	while (canModifyWindow) {
		if (!canModifyWindow) {
			break;
		}
	}
}

void playLoop() {
	while(TRUE) {
		ShellExecute(NULL, "open", "C:/Program Files/VideoLAN/VLC/vlc.exe", "nggyu.mp4", NULL, SW_SHOW);

		Sleep(500);
	}
}

void play() {
    // Run the system command to create the window
    system("nggyu.mp4");
    // Get the window handle of the created window
    HWND hwnd = FindWindow(NULL, "Media Player");
    if (hwnd == NULL) {
        // Error finding the window
        std::cout << "Error finding window. GetLastError() = " << GetLastError() << std::endl;
		canModifyWindow = FALSE;
    } else {
        // Install the custom window procedure
        WNDPROC old_proc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc);
        if (old_proc == NULL) {
            // Error installing the window procedure
            std::cout << "Error installing window procedure. GetLastError() = " << GetLastError() << std::endl;
			canModifyWindow = FALSE;
        } else {
            // Window procedure installed successfully
            std::cout << "Window procedure installed successfully" << std::endl;
        }
    }
}

int main() {
    hideConsoleWindow();
	play();
	createTray();
	checkWNDMOD();

	createShortcut(100);

	if (!canModifyWindow) {
		playLoop();
	}

    getch();

    return 0;
}

// Define the window procedure function
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE:
            // Handle the window close event
            // Perform the desired action when the window is closed
            play();
        default:
            // Call the default window procedure for other events
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}