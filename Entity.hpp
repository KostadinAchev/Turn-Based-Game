#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <iostream>
#include <unordered_map>

/*
 #########################################################
 #                                                       #
 #                     Namespaces                        #
 #                                                       #
 #########################################################
*/

// HealValue is for the health value to be returned to a target it's a fixed number so there is no magic values in the code.
namespace HealValue
{
    const int HEALER_HEAL = 100;
    const int PALADIN_HEAL = 125;
    const int PHANTOM_HEAL = 250;
    const int DEATHKNIGHT_HEAL = 175;
}

// Spells is for the mana needed for the spell to be cast. It's put in an namespace so there are no magic values.
namespace Spells
{
    const int HEALER_HEAL = 100;
    const int MAGE_ATTACK = 50;
    const int NECROMANCER_RAISESKELETON = 50;
    const int DYBBUK_ATTACK = 150;
    const int LICH_RAISEDEAD = 750;
    const int DREADLORD_SUMMONNECROMANCER = 400;
    const int DREADLORD_SUMMONGHOUL = 500;
    const int DEATHKNIGHT_HEAL = 350;
    const int UNDEADHUNTER_ELIMINATE = 1000;
    const int PALADIN_REVIVE = 1350;
    const int PALADIN_HEAL = 500;
}

/*
 #########################################################
 #                                                       #
 #                        Class                          #
 #                                                       #
 #########################################################
*/

// main class entity where units such as heroes or just army units sit

class Entity
{
public:
    // important logic don't change else dead bodies on field + raise mechanic won't work as intended
    static int deadBodyCount;
    static void incrementDeadBody() { deadBodyCount++; }
    static void decrementDeadBody()
    {
        if (deadBodyCount > 0)
            deadBodyCount--;
    }
    static int getDeadBodyCount() { return deadBodyCount; }

public:
    /*
     #########################################################
     #                                                       #
     #                        Enums                          #
     #                                                       #
     #########################################################
    */

    // every army unit and heroes that exists in the game are in this enum if you want a new one add here under specific category
    enum Entities
    {
        // Army

        // Good
        INFANTRYMAN,
        ARCHER,
        KNIGHT,
        HEALER,
        MAGE,

        // Bad
        SKELETON,
        NECROMANCER,
        GHOUL,
        ZOMBIE,
        DYBBUK,
        REVENANT,
        PHANTOM,

        // Heroes

        // Bad
        LICH,
        DREAD_LORD,
        DEAD_KNIGHT,

        // Good
        UNDEAD_HUNTER,
        BLADE_DANCER,
        PALADIN,
    };

    // armor type is the type of armor that an Entity (unit or hero) wears it provides different type of protection from 0 -> 75%
    enum armorType
    {
        UNARMORED = 0,
        LEATHER = 25,
        MEDIUM = 50,
        HEAVY = 75
    };

    // used for printing later on don't touch it uses the value of armorType
    std::string armorType2str(int armorType)
    {
        switch (armorType)
        {
        case 0:
            return "Unarmored";
        case 25:
            return "Leather";
        case 50:
            return "Medium";
        case 75:
            return "Heavy";
        default:
            return "Unknown armor type";
        }
    }

    // entities can be good or bad depending on their faction so this enum helps us with determening if an entity is good or bad
    enum goodOrBad
    {
        GOOD,
        BAD
    };

    // all the stats that an entity has be it army unit or hero
    struct armyStats
    {
        std::string type;
        float health;
        float maxHP;
        armorType aType;
        int armorDurability;
        goodOrBad gOb;
        int damage;
        int moneyCost;
        bool isAlive;

        bool isCaster;
        int mana;
        int maxMP;
    };

    // in the map we put set values for every entity be it hero or army unit
    // clang-format off
    std::unordered_map<Entities, armyStats> Units{
        //type             type         || health || maxHP || armorType || armor durability || gOb || damage || moneyCost || isAlive || Caster || mana || maxMP 
        // Army

        // Good
        {INFANTRYMAN,   {"Infantryman",     420,      420,    MEDIUM,       8,                GOOD,     7,         250,       true,     false,      0,      0   }},
        {ARCHER,        {"Archer",          535,      535,    MEDIUM,       3,                GOOD,     10,        300,       true,     false,      0,      0   }},
        {KNIGHT,        {"Knight",          835,      835,    HEAVY,        10,               GOOD,     45,        700,       true,     false,      0,      0   }},
        {HEALER,        {"Healer",          290,      290,    UNARMORED,    0,                GOOD,     2,         150,       true,     true,      200,     200 }},
        {MAGE,          {"Mage",            325,      325,    LEATHER,      3,                GOOD,     10,        250,       true,     true,      200,     200 }},
        
        // Bad
        {SKELETON,      {"Skeleton",        500,      500,    MEDIUM,       8,                BAD,      5,         100,       true,     false,      0,      0   }},
        {NECROMANCER,   {"Necromancer",     300,      300,    UNARMORED,    0,                BAD,      4,         400,       true,     true,      200,     200 }},
        {GHOUL,         {"Ghoul",           400,      400,    HEAVY,        6,                BAD,      12,        250,       true,     false,      0,      0   }},
        {ZOMBIE,        {"Zombie",          250,      250,    UNARMORED,    0,                BAD,      15,        300,       true,     false,      0,      0   }},
        {PHANTOM,       {"Phantom",         0,        0,      UNARMORED,    0,                BAD,      0,         500,       true,     false,      0,      0   }},
        
        // Heroes

        // Bad 
        {LICH,          {"Lich",            1500,     1500,   HEAVY,        15,               BAD,      100,       500,       true,     true,       1000,   1000}},
        {DREAD_LORD,    {"Dread Lord",      3000,     3000,   HEAVY,        20,               BAD,      200,       500,       true,     true,       2000,   2000}},
        {DEAD_KNIGHT,   {"Dead Knight",     2500,     2500,   HEAVY,        15,               BAD,      150,       500,       true,     true,       1000,   1000}},

        // Good
        {UNDEAD_HUNTER, {"Undead Hunter",   2000,     2000,   HEAVY,        17,               GOOD,     75,        500,       true,     true,       1500,   1500}},
        {BLADE_DANCER,  {"Blade Dancer",    4000,     4000,   MEDIUM,       25,               GOOD,     300,       500,       true,     false,      0,      0   }},
        {PALADIN,       {"Paladin",         5000,     5000,   HEAVY,        20,               GOOD,     250,       500,       true,     true,       3000,   3000}}
        

    };
    // clang-format on

public:
    /*
     #########################################################
     #                                                       #
     #                   Constructors                        #
     #                                                       #
     #########################################################
    */

