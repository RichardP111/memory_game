# 🧠 Arduino Memory Game

**Author:** Richard Pu  
**Course:** TEJ201-01 | Thornhill SS  
**Version:** Beta 1.7  

## 📖 Overview

This is an interactive Memory Game built on the Arduino platform. The game challenges players to memorize and repeat increasingly complex sequences of flashing lights. It features an LCD menu system, sound effects, and four distinct difficulty levels ranging from "Easy" to the near-impossible "Death Mode."

## 🎮 How to Play

1.  **Start Up:** Power on the Arduino. The LCD will display the intro screen.
2.  **Select Mode:** The game cycles through difficulty modes on the LCD screen. Press the **Main Switch** when your desired mode appears to select it.
3.  **The Game:**
    * Watch the LED sequence carefully.
    * Repeat the sequence by pressing the corresponding colored buttons.
    * If you get it right, the level increases, and a new light is added to the sequence.
    * If you press the wrong button or take too long (Timeout), you lose!
4.  **Winning:** Reach the target level for your chosen difficulty to win the game.

## 🕹️ Game Modes

| Mode | Flash Speed | Reaction Time | Win Level | Description |
| :--- | :--- | :--- | :--- | :--- |
| **EASY** | Slow | 5.0 Seconds | 5 | Perfect for beginners. |
| **MEDIUM** | Normal | 3.0 Seconds | 10 | The standard challenge. |
| **HARD** | Fast | 1.5 Seconds | 20 | For those with quick reflexes. |
| **DEATH** | Extreme | 1.0 Second | 20 | "U hacking?" - Near impossible speed. |

## 🛠️ Hardware Setup

### Components Required
* Arduino Uno (or compatible)
* 16x2 LCD Display with I2C Interface (`0x27`)
* 4x LEDs (Blue, Red, Green, Yellow/Gray)
* 5x Push Buttons (4 for colors, 1 for Main Select)
* Piezo Speaker/Buzzer
* Resistances & Wires

### 🔌 Pinout Configuration

| Component | Arduino Pin | Variable Name |
| :--- | :--- | :--- |
| **Speaker** | 3 | `speak` |
| **Blue LED** | 4 | `ledB` |
| **Red LED** | 5 | `ledR` |
| **Yellow/Gray LED** | 6 | `ledGY` |
| **Green LED** | 7 | `ledG` |
| **Blue Button** | 8 | `swtichB` |
| **Red Button** | 9 | `swtichR` |
| **Yellow/Gray Button** | 10 | `swtichGY` |
| **Green Button** | 2 | `swtichG` |
| **Main Select Switch** | 13 | `switchmain` |
| **LCD SDA/SCL** | A4/A5 | *I2C Bus* |

## 💻 Software & Libraries

To run this code, you must have the Arduino IDE installed along with the following library:

* **LiquidCrystal_I2C**

**Installation:**
1.  Open the Arduino IDE.
2.  Go to **Sketch** > **Include Library** > **Manage Libraries...**
3.  Search for `LiquidCrystal_I2C` and install it.
4.  Upload `UNIT_PROJECT.ino` to your board.

## 🎵 Features

* **Sound Effects:** Custom tones for winning a level, losing a game, and button feedback.
* **Death Mode Song:** A special melody plays only when beating the hardest difficulty.
* **Timeout System:** A countdown timer ensures players act quickly.
* **LCD Interface:** Provides real-time feedback on current levels and game status.

## 📜 Acknowledgements

Memory Game is made possible by open-source projects referenced in the [project documentation](https://docs.google.com/document/d/1chmq-w709f7BhciBZjUFDth4jQfBt6dHSzW_fdwIHU8/edit?usp=sharing).
