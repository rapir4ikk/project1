#include "Evil.h"
#include <iostream>

Evil::Evil() {
    name = "Злодей";
    health = 10;
    damage = 5;
    armor = 3;
}
Evil::Evil(const std::string& characterName) : Evil() { name = characterName; }
Evil::Evil(const std::string& characterName, unsigned int characterDamage)
    : Evil(characterName) { damage = characterDamage; }
Evil::Evil(const std::string& characterName, unsigned int characterDamage, unsigned int characterHealth)
    : Evil(characterName, characterDamage) { health = characterHealth; }
Evil::Evil(const std::string& characterName, unsigned int characterDamage,
           unsigned int characterHealth, unsigned int characterArmor)
    : Evil(characterName, characterDamage, characterHealth) { armor = characterArmor; }

Evil::~Evil() {
    std::cout << name << " сгинул в пучине адского пламени\n";
}
