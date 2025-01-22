#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
using namespace std;

enum Race
{
    Elf,
    Human,
    Dwarf,
    Tiefling,
    Halfling,
    HalfOrc,
    Dragonborn,
    Gnome,
    HalfElf
};

enum Classe
{
    Fighter,
    Cleric,
    Rogue,
    Wizard
};


class Character
{
public:
    int expToNextLvl;
    int currentExp;
    int damage;
    int hp;
    int currentHP;
    string name;
    int level;
    Race race;
    Classe classe;
   // random_device rnd; 
    //Dictionnaire qui contient le chemins pour chaque race
    map<Race, string> raceFileMap = {
        {Human, "NamesFolder/HumanNames.txt"},
        {Elf, "NamesFolder/ElfNames.txt"},
        {Dwarf, "NamesFolder/DwarfNames.txt"},
        {Tiefling, "NamesFolder/TieflingNames.txt"},
        {Halfling, "NamesFolder/HalflingNames.txt"},
        {HalfOrc, "NamesFolder/HalfOrcNames.txt"},
        {Dragonborn, "NamesFolder/DragonBornNames.txt"},
        {Gnome, "NamesFolder/GnomeNames.txt"},
        {HalfElf, "NamesFolder/ElfNames.txt"}
    };
    map<Race, string> raceToString = {
        {Human, "Human"},
        {Elf, "Elf"},
        {Dwarf, "Dwarf"},
        {Tiefling, "Tiefling"},
        {Halfling, "Halfling"},
        {HalfOrc, "HalfOrc"},
        {Dragonborn, "Dragonborn"},
        {Gnome, "Gnome"},
        {HalfElf, "HalfElf"}
    };
    map<Classe, string> classeToString = {
        {Fighter, "Fighter"}, {Cleric, "Cleric"}, {Rogue, "Rogue"}, {Wizard, "Wizard"}
    };


    Character(int _damage, int _hp, Race _race, Classe _classe, int _level)
        : damage(_damage),
          hp(_hp),
          race(_race),
          classe(_classe),
          level(_level)
    {
        name = GetNameFromFile(raceFileMap[race]);
        currentHP = _hp;
        expToNextLvl = 5;
        currentExp = 0;
    }

    Character(string _name, int _damage, int _hp, Race _race, Classe _classe, int _level, int _expToNextLevel, int _currentXP)
        : damage(_damage),
          hp(_hp),
          race(_race),
          classe(_classe),
          level(_level),
          name(_name),
          expToNextLvl(_expToNextLevel),
          currentExp(_currentXP)
    {
        currentHP = _hp;
    }

    void GainExp(int expGain)
    {
        currentExp += expGain;
        if (currentExp >= expToNextLvl)
        {
            currentExp -= expToNextLvl;
            expToNextLvl += 5;
            hp += 5;
            currentHP += 5;
            level++;

            if (classe == Fighter || classe == Rogue)
            {
                damage += 2;
            }
            else
            {
                damage += 1;
            }
            cout << name << " LEVELED UP!" << '\n';
        }
    }

    void DisplayCharInfo()
    {
        cout << " ||" + name << ", " << "Level " << to_string(level) << " " + raceToString[race] << " " +
            classeToString[classe] << " ; " << currentHP << "/" << hp << " HP" "\n";
    }

    ~Character() = default;

    string GetNameFromFile(const string& filename)
    {
        ifstream file(filename);
        vector<string> names;
        random_device rnd;

        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                names.push_back(line);
            }
            file.close();
            int randomIndex = rnd.operator()() % names.size();

            return names[randomIndex];
        }
        else
        {
            cout << "Unable to open file." << endl;
            return "DefaultName";
        }
    }

private:
};
