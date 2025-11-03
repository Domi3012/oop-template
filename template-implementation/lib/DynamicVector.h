#ifndef DVECTOR_H
#define DVECTOR_H

#include <iostream>
#include <expected>

using std::expected, std::unexpected;

template <class T>
class DynamicVector {
private:
    int _size;
    int _capacity;
    T* _data = NULL;
    const int INIT_CAPACITY = 1;
    
    void resize() {
        _capacity = (_capacity == 0 ? 1 : _capacity*2);
        T* newData = new T[_capacity];

        // Co mot cach chuyen luon 1 block memory (C style memcpy) nhung cach do nguy hiem vi
        // no copy raw bit -> Shallow copy (nguy hiem voi nhung truong hop object co con tro tro den data thuc su tren heap)
        // -> Ket luan: Su dung for loop copy tu tu
        for (int i = 0; i < _size; i++) {
            newData[i] = _data[i];
        }

        delete[] _data;
        _data = newData;
    }
public:
    DynamicVector() : DynamicVector(INIT_CAPACITY) {}

    DynamicVector(const int& size) {
        _size = 0;
        _capacity = size;
        _data = new T[_capacity];
    }

    DynamicVector(const int& size, const T& value) : DynamicVector(size) {
        for (int i = 0; i < size; i++) {
            _data[i] = value;
        }
        _size = size;
    }

    ~DynamicVector() {
        delete[] _data;
    }
    
    int size() const { return this->_size; }

    expected<T, std::string> operator[](int index) const {
        if ( (index < 0) 
            || (_size <= index)
        ) {
            return unexpected("Index out of range");
        }
        return _data[index];
    }

    void push_back(const T& item) {
        if (_size == _capacity) resize();
        
        _data[_size] = item;
        _size++;

    }

    void print() const {
        for (int i = 0; i < _size; i++) {
            std::cout << _data[i] << ' ';
        }
    }
};

#endif