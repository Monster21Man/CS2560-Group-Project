# Reversi / Othello — C++ with SDL2

A fully graphical implementation of the classic strategy board game **Othello (Reversi)** written in C++ using SDL2 for rendering. Play as Black against an AI opponent in a clean, interactive 640×640 window.

---

## Gameplay

Othello is a two-player strategy game played on an 8×8 board. Players take turns placing discs — one player controls **Black**, the other **White**. When you place a disc, any of your opponent's discs that are sandwiched between your new disc and another of your discs (horizontally, vertically, or diagonally) are flipped to your color.

The game ends when neither player has a valid move. The player with the most discs on the board wins.

**In this implementation:** You play as **Black** (clicking the board), and an **AI** controls **White**.

---

## Project Structure

```
.
├── main.cpp          # Entry point, SDL2 game loop, rendering
├── Game.h / .cpp     # Game state management, turn switching, win conditions
├── Board.h / .cpp    # 8×8 grid logic, move validation, flip calculation
├── Player.h / .cpp   # Base player class
├── AIPlayer.h / .cpp # AI player (inherits Player, picks moves automatically)
├── Display.h / .cpp  # SDL2 rendering wrapper (window, renderer, shapes, text)
└── Makefile          # Build system using clang++ and Homebrew SDL2
```

---

## Dependencies

- **C++17** or later
- **clang++** (or adapt `CXX` in the Makefile for g++)
- **SDL2**
- **SDL2_ttf**
- **SDL2_image**

### Installing Dependencies (macOS via Homebrew)

```bash
brew install sdl2 sdl2_ttf sdl2_image
```

---

## Building

```bash
make
```

This compiles all `.cpp` files and links the SDL2 libraries automatically using `brew --prefix` to locate headers and libraries.

To clean build artifacts:

```bash
make clean
```

---

## Running

```bash
./main
```

A 640×640 window titled **"Reversi"** will open showing the game board.

---

## How to Play

1. **You are Black.** Click any valid square to place your disc.
2. After your move, the **AI (White)** will automatically respond.
3. If a player has no valid moves, their turn is skipped automatically.
4. The game ends when neither player can move. The player with more discs wins.

---

## Architecture Notes

| Class | Responsibility |
|-------|---------------|
| `Board` | Pure game logic — grid state, move validation, flip calculation |
| `Game` | Orchestrates turns, tracks current player, evaluates win conditions |
| `Player` | Abstract base with `getName()`, `getColor()`, virtual `getMove()` |
| `AIPlayer` | Extends `Player`, overrides `getMove()` to pick a valid move |
| `Display` | Thin SDL2 wrapper — handles window, renderer, drawing primitives and text |
| `main.cpp` | SDL2 event loop, renders board and pieces, wires human clicks to `Board::applyMove` |

---

## Known Limitations / Future Work

- The AI currently picks moves randomly from valid positions — a stronger minimax or heuristic strategy could be implemented in `AIPlayer::getMove()`
- No player-vs-player mode (currently hardcoded as Human vs AI)

---

## Team

CS2560 Group Project
