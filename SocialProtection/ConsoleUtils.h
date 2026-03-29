#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

class ConsoleUtils {
public:
    // Otrymaty shyrynu konsoli
    static int getShyryna() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }

    // Otrymaty vysotu konsoli
    static int getVysota() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    // Druk tekstu po centru
    static void drukuCentr(const std::string& text) {
        int shyryna = getShyryna();
        int vidstup = (shyryna - text.length()) / 2;
        if (vidstup < 0) vidstup = 0;
        std::cout << std::string(vidstup, ' ') << text << std::endl;
    }

    // Druk liniji po centru
    static void drukuLiniyuCentr(int dovzhyna = 50, char symvol = '=') {
        int shyryna = getShyryna();
        int vidstup = (shyryna - dovzhyna) / 2;
        if (vidstup < 0) vidstup = 0;
        std::cout << std::string(vidstup, ' ') << std::string(dovzhyna, symvol) << std::endl;
    }

    // Pustyj riadok
    static void pustyjRiadok(int kilkist = 1) {
        for (int i = 0; i < kilkist; i++) {
            std::cout << std::endl;
        }
    }

    // Kolor tekstu
    static void kolor(int kolir) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolir);
    }

    // Skynuty kolor
    static void skynutyKolor() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    // Vidstup dlja centruvannja
    static int getVidstup(int dovzhynaTekstu) {
        return (getShyryna() - dovzhynaTekstu) / 2;
    }
};

#endif