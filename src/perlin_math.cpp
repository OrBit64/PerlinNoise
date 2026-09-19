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


std::vector<double>gradX={1.0, -1.0, 0.0, 0.0, 1.0, -1.0, 1.0, -1.0};
std::vector<double>gradY={0.0, 0.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};

//я не доделал эту функцию
double perlinNoize::dotXY(double X, double Y)
{
    int LeftLowX = std::floor(X);
    int LeftLowY = std::floor(Y);
    double dotX = X - LeftLowX;     //расположение точки X пример: х=2.2  2.2-2=0.2 
    double dotY = Y - LeftLowY;
    int RightLowX   = LeftLowX + 1; // координата правой нижней части
    int LeftHightY  = LeftLowY + 1;
    int RightHightX = LeftLowX + 1;
    int hashLL = p[(p[LeftLowX & 255] + LeftLowY) & 255];
    int hashRL = p[(p[RightLowX & 255] + LeftLowY) & 255];
    int hashLH = p[(p[LeftLowX & 255] + LeftHightY) & 255];
    int hashRH = p[(p[RightLowX & 255] + LeftHightY) & 255];

    double vX_LL = gradX[hashLL % 8];
    double vY_LL = gradY[hashLL % 8];
    double vX_RL = gradX[hashRL % 8];
    double vY_RL = gradY[hashRL % 8];
    double vX_LH = gradX[hashLH % 8];
    double vY_LH = gradY[hashLH % 8];
    double vX_RH = gradX[hashRH % 8];
    double vY_RH = gradY[hashRH % 8];

    double sLL = vX_LL * dotX + vY_LL * dotY;
    double sRL = vX_RL * (dotX - 1.0) + vY_RL * dotY;
    double sLH = vX_LH * dotX + vY_LH * (dotY - 1.0);
    double sRH = vX_RH * (dotX - 1.0) + vY_RH * (dotY - 1.0);

    return sLL;
}