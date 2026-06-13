#include <iostream>
#include "battleship.h"
#include <string>

int main() {
    std::string name1, name2;
    std::cout << "Bitte geben Sie die beiden Spielernamen ein: ";
    std::cin >> name1 >> name2;

    Battleship battleship1(name1, name2);

    char choice;

    do {
        battleship1.play();

        std::cout << "\nMöchten Sie noch einmal spielen? (j/n): ";
        std::cin >> choice;

        switch (choice) {
        case 'j':
            break;
        case 'n':
            return 0;
        default:
            std::cout << "Ungültige Eingabe. Spiel wird beendet.\n";
            return 0;
        }

    } while (true);

    return 0;
}
