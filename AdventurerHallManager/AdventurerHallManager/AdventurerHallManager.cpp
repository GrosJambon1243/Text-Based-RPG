#include <string>
#include <fstream>
#include "Adventure.h"
#include "Character.h"
#include "Shop.h"
#include "Hall.h"
#include <queue>
#include <windows.h>
static bool inMainMenu = true;
string userChoice;
int userInt;

vector<Character> theParty;
random_device rnd;

map<int, Race> intToRace = {
    {0, Human},
    {1, Elf},
    {2, Dwarf},
    {3, Tiefling},
    {4, Halfling},
    {5, HalfOrc},
    {6, Dragonborn},
    {7, Gnome},
    {8, HalfElf}
};

void CreateParty()
{
    Character c1 = Character(5, 50, intToRace[rnd.operator()() % 9], Fighter, 1);
    Character c2 = Character(5, 50, intToRace[rnd.operator()() % 9], Rogue, 1);
    Character c3 = Character(5, 50, intToRace[rnd.operator()() % 9], Wizard, 1);
    Character c4 = Character(5, 50, intToRace[rnd.operator()() % 9], Cleric, 1);
    // Array Pour le Party
    theParty = {c1, c2, c3, c4};
}

// Adventure init
Adventure currentAdventure = Adventure("temp", nullptr);

//Queue Pour Recruit
queue<Character> recruit_queue_rogue;
queue<Character> recruit_queue_cleric;
queue<Character> recruit_queue_wizard;
queue<Character> recruit_queue_figther;

// Shop
Shop theShop = Shop(theShop.shopItem);

// Hall
Hall theHall = Hall(theHall.hallItem);

