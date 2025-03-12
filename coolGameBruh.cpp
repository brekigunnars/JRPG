#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream> 

void loadProgress(int &wins, int &losses) {
    std::ifstream file("progress.txt");
    if (file.is_open()) {
        file >> wins >> losses;
        file.close();
    } else {
        wins = 0;
        losses = 0;
    }
}

void saveProgress(int wins, int losses) {
    std::ofstream file("progress.txt");
    if (file.is_open()) {
        file << wins << " " << losses;
        file.close();
    }
}

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
    std::string backstory;
    bool stunned = false;
    bool specialUsed = false;

public:
    Character(std::string n, int h, int s, int atk, int def, std::string story)
        : name(n), health(h), maxHealth(h), stamina(s), maxStamina(s),
          attackPower(atk), defensePower(def), backstory(story) {}

    virtual ~Character() {} 
    int getStamina() { return stamina; }
    void setStamina(int value) { stamina = value; }
    int getAttackPower() { return attackPower; }
    void setAttackPower(int value) { attackPower = value; }
    bool isStunned() { return stunned; }
    void setStunned(bool status) { stunned = status; }
    bool hasUsedSpecial() { return specialUsed; }
    void setSpecialUsed() { specialUsed = true; }
    bool checkSpecialUsed() {return specialUsed; }
    virtual void useSpecialAbility(Character &opponent) = 0;

    void attack(Character &opponent) {
        int damage = (std::rand() % attackPower) + 10;
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
        if (reducedDamage < 1) reducedDamage = 1;
        health -= reducedDamage;
        if (health < 0) health = 0;
        std::cout << name << " took " << reducedDamage << " damage!\n";
    }

    void regenerateStamina() {
        stamina += 5;
        if (stamina > maxStamina) stamina = maxStamina;
    }

    void displayBackstory() {
        std::cout << "\n--- Backstory of " << name << " ---\n" << backstory << "\n\n";
    }

    void displayStatus() {
        std::cout << name << " | Health: " << health << " " << getBar(health, maxHealth)
                  << " | Stamina: " << stamina << " " << getBar(stamina, maxStamina) << "\n";
    }

    void displayCharacterTraits() {
        std::cout<< "You chose " << name << ", which begins with " << health << " health and takes " << attackPower << " damage when attacking.\n" << name << " also has a special ability which is a suprise!\n" ;
    };

    std::string getName() { return name; }
    int getHealth() { return health; }
    bool isAlive() { return health > 0; }
};

class Zombie : public Character {
public:
    Zombie(std::string playerName)
        : Character(playerName + " (Zombie)", 70, 50, 14, 9,
            "Once a noble warrior, now cursed to roam the earth.\n"
            "The zombie is neither alive nor dead, seeking revenge for its lost humanity.") {}

    void useSpecialAbility(Character &opponent) override {
        (void)opponent;
        if (hasUsedSpecial()) { std::cout << "Special ability already used!\n"; return; }
        setSpecialUsed();
        health = std::min(health + 20, maxHealth);
        std::cout << name << " uses **Undead Regeneration**, healing 20 HP!\n";
    }
};

class Alien : public Character {
public:
    Alien(std::string playerName)
        : Character(playerName + " (Alien)", 75, 50, 14, 7,
            "A mysterious visitor from a distant galaxy.\n"
            "This alien fights to prove its superiority over lesser beings.") {}

    void useSpecialAbility(Character &opponent) override {
        (void)opponent;
        if (hasUsedSpecial()) { std::cout << "Special ability already used!\n"; return; }
        setSpecialUsed();
        std::cout << name << " uses **Plasma Blast**, dealing 25 damage!\n";
        opponent.takeDamage(25);
    }
};

class Roman : public Character {
public:
    Roman(std::string playerName)
        : Character(playerName + " (Roman)", 80, 50, 12, 8,
            "A disciplined soldier from the mighty Roman Empire.\n"
            "Forged in battle, he fights for the eternal glory of Rome.") {}

    void useSpecialAbility(Character &opponent) override {
        (void)opponent;
        if (hasUsedSpecial()) { std::cout << "Special ability already used!\n"; return; }
        setSpecialUsed();
        std::cout << name << " uses **Shield Wall**, blocking all damage this turn!\n";
        defensePower += 999;
    }
};

class Spartan : public Character {
public:
    Spartan(std::string playerName)
        : Character(playerName + " (Spartan)", 90, 50, 11, 7,
            "A fearless warrior raised from birth to battle.\n"
            "The Spartan knows no fear—only victory or death!") {}

    void useSpecialAbility(Character &opponent) override {
        (void)opponent;
        if (hasUsedSpecial()) { std::cout << "Special ability already used!\n"; return; }
        setSpecialUsed();
        std::cout << name << " enters **Spartan Fury**! The next attack does DOUBLE DAMAGE!\n";
        attackPower *= 2;
    }
};

class DarthWader : public Character {
public:
    DarthWader(std::string playerName)
        : Character(playerName + " (Darth Wader)", 70, 50, 17, 4,
            "Once a great warrior, now consumed by the dark side.\n"
            "Darth Wader seeks total domination with his immense power.") {}

    void useSpecialAbility(Character &opponent) override {
        (void)opponent;
        if (hasUsedSpecial()) { std::cout << "Special ability already used!\n"; return; }
        setSpecialUsed();
        std::cout << name << " uses **Force Choke**, dealing 30 damage and stunning " << opponent.getName() << "!\n";
        opponent.takeDamage(30);
    }
};

class ObiWanKenobi : public Character {
public:
    ObiWanKenobi(std::string playerName)
        : Character(playerName + " (Obi-Wan Kenobi)", 95, 50, 12, 7,
            "A wise Jedi Knight, protector of peace in the galaxy.\n"
            "He uses the Force to defend the innocent against darkness.") {}

