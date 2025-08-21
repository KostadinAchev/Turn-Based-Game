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
    Entity(std::string type, float health, armorType aType, int armor, goodOrBad gOb, int damage, int moneyCost, int mana, bool manaBool, bool isAlive)
    {
        this->m_type = type;
        this->m_health = health;
        this->m_armorType = aType;
        this->m_goodOrBad = gOb;
        this->m_armor = armor;
        this->m_damage = damage;
        this->m_moneyCost = moneyCost;
        this->m_mana = mana;
        this->m_manaBool = manaBool;
        this->m_isAlive = isAlive;
    }

    // Done but idk if logic is good may need further improvements
    virtual void Attack(Entity *attacker, Entity *target)
    {
        float healthAfterDmg=0;
        if (target->get_is_alive() == true && attacker->get_is_alive() == true)
        {

            if (attacker->get_damage() <= 0)
            {
                std::cout << "No Damage Delt!" << std::endl;
            }
            if (target->get_health() <= 0)
            {
                target->set_is_alive(false);
            }
            else
            {
                if(target->get_armor() > 0)
                {
                    float reduction = static_cast<float>(100 - target->get_armorType()) / 100.0f;
                    healthAfterDmg = target->get_health() - (attacker->get_damage() * reduction);
                    target->set_health(healthAfterDmg);                   
                    std::cout << attacker->get_type() << " Delt: " << attacker->get_damage() << " damage to: " << target->get_type() << " Health remaining: "<< target->get_health()<< '\n';
                    target->set_armor(target->get_armor() - 1);
                    if (target->get_health() <= 0)
                    {
                        target->set_is_alive(false);
                    }
                
                }
                else
                {
                    healthAfterDmg = target->get_health() - attacker->get_damage();
                    target->set_health(healthAfterDmg);
                    std::cout << attacker->get_type() << " Delt: " << attacker->get_damage() << " damage to: " << target->get_type() << " Health remaining: "<< target->get_health()<< '\n';
                    if (target->get_health() <= 0)
                    {
                        target->set_is_alive(false);
                    }
                
                }

            }
        }
        else if (target->get_is_alive() == false)
        {
            target->death();
        }
    }

    void printInfo()
    {
        std::cout << " Type: " << get_type() << " | Health " << get_health() << " | Armor Type " << getArmorType(get_armorType())  << " | Armor " << get_armor() << " | Damage " << get_damage() << " | Cost " << get_moneyCost() << " | Mana " << get_mana() << " | Mana State " << (get_manaBool()? " True " : " False ") << " | Alive State " << get_is_alive() << std::endl;
    }

    virtual void death()
    {
        set_health(0);
        std::cout << get_type() << " died" << std::endl;
    }

    float get_health() { return m_health; }

    int get_armor() { return m_armor; }

    armorType get_armorType() {return m_armorType; }

    int get_damage() { return m_damage; }

    int get_moneyCost() { return m_moneyCost; }

    int get_mana() { return m_mana; }

    bool get_manaBool() { return m_manaBool; }

    std::string get_type() { return m_type; }

    bool get_is_alive() { return m_isAlive; }

protected:

    void set_type(std::string new_name) { this->m_type = new_name; }

    void set_health(float new_health) { this->m_health = new_health; }

    void set_mana(int new_mana) { this->m_mana = new_mana; }
    
    void set_manaBool(bool new_mana_state) { this->m_manaBool = new_mana_state; }
    
    void set_is_alive(bool state) { this->m_isAlive = state; }
    
    void set_armor(int armor) { this->m_armor = armor; }

    void set_armorType (armorType armorType) { this->m_armorType = armorType; }

private:
    std::string m_type;
    float m_health;
    int m_armor;
    enum armorType m_armorType;
    enum goodOrBad m_goodOrBad;
    int m_damage;
    int m_moneyCost;
    bool m_manaBool;
    int m_mana;
    bool m_isAlive;


};

#endif