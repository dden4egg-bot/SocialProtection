#include "DataManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>

DataManager::DataManager() : nextDeptId(1), nextFamilyId(1) {}

bool DataManager::compareDepartmentsById(const Department& a, const Department& b) {
    return a.id < b.id;
}

bool DataManager::compareFamiliesByName(const Family& a, const Family& b) {
    return a.familyName < b.familyName;
}

bool DataManager::compareFamiliesByChildren(const Family& a, const Family& b) {
    return a.childrenCount > b.childrenCount;
}

bool DataManager::compareFamiliesByAllowance(const Family& a, const Family& b) {
    return a.monthlyAllowance > b.monthlyAllowance;
}

void DataManager::addDepartment(const std::string& postal, const std::string& specialist) {
    Department newDept(nextDeptId++, postal, specialist);
    departments.add(newDept);
    ConsoleUtils::kolor(10);
    std::cout << "\nPidviddil dodano z ID: " << newDept.id << std::endl;
    ConsoleUtils::skynutyKolor();
}

bool DataManager::removeDepartment(int id) {
    // VYPAVLJAJEMO size_t V int
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        if (families.get(i).departmentId == id) {
            ConsoleUtils::kolor(12);
            std::cout << "\nNemozhlyvo vydalyty: v pidviddili ie sim'i!" << std::endl;
            ConsoleUtils::skynutyKolor();
            return false;
        }
    }

    for (int i = 0; i < static_cast<int>(departments.size()); i++) {
        if (departments.get(i).id == id) {
            departments.remove(i);
            ConsoleUtils::kolor(10);
            std::cout << "\nPidviddil vydaleno." << std::endl;
            ConsoleUtils::skynutyKolor();
            return true;
        }
    }

    ConsoleUtils::kolor(12);
    std::cout << "\nPidviddil z ID " << id << " ne znajdeno." << std::endl;
    ConsoleUtils::skynutyKolor();
    return false;
}

bool DataManager::editDepartment(int id, const std::string& newPostal, const std::string& newSpecialist) {
    for (int i = 0; i < static_cast<int>(departments.size()); i++) {
        if (departments.get(i).id == id) {
            departments.get(i).postalIndex = newPostal;
            departments.get(i).specialistName = newSpecialist;
            ConsoleUtils::kolor(10);
            std::cout << "\nPidviddil onovleno." << std::endl;
            ConsoleUtils::skynutyKolor();
            return true;
        }
    }
    ConsoleUtils::kolor(12);
    std::cout << "\nPidviddil ne znajdeno." << std::endl;
    ConsoleUtils::skynutyKolor();
    return false;
}

Department* DataManager::findDepartmentById(int id) {
    for (int i = 0; i < static_cast<int>(departments.size()); i++) {
        if (departments.get(i).id == id) {
            return &departments.get(i);
        }
    }
    return nullptr;
}

void DataManager::printAllDepartments() const {
    if (departments.size() == 0) {
        ConsoleUtils::kolor(14);
        std::cout << "\nSpysok pidviddiliv porozhnij." << std::endl;
        ConsoleUtils::skynutyKolor();
        return;
    }

    ConsoleUtils::kolor(11);
    std::cout << "\n=== SPYSOK PIDVIDDILIV ===" << std::endl;
    ConsoleUtils::skynutyKolor();
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Posht. indeks"
        << "Fahivets" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 0; i < static_cast<int>(departments.size()); i++) {
        const auto& dept = departments.get(i);
        std::cout << std::left << std::setw(5) << dept.id
            << std::setw(15) << dept.postalIndex
            << dept.specialistName << std::endl;
    }
}

void DataManager::addFamily(const std::string& name, const std::string& addr,
    int children, HelpCategory cat, int deptId) {
    if (findDepartmentById(deptId) == nullptr) {
        ConsoleUtils::kolor(12);
        std::cout << "\nPomylka: pidviddil z ID " << deptId << " ne isnuje!" << std::endl;
        ConsoleUtils::skynutyKolor();
        return;
    }

    Family newFamily(nextFamilyId++, name, addr, children, cat, deptId);
    families.add(newFamily);
    ConsoleUtils::kolor(10);
    std::cout << "\nSim'ju dodano z ID: " << newFamily.id << std::endl;
    std::cout << "Rozrakhovana dopomoga: " << newFamily.monthlyAllowance << " grn" << std::endl;
    ConsoleUtils::skynutyKolor();
}

