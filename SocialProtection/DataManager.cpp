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
    std::cout << "Pidviddil dodano z ID: " << newDept.id << std::endl;
}

bool DataManager::removeDepartment(int id) {
    for (int i = 0; i < families.size(); i++) {
        if (families.get(i).departmentId == id) {
            std::cout << "Nemozhlyvo vydalyty: v pidviddili ye sim'yi!" << std::endl;
            return false;
        }
    }

    for (int i = 0; i < departments.size(); i++) {
        if (departments.get(i).id == id) {
            departments.remove(i);
            std::cout << "Pidviddil vydaleno." << std::endl;
            return true;
        }
    }

    std::cout << "Pidviddil z ID " << id << " ne znajdeno." << std::endl;
    return false;
}

bool DataManager::editDepartment(int id, const std::string& newPostal, const std::string& newSpecialist) {
    for (int i = 0; i < departments.size(); i++) {
        if (departments.get(i).id == id) {
            departments.get(i).postalIndex = newPostal;
            departments.get(i).specialistName = newSpecialist;
            std::cout << "Pidviddil onovleno." << std::endl;
            return true;
        }
    }
    std::cout << "Pidviddil ne znajdeno." << std::endl;
    return false;
}

Department* DataManager::findDepartmentById(int id) {
    for (int i = 0; i < departments.size(); i++) {
        if (departments.get(i).id == id) {
            return &departments.get(i);
        }
    }
    return nullptr;
}

void DataManager::printAllDepartments() const {
    if (departments.size() == 0) {
        std::cout << "Spysok pidviddiliv porozhnij." << std::endl;
        return;
    }

    std::cout << "\n=== SPYSOK PIDVIDDILIV ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Posht. indeks"
        << "Fahivets" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (int i = 0; i < departments.size(); i++) {
        const auto& dept = departments.get(i);
        std::cout << std::left << std::setw(5) << dept.id
            << std::setw(15) << dept.postalIndex
            << dept.specialistName << std::endl;
    }
}

void DataManager::addFamily(const std::string& name, const std::string& addr,
    int children, HelpCategory cat, int deptId) {
    if (findDepartmentById(deptId) == nullptr) {
        std::cout << "Pomylka: pidviddil z ID " << deptId << " ne isnuye!" << std::endl;
        return;
    }

    Family newFamily(nextFamilyId++, name, addr, children, cat, deptId);
    families.add(newFamily);
    std::cout << "Sim'yu dodano z ID: " << newFamily.id << std::endl;
    std::cout << "Rozrakhovana dopomoga: " << newFamily.monthlyAllowance << " grn" << std::endl;
}

bool DataManager::removeFamily(int id) {
    for (int i = 0; i < families.size(); i++) {
        if (families.get(i).id == id) {
            families.remove(i);
            std::cout << "Sim'yu vydaleno." << std::endl;
            return true;
        }
    }
    std::cout << "Sim'yu z ID " << id << " ne znajdeno." << std::endl;
    return false;
}

bool DataManager::editFamily(int id, int newChildren, HelpCategory newCat) {
    for (int i = 0; i < families.size(); i++) {
        if (families.get(i).id == id) {
            families.get(i).childrenCount = newChildren;
            families.get(i).category = newCat;
            families.get(i).calculateAllowance();
            std::cout << "Sim'yu onovleno. Nova dopomoga: "
                << families.get(i).monthlyAllowance << " grn" << std::endl;
            return true;
        }
    }
    std::cout << "Sim'yu ne znajdeno." << std::endl;
    return false;
}

Family* DataManager::findFamilyById(int id) {
    for (int i = 0; i < families.size(); i++) {
        if (families.get(i).id == id) {
            return &families.get(i);
        }
    }
    return nullptr;
}

