#include <iostream>
#include <vector>
#include <string> 
using namespace std;

class Item {
public:
    string name;
    double price;

    Item(string name, double price) : name(name), price(price) {}
};

/*
Реализуем проверку продуктов на фактор купленности
Т.е. Купили ли продукты на этапе накопления бонуов
Или продукт был оставлен на этап траты бонусов
*/

bool nakoplenie(int spisok, int index) {
    return spisok & (1 << index);
}

double Bonusnaya(const vector<Item>& items, int spisok, double& BonusBalance) { // Расчитываем бонусы и траты
    double PlotiteNalog = 0.0; 
    BonusBalance = 0.0;

    for (int i = 0; i < items.size(); ++i) {
        if (nakoplenie(spisok, i)) {
            PlotiteNalog += items[i].price;
            BonusBalance += items[i].price * 0.03;
        }
    }

    return PlotiteNalog;
}

void TotalShopMadness(const vector<Item>& items) { //Магия Void - то что входит в него, не "возвращается"
    int n = items.size();

    double Maximalka = -numeric_limits<double>::infinity();
    double Remaining = numeric_limits<double>::infinity();
    double SummarnostiOne = 0;
    double BonusCount = 0;
    vector<Item> AllAheadFirst;
    vector<Item> AllAheadSecond;
    vector<Item> ZeroFirst;
    vector<Item> ZeroSecond;

    // Перебираем все возможные комбинации первой покупки (исключая маску 0, так как она пустая)
    for (int spisok = 1; spisok < (1 << n) - 1; ++spisok) {
        double BonusBalance = 0;
        double PlotiteNalog = Bonusnaya(items, spisok, BonusBalance);
        double SecondSumma = 0;
        for (int i = 0; i < n; ++i) {
            if (!nakoplenie(spisok, i)) {
                SecondSumma += items[i].price;
            }
        }

        double Ostatok = max(0.0, BonusBalance - SecondSumma);

        if (Ostatok == 0 && BonusBalance > Maximalka) { //Максимальные бонусы
            Maximalka = BonusBalance;
            SummarnostiOne = BonusBalance;
            AllAheadFirst.clear();
            AllAheadSecond.clear();
            for (int i = 0; i < n; ++i) {
                if (nakoplenie(spisok, i)) {
                    AllAheadFirst.push_back(items[i]);
                } else {
                    AllAheadSecond.push_back(items[i]);
                }
            }
        }

        if (Ostatok > 0 && Ostatok < Remaining) { //Пункт 2 с остатком минимальным
            Remaining = Ostatok;
            BonusCount = BonusBalance;
            ZeroFirst.clear();
            ZeroSecond.clear();
            for (int i = 0; i < n; ++i) {
                if (nakoplenie(spisok, i)) {
                    ZeroFirst.push_back(items[i]);
                } else {
                    ZeroSecond.push_back(items[i]);
                }
            }
        }
    }

    // Выводим результаты для обоих случаев
    cout << " Situation 1: Bolshie bonusi\n";
    cout << " First buy: ";
    for (const auto& item : AllAheadFirst) {
        cout << "[Item: " << item.name << " | Cost: " << item.price << "] | ";
    }
    cout << " Bonuses: " << Maximalka;
    cout << "\n Second buy: ";
    for (const auto& item : AllAheadSecond) {
        cout << "[Item: " << item.name << " | Cost: " << item.price << "] | " << endl;
        cout << " Final price: " << item.price - SummarnostiOne;
    }
    cout << "\n \n --------------------------------------\n \n";

    cout << " punkt 2: bolshie summi\n";
    cout << " First buy: ";
    for (const auto& item : ZeroFirst) {
        cout << "[Item: " << item.name << " | Cost: " << item.price << "] | ";
    }
    cout << "\n Bonuses: " << BonusCount;
    cout << "\n Second buy: ";
    for (const auto& item : ZeroSecond) {
        cout << "[Item: " << item.name << " | Cost: " << item.price << "] | ";
    }
    cout << "\n Ostatok: " << Remaining;
}

int main() { //Создание списка продуктов из списка в задании (названия на русском не ломают программу, но на всякий случай англ. яз.)
    vector<Item> purchases = {
        Item("apples", 200),
        Item("milk", 120),
        Item("candies", 300),
        Item("butter", 500),
        Item("nuts", 1000),
        Item("sausage", 350),
        Item("mustard", 45),
        Item("bread", 50),
        Item("tea", 100),
        Item("cake", 650)
    };

    TotalShopMadness(purchases);

    return 0;
}