Adventure CreateAdventure(string name)
{
    //set root node --> On the Road
    TreeNode<AdventurePoint>* rootNode = new TreeNode<AdventurePoint>(AdventurePoint(
        "On the Road",
        "The long, windy road stretches before the party, the music and comfort of the guildhall slowly disappearing behind them.",
        Encounter("Bandits!", true, "A group of thugs and brigands jump out of the bushes and ambush the party!", 10,
                  20, 10, 0),
        Encounter("Lost travellers", false,
                  "A group of travelers are lost on the road. Your party gratiously escorts them all the way to a roadside inn, where they thank them for their help and reward them with 10 gold pieces.",
                  0, 0, 10, 0),
        Encounter("A poor soul", false,
                  "On the side of the road lies a courrier of the lord's army, dried blood surrounds a deep stab wound in his belly. Somehow, those who killed him did not find an interest in his pouch. He won't be needing these 5 gold coins.",
                  0, 0, 5, 0)));
    //Crossroads
    rootNode->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "The Crossroads",
        "The crossroads are not always safe. To the West lies the Rocky Road. To the East stretches the River Road.",
        Encounter("Tax Collectors", false,
                  "As frustrating as it is, the roads don't pay for themselves. 5 gold pieces are collected from your party for the road tax.",
                  0, 0, -5, 0),
        Encounter("Orc Raiders", true,
                  "Orcs from the local warband are roaming the countryside. They spotted your party. It's a fight to the death!",
                  20, 30, 15, 0),
        Encounter("Death from above", true,
                  "A massive Griffin swoops down from the clouds and attacks the party! Will they become just another meal for this feral predator?",
                  15, 35, 15, 0)));
    //Rocky Road
    rootNode->left->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Rocky Road",
        "The Rocky Road is dotted with crags, caves and small cliffs. Lots of good spots for ambushes.",
        Encounter("Wandering Priest", false,
                  "A well equipped priest is traveling alone. He offers the blessings of his deity and heals some of the party's wounds as a gesture of good faith.",
                  0, 0, 0, 10),
        Encounter("Wolf Pack", true,
                  "A pack of feral wolves appear between the rocks, led by a huge Dire Wolf with dagger-like fangs and a coat of pitch black fur.",
                  20, 40, 20, 0),
        Encounter("Spectral Host", true,
                  "The party walks past a long forgotten battlefield. Suddenly a whole army of ghostly figures clad in torn mail and holding battered weapons seems to appear out of thin air. With a cold and quiet stare, they move menacingly towards the party.",
                  15, 50, 20, 0)));
    //Forest
    rootNode->left->left->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Forest",
        "Tall trees and thick bush cover this whole area. The road twists and turns around small ponds and quiet clearings. But eyes are watching the party. The forest is home to many a fearsome creature.",
        Encounter("Owlbear", true,
                  "This creature resembles a fusion between a massive bear and an owl. Do not be fooled by its cute beak, it will use it to shred your party to pieces.",
                  25, 50, 25, 0),
        Encounter("Mystic Pond", false,
                  "A beautiful dryad welcomes the party in her humble domain. Satyrs dance and play the flute, joyfully calling to the party to join them. The mystic pond is majestic and enthralling. The party rests a bit, regaining strength for the final parts of the journey. But the magic of the denizens of the Mystic pond is subtle. Wasn't there gold in that bag before?",
                  0, 0, -20, 10),
        Encounter("Goblin Skirmishers", true,
                  "A band of goblins hiding in the trees and the overgrowth jump from all around the party. Their numbers are so great, its overwhelming!",
                  10, 80, 25, 0)));
    //Goblin Camp
    rootNode->left->left->left->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Goblin Camp",
        "Huts adorned with animal bones, a big campfire in the center, and so, so many goblins roaming around.",
        Encounter("Goblin Shaman", true,
                  "The goblin shaman cries out incantations in his guttural language, and yells out orders at his tribe. They attack from everywhere, and the shaman's magic is powerful!",
                  40, 100, 50, 0, "Goblin Shaman's Staff"),
        Encounter("Goblin Shaman", true,
                  "The goblin shaman cries out incantations in his guttural language, and yells out orders at his tribe. They attack from everywhere, and the shaman's magic is powerful!",
                  40, 100, 50, 0, "Goblin Shaman's Staff"),
        Encounter("Goblin Shaman", true,
                  "The goblin shaman cries out incantations in his guttural language, and yells out orders at his tribe. They attack from everywhere, and the shaman's magic is powerful!",
                  40, 100, 50, 0, "Goblin Shaman's Staff")));
    //Druid Grove
    rootNode->left->left->left->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "Druid Grove",
        "The plants and animals around here seem to try to drive your party away. The druids do not tolerate intruders in their secret grove.",
        Encounter("Angry Druids", true,
                  "Some of the druids transform into feral beasts and leap at the party while others stay back and use their druidic magic to harass and hinder. They are well coordinated and use the terrain to their advantage.",
                  40, 100, 50, 0, "Druidic Totem"),
        Encounter("Angry Druids", true,
                  "Some of the druids transform into feral beasts and leap at the party while others stay back and use their druidic magic to harass and hinder. They are well coordinated and use the terrain to their advantage.",
                  40, 100, 50, 0, "Druidic Totem"),
        Encounter("Angry Druids", true,
                  "Some of the druids transform into feral beasts and leap at the party while others stay back and use their druidic magic to harass and hinder. They are well coordinated and use the terrain to their advantage.",
                  40, 100, 50, 0, "Druidic Totem")));
    //Swamp
    rootNode->left->left->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "Swamps",
        "Thick bogs and deep marshes cover this foggy area, stretching for miles. It's easy to get lost...",
        Encounter("Forgotten Treasure", false,
                  "A half-sunk wagon lies abandoned on the side of the muddy road. A small chest has fallen in the swamp. A stroke of Luck! it's filled with gold pieces stamped with a neighbouring lord's effigy.",
                  0, 0, 40, 0),
        Encounter("Giant Alligator", true,
                  "The party has entered a ferocious beast's hunting grounds. A giant alligator preys on anything that moves around here, adventurer or not.",
                  20, 60, 25, 0),
        Encounter("Ghoul Pack", true,
                  "Those who die in these forsaken swamps rise as mindless undead hungry for living flesh. For some reason they tend to gather in small packs to hunt. They've caught your party's scent!",
                  15, 70, 25, 0)));
    //Troll Cave
    rootNode->left->left->right->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Troll Cave",
        "A damp cave so dark torchlight seems to wither away as the party enters. A stench hits them with the full force of a hundred rotting carcasses, so foul it takes all the strength in their bodies to avoid retching and falling unconcious. And then a growl comes from deeper in the lair. The troll has awakened!",
        Encounter("Troll", true,
                  "The Troll's nasty club is bigger than the tallest warrior, and its claws as sharp as razors! It laughs gutturally while deciding which member of your party it will eat first.",
                  40, 100, 50, 0, "Troll Hide"),
        Encounter("Troll", true,
                  "The Troll's nasty club is bigger than the tallest warrior, and its claws as sharp as razors! It laughs gutturally while deciding which member of your party it will eat first.",
                  40, 100, 50, 0, "Troll Hide"),
        Encounter("Troll", true,
                  "The Troll's nasty club is bigger than the tallest warrior, and its claws as sharp as razors! It laughs gutturally while deciding which member of your party it will eat first.",
                  40, 100, 50, 0, "Troll Hide")));
    //Lizardmen Temple
    rootNode->left->left->right->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "Lizardmen Temple",
        "This part of the swamps is filled with luxurious vegetation, almost jungle-like. Between the trees, stone totems with angry faces and bone idols representing a serpent god can be seen. Then, a temple, shaped like a pyramid, adorned in gold and precious stones. It is guarded by many a warrior, curled figures with scaly skin, lizard heads and tails, and spears and axes. At the top of the pyramid, a priest, wielding a jeweled mace and a ritual dagger, is about to sacrifice some poor victim while chanting to its serpent god!",
        Encounter("Lizarmen Warriors", true,
                  "The priest sees the party from atop the temple and yells. Suddenly, spears and stones are raining from all directions! The serpent god's worshippers have been angered.",
                  40, 100, 50, 0, "Saurian Sacred Tablet"),
        Encounter("Lizarmen Warriors", true,
                  "The priest sees the party from atop the temple and yells. Suddenly, spears and stones are raining from all directions! The serpent god's worshippers have been angered.",
                  40, 100, 50, 0, "Saurian Sacred Tablet"),
        Encounter("Lizarmen Warriors", true,
                  "The priest sees the party from atop the temple and yells. Suddenly, spears and stones are raining from all directions! The serpent god's worshippers have been angered.",
                  40, 100, 50, 0, "Saurian Sacred Tablet")));
    //River Road
    rootNode->left->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "River Road",
        "A beautiful river streches on the side of this road, twisting and winding. The sound of the rapids and the gentle winds make for a pleasant walk.",
        Encounter("Death from Below", true,
                  "The ground shakes, and all of a sudden two massive insect-like creatures burst out of burrowed holes, shrieking and grinding their huge mandibles. One spits acid while the other crawls at an impressive speed towards the party.",
                  20, 40, 20, 0),
        Encounter("Just in time", false,
                  "The party approches a group of travellers gathered in a defensive circle on a bridge. a group of ogres are harassing them with rocks. As the party comes in to attack, the ogres flee in a chaotic retreat, yelling angrily at each other. The rescued travelers offer food, medecine and gold as a sign of grattitude.",
                  0, 0, 10, 10),
        Encounter("Centaur Outriders", true,
                  "A group of Centaurs come galloping towards the party. They claim that this is their hunting grounds and trespass shall not be allowed. After a tense attempt at negotiations, it becomes clear they will not let it go and start circling the party. Suddenly one of them looses an arrow. It's a battle!",
                  15, 50, 20, 0)));
    //Coast
    rootNode->left->right->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Coast",
        "The sea stretches out before the party's eyes, waves crashing upon the rocky shores. This coast is known for its monstrous inhabitants, pirates and treasures. Fortune may hide there for those brave enough to reach out for it.",
        Encounter("Wyverns", true,
                  "Nesting in cracks in the shoreline cliffs, those nasty flying beasts have poisoned stingers at the tip of their tails. Two of them are patrolling the skies over the road. The party tries to hide, but to no avail. The monsters dive in to attack.",
                  25, 50, 25, 0),
        Encounter("Mercenary Battalion", true,
                  "These poorly armed mercenaries come from the neighbouring province. Whenever they are without a contract, they roam the country, showing a red banner, plundering and raiding wherever they find riches. Your party will not stand for such dishonorable conduct! They engage in bloody business with the mercenaries.",
                  10, 80, 25, 0),
        Encounter("Abandonned Wizard's Tower", true,
                  "This strange tower seems to move about, appearing in random places. It is a well known mystery in these parts. As the party enters the worn out building looking for valuables, stone golems step out of alcoves and attack.",
                  15, 70, 25, 0)));
    //Pirate Hideout
    rootNode->left->right->left->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Pirate Hideout",
        "This cove is well known to be a pirate safe haven. After traversing some well hidden paths between cliffs and trees, the party lay there eyes on a plethora of vessels, from small boats to large frigates, all sporting different versions of the skull and bones flag.",
        Encounter("Pirate King", true,
                  "After fighting a bunch of drunken sailors, the Pirate King emerges from his makeshift palace. He challenges the party to a fair fight... And immediately calls for all his corsairs to attack!",
                  40, 100, 50, 0, "Jolly Roger"),
        Encounter("Pirate King", true,
                  "After fighting a bunch of drunken sailors, the Pirate King emerges from his makeshift palace. He challenges the party to a fair fight... And immediately calls for all his corsairs to attack!",
                  40, 100, 50, 0, "Jolly Roger"),
        Encounter("Pirate King", true,
                  "After fighting a bunch of drunken sailors, the Pirate King emerges from his makeshift palace. He challenges the party to a fair fight... And immediately calls for all his corsairs to attack!",
                  40, 100, 50, 0, "Jolly Roger")));
    //Fishmen Lagoon
    rootNode->left->right->left->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "Fishmen Lagoon",
        "This reef is dotted with beautiful coral formations and rocky formations. With a closer look though, it is possible to see bone statues, fishing boat carcasses and strange, wet, slimy creatures moving about, yapping at each other in their gurgly language.",
        Encounter("Fishmen Assault", true,
                  "The creatures spot the party and point their crooked harpoons at them. More of them come out of pools and small grottos. And then, a massive, half-octopus, half ogre creature rises from beneath the surface. It charges at the party.",
                  40, 100, 50, 0, "Black Pearl"),
        Encounter("Fishmen Assault", true,
                  "The creatures spot the party and point their crooked harpoons at them. More of them come out of pools and small grottos. And then, a massive, half-octopus, half ogre creature rises from beneath the surface. It charges at the party.",
                  40, 100, 50, 0, "Black Pearl"),
        Encounter("Fishmen Assault", true,
                  "The creatures spot the party and point their crooked harpoons at them. More of them come out of pools and small grottos. And then, a massive, half-octopus, half ogre creature rises from beneath the surface. It charges at the party.",
                  40, 100, 50, 0, "Black Pearl")));
    //Mountain
    rootNode->left->right->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "Mountain",
        "This road is hard to travel. Steep climbs, rock slides, cold winds... nature itself seems to be telling your party a message: You are not welcome here.",
        Encounter("Savage Dwarves", true,
                  "The party passes by a dirty mine, with recent bodies littering the floor of the entrance. A sentry rings a bell. And they come out, screaming, axes and hammers and picks whirling above their heads. The crazy dwarves of the mountains fight with no care for their own life!",
                  15, 70, 25, 0),
        Encounter("Bear Cave", true,
                  "The party stops to rest in a small cave by the road. Tired and cold, they enjoy a warm broth. But a low growl interrupts their well deserved meal. The growl grows into a full blown rageful roar, as a huge cave bear walks in what the party now realizes to be the den of massive animal.",
                  25, 50, 25, 0),
        Encounter("Windswept Tower", false,
                  "This tower is known amongst travelers as a place of warmth and respite. The party enjoys a well deserved meal and warm bed for the night. The owner of the tavern helps with injuries while listening to the stories of yout party's adventures.",
                  0, 0, 0, 15)));
    //Giant's Summit
    rootNode->left->right->right->left = new TreeNode<AdventurePoint>(AdventurePoint(
        "Giant's Summit",
        "The top of this mountain is cold, windy, inhospitable. At first, only traces of its inhabitants are visible. Goat bones here, a crude runic painting there. Eventually the party climbs up to what looks like a small fort, made out of torn out trees and boulders tied together with furs and vines. Upon entering, it is obvious the creature that lives here is at least 5 times the size of a regular adventurer.",
        Encounter("Mountain Giant", true,
                  "The giant comes out of its home, axe in hand. Visitors are not welcome in its abode, and the punishment for trespassing is getting cleaved in half.",
                  40, 100, 50, 0, "Giant's Axe"),
        Encounter("Mountain Giant", true,
                  "The giant comes out of its home, axe in hand. Visitors are not welcome in its abode, and the punishment for trespassing is getting cleaved in half.",
                  40, 100, 50, 0, "Giant's Axe"),
        Encounter("Mountain Giant", true,
                  "The giant comes out of its home, axe in hand. Visitors are not welcome in its abode, and the punishment for trespassing is getting cleaved in half.",
                  40, 100, 50, 0, "Giant's Axe")));
    //Harpy's Nest
    rootNode->left->right->right->right = new TreeNode<AdventurePoint>(AdventurePoint(
        "Harpy's Nest",
        "Weird sounds can be heard from a considerable distance from this mountain peak. A mixture between singing and croaking. Then, as the party approaches, the singing is clearer, more beautiful. Climbing up to the top, they find a huge nest of intertwined branches and bones, filled with bird-like creatures, with raven wings and a woman's body. Their eyes glow a deep yellow and their beaks are menacing. Their Queen is twice the size of the others, and points a bony, clawed finger in your party's direction.",
        Encounter("Harpy Hags", true,
                  "The Harpys lunge and sweep at the party, attacking with their beaks and claws, attempting to push the heroes down the steep cliffs of the mountain.",
                  40, 100, 50, 0, "Queen's Feather"),
        Encounter("Harpy Hags", true,
                  "The Harpys lunge and sweep at the party, attacking with their beaks and claws, attempting to push the heroes down the steep cliffs of the mountain.",
                  40, 100, 50, 0, "Queen's Feather"),
        Encounter("Harpy Hags", true,
                  "The Harpys lunge and sweep at the party, attacking with their beaks and claws, attempting to push the heroes down the steep cliffs of the mountain.",
                  40, 100, 50, 0, "Queen's Feather")));

    Adventure newAdventure = Adventure(name, rootNode);
    return newAdventure;
}

