#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Visokos(int year) { //Проверка на високосный год (он кратен 4)
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        return true;
    }
    return false;
}

int MonthDays(int month, int year) { //Список дней в месяцах (Все кроме февраля постоянные)
    vector<int> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Задали все 12 месяцев
    if (month == 2 && Visokos(year)) { //Проверка на високосный
        return 29; //Для високосного 2 месяц (Февраль) будет 29 а не 28
    }
    return days[month - 1];
}

/*
Определяем разницу между датами
Нужно это для вычесления текущего дня недели, с учетом исходных данных
Исходные данные: 1.01.1970 - это был четверг.
*/
int Raznica(int d, int m, int y) {
    int totalDays = 0;
    // Сначала считаем полные годы между 1970 и данным годом
    for (int year = 1970; year < y; ++year) { //Подсчет: сколько лет до 1970?
        totalDays += Visokos(year) ? 366 : 365;
    }
    for (int month = 1; month < m; ++month) { //Подсчет: сколько дней в этом году прошло до нашей даты
        totalDays += MonthDays(month, y); //Если месяц полность прошел, то проще
    }
    totalDays += d - 1; //1 января 1970 тоже день, убираем его

    return totalDays;
}

string NuKakovDen(int d) {  //Начинаем определять день недели
    int day = d / 10000; //Определяем день
    int month = (d / 100) % 100; //Определяем месяц
    int year = d % 100; //Определяем год
    if (year < 25) {
        year += 2000; // Года до 1970 идут как 19xx
    } else {
        year += 1900; // Года начиная с 1970 (или позже) как 19xx
    }
    int allday70 = Raznica(day, month, year); //Колличество дней между нашей датой и датой по умолчания
    int Wday = (allday70 + 3) % 7; //Помним что 1 января 1970 это четверг, а не понедельник (Можно конечно со сдвигами работать, но визуально не комфортно)
    vector<string> Week = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; //Дни недели

    return Week[Wday];
}

int main() {
    int date; //Вводим дату
    cout << "Input number: (DDMMYY): ";
    cin >> date;
    string Wday = NuKakovDen(date); //Обращаемся к определителю дня недели
    cout << "Your day of week: " << Wday << endl;

    return 0;
}