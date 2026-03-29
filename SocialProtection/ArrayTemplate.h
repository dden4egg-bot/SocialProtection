#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <iostream>
#include <stdexcept>

template<typename T>
class ArrayTemplate {
private:
    T* data;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    ArrayTemplate() : capacity(10), count(0) {
        data = new T[capacity];
    }

    // Konstruktor kopijuvannja
    ArrayTemplate(const ArrayTemplate& other)
        : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    // Operator prisvoiennja
    ArrayTemplate& operator=(const ArrayTemplate& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            count = other.count;
            data = new T[capacity];
            for (int i = 0; i < count; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~ArrayTemplate() {
        delete[] data;
    }

    void add(const T& item) {
        if (count >= capacity) {
            resize();
        }
        data[count++] = item;
    }

    void remove(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index poza mezhamy");
        }
        for (int i = index; i < count - 1; i++) {
            data[i] = data[i + 1];
        }
        count--;
    }

    T& get(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index poza mezhamy");
        }
        return data[index];
    }

    const T& get(int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index poza mezhamy");
        }
        return data[index];
    }

    int size() const {
        return count;
    }

    void clear() {
        count = 0;
    }

    void sort(bool (*compare)(const T&, const T&)) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (compare(data[j + 1], data[j])) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
};

#endif