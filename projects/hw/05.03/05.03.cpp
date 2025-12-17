#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>


class GameEntity
{
public:
    virtual ~GameEntity() = default;
    virtual void attack(GameEntity* target) = 0;
    virtual void takeDamage(int damage) = 0;
    virtual int getHealth() const = 0;
    virtual std::string getName() const = 0;
    virtual void display() const = 0;
};

class UnitGroup : public GameEntity
{
public:
    UnitGroup(const std::string& name) : m_name(name) {}

    void add(std::shared_ptr<GameEntity> entity)
    {
        m_entities.push_back(entity);
    }

    void remove(std::shared_ptr<GameEntity> entity)
    {
        m_entities.erase(
            std::remove(m_entities.begin(), m_entities.end(), entity),
            m_entities.end()
        );
    }

    void attack(GameEntity* target) override
    {
        for (auto& entity : m_entities)
        {
            if (entity->getHealth() > 0)
            {
                entity->attack(target);
            }
        }
    }

    void takeDamage(int damage) override
    {
        if (m_entities.empty())
        {
            return;
        }
        
        int damagePerUnit = damage / static_cast<int>(m_entities.size());
        int remainder = damage % static_cast<int>(m_entities.size());
        
        for (size_t i = 0; i < m_entities.size(); ++i)
        {
            int unitDamage = damagePerUnit + (i < static_cast<size_t>(remainder) ? 1 : 0);
            m_entities[i]->takeDamage(unitDamage);
        }
    }

    int getHealth() const override
    {
        int totalHealth = 0;
        for (const auto& entity : m_entities)
        {
            totalHealth += entity->getHealth();
        }
        return totalHealth;
    }

    std::string getName() const override { return m_name; }

    void display() const override
    {
        std::cout << "Group: " << m_name << " (Size: " << m_entities.size() 
                  << ", Health: " << getHealth() << ")\n";
        for (const auto& entity : m_entities)
        {
            std::cout << "  - ";
            entity->display();
        }
    }

    size_t size() const { return m_entities.size(); }

private:
    std::string m_name;
    std::vector<std::shared_ptr<GameEntity>> m_entities;
};


class GameUnit : public GameEntity
{
public:
    GameUnit(const std::string& name, int health, int damage, int defense)
        : m_level(1), m_name(name), m_health(health), m_maxHealth(health), m_damage(damage), m_defense(defense)
    {
    }

    void performAction(GameEntity* target)
    {
        if (!canAct())
        {
            return;
        }

        prepareAction();
        executeAction(target);
        finalizeAction();
    }

    void attack(GameEntity* target) override
    {
        performAction(target);
    }

    void takeDamage(int damage) override
    {
        int actualDamage = std::max(1, damage - m_defense);
        m_health = std::max(0, m_health - actualDamage);
        
        if (m_health == 0)
        {
            onDestroyed();
        }
    }

    int getHealth() const override { return m_health; }
    int getMaxHealth() const { return m_maxHealth; }
    int getDamage() const { return m_damage; }
    int getDefense() const { return m_defense; }
    int getLevel() const { return m_level; }
    std::string getName() const override { return m_name; }

    void display() const override
    {
        std::cout << m_name << " [HP: " << m_health << "/" << m_maxHealth 
                  << ", DMG: " << m_damage << ", DEF: " << m_defense 
                  << ", Level: " << m_level << "]\n";
    }

protected:
    virtual bool canAct() const { return m_health > 0; }
    virtual void prepareAction() {}
    virtual void executeAction(GameEntity* target)
    {
        if (target)
        {
            int damage = m_damage + m_level;
            target->takeDamage(damage);
        }
    }
    virtual void finalizeAction() {}
    virtual void onDestroyed() {}

    int m_level;

protected:
    std::string m_name;
    int m_health;
    int m_maxHealth;
    int m_damage;
    int m_defense;
};