void PressEnter()
{
    char userInput = 'a';
    do
    {
        cout << "Press Enter to Proceed";
        userInput = cin.get();
    }
    while (userInput != '\n');
}

void PressEnter2()
{
    char userInput = 'a';
    do
    {
        cout << "Press Enter to Proceed";
        cin.ignore();
        userInput = cin.get();
    }
    while (userInput != '\n');
}

void Combat(vector<Character>& party, Encounter* ennemi)
{
    //initiative
    bool isPartyTurn = false;
    if ((rnd.operator()() % 2) == 1)
    {
        isPartyTurn = true;
    }

    cout << "Combat Begins!\n";
    Sleep(1000);
    if (isPartyTurn)
    {
        cout << "The party wins the initiative.\n\n";
    }
    else
    {
        cout << "The enemy wins the initiative.\n\n";
    }
    Sleep(1000);
    //combat loop
    while (ennemi->GetHP() > 0 && !party.empty())
    {
        if (isPartyTurn)
        {
            for (auto character : party)
            {
                if (ennemi->GetHP() > 0)
                {
                    int dmg = character.damage + (rnd.operator()() % 6);
                    // Fighter Ability
                    if (character.classe == Fighter)
                    {
                        int bonusDmg = character.level;
                        if (rnd.operator()() % 11 == 0)
                        {
                            bonusDmg += dmg;
                            cout << "CRITICAL HIT!!!\n";
                        }
                        dmg += bonusDmg;
                    }

                    //Apply dmg to ennemy HP
                    ennemi->SetHP(ennemi->GetHP() - dmg);
                    string ennemiHP = (ennemi->GetHP() > 0) ? std::to_string(ennemi->GetHP()) : "0";
                    cout << character.name << " the " << character.classeToString[character.classe] <<
                        " attacks enemy for " << dmg << " points of damage! \n"
                        << "Enemy has " << ennemiHP << " HP remaining.\n";
                    Sleep(1000);
                }
            }
        }
        else
        {
            int victim = rnd.operator()() % party.size();
            int dmgMod = rnd.operator()() % 6;
            if (rnd.operator()() % 2 == 1 && dmgMod != 0)
            {
                dmgMod = -dmgMod;
            }
            int dmg = ennemi->GetDamage() + dmgMod;


            cout << "Enemy strikes " << party[victim].name << " the " << party[victim].classeToString[party[victim].
                classe] << " for " << dmg << " points of damage. \n";
            Sleep(1000);
            for (auto character : party)
            {
                if (character.classe == Wizard)
                {
                    int shieldValue = character.level + rnd.operator()() % 5;
                    if (rnd.operator()() % 2 == 1)
                    {
                        dmg -= shieldValue;
                        cout << character.name << " the Wizard has shielded " << shieldValue <<
                            " points of damage from the incoming attack reducing it to " << dmg << "!\n";
                        Sleep(1000);
                    }
                }
            }

            if (dmg > 0)
            {
                party[victim].currentHP -= dmg;

                if (party[victim].currentHP > 0)
                {
                    cout << party[victim].name << " has " << party[victim].currentHP << "/" << party[victim].hp <<
                        " HP left. \n";
                }
                else
                {
                    cout << "Oh no! " << party[victim].name << " has died!\n";
                    party.erase(party.begin() + victim);
                }
            }
            else
            {
                cout << "All damage has been shielded.\n";
            }
            Sleep(1000);
        }
        isPartyTurn = !isPartyTurn;
    }

    cout << "End of Combat.\n";
    Sleep(1000);
    if (!party.empty())
    {
        cout << "The party prevails!\n";
        Sleep(1000);
        for (auto healer : party)
        {
            if (healer.classe == Cleric)
            {
                int healValue = healer.level + rnd.operator()() % 5;
                for (int x = 0; x < party.size(); x++)
                {
                    party[x].currentHP += healValue;

                    if (party[x].currentHP > party[x].hp)
                    {
                        party[x].currentHP = party[x].hp;
                    }
                }
                cout << healer.name << " the Cleric healed the party for " << healValue << " HP!\n";
                Sleep(1000);
            }
        }
        for (auto member : party)
        {
            member.DisplayCharInfo();
        }
    }
    else
    {
        cout << "Everybody is dead. Time to recruit some more adventurers.\n";
        Sleep(1000);
    }
}

