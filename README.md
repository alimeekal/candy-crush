# Candy Crush — C++ Console Game

A terminal-based Candy Crush clone built in C++. Match candies on a colored console board, chain combos, and compete for the top 3 on the leaderboard.

---

## Features

- **Two difficulty modes** — Easy (8×8 board, 5 candy types) and Hard (10×10 board, 7 candy types)
- **Colored candy symbols** rendered using ANSI escape codes in the Windows console
- **Match detection** for horizontal, vertical, diagonal, and L-shape patterns
- **Cascading gravity** — destroyed candies are replaced from above, with chain reactions resolved automatically
- **Auto-reverse** — if a swap produces no match, it is undone and the move is not counted
- **60-second timer** with a 15-move limit per game
- **Persistent leaderboard** stored in `score_file.txt`, displaying the top 3 scores across all sessions

---

## Gameplay

Each turn, select a candy by entering its row and column, then choose a direction to swap it. If the swap creates a match of three or more, the candies are destroyed, the board refills from above, and any new matches are resolved automatically. If no match is formed, the move is reversed and not counted against you. The game ends when time runs out or all 15 moves are used.

---

## Controls

| Key | Action           |
|-----|------------------|
| `W` | Move candy up    |
| `S` | Move candy down  |
| `A` | Move candy left  |
| `D` | Move candy right |

---

## Scoring

| Match Type | Points |
|------------|--------|
| Horizontal | 10     |
| Vertical   | 10     |
| Diagonal   | 20     |
| L-shape    | 25     |

---

## Authors

- Bilal Mohsin & Ali Meekal