class Soldier : public GameUnit
{
public:
    Soldier(const std::string& name, int health, int damage, int defense)
        : GameUnit(name, health, damage, defense)
    {
    }

protected:
    void prepareAction() override
    {
        std::cout << "soldier " << m_name << "is preparing for attack\n";
    }

    void executeAction(GameEntity* target) override
    {
        GameUnit::executeAction(target);
        m_level += 1;
    }
};

class Tank : public GameUnit
{
public:
    Tank(const std::string& name, int health, int damage, int defense)
        : GameUnit(name, health, damage, defense)
    {
    }

protected:
    void executeAction(GameEntity* target) override
    {
        if (dynamic_cast<UnitGroup*>(target))
        {
            int damage = (m_damage + m_level) * 2;
            target->takeDamage(damage);
        }
        else
        {
            GameUnit::executeAction(target);
        }
    }
};


class UnitBuilder
{
public:
    UnitBuilder() 
        : m_name("Unit"), m_health(100), m_damage(10), m_defense(5)
    {
    }

    UnitBuilder& name(const std::string& name)
    {
        m_name = name;
        return *this;
    }

    UnitBuilder& health(int health)
    {
        m_health = health;
        return *this;
    }

    UnitBuilder& damage(int damage)
    {
        m_damage = damage;
        return *this;
    }

    UnitBuilder& defense(int defense)
    {
        m_defense = defense;
        return *this;
    }

    std::shared_ptr<GameUnit> buildSoldier()
    {
        return std::make_shared<Soldier>(m_name, m_health, m_damage, m_defense);
    }

    std::shared_ptr<GameUnit> buildTank()
    {
        return std::make_shared<Tank>(
            m_name, m_health * 2, m_damage * 3, m_defense * 2
        );
    }

    std::shared_ptr<GameUnit> buildBasicUnit()
    {
        return std::make_shared<GameUnit>(m_name, m_health, m_damage, m_defense);
    }

    UnitBuilder& reset()
    {
        m_name = "Unit";
        m_health = 100;
        m_damage = 10;
        m_defense = 5;
        return *this;
    }

private:
    std::string m_name;
    int m_health;
    int m_damage;
    int m_defense;
};


int main()
{
    std::cout << "Game startedn\n";

    std::cout << "Creating Units...\n";
    UnitBuilder builder;
    
    auto soldier1 = builder.name("Captain Price")
                          .health(100)
                          .damage(20)
                          .defense(5)
                          .buildSoldier();

    auto tank1 = builder.reset()
                        .name("Challenger 2")
                        .health(300)
                        .damage(40)
                        .defense(15)
                        .buildTank();

    auto soldier2 = builder.reset()
                           .name("Lieutenant Soap")
                           .health(80)
                           .damage(15)
                           .defense(3)
                           .buildSoldier();

    auto tank2 = builder.reset()
                        .name("M1A2")
                        .health(350)
                        .damage(30)
                        .defense(12)
                        .buildTank();

    auto soldier3 = builder.reset()
                           .name("General Shepherd")
                           .health(90)
                           .damage(22)
                           .defense(4)
                           .buildSoldier();

    std::cout << "Creating Unit Groups\n";
    auto army1 = std::make_shared<UnitGroup>("First Army");
    army1->add(soldier1);
    army1->add(tank1);
    army1->add(soldier2);

    auto army2 = std::make_shared<UnitGroup>("Second Army");
    army2->add(tank2);
    army2->add(soldier3);

    std::cout << "Unit status: \n";
    army1->display();
    std::cout << "\n";
    army2->display();

    std::cout << "Before attack:\n";
    soldier3->display();
    tank1->display();

    soldier3->attack(tank1.get());
    
    std::cout << "\nAfter attack:\n";
    soldier3->display();
    tank1->display();

    std::cout << "Group Attack\n";
    std::cout << "Army 1 attacks Army 2:\n";
    army1->attack(army2.get());
    
    std::cout << "\nAfter group attack:\n";
    army2->display();

    std::cout << "Game is over\n";

    return 0;
}
