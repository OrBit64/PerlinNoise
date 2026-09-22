// perlin_math.h -- прототипы функций и объявления классов
// для математической части шума Перлина

#pragma once
#include <vector>

/**
 * Класс perlinNoize отвечает только за МАТЕМАТИКУ шума Перлина:
 *  - хранит таблицу перестановок (permutation table),
 *  - умеет посчитать значение шума в одной точке (dotXY),
 *  - умеет построить целую карту шума для картинки (generateNoiseMap).
 *
 * За вывод на экран, работу с пикселями/окном и т.п. отвечает
 * уже другой код (например, main.cpp твоего друга).
 */
class perlinNoize {
    private:
        std::vector<int> p; // таблица перестановок (256 значений, продублированная до 512)

    public:
        explicit perlinNoize(unsigned int seed); // Конструктор: создаёт и перемешивает таблицу p на основе seed.
        double dotXY(double X, double Y) const;// Приводит значение шума из диапазона [-1, 1] к диапазону [0, 1].
        static double normalize(double value);

        // Строит карту шума размером width x height.
        // scale-сколько пикселей приходится на одну "клетку" шума:
        std::vector<std::vector<double>> generateNoiseMap(int width, int height, double scale) const;
};