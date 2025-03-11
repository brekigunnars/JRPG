#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to display a bar for health/stamina
std::string getBar(int value, int maxValue, int length = 10) {
    int filled = (value * length) / maxValue;
    std::string bar = "[";
    for (int i = 0; i < length; i++) {
        bar += (i < filled) ? "#" : "-";
    }
    bar += "]";
    return bar;
}

class Character {
protected:
    std::string name;
    int health, maxHealth;
    int stamina, maxStamina;
    int attackPower;
    int defensePower;

public:
    Character(std::string n, int h, int s, int atk, int def)
        : name(n), health(h), maxHealth(h), stamina(s), maxStamina(s), attackPower(atk), defensePower(def) {}

    void attack(Character &opponent) {
        int damage = (std::rand() % attackPower) + 5;
        std::cout << name << " attacks " << opponent.getName() << " for " << damage << " damage!\n";
        opponent.takeDamage(damage);
    }

    void defend() {
        if (stamina >= 10) {
            stamina -= 10;
            std::cout << name << " defends! Damage will be reduced this turn.\n";
        } else {
            std::cout << name << " is too tired to defend!\n";
        }
    }

    void takeDamage(int damage) {
        int reducedDamage = (stamina >= 10) ? damage - defensePower : damage;
        if (reducedDamage < 1) reducedDamage = 1; // Ensure at least 1 damage
        health -= reducedDamage;
        if (health < 0) health = 0;
        std::cout << name << " took " << reducedDamage << " damage!\n";
    }

    void regenerateStamina() {
        stamina += 5;
        if (stamina > maxStamina) stamina = maxStamina;
    }

    void displayStatus() {
        std::cout << name << " | Health: " << health << " " << getBar(health, maxHealth)
                  << " | Stamina: " << stamina << " " << getBar(stamina, maxStamina) << "\n";
    }

    std::string getName() { return name; }
    int getHealth() { return health; }
    bool isAlive() { return health > 0; }
};

// Zombie class
class Zombie : public Character {
public:
    Zombie(std::string playerName) : Character("Zombie", 100, 50, 10, 5) {}
};

// Alien class
class Alien : public Character {
public:
    Alien(std::string playerName) : Character("Alien", 100, 50, 10, 5) {}
};

class Roman : public Character {
public:
    Roman(std::string playerName) : Character("Roman", 100, 50, 10, 5) {}
};

class Spartan : public Character {
    public: Spartan(std::string playername) : Character("Spartan", 100, 50, 10, 5) {}
};

class DarthWader : public Character {
    public: DarthWader(std::string playername) : Character("Darth Wader", 100, 50, 10, 5) {}
};

class ObiWanKenobi : public Character {
    public: ObiWanKenobi(std::string playername) : Character("Obi-wan Kenobi", 100, 50, 10, 5) {}

};






// Function to handle the battle
void battle(Character &player, Character &enemy) {
    std::cout << "\nA wild " << enemy.getName() << " appears!\n";

    while (player.isAlive() && enemy.isAlive()) {
        // Display health and stamina bars
        player.displayStatus();
        enemy.displayStatus();

        // Player's turn
        std::cout << "\n" << player.getName() << "'s turn!\n";
        std::cout << "1. Attack\n2. Defend (-10 Stamina)\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            player.attack(enemy);
        } else if (choice == 2) {
            player.defend();
        }

        if (!enemy.isAlive()) {
            std::cout << enemy.getName() << " has been defeated! " << player.getName() << " wins!\n";
            break;
        }

        // AI Enemy's Turn
        std::cout << "\n" << enemy.getName() << "'s turn!\n";
        if (std::rand() % 2 == 0 && enemy.getHealth() > 20) {
            enemy.attack(player);
        } else {
            enemy.defend();
        }

        if (!player.isAlive()) {
            std::cout << player.getName() << " has been defeated! " << enemy.getName() << " wins!\n";
            break;
        }

        // Regenerate stamina at the end of the turn
        player.regenerateStamina();
        enemy.regenerateStamina();
    }
}

// Main function
int main() {
    std::srand(std::time(0)); // Seed random number generator

    std::string playerName;
    
    // Player selects their name and character
    std::cout << "Please enter your name: ";
    std::cin >> playerName;
    std::cout << "Choose your character:\n1. Zombie\n2. Alien\n3. Roman\n4. Spartan\n5.Obi-wan Kenobi\n6. Darth Wader";
    int choice;
    std::cin >> choice;

    Character *player, *enemy;
    
    if (choice == 1) {
        player = new Zombie(playerName);
        enemy = new Alien("Evil Alien");
    }
    else if (choice == 2)
    {
        player = new Alien(playerName);
        enemy = new Zombie("Zombie");
    }
    else if (choice == 3)
    {
        player = new Roman(playerName);
        enemy = new Spartan("Spartan");
    }
    else if (choice == 4)
    {
        player = new Spartan(playerName);
        enemy = new Roman("Roman");
    }
    else if (choice == 5)
    {
        player = new ObiWanKenobi(playerName);
        enemy = new DarthWader("Darth Wader");
    }
    else{
        player = new DarthWader(playerName);
        enemy = new ObiWanKenobi("Obi-wan Kenobi");
    }
    
    battle(*player, *enemy);

    delete player;
    delete enemy;

    return 0;
}
