#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "ArrayTemplate.h"
#include "Department.h"
#include "Family.h"
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

    void addDepartment(const std::string& postal, const std::string& specialist);
    bool removeDepartment(int id);
    bool editDepartment(int id, const std::string& newPostal, const std::string& newSpecialist);
    Department* findDepartmentById(int id);
    void printAllDepartments() const;

    void addFamily(const std::string& name, const std::string& addr,
        int children, HelpCategory cat, int deptId);
    bool removeFamily(int id);
    bool editFamily(int id, int newChildren, HelpCategory newCat);
    Family* findFamilyById(int id);
    void printFamiliesByDepartment(int deptId) const;
    void printAllFamilies() const;

    void searchFamiliesByName(const std::string& name) const;
    void searchFamiliesByCategory(HelpCategory cat) const;

    void sortFamiliesByName();
    void sortFamiliesByChildren();
    void sortFamiliesByAllowance();

    double calculateTotalMonthlyAllowance() const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    const ArrayTemplate<Department>& getDepartments() const { return departments; }
    const ArrayTemplate<Family>& getFamilies() const { return families; }
};

#endif