bool DataManager::removeFamily(int id) {
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        if (families.get(i).id == id) {
            families.remove(i);
            ConsoleUtils::kolor(10);
            std::cout << "\nSim'ju vydaleno." << std::endl;
            ConsoleUtils::skynutyKolor();
            return true;
        }
    }
    ConsoleUtils::kolor(12);
    std::cout << "\nSim'ju z ID " << id << " ne znajdeno." << std::endl;
    ConsoleUtils::skynutyKolor();
    return false;
}

bool DataManager::editFamily(int id, int newChildren, HelpCategory newCat) {
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        if (families.get(i).id == id) {
            families.get(i).childrenCount = newChildren;
            families.get(i).category = newCat;
            families.get(i).calculateAllowance();
            ConsoleUtils::kolor(10);
            std::cout << "\nSim'ju onovleno. Nova dopomoga: "
                << families.get(i).monthlyAllowance << " grn" << std::endl;
            ConsoleUtils::skynutyKolor();
            return true;
        }
    }
    ConsoleUtils::kolor(12);
    std::cout << "\nSim'ju ne znajdeno." << std::endl;
    ConsoleUtils::skynutyKolor();
    return false;
}

Family* DataManager::findFamilyById(int id) {
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        if (families.get(i).id == id) {
            return &families.get(i);
        }
    }
    return nullptr;
}

void DataManager::printFamiliesByDepartment(int deptId) const {
    Department* dept = const_cast<DataManager*>(this)->findDepartmentById(deptId);
    if (!dept) {
        ConsoleUtils::kolor(12);
        std::cout << "\nPidviddil ne znajdeno." << std::endl;
        ConsoleUtils::skynutyKolor();
        return;
    }

    bool found = false;
    ConsoleUtils::kolor(11);
    std::cout << "\n=== SIM'I PIDVIDDILU No" << deptId
        << " (Fahivets: " << dept->specialistName << ") ===" << std::endl;
    ConsoleUtils::skynutyKolor();

    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Rodyna"
        << std::setw(20) << "Adresa"
        << std::setw(8) << "Ditej"
        << std::setw(15) << "Kategorija"
        << "Suma, grn" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        const auto& fam = families.get(i);
        if (fam.departmentId == deptId) {
            found = true;
            std::string categoryStr;
            switch (fam.category) {
            case BAGATODITNA: categoryStr = "Bagatoditna"; break;
            case CHORNOBILSKA: categoryStr = "Chornobilska"; break;
            case INVALIDNIST: categoryStr = "Invalidnist"; break;
            case MALOZABEZPECHENA: categoryStr = "Malozabezpechena"; break;
            case ODYNOKA_MATY: categoryStr = "Odynoka maty"; break;
            }

            std::cout << std::left << std::setw(5) << fam.id
                << std::setw(15) << fam.familyName
                << std::setw(20) << fam.address
                << std::setw(8) << fam.childrenCount
                << std::setw(15) << categoryStr
                << std::fixed << std::setprecision(2) << fam.monthlyAllowance << std::endl;
        }
    }

    if (!found) {
        ConsoleUtils::kolor(14);
        std::cout << "V c'omu pidviddili nemaje zarejestrovanykh sim'ej." << std::endl;
        ConsoleUtils::skynutyKolor();
    }
}

