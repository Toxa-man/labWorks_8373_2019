#include <iostream>

using namespace std;

using T = int;

class Vector {
public:
    Vector(unsigned sizeIn);
    ~Vector();
    Vector(unsigned size, const T &val);
    Vector(const Vector &vec);
    unsigned Size();
    void resize(unsigned sizeIn);
    bool insert(unsigned pos, const T &val);
    void push_back(const T &val);
    bool contains(const T &val);
    T& operator [] (unsigned index);
    int find(const T &val);
    T* getData();
    Vector& operator = (const Vector& vec);

private:
    T *data;
    unsigned size;
};

Vector::Vector(unsigned sizeIn) {
    size = sizeIn;
    data = new T[size];
    for (unsigned i = 0; i < size; i++) {
        data[i] = 0;
    }
}
Vector::~Vector() {
    size = 0;
    delete[] data;
}
Vector::Vector(unsigned sizeIn, const T &val) {
    size = sizeIn;
    data = new T[size];
    for (unsigned i = 0; i < size; i++) {
        data[i] = val;
    }
}
Vector::Vector(const Vector &vec) {
    size = vec.size;
    data = new T[size];
    memcpy(data, vec.data, sizeof(T) * size);
}
unsigned Vector::Size() {
    return size;
}
void Vector::resize(unsigned sizeIn) {
    T *dataNew;
    if (sizeIn > size) {
        dataNew = new T[sizeIn];
        memcpy(dataNew, data, (sizeof(T) * size));
        delete[] (data);
        for (unsigned i = size; i < sizeIn; i++) {
            dataNew[i] = 0;
        }
        data = dataNew;
        size = sizeIn;
    } else {
        dataNew = new T[size];
        memcpy(dataNew, data, (sizeof(T) * size));
        delete[] (data);
        data = dataNew;
        size = sizeIn;
    }
}
bool Vector::insert(unsigned pos, const T &val) {
    if ((pos < size) && (pos >= 0)) {
        resize(Size() + 1);
        for (unsigned i = (Size() - 1); i > pos; i--) {
            data[i] = data[i - 1];
        }
        data[pos] = val;
        return true;
    } else {
        return false;
    }
}
void Vector::push_back(const T &val) {
    resize(Size() + 1);
    data[size - 1] = val;
}
bool Vector::contains(const T &val) {
    for (unsigned i = 0; i < size; i++) {
        if (data[i] == val) {
            return true;
        }
    }
    return false;
}
T& Vector::operator [](unsigned index) {
    return data[index];
}
int Vector::find(const T &val) {
    for (unsigned i = 0; i < size; i++) {
        if (data[i] == val) {
            return i;
        }
    }
    return -1;
}
T* Vector::getData() {
    return data;
}
Vector& Vector::operator = (const Vector& vec) {
    if (this != &vec) {
        size = vec.size;
        delete[] data;
        data = new T[size];
        memcpy(data, vec.data, sizeof(T) * size);
    }
    return *this;
}
int main() {
    Vector vec1(2);
    Vector vec2(4);
    vec1.push_back(3);
    vec1.push_back(-5);
    vec1.resize(6);
    cout << "Size of vec1(6): " << vec1.Size() << endl;
    vec2.push_back(11);
    vec2.push_back(-18);
    vec1 = vec2;
    for (unsigned i = 0; i < vec1.Size(); i++) {
        cout << vec1[i] << " ; ";
    }
    cout << endl;
    vec1.insert(0, 23);
    cout << "Position (0): " << vec1.find(23) << endl;
    cout << "Size of vec1 (7): " << vec1.Size() << endl;
    vec2.resize(2);
    vec2.push_back(890);
    cout << "Is 890 in vec2? (1): " << vec2.contains(763) << endl;
    cout << "Is 80 in vec2? (0): " << vec2.contains(70) << endl;
    cout << "Size of vec2 (3): " << vec2.Size() << endl;
    cout << "Get Data: " << vec2.getData() << endl;
    Vector vec3(4, -9);
    for (unsigned i = 0; i < vec3.Size(); i++) {
        cout << vec3[i] << " ; ";
    }
    return 0;
}
