#include <iostream>
#include <vector>
#include <string> 
using namespace std;

class Item { 
public: 
    string name; 
    double price;
    
    Item(string itemName, double itemPrice) : name(itemName), price(itemPrice) {}
    
    
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
    double PlotiteNalog = 0.0; // Итог к оплате
    BonusBalance = 0.0; // Зачисляем бонусы
    double NashBalance = 0.0; // По умолчанию без бонусов 

    for (int i=0; i<items.size(); i++) {
        if (nakoplenie(spisok, i)) {
            PlotiteNalog += items[i].price; 
            BonusBalance += items[i].price * 0.03;
        }
    }

    return PlotiteNalog;
}

void TotalShopMadness(const vector<Item> & items) {
    int sdvig = items.size();

    for (int spisok = 1; spisok < (1<<sdvig) -1; ++spisok) {
        double BonusBalance = 0;
        double PlotiteNalog = Bonusnaya(items, spisok, BonusBalance);

        double FatalTotal = 0;
        for (int i = 0; i < sdvig; ++i) {
            if (!nakoplenie(spisok, i)) {
                FatalTotal += items[i].price;
            }
        }

        double BonusAhead = max(0.0, FatalTotal - BonusBalance); //Копим бонусы

        cout << " First buy: "; // Перечисление покупок
        for (int i = 0; i < sdvig; ++i) {
            if (nakoplenie(spisok, i)) {
                cout << "Item: " << items[i].name << " Cost: " << items[i].price << "| ";
            }
        }

        cout << "\n Second buy: ";
        for (int i = 0; i < sdvig; ++i) {
            if (!nakoplenie(spisok, i)) {
                cout << "Item: " << items[i].name << " Cost: " << items[i].price << " | ";
            }
        }

        cout << "\n first price: " << PlotiteNalog;
        cout << "\n bonus: " << BonusBalance;
        cout << "\n Second price before bonus: " << FatalTotal;
        cout << "\n Second price after bonus: " << BonusAhead;
        cout << "\n \n -------------------------------------\n \n";
    }
}
      

int main() { //Создание списка продуктов из списка в задании (названия на русском не ломают программу, но на всякий случай англ. яз.)
    vector<Item> purchases = {
        Item("apple", 200),
        Item("milk", 120),
        Item("candies", 300),
        Item("oil", 500),
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
