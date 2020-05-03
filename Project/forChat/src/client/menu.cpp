#include "menu.hpp"

using std::cout;
using std::endl;

int Menu::mainMenu() {
    cout << "==================" << endl;
    cout << "1. login" << endl;
    cout << "2. reg" << endl;
    cout << "0. quit" << endl;
    cout << "==================" << endl;
    int choice = 0;
    std::cin >> choice;
    std::cin.get();
    return choice;
}