void HealParty()
{
    for (int i = 0; i < theParty.size(); ++i)
    {
        theParty[i].currentHP = theParty[i].hp;
    }
}

void SaveGold(int gold)
{
    ofstream file("SavedData/SaveGold");
    if (file.is_open())
    {
        file << gold;
        file.close();
    }
}

void SaveTrophies(vector<string> trophies)
{
    ofstream file("SavedData/SaveTrophies");
    if (file.is_open())
    {
        for (auto element : trophies)
        {
            file << element << '\n';
        }
        file.close();
    }
}

void SaveItems(vector<ShopItem> hallInventory, stack<ShopItem> shopInventory)
{
    //HallItems
    ofstream file("SavedData/SaveItems");
    if (file.is_open())
    {
        for (auto element : hallInventory)
        {
            file << element.name << "|" << element.description << "|" << element.price << '\n';
        }
        file.close();
    }
    //ShopItems
    ofstream fileShop("SavedData/SaveShop");
    if (fileShop.is_open())
    {
        stack<ShopItem> tempShop = shopInventory;
        while (!tempShop.empty())
        {
            fileShop << tempShop.top().name << "|" << tempShop.top().description << "|" << tempShop.top().price << '\n';
            tempShop.pop();
        }
        fileShop.close();
    }
}

