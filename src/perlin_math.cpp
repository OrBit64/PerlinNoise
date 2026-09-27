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
 
#include <array>
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
 
// 8 заранее заданных градиентных направлений (диагонали и оси).
namespace {
    constexpr std::array<double, 8> gradX = {1.0, -1.0, 0.0, 0.0, 1.0, -1.0, 1.0, -1.0};
    constexpr std::array<double, 8> gradY = {0.0, 0.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0};
}
 
perlinNoize::perlinNoize(unsigned int seed) {
    p.resize(256);
    for (int i = 0; i < 256; i++) {
        p[i] = i;
    }
 
    std::mt19937 generator(seed);
 
    // Перемешиваем элементы массива случайным образом
    std::shuffle(p.begin(), p.end(), generator);

    std::vector<int> doubled = p;
    p.insert(p.end(), doubled.begin(), doubled.end());
}
 
double perlinNoize::dotXY(double X, double Y) const {
    // Координаты левого нижнего угла квадрата сетки, в который попала точка
    int LeftLowX = static_cast<int>(std::floor(X));
    int LeftLowY = static_cast<int>(std::floor(Y));
 
    // Положение точки внутри квадрата (дробная часть), пример: x=2.2 -> 2.2-2=0.2
    double dotX = X - LeftLowX;
    double dotY = Y - LeftLowY;
 
    int RightLowX  = LeftLowX + 1; // координата правого нижнего угла
    int LeftHightY = LeftLowY + 1; // координата верхней стороны (по Y)
 
    // Хэшируем координаты всех 4 углов квадрата через таблицу перестановок p.

    int hashLL = p[(p[LeftLowX  & 255] + LeftLowY)  & 255]; // левый нижний угол
    int hashRL = p[(p[RightLowX & 255] + LeftLowY)  & 255]; // правый нижний угол
    int hashLH = p[(p[LeftLowX  & 255] + LeftHightY) & 255]; // левый верхний угол
    int hashRH = p[(p[RightLowX & 255] + LeftHightY) & 255]; // правый верхний угол
 
    // По хэшу выбираем один из 8 градиентных векторов для каждого угла
    double vX_LL = gradX[hashLL % 8];
    double vY_LL = gradY[hashLL % 8];
    double vX_RL = gradX[hashRL % 8];
    double vY_RL = gradY[hashRL % 8];
    double vX_LH = gradX[hashLH % 8];
    double vY_LH = gradY[hashLH % 8];
    double vX_RH = gradX[hashRH % 8];
    double vY_RH = gradY[hashRH % 8];
 
    // Скалярное произведение градиента каждого угла с вектором
    double sLL = vX_LL * dotX+ vY_LL * dotY;
    double sRL = vX_RL * (dotX-1.0) +vY_RL * dotY;
    double sLH = vX_LH * dotX+ vY_LH * (dotY - 1.0);
    double sRH = vX_RH * (dotX-1.0)+vY_RH*(dotY - 1.0);
 

    double u = dotX * dotX * dotX * (dotX * (dotX * 6.0 - 15.0) + 10.0);
    double v = dotY * dotY * dotY * (dotY * (dotY * 6.0 - 15.0) + 10.0);
 
    //интерполяция 
    double low  = sLL + u * (sRL - sLL);
    double high = sLH + u * (sRH - sLH);
 
    return low + v * (high - low); // итоговое значение шума, примерно [-1, 1]
}
 
double perlinNoize::normalize(double value) {
    return (value + 1.0) / 2.0; // переводим [-1,1] в [0,1]
}
 
std::vector<std::vector<double>> perlinNoize::generateNoiseMap(int width, int height, double scale) const {
    if (scale <= 0.0) {
        scale = 1.0;
    }
 
    std::vector<std::vector<double>> map(height, std::vector<double>(width));
 
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double nx = x / scale; // переводим координату пикселя
            double ny = y / scale; // в координату "пространства шума"
 
            double raw = dotXY(nx, ny);       // шум в диапазоне [-1, 1]
            map[y][x]  = normalize(raw);      // приводим к [0, 1] для удобства друга
        }
    }
 
    return map;
}