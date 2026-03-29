#ifndef FAMILY_H
#define FAMILY_H

#include <string>

enum HelpCategory {
    BAGATODITNA = 1,
    CHORNOBILSKA,
    INVALIDNIST,
    MALOZABEZPECHENA,
    ODYNOKA_MATY
};

const double CATEGORY_RATES[] = {
    0.0,        // Zaglushka
    2500.0,     // Bahatoditna
    3000.0,     // Chornobilska
    3500.0,     // Invalidnist
    2000.0,     // Malozabezpechena
    2800.0      // Odynoka maty
};

struct Family {
    int id;
    std::string familyName;
    std::string address;
    int childrenCount;
    HelpCategory category;
    int departmentId;
    double monthlyAllowance;

    Family() : id(0), childrenCount(0), category(BAGATODITNA),
        departmentId(0), monthlyAllowance(0.0) {
    }

    Family(int _id, const std::string& _name, const std::string& _addr,
        int _children, HelpCategory _cat, int _deptId)
        : id(_id), familyName(_name), address(_addr),
        childrenCount(_children), category(_cat), departmentId(_deptId) {
        calculateAllowance();
    }

    void calculateAllowance() {
        monthlyAllowance = childrenCount * CATEGORY_RATES[category];
    }
};

#endif