    void useSpecialAbility(Character &opponent) override {
        (void)opponent;
        if (hasUsedSpecial()) { std::cout << "Special ability already used!\n"; return; }
        setSpecialUsed();
        std::cout << name << " uses **Jedi Strike**, dealing 35 damage!\n";
        opponent.takeDamage(35);
    }
};

void battle(Character &player, Character &enemy) {
    while (player.isAlive() && enemy.isAlive()) {
        player.displayStatus();
        enemy.displayStatus();

        std::cout << "\n" << player.getName() << "'s turn!\n";
        if (!player.checkSpecialUsed()) { 
        std::cout << "1. Attack\n2. Defend (-10 Stamina)\n3. Use Special Ability (One-time use)\n";
        } else { 
            std::cout << "1. Attack\n2. Defend (-10 Stamina)\n";
        }

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            player.attack(enemy);
        } else if (choice == 2) {
            player.defend();
        } else if (choice == 3) {  
            player.useSpecialAbility(enemy);
        }

        if (!enemy.isAlive()) {
            std::cout << enemy.getName() << " has been defeated! " << player.getName() << " wins!\n";
            break;
        }

        std::cout << "\n" << enemy.getName() << "'s turn!\n";
        if (enemy.isStunned()) {
            std::cout << enemy.getName() << " is stunned and cannot attack!\n";
            enemy.setStunned(false);
        } else {
            int enemyChoice = std::rand() % 3;
            if (enemyChoice == 0) enemy.attack(player);
            else if (enemyChoice == 1) enemy.defend();
            else if (enemyChoice == 2) enemy.useSpecialAbility(player);
        }

        if (!player.isAlive()) {
            std::cout << player.getName() << " has been defeated! " << enemy.getName() << " wins!\n";
            break;
        }

        player.regenerateStamina();
        enemy.regenerateStamina();
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
}
int main() {
    std::srand(std::time(0));
    int wins = 0, losses = 0;
    loadProgress(wins, losses);
    bool playAgain = true;
    
    while (playAgain) {
    std::cout << "Choose your character (1-6):\n1. Zombie\n2. Alien\n3. Roman\n4. Spartan\n5. Darth Wader\n6. Obi-wan Kenobi\n";
    int choice;
    std::cin >> choice;

    std::cout << "Choose your opponent (1-6):\n";
    int opponentChoice;
    std::cin >> opponentChoice;

    Character *player;
    Character *enemy;
    clearScreen();
    std::cout << "🏆 **Total Wins:** " << wins << "   ❌ **Total Losses:** " << losses << "\n\n";

    std::cout << R"(
  ███████╗██╗ ██████╗ ██╗  ██╗████████╗    ██████╗ ███╗  ██╗
  ██╔════╝██║██╔════╝ ██║  ██║╚══██╔══╝   ██╔═══██╗████╗ ██║
  █████╗  ██║██║  ███╗███████║   ██║      ██║   ██║██╔██╗██║
  ██╔══╝  ██║██║   ██║██╔══██║   ██║      ██║   ██║██║╚████║
  ██║     ██║╚██████╔╝██║  ██║   ██║      ╚██████╔╝██║ ╚███║
  ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝       ╚═════╝ ╚═╝  ╚══╝
)" << std::endl;
    switch (choice) {
        case 1: player = new Zombie("Player"); break;
        case 2: player = new Alien("Player"); break;
        case 3: player = new Roman("Player"); break;
        case 4: player = new Spartan("Player"); break;
        case 5: player = new DarthWader("Player"); break;
        case 6: player = new ObiWanKenobi("Player"); break;
        default: std::cout << "Invalid choice! Defaulting to Zombie.\n"; player = new Zombie("Player"); break;
    }

    switch (opponentChoice) {
        case 1: enemy = new Zombie("Enemy"); break;
        case 2: enemy = new Alien("Enemy"); break;
        case 3: enemy = new Roman("Enemy"); break;
        case 4: enemy = new Spartan("Enemy"); break;
        case 5: enemy = new DarthWader("Enemy"); break;
        case 6: enemy = new ObiWanKenobi("Enemy"); break;
        default: std::cout << "Invalid choice! Defaulting to Alien.\n"; enemy = new Alien("Enemy"); break;
    }


    player->displayCharacterTraits();
    player->displayBackstory();
    enemy->displayBackstory();
    
    battle(*player, *enemy);

    if (player->isAlive()) {
            wins++; 
        } else {
            losses++;  
        }

        saveProgress(wins, losses);
    delete player;
    delete enemy;
    std::cout << R"(
  ██████╗  █████╗ ███╗   ███╗███████╗    ██████╗ ██╗   ██╗███████╗██████╗ 
 ██╔════╝ ██╔══██╗████╗ ████║██╔════╝   ██╔═══██╗██║   ██║██╔════╝██╔══██╗
 ██║  ███╗███████║██╔████╔██║█████╗     ██║   ██║██║   ██║█████╗  ██████╔╝
 ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝     ██║   ██║██║   ██║██╔══╝  ██╔══██╗
 ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗   ╚██████╔╝╚██████╔╝███████╗██║  ██║
  ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝    ╚═════╝  ╚═════╝ ╚══════╝╚═╝  ╚═╝
)" << std::endl;

    
    std::cout << "Would you like to play again? (y/n): ";
        char again;
        std::cin >> again;
        playAgain = (again == 'y' || again == 'Y');
    
    }
    std::cout << "Thanks for playing! 🏆 Wins: " << wins << " | ❌ Losses: " << losses << "\nGoodbye!\n";
    return 0;
}
