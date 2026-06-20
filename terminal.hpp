#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class TerminalUI {
private:
    static HANDLE hConsole;
    static bool initialized;
    
    static void init() {
        if (!initialized) {
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            initialized = true;
        }
    }
    
public:
    static void setColor(int color) {
        init();
        SetConsoleTextAttribute(hConsole, color);
    }

    static void resetColor() {
        init();
        SetConsoleTextAttribute(hConsole, 7); 
    }
    
    static void clearScreen() {
        system("cls");
    }

    static void print(const string& text, int color = 7) {
        setColor(color);
        cout << text;
        resetColor();
    }

    static void printLine(const string& text, int color = 7) {
        setColor(color);
        cout << text << endl;
        resetColor();
    }

    static void separator() {
        setColor(8); 
        cout << "----------------------------------------" << endl;
        resetColor();
    }

    static void header(const string& text) {
        setColor(14);
        cout << "========================================" << endl;
        cout << "        " << text << endl;
        cout << "========================================" << endl;
        resetColor();
    }
    
    static void render(const string& text) {
        cout << text << endl;
    }
};

HANDLE TerminalUI::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
bool TerminalUI::initialized = false;

namespace Color {
    const int BLACK = 0;
    const int BLUE = 1;
    const int GREEN = 2;
    const int RED = 4;
    const int YELLOW = 6;
    const int WHITE = 7;
    const int GRAY = 8;
    const int LIGHT_BLUE = 9;
    const int LIGHT_GREEN = 10;
    const int LIGHT_RED = 12;
    const int LIGHT_YELLOW = 14;
}