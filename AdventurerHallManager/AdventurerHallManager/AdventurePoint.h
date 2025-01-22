#include <cstdlib>
#include <iostream>
#include <random>
using namespace std;

struct Encounter
{
public:
    string name;
    string trophy;
    bool isBattle;
    int goldValue;
    int healValue;
    int GetDamage()
    {
        return dmg;
    }
    void SetDamage(int value)
    {
        dmg = value;
    }
    int GetHP()
    {
        return hp;
    }
    void SetHP(int value)
    {
        hp = value;
    }
    string GetDescription()
    {
        return description;
    }
    
private:
    string description;
    int dmg;
    int hp;
protected:
    

public:
    Encounter():
          isBattle(false),
          dmg(0),
          hp(0),
          goldValue(0),
          healValue(0)
    {
        name = "";
        description = "";
        trophy = "";
    }
    
    //~Encounter() {}
    Encounter(const string& name, bool is_battle, const string& description, int dmg, int hp, int gold, int heal, const string& trophy = "")
        : name(name),
          isBattle(is_battle),
          description(description),
          dmg(dmg),
          hp(hp),
          goldValue(gold),
          healValue(heal),
          trophy(trophy)

    {
    }
};

class AdventurePoint
{
public:
    string GetName()
    {
        return name;
    }
    string GetDescription()
    {
        return description;
    }
    Encounter chosenEncounter;
    
private:
    string name;
    string description;
    Encounter* possibleEncounters;
    
protected:
public:
    AdventurePoint()
    {
        possibleEncounters = new Encounter[]{Encounter(), Encounter(), Encounter()};
        chosenEncounter = Encounter();
    }

    AdventurePoint(const string& name, const string& description, Encounter encounter_1, Encounter encounter_2, Encounter encounter_3)
        : name(name),
          description(description)
    {
        possibleEncounters = new Encounter[]{encounter_1, encounter_2, encounter_3};
        chosenEncounter = ChooseEncounter();
    }

    Encounter ChooseEncounter()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        int index = rand() %  3;
        return possibleEncounters[index];
    }
};
