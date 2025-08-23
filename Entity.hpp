#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <iostream>


// virtual entity class
// identation

class Entity
{
public:

    enum armorType
    {
        UNARMORED = 0,
        LEATHER = 25,
        MEDIUM = 50,
        HEAVY= 75
    };

    std::string getArmorType(int armorType){
        switch (armorType){
            case 0  : return "Unarmored";
            case 25 : return "Leather"; 
            case 50 : return "Medium"; 
            case 75 : return "Heavy"; 
            

        }
    }

    enum goodOrBad
    {
        GOOD,
        BAD
    };


    // fast constructor to make
    Entity(std::string type, float health, float maxHP, armorType aType, int armor, goodOrBad gOb, int damage, int moneyCost, int mana, int maxMP, int minManaSpell, bool manaBool, bool isAlive)
    {
        this->m_type = type;
        this->m_health = health;
        this->m_maxHP = maxHP;
        this->m_armorType = aType;
        this->m_goodOrBad = gOb;
        this->m_armor = armor;
        this->m_damage = damage;
        this->m_moneyCost = moneyCost;
        this->m_mana = mana;
        this->m_maxMP = maxMP;
        this->m_minManaSpell = minManaSpell;
        this->m_manaBool = manaBool;
        this->m_isAlive = isAlive;
    }

    // Done but idk if logic is good may need further improvements
    void Damage_NoReduction(Entity *target);
    void Damage_Reduction(Entity *target);
    void manaRegen();

    
    virtual void Attack(Entity *target);

    void printInfo();

    virtual void death();

    virtual void Heal(Entity *target);

    // geters

    float get_health() { return m_health; }

    int get_maxHP() { return m_maxHP; }

    int get_armor() { return m_armor; }

    armorType get_armorType() { return m_armorType; }

    goodOrBad get_fraction() { return m_goodOrBad; }

    int get_damage() { return m_damage; }

    int get_moneyCost() { return m_moneyCost; }

    bool get_manaBool() { return m_manaBool; }

    int get_mana() { return m_mana; }

    int get_maxMP() { return m_maxMP; }

    int get_minManaSpell() { return m_minManaSpell; }

    std::string get_type() { return m_type; }

    bool get_is_alive() { return m_isAlive; }

    

    // Setters 

    void set_type(std::string new_name) { this->m_type = new_name; }

    void set_health(float new_health) { this->m_health = new_health; }

    void set_manaBool(bool new_mana_state) { this->m_manaBool = new_mana_state; }

    void set_mana(int new_mana) { this->m_mana = new_mana; }

    void set_minManaAttack(int new_mana) { this->m_minManaSpell = new_mana; }
    
    void set_is_alive(bool state) { this->m_isAlive = state; }
    
    void set_armor(int armor) { this->m_armor = armor; }

    void set_armorType (armorType armorType) { this->m_armorType = armorType; }

private:
    std::string m_type;
    float m_maxHP;
    float m_health;
    int m_armor;
    enum armorType m_armorType;
    enum goodOrBad m_goodOrBad;
    int m_damage;
    int m_moneyCost;
    bool m_manaBool;
    int m_maxMP;
    int m_mana;
    int m_minManaSpell;
    bool m_isAlive;


};

#endif