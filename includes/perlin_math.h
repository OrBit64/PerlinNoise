// perlin_math.h -- прототипы функций и объявления классов для математической части шума Перлина

#pragma once


class perlinNoize{
    private:
        std::vector<int>p;
    public:
        double dotXY(double X,double Y);//функция для обнаружения координат сетки
        double dotXY(double X,double Y);
        perlinNoize(unsigned int seed);
};

