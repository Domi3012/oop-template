#include "Algorithms.h"

int bus::addIfEven(int init, int item) {
    return init + (item % 2 == 0 ? item : 0);
}

Student bus::findMaxGPA(Student a, Student b) {
    return (a.gpa() >= b.gpa() ? a : b);
}