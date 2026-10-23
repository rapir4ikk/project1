#pragma once
#include "NPC.h"
#include <string>

class Evil : public NPC {
public:
    Evil();
    explicit Evil(const std::string& name);
    Evil(const std::string& name, unsigned int damage);
    Evil(const std::string& name, unsigned int damage, unsigned int health);
    Evil(const std::string& name, unsigned int damage, unsigned int health, unsigned int armor);
    ~Evil() override;
};
