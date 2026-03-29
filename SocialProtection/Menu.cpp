#include "Menu.h"
#include <iostream>
#include <limits>
#include <iomanip>

// VYPAVLJAJEMO KONFLIKT Z MAKROSOM MAX Z WINDOWS
#ifdef max
#undef max
#endif

void Menu::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Menu::waitForKey() {
    std::cout << "\nNajmit' Enter dlja prodovzhennja...";
    // VYKORYSTOVUJEMO DODATKOVI DUZHKY DLJA OBMYNU MAKROSU MAX
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::cin.get();
}

void Menu::printMainMenu() {
    clearScreen();
    int shyryna = ConsoleUtils::getShyryna();
    int vidstup = ConsoleUtils::getVidstup(40);

    ConsoleUtils::pustyjRiadok(2);
    ConsoleUtils::kolor(14);
    ConsoleUtils::drukuLiniyuCentr(50, '=');
    ConsoleUtils::drukuCentr("SOTSIALNYJ ZAKHYST NASELENNJA");
    ConsoleUtils::drukuCentr("Informacijna systema obliku sim'ej");
    ConsoleUtils::drukuLiniyuCentr(50, '=');
    ConsoleUtils::skynutyKolor();

    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::kolor(15);

    std::cout << std::setw(vidstup) << "" << "1. Robota z pidviddilamy" << std::endl;
    std::cout << std::setw(vidstup) << "" << "2. Robota z sim'jamy" << std::endl;
    std::cout << std::setw(vidstup) << "" << "3. Formuvannja zvitiv" << std::endl;
    std::cout << std::setw(vidstup) << "" << "4. Poshuk danykh" << std::endl;
    std::cout << std::setw(vidstup) << "" << "5. Sortuvannja danykh" << std::endl;
    std::cout << std::setw(vidstup) << "" << "6. Zberehty dani u fajl" << std::endl;
    std::cout << std::setw(vidstup) << "" << "7. Zavantazhyty dani z fajlu" << std::endl;
    std::cout << std::setw(vidstup) << "" << "8. Statystyka" << std::endl;

    ConsoleUtils::kolor(12);
    std::cout << std::setw(vidstup) << "" << "9. Vyjty z programy" << std::endl;
    ConsoleUtils::skynutyKolor();

    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::drukuLiniyuCentr(50, '=');
    ConsoleUtils::drukuCentr("Vash vybir: ");
}

void Menu::printDepartmentMenu() {
    clearScreen();
    int vidstup = ConsoleUtils::getVidstup(35);

    ConsoleUtils::pustyjRiadok(2);
    ConsoleUtils::kolor(11);
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::drukuCentr("ROBOTA Z PIDVIDDILAMY");
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::skynutyKolor();
    ConsoleUtils::pustyjRiadok(1);

    std::cout << std::setw(vidstup) << "" << "1. Dodaty pidviddil" << std::endl;
    std::cout << std::setw(vidstup) << "" << "2. Vydalyty pidviddil" << std::endl;
    std::cout << std::setw(vidstup) << "" << "3. Redahuvaty pidviddil" << std::endl;
    std::cout << std::setw(vidstup) << "" << "4. Perehliadnuty vsi pidviddily" << std::endl;
    std::cout << std::setw(vidstup) << "" << "5. Povernutysja do holovnogo menu" << std::endl;

    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::drukuCentr("Vash vybir: ");
}

void Menu::printFamilyMenu() {
    clearScreen();
    int vidstup = ConsoleUtils::getVidstup(40);

    ConsoleUtils::pustyjRiadok(2);
    ConsoleUtils::kolor(11);
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::drukuCentr("ROBOTA Z SIM'JAMY");
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::skynutyKolor();
    ConsoleUtils::pustyjRiadok(1);

    std::cout << std::setw(vidstup) << "" << "1. Dodaty sim'ju" << std::endl;
    std::cout << std::setw(vidstup) << "" << "2. Vydalyty sim'ju" << std::endl;
    std::cout << std::setw(vidstup) << "" << "3. Redahuvaty sim'ju" << std::endl;
    std::cout << std::setw(vidstup) << "" << "4. Perehliadnuty sim'i za pidviddilom" << std::endl;
    std::cout << std::setw(vidstup) << "" << "5. Perehliadnuty vsi sim'i" << std::endl;
    std::cout << std::setw(vidstup) << "" << "6. Povernutysja do holovnogo menu" << std::endl;

    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::drukuCentr("Vash vybir: ");
}

void Menu::printSearchMenu() {
    clearScreen();
    int vidstup = ConsoleUtils::getVidstup(40);

    ConsoleUtils::pustyjRiadok(2);
    ConsoleUtils::kolor(11);
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::drukuCentr("POSHUK DANYKH");
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::skynutyKolor();
    ConsoleUtils::pustyjRiadok(1);

    std::cout << std::setw(vidstup) << "" << "1. Poshuk sim'ei za prizvyshchem" << std::endl;
    std::cout << std::setw(vidstup) << "" << "2. Poshuk sim'ei za katehorijeju" << std::endl;
    std::cout << std::setw(vidstup) << "" << "3. Povernutysja do holovnogo menu" << std::endl;

    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::drukuCentr("Vash vybir: ");
}