void DataManager::printAllFamilies() const {
    if (families.size() == 0) {
        ConsoleUtils::kolor(14);
        std::cout << "\nSpysok sim'ej porozhnij." << std::endl;
        ConsoleUtils::skynutyKolor();
        return;
    }

    ConsoleUtils::kolor(11);
    std::cout << "\n=== VSI SIM'I ===" << std::endl;
    ConsoleUtils::skynutyKolor();

    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Rodyna"
        << std::setw(20) << "Adresa"
        << std::setw(8) << "Ditej"
        << std::setw(5) << "Vid."
        << "Suma, grn" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        const auto& fam = families.get(i);
        std::cout << std::left << std::setw(5) << fam.id
            << std::setw(15) << fam.familyName
            << std::setw(20) << fam.address
            << std::setw(8) << fam.childrenCount
            << std::setw(5) << fam.departmentId
            << std::fixed << std::setprecision(2) << fam.monthlyAllowance << std::endl;
    }
}

void DataManager::searchFamiliesByName(const std::string& name) const {
    bool found = false;
    std::string searchName = name;
    for (char& c : searchName) c = tolower(c);

    ConsoleUtils::kolor(11);
    std::cout << "\n=== REZULTATY POSHUKU: \"" << name << "\" ===" << std::endl;
    ConsoleUtils::skynutyKolor();

    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        const auto& fam = families.get(i);
        std::string famName = fam.familyName;
        for (char& c : famName) c = tolower(c);

        if (famName.find(searchName) != std::string::npos) {
            found = true;
            std::cout << "ID: " << fam.id
                << ", Rodyna: " << fam.familyName
                << ", Adresa: " << fam.address
                << ", Ditej: " << fam.childrenCount
                << ", Dopomoga: " << fam.monthlyAllowance << " grn" << std::endl;
        }
    }

    if (!found) {
        ConsoleUtils::kolor(14);
        std::cout << "Nichogo ne znajdeno." << std::endl;
        ConsoleUtils::skynutyKolor();
    }
}

void DataManager::searchFamiliesByCategory(HelpCategory cat) const {
    bool found = false;

    ConsoleUtils::kolor(11);
    std::cout << "\n=== SIM'I ZA KATEGORIJEJU ===" << std::endl;
    ConsoleUtils::skynutyKolor();

    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        const auto& fam = families.get(i);
        if (fam.category == cat) {
            found = true;
            std::cout << "ID: " << fam.id
                << ", Rodyna: " << fam.familyName
                << ", Ditej: " << fam.childrenCount
                << ", Dopomoga: " << fam.monthlyAllowance << " grn" << std::endl;
        }
    }

    if (!found) {
        ConsoleUtils::kolor(14);
        std::cout << "Sim'ej z cijeju kategorijeju ne znajdeno." << std::endl;
        ConsoleUtils::skynutyKolor();
    }
}

void DataManager::sortFamiliesByName() {
    families.sort(compareFamiliesByName);
    ConsoleUtils::kolor(10);
    std::cout << "\nSim'i vidsortovano za prizvyshchem." << std::endl;
    ConsoleUtils::skynutyKolor();
}

void DataManager::sortFamiliesByChildren() {
    families.sort(compareFamiliesByChildren);
    ConsoleUtils::kolor(10);
    std::cout << "\nSim'i vidsortovano za kilkistju ditej (spadannja)." << std::endl;
    ConsoleUtils::skynutyKolor();
}

void DataManager::sortFamiliesByAllowance() {
    families.sort(compareFamiliesByAllowance);
    ConsoleUtils::kolor(10);
    std::cout << "\nSim'i vidsortovano za sumoju dopomohy (spadannja)." << std::endl;
    ConsoleUtils::skynutyKolor();
}

double DataManager::calculateTotalMonthlyAllowance() const {
    double total = 0.0;
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        total += families.get(i).monthlyAllowance;
    }
    return total;
}