void SaveParty(vector<Character> party)
{
    ofstream fileParty("SavedData/SaveParty");
    if (fileParty.is_open())
    {
        for (auto character : party)
        {
            fileParty << character.name << "|" << character.race << "|" << character.classe << "|" << character.level <<
                "|" << character.currentExp << "|" << character.damage << "|" << character.hp << '\n';
        }
        fileParty.close();
    }
}

void LoadData()
{
    //Gold
    ifstream goldSavedFile("SavedData/SaveGold");
    if (goldSavedFile.is_open())
    {
        goldSavedFile >> theHall.totalGold;
        goldSavedFile.close();
    }
    //Trophies
    ifstream trophiesSavedData("SavedData/SaveTrophies");
    if (trophiesSavedData.is_open())
    {
        string line;
        while (getline(trophiesSavedData, line))
        {
            theHall.trophies.emplace_back(line);
        }
        trophiesSavedData.close();
    }
    //HallItems
    ifstream itemsSavedData("SavedData/SaveItems");
    if (itemsSavedData.is_open())
    {
        string line;
        while (getline(itemsSavedData, line))
        {
            vector<string> splitLine;
            int index = 0;
            string temp = "";
            splitLine.push_back(temp);
            for (char value : line)
            {
                if (value != '|')
                {
                    splitLine[index] += value;
                }
                else
                {
                    splitLine.push_back(temp);
                    index++;
                }
            }
            theHall.hallItem.emplace_back(ShopItem(splitLine[1], splitLine[0], stoi(splitLine[2])));
        }
        itemsSavedData.close();
    }
    //ShopItems
    ifstream shopSavedData("SavedData/SaveShop");
    if (shopSavedData.is_open())
    {
        string line;
        vector<ShopItem> tempVector;
        while (getline(shopSavedData, line))
        {
            vector<string> splitLine;
            int index = 0;
            string temp = "";
            splitLine.push_back(temp);
            for (char value : line)
            {
                if (value != '|')
                {
                    splitLine[index] += value;
                }
                else
                {
                    splitLine.push_back(temp);
                    index++;
                }
            }
            tempVector.emplace_back(ShopItem(splitLine[1], splitLine[0], stoi(splitLine[2])));
        }
        itemsSavedData.close();
        while (!theShop.shopItem.empty())
        {
            theShop.shopItem.pop();
        }
        for (int i = tempVector.size() - 1; i >= 0; i--)
        {
            theShop.shopItem.push(tempVector[i]);
        }
    }
    //Party
    ifstream partySavedData("SavedData/SaveParty");
    //theParty.clear();
    if (partySavedData.is_open())
    {
        string line;
        map<int, Race> intToRace = {
            {1, Human},
            {0, Elf},
            {2, Dwarf},
            {3, Tiefling},
            {4, Halfling},
            {5, HalfOrc},
            {6, Dragonborn},
            {7, Gnome},
            {8, HalfElf}
        };
        map<int, Classe> intToClasse = {
            {0, Fighter},
            {1, Cleric},
            {2, Rogue},
            {3, Wizard}
        };
        while (getline(partySavedData, line))
        {
            vector<string> splitLine;
            int index = 0;
            string temp = "";
            splitLine.push_back(temp);
            for (char value : line)
            {
                if (value != '|')
                {
                    splitLine[index] += value;
                }
                else
                {
                    splitLine.push_back(temp);
                    index++;
                }
            }
            theParty.push_back(Character(splitLine[0], stoi(splitLine[5]), stoi(splitLine[6]),
                                         intToRace[stoi(splitLine[1])], intToClasse[stoi(splitLine[2])],
                                         stoi(splitLine[3]), stoi(splitLine[3]) * 5, stoi(splitLine[4])));
        }
        partySavedData.close();
    }
}

