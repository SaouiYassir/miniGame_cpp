# 🎮 Mini Game C++  

A small 2D mini game built in **C++** using **SFML 2**, focused on smooth gameplay, animations, collisions, UI elements, and game states.

This project was created to improve game development skills in:
- Object-Oriented Programming (OOP)
- SFML graphics and audio
- Collision detection
- Sprite animation
- Game loop architecture
- Asset management

---

## ✨ Features

- 🎯 Smooth player movement
- 🏃 Running, crouching, sliding animations
- ❤️ Health bar / hearts system
- ⏱️ Timer system
- 🎵 Background music and sound effects
- 💥 Damage and game-over effects
- 🖼️ Multiple backgrounds
- 🧱 Clean `src` + `assets` project structure
- 🛠️ Easy build script

---

## 📁 Project Structure

```bash
miniGame_cpp/
│
├── assets/            # Images, sprites, sounds, fonts
│   ├── imgs/
│   ├── sounds/
│   └── fonts/
│
├── src/               # Game classes
│   ├── Game.hpp / .cpp
│   ├── Player.hpp / .cpp
│   ├── Obstacle.hpp / .cpp
│   ├── Heart.hpp / .cpp
│   ├── Timer.hpp / .cpp
│   └── ...
│
├── main.cpp
├── build.sh           # Build script
└── README.md
```

---

## 🎮 Controls

| Key | Action |
|---|---|
| `A / D` | Move left / right |
| `Space` | Jump |
| `C` | Crouch |
| `P` | Pause |
| `Esc` | Exit |

---

## ⚙️ Installation & Run

### 1) Clone the repository
```bash
git clone https://github.com/SaouiYassir/miniGame_cpp.git
cd miniGame_cpp
```

### 2) Build
```bash
chmod +x build.sh
./build.sh
```

### 3) Run
```bash
./game
```

---

## 🛠️ Requirements

Make sure you have:

- C++17 or newer
- SFML 2.5+
- g++
- Linux / macOS / Windows (MinGW)

### Ubuntu install
```bash
sudo apt install libsfml-dev
```

---

## 🧠 What I Learned

This project helped improve my understanding of:

- Game architecture
- Class separation
- Delta time movement
- Sprite sheets
- SFML event handling
- Resource loading
- GitHub collaboration workflow

---

## 👨‍💻 Authors

**Yassir Saoui**  
C++ / Game Development / SFML  

- GitHub: https://github.com/SaouiYassir
- LinkedIn : https://www.linkedin.com/in/yassir-saoui/

---

**Aymane Hamouch**  
C++ / Game Development / SFML  

- GitHub: https://github.com/aymanehamouch05
- LinkedIn : https://www.linkedin.com/in/hamouchaymane/

---

## ⭐ Support

If you like this project, give it a **star ⭐** and feel free to contribute.