    // removed the default constructor and both the copy constructors because we dont need them right now maybe later idk
    Entity() = delete;
    Entity(Entity &e) = delete;
    Entity &operator=(Entity &e) = delete;

    // constructor must be below the unordered_map and the enums Entities and armyStats because it won't work. It sets the stats for an Entity
    Entity(Entities heroClass)
    {
        if (Units.find(heroClass) != Units.end())
        {
            armyStats stats = Units[heroClass];

            m_type = stats.type;
            m_health = stats.health;
            m_maxHP = stats.maxHP;
            m_armorType = stats.aType;
            m_armorDurability = stats.armorDurability;
            m_goodOrBad = stats.gOb;
            m_damage = stats.damage;
            m_moneyCost = stats.moneyCost;
            m_isAlive = stats.isAlive;

            m_isCaster = stats.isCaster;
            m_mana = stats.maxMP;
        }

        else
        {
            std::cerr << "Error: Invalid class passed to Entity constructor." << std::endl;
        }
    }

public:
    /*
     #########################################################
     #                                                       #
     #                Function declarations                  #
     #                                                       #
     #########################################################
    */

    // function declarations used later in Entity.cpp

    // deal damage without reduction
    void Damage_NoReduction(Entity *target);

    // deal damage with reduction
    void Damage_Reduction(Entity *target);

    // mana regen function
    void manaRegen();

    // check for entity is alive meaning if after being attacked to make a check if its still alive or dead
    void is_alive_check(Entity *target);

    // helper function for healing everything from army units to heroes
    void healingDone(Entity *target, float healing);

    // function for reviving dead army units
    void revive(Entity *target);

    // main attack function used by every entity
    virtual void Attack(Entity *target);

    // printing the entitie's information
    void printInfo();

    // death when health is <0 or 0
    virtual void death();

    // main heal function used to heal everything
    virtual void Heal(Entity *target);

    /*
     #########################################################
     #                                                       #
     #                       Getters                         #
     #                                                       #
     #########################################################
    */

    // getters for every variable that the entity has

    float get_health() { return m_health; }

    int get_maxHP() { return m_maxHP; }

    int get_armorDurability() { return m_armorDurability; }

    armorType get_armorType() { return m_armorType; }

    goodOrBad get_faction() { return m_goodOrBad; }

    int get_damage() { return m_damage; }

    int get_moneyCost() { return m_moneyCost; }

    bool get_isCaster() { return m_isCaster; }

    int get_mana() { return m_mana; }

    int get_maxMP() { return m_maxMP; }

    std::string get_type() { return m_type; }

    bool get_is_alive() { return m_isAlive; }

    /*
     #########################################################
     #                                                       #
     #                       Setters                         #
     #                                                       #
     #########################################################
    */

protected:
    // setters for some variables that the entity has

    void set_type(std::string new_name) { this->m_type = new_name; }

    void set_health(float new_health) { this->m_health = new_health; }

    void set_isCaster(bool new_mana_state) { this->m_isCaster = new_mana_state; }

    void set_mana(int new_mana) { this->m_mana = new_mana; }

    void set_is_alive(bool state) { this->m_isAlive = state; }

    void set_armorDurability(int armorDurability) { this->m_armorDurability = armorDurability; }

    void set_armorType(armorType armorType) { this->m_armorType = armorType; }

private:
    // variables

    std::string m_type;
    float m_maxHP;
    float m_health;
    enum armorType m_armorType;
    int m_armorDurability;
    enum goodOrBad m_goodOrBad;
    int m_damage;
    int m_moneyCost;
    bool m_isAlive;
    bool m_isCaster;
    int m_mana;
    int m_maxMP;
};

#endif