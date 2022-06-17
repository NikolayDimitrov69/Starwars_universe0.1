#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>

//! Функция, която прави проверка дали подаден низ е число, което може да бъде с най-много една точка, която не е в началото или края (позволява дробни числа)
const bool& isNumber(const std::string&);

//! Функция, която намира най-голямо число в арей
unsigned biggestNumInArray(unsigned*, unsigned);

//! Сортира два низа в азбучен ред
std::string alpha_sort(std::string, std::string);

#endif