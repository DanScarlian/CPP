#include <iostream>
using namespace std;

/* 
Задание M01. 
Циклами сделать таблицу Пифагора с использованием табуляции.
Принцип таблицы: строки и столбцы озаглавлены множителями, а в ячейках их пересечения находится произведение
*/
int main() { // Таблица Пифагора 20х20 
    for (int stroka = 1; stroka <21; stroka++){ //Перебор строк

        for (int stolbec = 1; stolbec < 21; stolbec++){ // Перебор столбцов
        
            cout << "[" << stolbec*stroka << "]" << '\t';
        }
        cout << '\n';
    }

    return 0;
}