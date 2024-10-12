#include <iostream>
using namespace std;

int main() {
    cout << "Well, well, well, who you are?" << endl;
    cout << "okey, input A!" << endl;
    float a,b,c, AB;
    cin >> a;
    cout << "Now input B!" << endl;
    cin >> b;
    cout << "what can I do for you? \n 1: + \n 2: - \n 3: * \n 4: /" << endl;
    cout << "input number from 1 to 4: ";
    cin >> c;
    if (c==1) {
        AB = a + b;
    } else if (c==2) {
        AB = a - b;
    } else if (c==3) {
        AB = a * b;
    } else if (c==4) {
        AB = a / b;
    } else {
        cout << "Error" << endl;
    }
    cout << AB << endl;

    return 0;
}