# FIGHT ON - Turn-Based Battle Game

## For Players

### Game Overview
FIGHT ON is a turn-based battle game where you select a character to duel against an opponent. Each character has unique stats and special abilities that can be used strategically during combat.

### How to Play
1. **Starting the Game**: Run the executable to start the game.
2. **Character Selection**: Choose from 6 unique character classes:
   - Zombie: Resilient fighter with health regeneration abilities
   - Alien: Offensive character with plasma weapons
   - Roman: Defensive soldier with exceptional shield capabilities
   - Spartan: High health warrior with devastating fury attacks
   - Darth Wader: Powerful dark warrior with force abilities
   - Obi-Wan Kenobi: Balanced Jedi with strong special attacks

3. **Opponent Selection**: Choose which character you want to face in battle.

4. **Combat System**:
   - Battles are turn-based - you attack, then your opponent attacks
   - Each turn you can:
     - **Attack**: Deal damage to your opponent
     - **Defend**: Reduce incoming damage (-10 Stamina)
     - **Use Special Ability**: Each character has one unique special ability that can only be used once per battle

5. **Battle UI**:
   - Health and stamina bars show your current status
   - The game displays detailed combat information
   - ASCII art enhances the battle experience

6. **Win Conditions**: Reduce your opponent's health to zero before they defeat you.

7. **Progress Tracking**: The game automatically saves your win/loss record between sessions.

### Character Abilities

| Character | Health | Attack | Defense | Special Ability |
|-----------|--------|--------|---------|----------------|
| Zombie | 70 | 14 | 9 | Undead Regeneration: Heals 20 HP |
| Alien | 75 | 14 | 7 | Plasma Blast: Deals 25 damage |
| Roman | 80 | 12 | 8 | Shield Wall: Blocks all damage for one turn |
| Spartan | 90 | 11 | 7 | Spartan Fury: Doubles attack damage |
| Darth Wader | 70 | 17 | 4 | Force Choke: Deals 30 damage and stuns opponent |
| Obi-Wan Kenobi | 95 | 12 | 7 | Jedi Strike: Deals 35 damage |

### Game Mechanics
- **Health**: Represents how much damage a character can take before being defeated
- **Stamina**: Energy used for special moves and defense (regenerates 5 points each turn)
- **Attack Power**: Determines base damage dealt to opponents
- **Defense Power**: Reduces incoming damage when defending
- **Special Abilities**: Powerful one-time-use moves unique to each character

### Tips
- Use your special ability at a strategic moment - it can only be used once per battle
- Defending can be crucial when low on health, but costs stamina
- Different characters have different strengths - experiment to find your favorite
- Your wins and losses are tracked across game sessions

## For Developers

### Code Structure

The game is built using C++ with an object-oriented approach, utilizing inheritance for character classes.

#### Core Components

1. **Character Class Hierarchy**:
   - `Character` (Base abstract class)
     - `Zombie` (Specialized character class)
     - `Alien` (Specialized character class)
     - `Roman` (Specialized character class)
     - `Spartan` (Specialized character class)
     - `DarthWader` (Specialized character class)
     - `ObiWanKenobi` (Specialized character class)

2. **Game Loop**: The main function handles character selection, battle setup, and play-again functionality.

3. **Battle System**: Implemented in the `battle()` function, managing turn-based combat between two characters.

4. **File I/O**: Uses `loadProgress()` and `saveProgress()` functions to maintain persistent win/loss records.

5. **Utility Functions**:
   - `getBar()`: Creates visual bars for health/stamina display
   - `clearScreen()`: Cross-platform screen clearing

### Implementation Details

#### Character Base Class
The `Character` class provides the foundation for all character types with:
- Base stats (health, stamina, attack, defense)
- Basic actions (attack, defend, take damage)
- Pure virtual function for special abilities
- Status tracking and display

#### Inheritance Structure
Each specialized character class inherits from the base `Character` class and implements its own unique special ability through polymorphism using the virtual function `useSpecialAbility()`.

#### Game State Management
The game implements simple persistence by storing win/loss records in a text file (`progress.txt`), allowing player progress to be maintained between game sessions.

#### Random Elements
Random damage calculation is implemented using `std::rand()` to create variability in combat outcomes.

#### UI Elements
The game uses text-based UI with simple ASCII art for the title and game-over screens.

### Extending the Game

Here are some suggestions for extending the game:

1. **Add New Character Classes**:
   - Create a new class that inherits from `Character`
   - Define unique stats and implement the `useSpecialAbility()` function
   - Add the new class to the character selection menu in `main()`

2. **Implement Additional Actions**:
   - Add new action types to the battle menu
   - Update the battle logic to handle the new action types

3. **Enhanced Combat Mechanics**:
   - Add critical hits or miss chances
   - Implement status effects (poison, burn, etc.)
   - Add elemental damage types and resistances

4. **Expand Game Progression**:
   - Add character leveling
   - Implement an equipment system
   - Create a campaign mode with multiple battles

5. **Improved UI**:
   - Add more detailed ASCII art
   - Implement color coding for different message types
   - Create animated battle sequences

### Compilation Instructions

To compile the game, use the provided Makefile:

```
make
```

This will generate the executable. Run the game using:

```
make run
```

### Technical Requirements

- C++ compiler with C++11 support
- Standard library dependencies only
- Works on Windows, Linux, and macOS
