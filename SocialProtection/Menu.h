#ifndef MENU_H
#define MENU_H

#include "DataManager.h"
#include "ConsoleUtils.h"

class Menu {
private:
    DataManager manager;

    void clearScreen();
    void waitForKey();

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

public:
    void run();
};

#endif