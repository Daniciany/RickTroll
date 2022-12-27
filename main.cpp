#include <windows.h>
#include <conio.h>
#include <iostream>
#include <shellapi.h>
#include <opencv2/opencv.hpp>

int playVideo(int argc, char* argv[])
{
    // Open a video file
    cv::VideoCapture cap("video.mp4");
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Could not open video file" << std::endl;
        return -1;
    }

    // Get the video frame size
    int width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Create a window to display the video
    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);

    // Read and display video frames until the end of the video
    cv::Mat frame;
    while (cap.read(frame)) {
        cv::imshow("Video", frame);
        if (cv::waitKey(30) == 27) { // Wait for 'ESC' key press to exit
            break;
        }
    }

    return 0;
}


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
	//nid.dwInfoFlags =
	
	Shell_NotifyIcon(NIM_ADD, &nid);
	// Shell_NotifyIcon(NIM_DELETE, &nid);
}

int main() {
    std::cout << "my program" << std::endl;

    createTray();

    getch();

    return 0;
}