void DataManager::showStatistics() const {
    ConsoleUtils::pustyjRiadok(1);
    ConsoleUtils::drukuLiniyuCentr(50, '=');
    ConsoleUtils::drukuCentr("STATYSTYKA SYSTEMY");
    ConsoleUtils::drukuLiniyuCentr(50, '=');

    std::cout << "\nZahal'na kil'kist' pidviddiliv: " << departments.size() << std::endl;
    std::cout << "Zahal'na kil'kist' sim'ej: " << families.size() << std::endl;

    double total = calculateTotalMonthlyAllowance();
    std::cout << "Zahal'na suma vyplat: " << std::fixed << std::setprecision(2)
        << total << " grn" << std::endl;

    if (families.size() > 0) {
        std::cout << "Serednja suma na sim'ju: " << (total / families.size()) << " grn" << std::endl;
    }

    // Rozpodil za katehorijamy
    int bagatoditni = 0, chornobilci = 0, invalidy = 0, malozabezpecheni = 0, odynokiMamy = 0;
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        switch (families.get(i).category) {
        case BAGATODITNA: bagatoditni++; break;
        case CHORNOBILSKA: chornobilci++; break;
        case INVALIDNIST: invalidy++; break;
        case MALOZABEZPECHENA: malozabezpecheni++; break;
        case ODYNOKA_MATY: odynokiMamy++; break;
        }
    }

    ConsoleUtils::drukuLiniyuCentr(50, '-');
    ConsoleUtils::drukuCentr("ROZPODIL ZA KATEGORIJAMY:");
    std::cout << "  Bagatoditni sim'i: " << bagatoditni << std::endl;
    std::cout << "  Chornobil'ci: " << chornobilci << std::endl;
    std::cout << "  Invalidy: " << invalidy << std::endl;
    std::cout << "  Malozabezpecheni: " << malozabezpecheni << std::endl;
    std::cout << "  Odynoki maty: " << odynokiMamy << std::endl;
    ConsoleUtils::drukuLiniyuCentr(50, '=');
}

bool DataManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        ConsoleUtils::kolor(12);
        std::cout << "\nPomylka vidkryttja fajlu dlja zapisu!" << std::endl;
        ConsoleUtils::skynutyKolor();
        return false;
    }

    file << departments.size() << std::endl;
    for (int i = 0; i < static_cast<int>(departments.size()); i++) {
        const auto& dept = departments.get(i);
        file << dept.id << std::endl;
        file << dept.postalIndex << std::endl;
        file << dept.specialistName << std::endl;
    }

    file << families.size() << std::endl;
    for (int i = 0; i < static_cast<int>(families.size()); i++) {
        const auto& fam = families.get(i);
        file << fam.id << std::endl;
        file << fam.familyName << std::endl;
        file << fam.address << std::endl;
        file << fam.childrenCount << std::endl;
        file << static_cast<int>(fam.category) << std::endl;
        file << fam.departmentId << std::endl;
        file << fam.monthlyAllowance << std::endl;
    }

    file << nextDeptId << std::endl;
    file << nextFamilyId << std::endl;

    file.close();
    ConsoleUtils::kolor(10);
    std::cout << "\nDani uspishno zberezheno u fajl " << filename << std::endl;
    ConsoleUtils::skynutyKolor();
    return true;
}

bool DataManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        ConsoleUtils::kolor(14);
        std::cout << "\nFajl ne znajdeno. Bude stvoreno novyj pry pershomu zberezhenni." << std::endl;
        ConsoleUtils::skynutyKolor();
        return false;
    }

    departments.clear();
    families.clear();

    int deptCount;
    file >> deptCount;
    file.ignore();

    for (int i = 0; i < deptCount; i++) {
        Department dept;
        file >> dept.id;
        file.ignore();
        std::getline(file, dept.postalIndex);
        std::getline(file, dept.specialistName);
        departments.add(dept);
    }

    int familyCount;
    file >> familyCount;
    file.ignore();

    for (int i = 0; i < familyCount; i++) {
        Family fam;
        file >> fam.id;
        file.ignore();
        std::getline(file, fam.familyName);
        std::getline(file, fam.address);
        file >> fam.childrenCount;
        int cat;
        file >> cat;
        fam.category = static_cast<HelpCategory>(cat);
        file >> fam.departmentId;
        file >> fam.monthlyAllowance;
        file.ignore();
        families.add(fam);
    }

    file >> nextDeptId;
    file >> nextFamilyId;

    file.close();
    ConsoleUtils::kolor(10);
    std::cout << "\nDani uspishno zavantazheno z fajlu " << filename << std::endl;
    ConsoleUtils::skynutyKolor();
    return true;
}