void AdventureTraversal(Adventure* adventure)
{
    int depth = 1;
    bool isAdventureOver = false;
    char userInput = 'a';
    string myString;

    do
    {
        cout << adventure->CurrentNode->data.GetName() << '\n' << adventure->CurrentNode->data.GetDescription() << '\n'
            << '\n';
        PressEnter2();

        system("CLS");
        cout << adventure->CurrentNode->data.chosenEncounter.name << '\n' << adventure->CurrentNode->data.
            chosenEncounter.GetDescription() << '\n' << '\n';
        PressEnter();
        system("CLS");
        if (adventure->CurrentNode->data.chosenEncounter.isBattle)
        {
            Combat(theParty, &adventure->CurrentNode->data.chosenEncounter);
            if (!theParty.empty())
            {
                int gainedGold = adventure->CurrentNode->data.chosenEncounter.goldValue;
                for (auto rogue : theParty)
                {
                    if (rogue.classe == Rogue)
                    {
                        int bonusGold = rogue.level + rnd.operator()() % 5;
                        gainedGold += bonusGold;
                        cout << rogue.name << " the Rogue, has found " << bonusGold << " extra gold pieces!\n";
                    }
                }
                cout << "Your party has scavenged a total of " << gainedGold << " gold from the battlefield!\n";

                currentAdventure.gold += gainedGold;
                cout << "The party gained " << depth << " exp \n";

                for (int i = 0; i < theParty.size(); i++)
                {
                    theParty[i].GainExp(depth);
                }
            }
        }
        else
        {
            if (adventure->CurrentNode->data.chosenEncounter.healValue > 0)
            {
                cout << "Your party is healed by " << adventure->CurrentNode->data.chosenEncounter.healValue << "!" <<
                    '\n';
                // code pour healer
                for (int x = 0; x < theParty.size(); x++)
                {
                    theParty[x].currentHP += adventure->CurrentNode->data.chosenEncounter.healValue;

                    if (theParty[x].currentHP > theParty[x].hp)
                    {
                        theParty[x].currentHP = theParty[x].hp;
                    }
                    theParty[x].DisplayCharInfo();
                }
            }
            if (adventure->CurrentNode->data.chosenEncounter.goldValue > 0)
            {
                cout << "Your party receives " << adventure->CurrentNode->data.chosenEncounter.goldValue << " gold!" <<
                    '\n';
                //code pour gagner du gold
                currentAdventure.gold += adventure->CurrentNode->data.chosenEncounter.goldValue;
                cout << "Your party has " << currentAdventure.gold << " gold\n";
            }
            if (adventure->CurrentNode->data.chosenEncounter.goldValue < 0)
            {
                cout << "Your party has lost " << adventure->CurrentNode->data.chosenEncounter.goldValue * -1 <<
                    " gold!" <<
                    '\n';
                //code pour perdre du gold
                currentAdventure.gold += adventure->CurrentNode->data.chosenEncounter.goldValue;
                cout << "Your party has " << currentAdventure.gold << " gold\n";
            }
        }
        depth++;
        PressEnter();
        system("CLS");
        if (adventure->CurrentNode->data.chosenEncounter.trophy == "")
        {
            cout << "Choose your party's next move" << '\n';

            if (adventure->CurrentNode == adventure->RootNode)
            {
                cout << "1 - Continue to the Crossroads" << '\n';
            }
            else if (adventure->CurrentNode->left != NULL)
            {
                cout << "1 - " << adventure->CurrentNode->left->data.GetName() << '\n'
                    << "2 - " << adventure->CurrentNode->right->data.GetName() << '\n'
                    << "3 - Retreat to Guild Hall (Lose half of your earned gold)" << '\n';
            }
        }
        else
        {
            isAdventureOver = true;
            if (!theParty.empty())
            {
                theHall.totalGold += adventure->gold;
                bool hasTrophy = false;
                for (auto trophy : theHall.trophies)
                {
                    if (trophy == adventure->CurrentNode->data.chosenEncounter.trophy)
                    {
                        hasTrophy = true;
                    }
                }
                if (!hasTrophy)
                {
                    cout << "Congratulations, your party has completed an adventure and gained a trophy: " << adventure
                        ->
                        CurrentNode->data.chosenEncounter.trophy << '\n' << '\n';
                    theHall.trophies.emplace_back(adventure->CurrentNode->data.chosenEncounter.trophy);
                }
                else
                {
                    cout << "Congratulations, your party has completed an adventure, but you already own this trophy: "
                        << adventure->
                           CurrentNode->data.chosenEncounter.trophy << '\n' << '\n';
                }

                cout << "Your party brings back  " << adventure->gold << " gold pieces\n";
                HealParty();
                SaveGold(theHall.totalGold);
                SaveTrophies(theHall.trophies);
            }

            PressEnter();
        }

        if (!isAdventureOver)
        {
            do
            {
                cin >> userInput;
                if (userInput != '1' && userInput != '2' && userInput != '3')
                {
                    cout << "Please enter a valid option" << '\n';
                }
            }
            while (userInput != '1' && userInput != '2' && userInput != '3');
        }

        switch (userInput)
        {
        case '1':
            adventure->CurrentNode = adventure->CurrentNode->left;
            break;
        case '2':
            adventure->CurrentNode = adventure->CurrentNode->right;
            break;
        case '3':
            isAdventureOver = true;
            theHall.totalGold += adventure->gold / 2;
            HealParty();

            SaveGold(theHall.totalGold);
            break;
        default: ;
        }
        system("CLS");
    }
    while (!isAdventureOver);
}

