#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>

struct Department {
    int id;
    std::string postalIndex;
    std::string specialistName;

    Department() : id(0) {}

    Department(int _id, const std::string& _postal, const std::string& _name)
        : id(_id), postalIndex(_postal), specialistName(_name) {
    }
};

#endif