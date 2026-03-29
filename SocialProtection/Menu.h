#ifndef MENU_H
#define MENU_H

#include "DataManager.h"

class Menu {
private:
    DataManager manager;

    void printMainMenu();
    void printDepartmentMenu();
    void printFamilyMenu();
    void printSearchMenu();
    void printSortMenu();

    void handleDepartmentMenu();
    void handleFamilyMenu();
    void handleSearchMenu();
    void handleSortMenu();
    void handleReports();

    void clearScreen();
    void waitForKey();

public:
    void run();
};

#endif