void DisplayShop()
{
    if (theShop.shopItem.empty())
    {
        cout << "There are no items left to buy.\n";
        PressEnter2();
        system("CLS");
    }
    else
    {
        do
        {
            if (theShop.shopItem.empty())
            {
                cout << "There are no items left to buy.\n";
                PressEnter();
                system("CLS");
                return;
            }
            else
            {
                theShop.DisplayTopItem();
                cout << "\nDo you wish to buy the item?\nYou have " << theHall.totalGold <<
                    " gold\n1: Buy \n2: Return to previous Menu\n";
                cin >> userChoice;
                userInt = stoi(userChoice);
                switch (userInt)
                {
                case 1:
                    system("CLS");
                    if (theHall.totalGold >= theShop.shopItem.top().price)
                    {
                        theHall.hallItem.emplace_back(theShop.shopItem.top());
                        cout << "You have bought " << theShop.shopItem.top().name << " for " << theShop.shopItem.top().price
                            <<
                            " gold\n";
                        theHall.totalGold -= theShop.shopItem.top().price;
                        theShop.shopItem.pop();
                        SaveGold(theHall.totalGold);
                        SaveItems(theHall.hallItem, theShop.shopItem);
                    }
                    else
                    {
                        system("CLS");
                        cout << "You don't have enough gold.\n";
                    }
                    PressEnter2();
                    system("CLS");
                    break;
                case 2:
                    system("CLS");
                    break;
                }
            }
        }
        while (userInt != 2);
    }
}


void DisplayPartyInfo()
{
    system("CLS");
    if (theParty.empty())
    {
        cout << "Your party is currently empty. You should recruit adventurers.\n";
    }
    else
    {
        for (Character x : theParty)
            x.DisplayCharInfo();
    }
    PressEnter2();
    system("CLS");
}


void RecruitPartyMember(vector<Character>& characters)
{
    Character r = recruit_queue_rogue.front();
    Character c = recruit_queue_cleric.front();
    Character f = recruit_queue_figther.front();
    Character w = recruit_queue_wizard.front();
    cout << "Welcome to the Recruiting Hall.\n";
    if (theParty.empty())
    {
        cout << "Your party is currently empty.\n";
    }
    else
    {
        cout << "Your current party: \n";
        for (auto member : theParty)
        {
            member.DisplayCharInfo();
        }
    }
    cout << "The following recruits are available for 10 gold each. Who do you want to hire?\nFighter\n1: ";
    f.DisplayCharInfo();
    cout << "\nRogue\n2: ";
    r.DisplayCharInfo();
    cout << "\nCleric\n3: ";
    c.DisplayCharInfo();
    cout << "\nWizard\n4: ";
    w.DisplayCharInfo();
    cout << "\n5: Exit\n";
    try
    {
        cin >> userChoice;
        userInt = stoi(userChoice);
        switch (userInt)
        {
        case 1:
            system("CLS");
            if (theHall.totalGold < 10)
            {
                cout << "You do not have enough gold to hire adventurers.\n";
            }
            else
            {
                characters.emplace_back(f);
                cout << "Recruited ";
                f.DisplayCharInfo();
                cout << "for 10 gold.\n";
                theHall.totalGold -= 10;
                SaveGold(theHall.totalGold);
                recruit_queue_figther.pop();
            }
            PressEnter2();
            system("CLS");
            break;

        case 2:
            system("CLS");
            if (theHall.totalGold < 10)
            {
                cout << "You do not have enough gold to hire adventurers.\n";
            }
            else
            {
                characters.emplace_back(r);
                cout << "Recruited ";
                r.DisplayCharInfo();
                cout << "for 10 gold.\n";
                theHall.totalGold -= 10;
                SaveGold(theHall.totalGold);
                recruit_queue_rogue.pop();
            }
            PressEnter2();
            system("CLS");
            break;
        case 3:
            system("CLS");
            if (theHall.totalGold < 10)
            {
                cout << "You do not have enough gold to hire adventurers.\n";
            }
            else
            {
                characters.emplace_back(c);
                cout << "Recruited ";
                c.DisplayCharInfo();
                cout << "for 10 gold.\n";
                theHall.totalGold -= 10;
                SaveGold(theHall.totalGold);
                recruit_queue_cleric.pop();
            }
            PressEnter2();
            system("CLS");
            break;
        case 4:
            system("CLS");
            if (theHall.totalGold < 10)
            {
                cout << "You do not have enough gold to hire adventurers.\n";
            }
            else
            {
                characters.emplace_back(w);
                cout << "Recruited ";
                w.DisplayCharInfo();
                cout << "for 10 gold.\n";
                theHall.totalGold -= 10;
                SaveGold(theHall.totalGold);
                recruit_queue_wizard.pop();
            }
            PressEnter2();
            system("CLS");
            break;
        case 5:
            system("CLS");
            break;
        default:
            throw(userChoice);
            break;
        }
    }
    catch (...)
    {
        cout << "Please choose a valid option\n";
        system("CLS");
        RecruitPartyMember(theParty);
    }
}

