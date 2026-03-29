#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "ArrayTemplate.h"
#include "Department.h"
#include "Family.h"
#include "ConsoleUtils.h"
#include <string>

class DataManager {
private:
    ArrayTemplate<Department> departments;
    ArrayTemplate<Family> families;
    int nextDeptId;
    int nextFamilyId;

    static bool compareDepartmentsById(const Department& a, const Department& b);
    static bool compareFamiliesByName(const Family& a, const Family& b);
    static bool compareFamiliesByChildren(const Family& a, const Family& b);
    static bool compareFamiliesByAllowance(const Family& a, const Family& b);

public:
    DataManager();

    // Robota z pidviddilamy
    void addDepartment(const std::string& postal, const std::string& specialist);
    bool removeDepartment(int id);
    bool editDepartment(int id, const std::string& newPostal, const std::string& newSpecialist);
    Department* findDepartmentById(int id);
    void printAllDepartments() const;

    // Robota z simjamy
    void addFamily(const std::string& name, const std::string& addr,
        int children, HelpCategory cat, int deptId);
    bool removeFamily(int id);
    bool editFamily(int id, int newChildren, HelpCategory newCat);
    Family* findFamilyById(int id);
    void printFamiliesByDepartment(int deptId) const;
    void printAllFamilies() const;

    // Poshuk
    void searchFamiliesByName(const std::string& name) const;
    void searchFamiliesByCategory(HelpCategory cat) const;

    // Sortuvannja
    void sortFamiliesByName();
    void sortFamiliesByChildren();
    void sortFamiliesByAllowance();

    // Zvit
    double calculateTotalMonthlyAllowance() const;
    void showStatistics() const;  // DODANO

    // Robota z fajlamy
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Gettery
    const ArrayTemplate<Department>& getDepartments() const { return departments; }
    const ArrayTemplate<Family>& getFamilies() const { return families; }
    int getNextDeptId() const { return nextDeptId; }
    int getNextFamilyId() const { return nextFamilyId; }
};

#endif