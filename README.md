# 🎮 Tetris Game — Console C++

> A fully playable Tetris clone built from scratch in C++ with a file-based login system.
> Built as the Programming Fundamentals final project at UET Lahore (Narowal Campus).

![Language](https://img.shields.io/badge/Language-C++-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Course](https://img.shields.io/badge/Course-Programming%20Fundamentals-purple)
![Status](https://img.shields.io/badge/Status-Completed-green)

---

## 🕹️ What is it?

A console-based Tetris game implemented entirely in C++ — no game engine, 
no external libraries, no shortcuts. Just raw logic, arrays, and the 
Windows console API.

Players sign up or sign in before playing. The game features real-time 
keyboard controls, collision detection, line clearing, and score tracking — 
all rendered in a Windows terminal.

---

## ✨ Features

- **Login System** — Sign Up / Sign In with persistent file-based storage
- **Real-time Controls** — Arrow keys for movement and rotation
- **Collision Detection** — Accurate block-to-block and boundary collision
- **Line Clearing** — Complete rows are cleared and points awarded
- **Speed Boost** — Hold DOWN arrow to accelerate block fall
- **Color-coded UI** — Console text colors for visual distinction
- **Score Tracking** — Points displayed live during gameplay
- **Game Over Detection** — Triggers when blocks reach the top

---

## 🏗️ Architecture

```
tetris-cpp/
├── main.cpp        # Complete integrated file (login + game)
├── Game.cpp        # Game engine (development version)
├── Login.cpp       # Login system (development version)
├── .gitignore      # Excludes runtime files (sign.txt)
└── README.md
```

---

## ⚙️ Technical Highlights

### Tetromino Encoding
Shapes are encoded as binary 3×3 maps (9 bits) stored as integers:
```cpp
int figures[16] = {56, 146, 56, 146, 58, 178, 184, 154, 
                   312, 210, 57, 150, 27, 27, 27, 27};
// 4 shapes × 4 orientations = 16 values
// Example: L-block = 010 010 110 = 150 in binary
```

### Collision Detection
```cpp
collision += playfield[offset + i%3 + i/3*size + size] 
           * ((figures[figure_number*4 + direction] & 1 << i) > 0);
```

### Real-time Input (Windows API)
```cpp
if ((GetKeyState(VK_RIGHT) & 0x8000) && (offset % size < size - 3))
    offset++;   // move right
if ((GetKeyState(VK_UP) & 0x8000) && key_delay == 0) {
    direction = (direction + 1) % 4;  // rotate
    key_delay = 2;
}
```

### File-based Login
```cpp
// Write username to file
nfile.open("sign.txt", ios::out);
nfile << user_name << endl;

// Read and match on sign in
while(getline(file, word)) { name[idx] = word; idx++; }
```

---

## 🚀 How to Run

### Prerequisites
- Windows OS (uses `windows.h`)
- C++ compiler: MinGW / DevC++ / Visual Studio

### Compile & Run
```bash
g++ main.cpp -o tetris
tetris.exe
```

Or open in DevC++ / Visual Studio and hit Run.

### Controls
| Key        | Action           |
|------------|------------------|
| ← Left     | Move left        |
| → Right    | Move right       |
| ↑ Up       | Rotate block     |
| ↓ Down     | Speed up fall    |
| ESC        | Quit game        |

---

## 📸 Screenshot

```
<<< Welcome To The Game >>>

<<<<>>>>
*                  *
*                  *
*    ***           *
*                  *
*         **       *
*       ***        *
********************
```

---

## 🧠 Concepts Applied

| Concept | Where used |
|---------|-----------|
| Arrays | Playfield grid, figure encoding |
| Bitwise Operations | Tetromino shape/orientation |
| File I/O (fstream) | Login persistence |
| Windows API | Console control, keyboard input |
| Collision Detection | Block movement validation |
| Modular Functions | play(), write(), read(), display() |
| Loops & Conditionals | Game loop, line clearing |

---

## 🔮 Future Improvements

- [ ] Graphical interface using SFML or SDL2
- [ ] High score leaderboard
- [ ] Multiple levels with increasing speed
- [ ] Sound effects
- [ ] Cross-platform support (remove windows.h dependency)
- [ ] Pause / resume functionality

---

## 👥 Team

| Name | Roll No |
|------|---------|
| M Ehtasham Ali | 572 |
| Jahanzaib | 558 |
| Haseeb Najam | 534 |
| Amna Tariq | 524 |
| Abid Shafique | 502 |

**Submitted to:** Sir Muzammil Yousaf & Mam Rabia Sana  
**Department:** Computer Science — UET Lahore (Narowal Campus)  
**Course:** Programming Fundamentals (PF) — Final Project

---

## 📄 License

MIT License — free to use, modify, and distribute.

---

*Built with curiosity, debugged with patience.*
