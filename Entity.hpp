#include <iostream>

enum armorType
{
    UNARMORED = 0,
    LEATHER = 25,
    MEDIUM =50,
    HEAVY= 75
};

enum goodOrBad
{
    GOOD,
    BAD
};

// virtual entity class
// identation

class Entity
{
public:
    // fast constructor to make
    Entity(std::string type, int health, armorType aType, int armor, goodOrBad gOb, int damage, int moneyCost, bool mana, bool isAlive)
    {
        this->m_type = type;
        this->m_health = health;
        this->m_armorType = aType;
        this->m_goodOrBad = gOb;
        this->m_armor = armor;
        this->m_damage = damage;
        this->m_moneyCost = moneyCost;
        this->m_mana = mana;
        this->m_isAlive = isAlive;
    }

    // Done but idk if logic is good may need further improvements
    virtual void Attack(Entity *attacker, Entity *target)
    {
        int healthAfterDmg;
        if (target->get_alive() == true && attacker->get_alive() == true)
        {

            if (attacker->get_damage() <= 0)
            {
                std::cout << "No Damage Delt!" << std::endl;
            }
            if (target->get_health() <= 0)
            {
                target->set_alive(false);
            }
            else
            {
                if(target->get_armor() > 0)
                {
                    healthAfterDmg = target->get_health() - static_cast<float>(attacker->get_damage() * target->get_armorType()/100 );
                    target->set_health(healthAfterDmg);
                    std::cout << attacker->get_type() << " Delt: " << healthAfterDmg << " damage to: " << target->get_type() << '\n';
                }
                else
                {
                    healthAfterDmg = target->get_health() - attacker->get_damage();
                    target->set_health(healthAfterDmg);
                    std::cout << attacker->get_type() << " Delt: " << healthAfterDmg << " damage to: " << target->get_type() << '\n';
                }

            }
        }
        else if (target->get_alive() == false)
        {
            death(target);
        }
    }

    void printInfo(Entity *e)
    {
        std::cout << " Type: " << e->get_type() << " Health " << e->get_health() << " Armor " << e->get_armor() << " Damage " << e->get_damage() << " Cost " << e->get_moneyCost() << " Alive State " << e->get_alive() << std::endl;
    }

    virtual void death(Entity *target)
    {
        target->set_health(0);
        std::cout << target->get_type() << " died" << std::endl;
    }

    int get_health() { return m_health; }

    void set_health(int new_health) { this->m_health = new_health; }

    int get_armor() { return m_armor; }

    int get_armorType() {return m_armorType; }

    int get_damage() { return m_damage; }

    int get_moneyCost() { return m_moneyCost; }

    std::string get_type() { return m_type; }

    bool get_alive() { return m_isAlive; }

    void set_alive(bool state) { this->m_isAlive = state; }

private:
    std::string m_type;
    int m_health;
    int m_armor;
    enum armorType m_armorType;
    enum goodOrBad m_goodOrBad;
    int m_damage;
    int m_moneyCost;
    bool m_mana;
    bool m_isAlive;
};
