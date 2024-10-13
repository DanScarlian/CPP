#define _USE_MATH_DEFINES //Для использования Пи
#include <iostream>
#include <cmath>
using namespace std;

bool CorrectValue(double a, double b, double c) { //Функция проверки введенных значений
    return (a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (c + b > a)); // стороны больше 0 и сумма двух сторон больше третей стороны
}

double get_angle(double a, double b, double c) { //Проверка введенных значений при помощи функции проверки
    if (!CorrectValue(a, b, c)) {
        cout << "Error 80.1: are you kidding me?";
        
        return -1; // выход из функции в случае ошибки 
    }

    double cosa = (pow(b,2) + pow(c,2) - pow(a,2)) / (2*b*c); //Теорема косинусов
    double degridation = acos(cosa)*(180/M_PI);

    return degridation;
}

int main() { 
    double a, b, c;
    cout << "Input sides of a triangle: ";
    cin >> a >> b >> c;
    double angle = get_angle(a, b, c);
    if (angle != -1) {
        cout << "angle opposite to side A: " << angle << " degees";
    }

    return 0;
}