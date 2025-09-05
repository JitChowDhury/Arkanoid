# 🧱 Arkanoid (C++ & SFML)

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17+-00599C?logo=c%2B%2B&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/SFML-2.6.1-8CC445?logo=sfml&logoColor=white" alt="SFML">
  <img src="https://img.shields.io/badge/Game-Arcade-blue?logo=gamepad">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License">
</p>

---

## 🎮 Overview

A **classic Arkanoid/Breakout clone** built using **C++17** and **SFML**.  
Control the paddle, bounce the ball, and break all the bricks to win!

✨ Current Features Implemented:

- ✅ Paddle movement (smooth left & right)
- ✅ Ball physics (bouncing, velocity control)
- ✅ Paddle–ball collision with realistic angle reflection
- ✅ Wall & bottom collision detection
- ✅ Lives system (ball reset when lost, game over when lives = 0)
- ✅ Restart system (press `R` to reset game state)
- ✅ Score system (points for breaking bricks)

🚧 Planned Features:

- Multiple levels with increasing difficulty
- Power-ups (expand paddle, extra balls, etc.)
- Retro-inspired visuals & sound effects

---

## 📸 Screenshots

<p align="center">
  🚧 Coming Soon 🚧  
</p>

---

## 🛠️ Tech Stack

- **Language:** C++17
- **Library:** [SFML](https://www.sfml-dev.org/)
- **IDE:** Visual Studio / CLion

---

## 🔄 Game Flow

```mermaid
flowchart TD
    A[Start Game] --> B[Initialize Window, Paddle, Ball, Bricks]
    B --> C[Game Loop]

    C -->|Handle Input| D[Paddle Movement]
    C -->|Update| E[Ball Movement & Physics]
    C -->|Update| F[Collision Detection]
    F --> F1[Ball ↔ Walls]
    F --> F2[Ball ↔ Paddle]
    F --> F3[Ball ↔ Bricks → Score++]

    C -->|Check State| G{Lives > 0?}
    G -->|Yes| C
    G -->|No| H[Game Over Screen]

    H -->|Press R| A
```