void DataManager::printFamiliesByDepartment(int deptId) const {
    Department* dept = const_cast<DataManager*>(this)->findDepartmentById(deptId);
    if (!dept) {
        std::cout << "Pidviddil ne znajdeno." << std::endl;
        return;
    }

    bool found = false;
    std::cout << "\n=== SIM'YI PIDVIDDILU №" << deptId
        << " (Fahivets: " << dept->specialistName << ") ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Rodyna"
        << std::setw(20) << "Adresa"
        << std::setw(8) << "Ditey"
        << std::setw(15) << "Kategoriya"
        << "Suma, grn" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (int i = 0; i < families.size(); i++) {
        const auto& fam = families.get(i);
        if (fam.departmentId == deptId) {
            found = true;
            std::string categoryStr;
            switch (fam.category) {
            case BAGATODITNA: categoryStr = "Bagatoditna"; break;
            case CHORNOBILSKA: categoryStr = "Chornobylska"; break;
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
        std::cout << "V tsomu pidviddili nemaie zareiestrovanykh simey." << std::endl;
    }
}

void DataManager::printAllFamilies() const {
    if (families.size() == 0) {
        std::cout << "Spysok simey porozhnij." << std::endl;
        return;
    }

    std::cout << "\n=== VSI SIM'YI ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(15) << "Rodyna"
        << std::setw(20) << "Adresa"
        << std::setw(8) << "Ditey"
        << std::setw(5) << "Vid."
        << "Suma, grn" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (int i = 0; i < families.size(); i++) {
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

    std::cout << "\n=== REZULTATY POSHUKU: \"" << name << "\" ===" << std::endl;

    for (int i = 0; i < families.size(); i++) {
        const auto& fam = families.get(i);
        std::string famName = fam.familyName;
        for (char& c : famName) c = tolower(c);

        if (famName.find(searchName) != std::string::npos) {
            found = true;
            std::cout << "ID: " << fam.id
                << ", Rodyna: " << fam.familyName
                << ", Adresa: " << fam.address
                << ", Ditey: " << fam.childrenCount
                << ", Dopomoga: " << fam.monthlyAllowance << " grn" << std::endl;
        }
    }

    if (!found) {
        std::cout << "Nichogo ne znajdeno." << std::endl;
    }
}

void DataManager::searchFamiliesByCategory(HelpCategory cat) const {
    bool found = false;

    std::cout << "\n=== SIM'YI ZA KATEGORIYEYU ===" << std::endl;

    for (int i = 0; i < families.size(); i++) {
        const auto& fam = families.get(i);
        if (fam.category == cat) {
            found = true;
            std::cout << "ID: " << fam.id
                << ", Rodyna: " << fam.familyName
                << ", Ditey: " << fam.childrenCount
                << ", Dopomoga: " << fam.monthlyAllowance << " grn" << std::endl;
        }
    }

    if (!found) {
        std::cout << "Simey z tsiieiu katehoriiu ne znajdeno." << std::endl;
    }
}

void DataManager::sortFamiliesByName() {
    families.sort(compareFamiliesByName);
    std::cout << "Sim'yi vidsortovano za prizvyshchem." << std::endl;
}

void DataManager::sortFamiliesByChildren() {
    families.sort(compareFamiliesByChildren);
    std::cout << "Sim'yi vidsortovano za kilkistyu ditey (spadannya)." << std::endl;
}

void DataManager::sortFamiliesByAllowance() {
    families.sort(compareFamiliesByAllowance);
    std::cout << "Sim'yi vidsortovano za sumoyu dopomogy (spadannya)." << std::endl;
}

double DataManager::calculateTotalMonthlyAllowance() const {
    double total = 0.0;
    for (int i = 0; i < families.size(); i++) {
        total += families.get(i).monthlyAllowance;
    }
    return total;
}

bool DataManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Pomylka vidkryttia failu dlia zapysu!" << std::endl;
        return false;
    }

    file << departments.size() << std::endl;
    for (int i = 0; i < departments.size(); i++) {
        const auto& dept = departments.get(i);
        file << dept.id << std::endl;
        file << dept.postalIndex << std::endl;
        file << dept.specialistName << std::endl;
    }

    file << families.size() << std::endl;
    for (int i = 0; i < families.size(); i++) {
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
    std::cout << "Dani uspishno zberezheno u fail " << filename << std::endl;
    return true;
}

bool DataManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Fail ne znajdeno. Bude stvoreno novyj." << std::endl;
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
    std::cout << "Dani uspishno zavantazheno z failu " << filename << std::endl;
    return true;
}