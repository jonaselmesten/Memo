//Jonas Elmesten
//joel1803@student.miun.se
//Projket - DT047G

#ifndef SMARTVECTOR_H
#define SMARTVECTOR_H

#include <vector>
#include <memory>
#include <string>


template <class T>
/**
 * @brief The SmartVector class
 * A generic class that saves added objects with smart pointers.
 * Basic add & delete operations.
 */
class SmartVector {

public:
    SmartVector(std::string name);

    void addObject(std::shared_ptr<T> object);

    void deleteObject(T* card);

    size_t size();

    std::string getName();

    auto begin();

    auto end();

private:

    std::vector<std::shared_ptr<T>> vector;

    std::string name;
};

template <class T>
auto SmartVector<T>::begin() {
    return vector.begin();
}

template <class T>
auto SmartVector<T>::end() {
    return vector.end();
}

template <class T>
SmartVector<T>::SmartVector(std::string name) :name(name) {}

template <class T>
void SmartVector<T>::addObject(std::shared_ptr<T> object) {
    vector.push_back(object);
}

template <class T>
void SmartVector<T>::deleteObject(T* object) {

    auto it = std::find_if(vector.begin(),
                           vector.end(),
                           [&](std::shared_ptr<T> delObj)
                           {return delObj.get() == object;});

    if(it != vector.end()) {
        vector.erase(it);
    }
}

template <class T>
size_t SmartVector<T>::size() {
    return vector.size();
}

template <class T>
std::string SmartVector<T>::getName() {
    return name;
}


#endif // SMARTVECTOR_H
