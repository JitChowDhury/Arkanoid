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

   Start → Init Window + Objects
      ↓
   Main Loop
      ↓
 ┌── Handle Events (input, quit, restart)
 │
 ├── Update (if playing)
 │     ├─ Move Paddle
 │     ├─ Update Ball
 │     │     ├─ Bounce walls/paddle
 │     │     ├─ Lose life if fall
 │     │     └─ Break bricks → Score++
 │     └─ Check win/loss conditions
 │
 └── Render (draw everything)
      ↓
     Loop back
```
