#ifndef REDUCE_H
#define REDUCE_H

#include <iostream>
#include "DynamicVector.h"

template <class T>
using Operator = T (*)(T, T);

template <class T>
T reduce(const DynamicVector<T>& data, T init, Operator<T> f) {
    T res = init;
    for (int i = 0; i < data.size(); i++) {
        auto result = data[i];
        res = f(res, result.value());
    }
    return res;
}

#endif