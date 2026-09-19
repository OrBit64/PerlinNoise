// perlin_math.cpp -- реализация функций и классов, объявленных в perlin_math.h
// Здесь не должно быть main()!!! main() только в src/main.cpp!!!

/**
 * В проектах использовать using namespace std нежелательно
 * так как может быть конфликт имён
 */ 

 /**
 * Табуляция 4 пробела + main функция находится в src/main.cpp, остальные
 * файлы являются функционалом приложения, который будет использоваться
 * непосредственно или косвенно в src/main.cpp
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>
#include "perlin_math.h"

/** Условные обозначения
 * size:        сколько квадратов с четырьмя случайными векторами
 * scale:       сколько пикселей в каждом квадрате
 * pixel or p:  каждый отдельный пиксель, для которого расчитывается градиент
 */

perlinNoize::perlinNoize(unsigned int seed) {
    p.resize(256);
    for (int i = 0; i < 256; i++) {
        p[i] = i;
    }

    std::mt19937 generator(seed);

    //  Перемешиваем элементы массива случайным образом
    std::shuffle(p.begin(), p.end(), generator);
    p.insert(p.end(), p.begin(), p.end());
}




//я не доделал эту функцию
double dotXY(double X, double Y)
{
    int LeftLowX = std::floor(X);
    int LeftLowY = std::floor(Y);
    double dotX = X - LeftLowX;     //расположение точки X пример: х=2.2  2.2-2=0.2 
    double dotY = Y - LeftLowY;
    int RightLowX   = LeftLowX + 1; // координата правой нижней части
    int LeftHightY  = LeftLowY + 1;
    int RightHightX = LeftLowX + 1;
    //std::vector<int>LL{LeftLowX,LeftLowY};//LL- left low
    //std::vector<int>RL{RightHightX,LeftLowY};//R-right (first letter-side/ second-height)
    //std::vector<int>LH{LeftLowX,LeftHightY};
    //std::vector<int>RH{RightHightX,LeftHightY};
    return 0.0;
}