void DisplayHall()
{
    system("CLS");
    cout << "Your vault contains " << theHall.totalGold << " gold\n\n" << "The Hall is furnished with: \n";
    if (!theHall.hallItem.empty())
    {
        for (auto hall_item : theHall.hallItem)
        {
            hall_item.DisplayItemHall();
        }
    }
    else
    {
        cout << "No items purchased yet. You can buy items in the Shop.\n";
    }
    cout << "\nThe trophy room is adorned with the following trophies : ";
    if (!theHall.trophies.empty())
    {
        for (auto hall_trophy : theHall.trophies)
        {
            cout << '\n' << hall_trophy;
        }
    }
    else
    {
        cout << "\nNo trophies collected yet. Complete an adventure to earn a trophy.\n";
    }
    cout << "\n\n";
    PressEnter2();
    system("CLS");
}

void SecondMenu()
{
    do
    {
        cout <<
            "Adventure Hall Manager\n1: Go Adventure\n2: Shop\n3: Recruit\n4: View Hall\n5: View Party\n6: Save and Exit\n";
        try
        {
            cin >> userChoice;
            userInt = stoi(userChoice);
            switch (userInt)
            {
            case 1:
                system("CLS");
                if (theParty.empty())
                {
                    cout << "You need to recruit adventurers to go \n";
                }
                else
                {
                    currentAdventure = CreateAdventure("Main Adventure");
                    AdventureTraversal(&currentAdventure);
                }
                break;
            case 2:
                system("CLS");
                DisplayShop();
                break;
            case 3:
                system("CLS");
                if (theParty.size() < 4)
                {
                    RecruitPartyMember(theParty);
                }
                else
                {
                    cout << "Your party is full. You can't recruit now\n";
                    PressEnter2();
                    system("CLS");
                }
                break;
            case 4:
                DisplayHall();
                break;
            case 5:
                DisplayPartyInfo();
                break;
            case 6:
                SaveGold(theHall.totalGold);
                SaveItems(theHall.hallItem, theShop.shopItem);
                SaveTrophies(theHall.trophies);
                SaveParty(theParty);
                exit(0);
                break;
            default:
                throw(userChoice);
                break;
            }
        }
        catch (...)
        {
            cout << "Please choose a valid option\n";
            system("CLS");
            SecondMenu();
        }
    }
    while (userInt != 6);
}


void MainMenu()
{
    do
    {
        std::cout << "Adventure Hall Manager\n1: Continue\n2: New Game\n3: Exit\n";
        try
        {
            cin >> userChoice;
            userInt = stoi(userChoice);

            switch (userInt)
            {
            case 1:
                system("CLS");
                LoadData();
                SecondMenu();
                break;
            case 2:
                system("CLS");
                CreateParty();
                SecondMenu();
                break;
            case 3:
                exit(0);
                break;
            default:
                throw(userChoice);
            }
        }
        catch (...)
        {
            std::cout << "Please choose a valid option\n";
            system("CLS");
            MainMenu();
        }
    }
    while (inMainMenu);
}

void CreateShop()
{
    theShop.shopItem.push(ShopItem(
        "A set of impressive marble statues representing the most legendary adventurers. A tribute to fallen comrades that will not be forgotten.",
        "Heroic Statues", 800));
    theShop.shopItem.push(ShopItem(
        "A collection of specialized gear for weapons and magic training including wooden mannequins and practice targets for archery and magic.",
        "Training Equipment", 400));
    theShop.shopItem.push(ShopItem(
        "An old and well constructed wooden barrel. It seems like we can't empty it no matter how much we drink.",
        "Bottomless wine barrel", 200));
    theShop.shopItem.push(ShopItem(
        "Elaborate chandeliers hanging from the ceiling, adorned with magical orbs to provide soft, warm lighting throughout the hall.",
        "Magical Chandeliers", 100));
    theShop.shopItem.push(ShopItem(
        "A large hearth built from stone, providing warmth and a focal point for the common room, with a mantle for displaying trinkets or trophies.",
        "Stone Fireplace with Hearth", 50));
    theShop.shopItem.push(ShopItem(
        "Sturdy wooden tables and benches, where your party can gather to dine and socialize.", "Tables and Benches",
        25));
}

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 20; i++)
    {
        Character c = Character(5, 50, intToRace[(rnd.operator()() - i) % 9], Rogue, 1);
        recruit_queue_rogue.push(c);
        Character v = Character(5, 50, intToRace[rnd.operator()() + (rand() / (17 * (i + 1)) % 9)], Cleric, 1);
        recruit_queue_cleric.push(v);
        Character x = Character(5, 50, intToRace[(rand() - i) % 9], Fighter, 1);
        recruit_queue_figther.push(x);
        Character y = Character(5, 50, intToRace[(rnd.operator()() * (i + 1) - rand()) % 9], Wizard, 1);
        recruit_queue_wizard.push(y);
    }
    CreateShop();


    MainMenu();
    return 0;
}
