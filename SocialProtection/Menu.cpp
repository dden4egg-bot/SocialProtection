#include "Menu.h"
#include <iostream>
#include <limits>
#include <cstdlib>

void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Menu::waitForKey() {
    std::cout << "\nNatysnit Enter dlia prodovzhennia...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Menu::printMainMenu() {
    clearScreen();
    std::cout << "===========================================" << std::endl;
    std::cout << "    SOTSIALNYI ZAKHYST NASELENNIA" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "1. Robota z pidviddilamy" << std::endl;
    std::cout << "2. Robota z sim'iamy" << std::endl;
    std::cout << "3. Formuvannia zvitiv" << std::endl;
    std::cout << "4. Poshuk danykh" << std::endl;
    std::cout << "5. Sortuvannia danykh" << std::endl;
    std::cout << "6. Zberehty dani u fail" << std::endl;
    std::cout << "7. Zavantazhyty dani z failu" << std::endl;
    std::cout << "8. Vykhid" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Vash vybir: ";
}

void Menu::printDepartmentMenu() {
    clearScreen();
    std::cout << "=== ROBOTA Z PIDVIDDILAMY ===" << std::endl;
    std::cout << "1. Dodaty pidviddil" << std::endl;
    std::cout << "2. Vydalyty pidviddil" << std::endl;
    std::cout << "3. Redahuvaty pidviddil" << std::endl;
    std::cout << "4. Perehlyanuty vsi pidviddily" << std::endl;
    std::cout << "5. Povernutysia do holovnoho meniu" << std::endl;
    std::cout << "Vash vybir: ";
}

void Menu::printFamilyMenu() {
    clearScreen();
    std::cout << "=== ROBOTA Z SIM'IAMY ===" << std::endl;
    std::cout << "1. Dodaty sim'iu" << std::endl;
    std::cout << "2. Vydalyty sim'iu" << std::endl;
    std::cout << "3. Redahuvaty sim'iu" << std::endl;
    std::cout << "4. Perehlyanuty sim'i za pidviddilom" << std::endl;
    std::cout << "5. Perehlyanuty vsi sim'i" << std::endl;
    std::cout << "6. Povernutysia do holovnoho meniu" << std::endl;
    std::cout << "Vash vybir: ";
}

void Menu::printSearchMenu() {
    clearScreen();
    std::cout << "=== POSHUK DANYKH ===" << std::endl;
    std::cout << "1. Poshuk simey za prizvyshchem" << std::endl;
    std::cout << "2. Poshuk simey za katehoriieiu" << std::endl;
    std::cout << "3. Povernutysia do holovnoho meniu" << std::endl;
    std::cout << "Vash vybir: ";
}

void Menu::printSortMenu() {
    clearScreen();
    std::cout << "=== SORTUVANNIA DANYKH ===" << std::endl;
    std::cout << "1. Sortuvaty sim'i za prizvyshchem" << std::endl;
    std::cout << "2. Sortuvaty sim'i za kilkistiu ditey" << std::endl;
    std::cout << "3. Sortuvaty sim'i za sumoiu dopomohy" << std::endl;
    std::cout << "4. Povernutysia do holovnoho meniu" << std::endl;
    std::cout << "Vash vybir: ";
}

void Menu::handleDepartmentMenu() {
    int choice;
    do {
        printDepartmentMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string postal, specialist;
            std::cout << "Vvedit poshtovyi indeks: ";
            std::getline(std::cin, postal);
            std::cout << "Vvedit PIB fakhivtsia: ";
            std::getline(std::cin, specialist);
            manager.addDepartment(postal, specialist);
            waitForKey();
            break;
        }
        case 2: {
            int id;
            std::cout << "Vvedit ID pidviddilu: ";
            std::cin >> id;
            manager.removeDepartment(id);
            waitForKey();
            break;
        }
        case 3: {
            int id;
            std::string postal, specialist;
            std::cout << "Vvedit ID pidviddilu: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Vvedit novyj poshtovyi indeks: ";
            std::getline(std::cin, postal);
            std::cout << "Vvedit nove PIB fakhivtsia: ";
            std::getline(std::cin, specialist);
            manager.editDepartment(id, postal, specialist);
            waitForKey();
            break;
        }
        case 4:
            manager.printAllDepartments();
            waitForKey();
            break;
        case 5:
            return;
        }
    } while (choice != 5);
}

