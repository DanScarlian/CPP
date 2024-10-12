#include <iostream>
#include <vector> // векторы, вернее массивы изменяемые
#include <string> // почти как векторы, но изменяемые строки
using namespace std;

class Item { // назвал класс товаров Item (согласно заданию)
public: // то что под ним, доступно не только в классе Item но и везде в коде. 
    string name; // свойство класса Item отвечающее за название товара
    double price; // свойство класса Item отвечающее за цену товара (плавающая точка (или знак))
    
    Item(string itemName, double itemPrice) : name(itemName), price(itemPrice) {}
    
    // Метод для вычисления бонуса на основе n процентов от цены
    double bonus(int percent) const {
        return price * percent / 100.0;
    }
};

double Bonusnaya(const vector<Item>& items, bool TratimBonus, double& BonusBalance) { // Расчитываем бонусы и траты
    double PlotiteNalog = 0.0; // Итог к оплате
    BonusBalance = 0.0; // Зачисляем бонусы
    double NashBalance = 0.0; // По умолчанию без бонусов 

    for (const auto& item : items) {
        if (TratimBonus && NashBalance >= item.price) { // Тратим бонусы 
            NashBalance -= item.price;
        } else {
            double purchasePrice = item.price; // время получать бонусы
            PlotiteNalog += purchasePrice;

            if (!TratimBonus) { // Начислите бонусы пожалуйста
                BonusBalance += item.bonus(3); // 3% начислим
            }
        }
    }
    return PlotiteNalog; // НДС считать не будем
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

    double Kopilka, Potratili; // Передача значения баланса

    double NoBonus = Bonusnaya(purchases, false, Kopilka); // накопление бонусрв
    double BonusAhead = Bonusnaya(purchases, true, Potratili) - Kopilka; // трата бонусов

    cout << "No bonus :( ? : " << NoBonus << "\n"; // Нет бонусов, платим полную цену :(
    cout << "Bank of bonuses: " << Kopilka << "\n"; // Зато бонусы дали за полную цену :D
    cout << "All In! : " << BonusAhead << "\n"; // Теперь можем и потратить бонусы на продукты, ура!
    cout << "A Gde?: " << Potratili << "\n"; // Правда теперь нам бонусов не дали :(
    
    return 0;
}