void Menu::printSortMenu() {
    clearScreen();
    int vidstup = ConsoleUtils::getVidstup(45);

    ConsoleUtils::pustyjRiadok(2);
    ConsoleUtils::kolor(11);
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::drukuCentr("SORTUVANNJA DANYKH");
    ConsoleUtils::drukuLiniyuCentr(40, '=');
    ConsoleUtils::skynutyKolor();
    ConsoleUtils::pustyjRiadok(1);

    std::cout << std::setw(vidstup) << "" << "1. Sortuvaty za prizvyshchem (A-Z)" << std::endl;
    std::cout << std::setw(vidstup) << "" << "2. Sortuvaty za kilkistju ditej (spadannja)" << std::endl;
    std::cout << std::setw(vidstup) << "" << "3. Sortuvaty za sumoju dopomohy (spadannja)" << std::endl;
    std::cout << std::setw(vidstup) << "" << "4. Povernutysja do holovnogo menu" << std::endl;

    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::drukuCentr("Vash vybir: ");
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
            ConsoleUtils::drukuCentr("Vvedit' poshtovyj indeks: ");
            std::getline(std::cin, postal);
            ConsoleUtils::drukuCentr("Vvedit' PIB fahivtsja: ");
            std::getline(std::cin, specialist);
            manager.addDepartment(postal, specialist);
            waitForKey();
            break;
        }
        case 2: {
            int id;
            ConsoleUtils::drukuCentr("Vvedit' ID pidviddilu dlja vydalennja: ");
            std::cin >> id;
            std::cin.ignore();
            manager.removeDepartment(id);
            waitForKey();
            break;
        }
        case 3: {
            int id;
            std::string postal, specialist;
            ConsoleUtils::drukuCentr("Vvedit' ID pidviddilu dlja redahuvannja: ");
            std::cin >> id;
            std::cin.ignore();
            ConsoleUtils::drukuCentr("Vvedit' novyj poshtovyj indeks: ");
            std::getline(std::cin, postal);
            ConsoleUtils::drukuCentr("Vvedit' novoje PIB fahivtsja: ");
            std::getline(std::cin, specialist);
            manager.editDepartment(id, postal, specialist);
            waitForKey();
            break;
        }
        case 4:
            manager.printAllDepartments();
            waitForKey();
            break;
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
            ConsoleUtils::drukuCentr("Vvedit' ID pidviddilu: ");
            std::cin >> deptId;
            std::cin.ignore();

            ConsoleUtils::drukuCentr("Vvedit' prizvyshche rodyny: ");
            std::getline(std::cin, name);
            ConsoleUtils::drukuCentr("Vvedit' adresu: ");
            std::getline(std::cin, addr);
            ConsoleUtils::drukuCentr("Vvedit' kilkist' ditej: ");
            std::cin >> children;

            ConsoleUtils::drukuCentr("Vybirite katehoriju:");
            ConsoleUtils::drukuCentr("1. Bagatoditna  2. Chornobilska  3. Invalidnist");
            ConsoleUtils::drukuCentr("4. Malozabezpechena  5. Odynoka maty");
            ConsoleUtils::drukuCentr("Vash vybir: ");
            std::cin >> cat;
            std::cin.ignore();

            manager.addFamily(name, addr, children, static_cast<HelpCategory>(cat), deptId);
            waitForKey();
            break;
        }
        case 2: {
            int id;
            ConsoleUtils::drukuCentr("Vvedit' ID sim'i dlja vydalennja: ");
            std::cin >> id;
            std::cin.ignore();
            manager.removeFamily(id);
            waitForKey();
            break;
        }
        case 3: {
            int id, children, cat;
            ConsoleUtils::drukuCentr("Vvedit' ID sim'i dlja redahuvannja: ");
            std::cin >> id;
            std::cin.ignore();
            ConsoleUtils::drukuCentr("Vvedit' novu kilkist' ditej: ");
            std::cin >> children;
            ConsoleUtils::drukuCentr("Vybirite novu katehoriju (1-5): ");
            std::cin >> cat;
            std::cin.ignore();
            manager.editFamily(id, children, static_cast<HelpCategory>(cat));
            waitForKey();
            break;
        }
        case 4: {
            int deptId;
            ConsoleUtils::drukuCentr("Vvedit' ID pidviddilu: ");
            std::cin >> deptId;
            std::cin.ignore();
            manager.printFamiliesByDepartment(deptId);
            waitForKey();
            break;
        }
        case 5:
            manager.printAllFamilies();
            waitForKey();
            break;
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
            ConsoleUtils::drukuCentr("Vvedit' prizvyshche dlja poshuku: ");
            std::getline(std::cin, name);
            manager.searchFamiliesByName(name);
            waitForKey();
            break;
        }
        case 2: {
            int cat;
            ConsoleUtils::drukuCentr("Vybirite katehoriju (1-5): ");
            std::cin >> cat;
            std::cin.ignore();
            manager.searchFamiliesByCategory(static_cast<HelpCategory>(cat));
            waitForKey();
            break;
        }
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
        }
    } while (choice != 4);
}

void Menu::handleReports() {
    manager.showStatistics();
    waitForKey();
}

void Menu::run() {
    manager.loadFromFile("dani.txt");

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
            manager.saveToFile("dani.txt");
            waitForKey();
            break;
        case 7:
            manager.loadFromFile("dani.txt");
            waitForKey();
            break;
        case 8:
            handleReports();
            break;
        case 9:
            ConsoleUtils::kolor(14);
            ConsoleUtils::drukuCentr("Djakujemo za vykorystannja programy!");
            ConsoleUtils::skynutyKolor();
            break;
        default:
            ConsoleUtils::kolor(12);
            ConsoleUtils::drukuCentr("Nevіrnyj vybir! Sprobujte znovu.");
            ConsoleUtils::skynutyKolor();
            waitForKey();
        }
    } while (choice != 9);
}