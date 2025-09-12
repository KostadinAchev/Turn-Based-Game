#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <iostream>
#include <unordered_map>

// virtual entity class
// identation

class Entity
{
public:
    static int deadBodyCount;
    static void incrementDeadBody() { deadBodyCount++; }
    static void decrementDeadBody()
    {
        if (deadBodyCount > 0)
            deadBodyCount--;
    }
    static int getDeadBodyCount() { return deadBodyCount; }

    enum classes
    {
        INFANTRYMAN,
        ARCHER,
        KNIGHT,
        HEALER,
        MAGE,
        SKELETON,
        NECROMANCER,
        GHOUL,
        ZOMBIE,
        DYBBUK,
        REVENANT,
        PHANTOM
    };

    enum armorType
    {
        UNARMORED = 0,
        LEATHER = 25,
        MEDIUM = 50,
        HEAVY = 75
    };

    std::string getArmorType(int armorType)
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

    enum goodOrBad
    {
        GOOD,
        BAD
    };

    struct classStats
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
        int minManaSpell;
    };

    std::unordered_map<classes, classStats> Heroes{
        //type             type         || health || maxHP || armorType || armor durability || gOb || damage || moneyCost || isAlive || Caster || mana || maxMP ||minManaSpell

        {INFANTRYMAN,   {"Infantryman",     420,      420,    MEDIUM,       8,                GOOD,     7,         250,       true,     false,      0,      0,      0}},
        {ARCHER,        {"Archer",          535,      535,    MEDIUM,       3,                GOOD,     10,        300,       true,     false,      0,      0,      0}},
        {KNIGHT,        {"Knight",          835,      835,    HEAVY,        10,               GOOD,     45,        700,       true,     false,      0,      0,      0}},
        {HEALER,        {"Healer",          290,      290,    UNARMORED,    0,                GOOD,     2,         150,       true,     true,      200,     200,    200}},
        {MAGE,          {"Mage",            325,      325,    LEATHER,      3,                GOOD,     10,        250,       true,     true,      200,     200,    200}},
        {SKELETON,      {"Skeleton",        500,      500,    MEDIUM,       8,                BAD,      5,         100,       true,     false,      0,      0,      0}},
        {NECROMANCER,   {"Necromancer",     300,      300,    UNARMORED,    0,                BAD,      4,         400,       true,     true,      200,     200,    200}},
        {GHOUL,         {"Ghoul",           400,      400,    HEAVY,        6,                BAD,      12,        250,       true,     false,      0,      0,      0}},
        {ZOMBIE,        {"Zombie",          250,      250,    UNARMORED,    0,                BAD,      15,        300,       true,     false,      0,      0,      0}},
        {PHANTOM,       {"Phantom",         0,        0,      UNARMORED,    0,                BAD,      0,         500,       true,     false,      0,      0,      0}},
    };

    Entity(classes heroClass)
    {
        if (Heroes.find(heroClass) != Heroes.end())
        {
            classStats stats = Heroes[heroClass];

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
            m_minManaSpell = stats.minManaSpell;
        }

        else
        {
            std::cerr << "Error: Invalid class passed to Entity constructor." << std::endl;
        }
    }

    // Done but idk if logic is good may need further improvements
    void Damage_NoReduction(Entity *target);
    void Damage_Reduction(Entity *target);
    void manaRegen();
    void is_alive_check(Entity *target);
    void healingDone(Entity *target, float healing);

    virtual void Attack(Entity *target);

    void printInfo();

    virtual void death();

    virtual void Heal(Entity *target);

    // geters

    float get_health() { return m_health; }

    int get_maxHP() { return m_maxHP; }

    int get_armorDurability() { return m_armorDurability; }

    armorType get_armorType() { return m_armorType; }

    goodOrBad get_fraction() { return m_goodOrBad; }

    int get_damage() { return m_damage; }

    int get_moneyCost() { return m_moneyCost; }

    bool get_isCaster() { return m_isCaster; }

    int get_mana() { return m_mana; }

    int get_maxMP() { return m_maxMP; }

    int get_minManaSpell() { return m_minManaSpell; }

    std::string get_type() { return m_type; }

    bool get_is_alive() { return m_isAlive; }

    // Setters
protected:
    void set_type(std::string new_name) { this->m_type = new_name; }

    void set_health(float new_health) { this->m_health = new_health; }

    void set_isCaster(bool new_mana_state) { this->m_isCaster = new_mana_state; }

    void set_mana(int new_mana) { this->m_mana = new_mana; }

    void set_minManaAttack(int new_mana) { this->m_minManaSpell = new_mana; }

    void set_is_alive(bool state) { this->m_isAlive = state; }

    void set_armorDurability(int armorDurability) { this->m_armorDurability = armorDurability; }

    void set_armorType(armorType armorType) { this->m_armorType = armorType; }

private:
    std::string m_type;
    float m_maxHP;
    float m_health;
    int m_armorDurability;
    enum armorType m_armorType;
    enum goodOrBad m_goodOrBad;
    int m_damage;
    int m_moneyCost;
    bool m_isCaster;
    int m_maxMP;
    int m_mana;
    int m_minManaSpell;
    bool m_isAlive;
};

#endif