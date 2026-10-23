#include <clocale>
#include <iostream>
#include <memory>
#include <windows.h>

#include "Evil.h"
#include "NPC.h"
#include "Paladin.h"
#include "Player.h"
#include "Warrior.h"
#include "Wizard.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Player player;
    std::cout << "Приветствую, путник! Присядь у костра да расскажи, кто ты.\n"
                 "\t1 - воин\n\t2 - маг\n\t3 - паладин\n";
    short choice = 0;
    if (!(std::cin >> choice)) return 1;

    switch (choice) {
    case 1:
        player.Create(std::make_unique<Warrior>());
        break;
    case 2:
        player.Create(std::make_unique<Wizard>());
        break;
    case 3:
        player.Create(std::make_unique<Paladin>());
        break;
    default:
        std::cout << "Таких героев еще не было в наших краях.\n";
        return 0;
    }

    TakeDamage(player.GetCharacter(), 5);
    return 0;
}