void Menu::handleFamilyMenu() {
    int choice;
    do {
        printFamilyMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string name, addr;
            int children, cat, deptId;

            manager.printAllDepartments();
            std::cout << "\nVvedit ID pidviddilu: ";
            std::cin >> deptId;
            std::cin.ignore();

            std::cout << "Vvedit prizvyshche rodyny: ";
            std::getline(std::cin, name);
            std::cout << "Vvedit adresu: ";
            std::getline(std::cin, addr);
            std::cout << "Vvedit kilkist ditey: ";
            std::cin >> children;

            std::cout << "\nVyberit katehoriiu dopomohy:" << std::endl;
            std::cout << "1. Bahatoditna" << std::endl;
            std::cout << "2. Chornobylska" << std::endl;
            std::cout << "3. Invalidnist" << std::endl;
            std::cout << "4. Malozabezpechena" << std::endl;
            std::cout << "5. Odynoka maty" << std::endl;
            std::cout << "Vash vybir: ";
            std::cin >> cat;

            manager.addFamily(name, addr, children, static_cast<HelpCategory>(cat), deptId);
            waitForKey();
            break;
        }
        case 2: {
            int id;
            std::cout << "Vvedit ID sim'yi: ";
            std::cin >> id;
            manager.removeFamily(id);
            waitForKey();
            break;
        }
        case 3: {
            int id, children, cat;
            std::cout << "Vvedit ID sim'yi: ";
            std::cin >> id;
            std::cout << "Vvedit novu kilkist ditey: ";
            std::cin >> children;
            std::cout << "Vyberit novu katehoriiu (1-5): ";
            std::cin >> cat;
            manager.editFamily(id, children, static_cast<HelpCategory>(cat));
            waitForKey();
            break;
        }
        case 4: {
            int deptId;
            std::cout << "Vvedit ID pidviddilu: ";
            std::cin >> deptId;
            manager.printFamiliesByDepartment(deptId);
            waitForKey();
            break;
        }
        case 5:
            manager.printAllFamilies();
            waitForKey();
            break;
        case 6:
            return;
        }
    } while (choice != 6);
}

void Menu::handleSearchMenu() {
    int choice;
    do {
        printSearchMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string name;
            std::cout << "Vvedit prizvyshche dlia poshuku: ";
            std::getline(std::cin, name);
            manager.searchFamiliesByName(name);
            waitForKey();
            break;
        }
        case 2: {
            int cat;
            std::cout << "Vyberit katehoriiu dlia poshuku (1-5): ";
            std::cin >> cat;
            manager.searchFamiliesByCategory(static_cast<HelpCategory>(cat));
            waitForKey();
            break;
        }
        case 3:
            return;
        }
    } while (choice != 3);
}

void Menu::handleSortMenu() {
    int choice;
    do {
        printSortMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            manager.sortFamiliesByName();
            manager.printAllFamilies();
            waitForKey();
            break;
        case 2:
            manager.sortFamiliesByChildren();
            manager.printAllFamilies();
            waitForKey();
            break;
        case 3:
            manager.sortFamiliesByAllowance();
            manager.printAllFamilies();
            waitForKey();
            break;
        case 4:
            return;
        }
    } while (choice != 4);
}

void Menu::handleReports() {
    clearScreen();
    std::cout << "=== SHCHOMISIACHNYI ZVIT ===" << std::endl;
    std::cout << "===========================================" << std::endl;

    double total = manager.calculateTotalMonthlyAllowance();

    std::cout << "Zahalna kilkist pidviddiliv: "
        << manager.getDepartments().size() << std::endl;
    std::cout << "Zahalna kilkist simey: "
        << manager.getFamilies().size() << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Zahalna suma dopomohy do vyplaty: "
        << std::fixed << total << " grn." << std::endl;
    std::cout << "===========================================" << std::endl;

    waitForKey();
}

void Menu::run() {
    manager.loadFromFile("families.txt");

    int choice;
    do {
        printMainMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            handleDepartmentMenu();
            break;
        case 2:
            handleFamilyMenu();
            break;
        case 3:
            handleReports();
            break;
        case 4:
            handleSearchMenu();
            break;
        case 5:
            handleSortMenu();
            break;
        case 6:
            manager.saveToFile("families.txt");
            waitForKey();
            break;
        case 7:
            manager.loadFromFile("families.txt");
            waitForKey();
            break;
        case 8:
            std::cout << "Diakuiemo za vykorystannia prohramy!" << std::endl;
            break;
        default:
            std::cout << "Nevirnyi vybir. Sprobuiyte shche raz." << std::endl;
            waitForKey();
        }
    } while (choice != 8);
}