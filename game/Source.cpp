#include "NPC.h"
#include "CharacterFactory.h"
#include "Player.h"
#include "WeaponQuality.h"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>

enum class GameState { MainMenu, CharacterCreation, Story, CharacterInfo, Exit };

const char* QualityName(WeaponQuality quality)
{
    switch (quality)
    {
    case WeaponQuality::Common: return "Common";
    case WeaponQuality::Uncommon: return "Uncommon";
    case WeaponQuality::Rare: return "Rare";
    case WeaponQuality::Epic: return "Epic";
    case WeaponQuality::Legendary: return "Legendary";
    }
    return "Unknown";
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 700 }), "Abracadabra");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window)) return 1;

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF(
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        18.0f,
        nullptr,
        io.Fonts->GetGlyphRangesCyrillic());
    ImGui::SFML::UpdateFontTexture();

    Player player;
    GameState currentState = GameState::MainMenu;
    int selectedClass = 0;
    const char* classes[] = { "Warrior", "Wizard", "Paladin" };
    int selectedQuality = 0;
    const char* qualities[] = { "Common", "Uncommon", "Rare", "Epic", "Legendary" };
    char heroName[64] = "Hero";
    sf::Clock clock;

    while (window.isOpen() && currentState != GameState::Exit)
    {
        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) currentState = GameState::Exit;
        }
        if (currentState == GameState::Exit) break;

        ImGui::SFML::Update(window, clock.restart());

        switch (currentState)
        {
        case GameState::MainMenu:
            ImGui::Begin("Main menu");
            ImGui::Text("Abracadabra");
            ImGui::Separator();
            if (const NPC* hero = player.PeekCharacter())
                ImGui::Text("Current hero: %s (%s)", hero->GetName(), hero->GetClassName());
            else
                ImGui::Text("Current hero: none");
            if (ImGui::Button("Create character")) currentState = GameState::CharacterCreation;
            if (ImGui::Button("Story")) currentState = GameState::Story;
            if (ImGui::Button("Character information")) currentState = GameState::CharacterInfo;
            if (ImGui::Button("Exit")) currentState = GameState::Exit;
            ImGui::End();
            break;

        case GameState::CharacterCreation:
            ImGui::Begin("Character creation");
            ImGui::InputText("Name", heroName, sizeof(heroName));
            ImGui::Combo("Class", &selectedClass, classes, 3);
            ImGui::Combo("Equipment quality", &selectedQuality, qualities, 5);
            if (ImGui::Button("Create"))
            {
                std::unique_ptr<NPC> newHero;
                newHero = CreateCharacter(selectedClass, heroName);
                if (newHero)
                {
                    newHero->SetEquipmentQuality(static_cast<WeaponQuality>(selectedQuality));
                    player.Create(std::move(newHero));
                    currentState = GameState::MainMenu;
                }
            }
            if (ImGui::Button("Back")) currentState = GameState::MainMenu;
            ImGui::End();
            break;

        case GameState::Story:
            ImGui::Begin("Story");
            ImGui::TextWrapped("Королевству угрожают существа из древнего леса.");
            ImGui::TextWrapped("Создай героя, улучши экипировку и приготовься к путешествию.");
            if (player.PeekCharacter())
                ImGui::Text("Твой герой готов отправиться в путь.");
            else
                ImGui::Text("Сначала создай персонажа.");
            if (ImGui::Button("Back")) currentState = GameState::MainMenu;
            ImGui::End();
            break;

        case GameState::CharacterInfo:
            ImGui::Begin("Character information");
            if (NPC* hero = player.PeekCharacter())
            {
                ImGui::Text("Class: %s", hero->GetClassName());
                ImGui::Text("Level: %d", hero->GetLevel());
                ImGui::Text("Health: %u", hero->GetHealth());
                ImGui::Text("Damage: %u", hero->GetDamage());
                ImGui::Text("Armor: %u", hero->GetArmor());
                ImGui::Text("Equipment quality: %s", QualityName(hero->GetEquipmentQuality()));

                if (ImGui::Button("Level up"))
                    hero->LvlUp();
            }
            else
                ImGui::Text("Create a character first!");
            if (ImGui::Button("Back")) currentState = GameState::MainMenu;
            ImGui::End();
            break;

        case GameState::Exit:
            break;
        }

        window.clear(sf::Color(30, 30, 40));
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}