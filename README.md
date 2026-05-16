# Dungeon Escape

A text-based dungeon crawler written in C++ for a Data Structures course.  
Every core data structure is implemented from scratch — no STL containers are used for the custom DS implementations.

---

## Table of Contents

1. [Game Summary](#1-game-summary)
2. [Genre and Influences](#2-genre-and-influences)
3. [What Makes It Interesting](#3-what-makes-it-interesting)
4. [Player Objective](#4-player-objective)
5. [Gameplay Mechanics](#5-gameplay-mechanics)
6. [Game Loop](#6-game-loop)
7. [System Design](#7-system-design)
8. [Data Structures Implemented](#8-data-structures-implemented)
9. [Algorithms Implemented](#9-algorithms-implemented)
10. [Big-O Runtime Analysis](#10-big-o-runtime-analysis)
11. [Input Validation](#11-input-validation)
12. [Building and Running](#12-building-and-running)
13. [Project Structure](#13-project-structure)
14. [Features Implemented](#14-features-implemented)
15. [Known Limitations and Future Work](#15-known-limitations-and-future-work)

---

## 1. Game Summary

**Dungeon Escape** is a text-based dungeon crawler programmed in C++. The player traverses a dungeon composed of rooms represented as an 8×8 grid (configurable). Each room is randomly assigned one of three types — enemy, item, or empty — and triggers a unique event when the player enters for the first time.

The player must navigate the dungeon, survive enemy encounters, collect items, and locate a randomly placed exit before their health runs out.

This project demonstrates how classic data structures and algorithms can be applied to a practical, interactive program rather than purely academic exercises. Every DS used — Stack, Queue, BST, Hash Table, Priority Queue — has a direct gameplay purpose.

---

## 2. Genre and Influences

- **Genre:** Text-based adventure / Dungeon crawler  
- **Subgenre:** Turn-based exploration

Inspired by older dungeon crawling games where the player moves through a dungeon one step at a time without knowledge of their surroundings. The goal was to build a simplified version of that concept using the fundamental data structures covered in class, making each DS choice justify itself through actual gameplay behavior rather than existing just to satisfy a requirement.

---

## 3. What Makes It Interesting

- **Random map generation** — unique dungeon layout every playthrough
- **Random exit placement** — the exit spawns at a random cell (never at the start), so the player cannot memorize a route
- **Three room types** — empty, enemy, and item rooms each produce different gameplay outcomes
- **Scaling difficulty** — enemy attack power increases based on how far the player has traveled (`difficulty = x + y`), making deeper rooms progressively more dangerous
- **Multiple player choices** — move, view inventory, undo last move, quit
- **Item effects** — items loaded from a file and each has a direct gameplay effect (heal, attack boost)
- **Shortest path display** — Dijkstra's algorithm runs every turn and shows the player how many steps they are from the exit
- **Visited room tracking** — explored rooms are marked on the map, helping the player navigate
- **Play again loop** — after a win or loss the player is offered a fresh run with a newly generated dungeon

---

## 4. Player Objective

**Objective:** Reach the exit (`E` on the map).

- Explore the randomly generated dungeon
- Defeat or flee from enemies
- Collect items to increase survivability
- Use the step counter (Dijkstra) to navigate toward the exit

| Condition | Result |
|-----------|--------|
| Player health ≤ 0 | **GAME OVER** |
| Player reaches exit cell | **YOU ESCAPED** |

---

## 5. Gameplay Mechanics

### Movement

| Key | Direction |
|-----|-----------|
| `W` | North (up) |
| `S` | South (down) |
| `A` | West (left) |
| `D` | East (right) |
| `U` | Undo last move |
| `I` | View inventory |
| `Q` | Quit game |

Movement is bounded by the map dimensions. The player cannot move outside the grid.

---

### Map Display

```
  . . . . . . . .
  * P . . . . . .
  * * . . . . . .
  . . . . . . . .
  . . . . . E . .
  . . . . . . . .
  . . . . . . . .
  . . . . . . . .
```

| Symbol | Meaning |
|--------|---------|
| `P` | Player (current position) |
| `E` | Exit |
| `*` | Visited room |
| `.` | Unexplored room |

---

### Room Events

Each room triggers its event exactly once (controlled by a `visited` flag). Revisiting a room produces no effect.

| Room Type | Event |
|-----------|-------|
| **Empty** | "You step into a quiet corridor. Nothing here." |
| **Item**  | Random item from `items.txt` is awarded; item effect applied immediately |
| **Enemy** | Enemy spawns; combat begins |

---

### Item System

Items are loaded at startup from `data/items.txt` using `<fstream>` and stored in a Hash Table for O(1) lookup.

**`data/items.txt` format:**
```
Sword 15
Shield 10
Potion 30
Magic_Staff 20
Axe 25
```

Each item has a direct gameplay effect when picked up:

| Item | Effect |
|------|--------|
| Potion | +15 HP |
| Sword | +5 ATK |
| Axe | +8 ATK |
| Shield / Magic_Staff | Added to inventory (no stat change) |

---

### Enemy System

Enemies are randomly selected from three types when the player enters an enemy room:

| Enemy | Base HP | Base ATK |
|-------|---------|----------|
| Goblin | 20 | 12 |
| Orc | 30 | 18 |
| Skeleton | 15 | 10 |

**Difficulty scaling:** `enemy.attack = baseAttack + (player.x + player.y)`  
Enemies hit harder the deeper into the dungeon the player travels.

---

### Combat System

Combat is turn-based. Each round the player chooses:

```
  1. Attack   2. Run
```

- **Attack** — player deals their current ATK to the enemy; enemy counter-attacks
- **Run** — combat ends, player escapes without consequence
- **Critical Hit** — 20% chance (1-in-5) the enemy deals double damage
- **On kill** — player ATK permanently increases by +2

HP bars are displayed for both the player and the enemy each round:
```
  Your HP  : [████████░░] 80/100  ATK:15
  Goblin HP: [████░░░░░░] 8/20
```

---

### Inventory System (BST)

All collected items are stored in a Binary Search Tree sorted by item value. Pressing `I` displays the inventory in ascending order using an in-order traversal.

---

### Undo System (Stack)

Before every move, the player's current position is pushed onto a linked-list stack. Pressing `U` pops the top position and restores the player to their previous location.

---

## 6. Game Loop

```
Start Game
    │
    ▼
Clear Screen
    │
    ▼
Render HUD + Map + Menu
    │
    ▼
Trigger Current Room Event (first visit only)
    │
    ▼
Check Win / Lose Conditions
    │          │
  Win        Lose
    │          │
    └────┬─────┘
         │
         ▼
    Read Player Input
         │
    ┌────┴────────────────────┐
    │                         │
  W/A/S/D                  U / I / Q
    │                         │
    ▼                         ▼
Push position to Stack    Handle command
Move player               (continue loop)
    │
    ▼
Repeat Loop
```

---

## 7. System Design

### Class Overview

| Class | File | Responsibility |
|-------|------|----------------|
| `Player` | `core/Player` | Position, movement, HP, ATK, bounds checking |
| `Map` | `core/Map` | 2D grid of Rooms, random exit placement, room access |
| `Room` | `core/Room` | Room type, visited flag, event dispatch |
| `Item` | `core/Item` | Item name and value |
| `Enemy` | `core/Enemy` | Enemy name, HP, ATK, combat methods |
| `BST` | `ds/BST` | Inventory stored as a Binary Search Tree |
| `HashTable` | `ds/HashTable` | Item pool stored with chaining |
| `Stack` | `ds/Stack` | Linked-list LIFO for undo system |
| `Queue` | `ds/Queue` | Linked-list FIFO for turn ordering |
| `MergeSort` | `ds/MergeSort` | Sorts items by value |
| `Dijkstra` | `systems/Dijkstra` | Finds shortest path from player to exit |
| `ItemLoader` | `systems/ItemLoader` | Parses `items.txt` into `vector<Item>` |
| `Display` | `systems/Display` | All terminal output (HUD, map, menus) |

Each class has its own `.h` header and `.cpp` implementation file.

---

## 8. Data Structures Implemented

All custom data structures are built from scratch using linked lists or arrays — no `<stack>`, `<queue>`, or similar STL containers were used for DS implementations.

---

### Stack — Undo System

**Application:** Stores the player's previous positions so moves can be undone.

**Justification:** A stack's LIFO (Last In, First Out) property perfectly mirrors the undo behavior. The most recent move is always the first one to be undone. Using any other structure (e.g., a queue) would undo moves in the wrong order.

**Implementation:** Singly linked list. Each node holds `(x, y)` coordinates. `push()` prepends a new node; `pop()` removes and frees the head node.

---

### Queue — Turn Order System

**Application:** Models turn order between the player and enemy during combat setup.

**Justification:** A queue's FIFO (First In, First Out) property correctly models the concept of taking turns in order. Whoever is added to the queue first acts first — this is the natural turn-order behavior.

**Implementation:** Singly linked list with `head` (front) and `tail` (back) pointers. `push()` appends to the tail; `pop()` removes from the head.

---

### Binary Search Tree (BST) — Inventory

**Application:** Stores all items the player has collected throughout the run.

**Justification:** A BST keeps items sorted by value automatically during insertion. Displaying the inventory in sorted order requires only a simple in-order traversal — no extra sorting step needed. Insertion and traversal are both O(log n) average, which is efficient for a collection that grows incrementally.

**Implementation:** Each node holds an `Item`. Smaller values go left, larger/equal values go right. In-order traversal prints items from lowest to highest value.

---

### Hash Table — Item Pool

**Application:** Stores all possible items loaded from `items.txt` for fast lookup by name.

**Justification:** A hash table provides O(1) average-case lookup, which is ideal for retrieving a specific item by name during gameplay. Compared to a linear scan (O(n)) or BST (O(log n)), the hash table is the fastest option for key-based access.

**Implementation:** Chaining with `vector<vector<Item>>` (10 buckets). Hash function sums ASCII values of the key characters and mods by bucket count.

---

### Priority Queue (Max-Heap) — Attack Priority

**Application:** Determines which combatant attacks first based on their attack stat.

**Justification:** A heap allows the highest-priority element (highest ATK) to be extracted in O(log n) time. This is more efficient than sorting the combatants each round and correctly models the concept of the strongest combatant striking first.

**Implementation:** Uses `std::priority_queue` (explicitly allowed for this use case as the standard max-heap implementation).

---

## 9. Algorithms Implemented

### Merge Sort

**Application:** Sorts the item pool by value (ascending) after loading from file.

**How it works:**
1. Recursively split the item vector into halves until each sub-array has one element
2. Merge adjacent sub-arrays back together in sorted order (compare by `item.getValue()`)
3. Repeat until the full array is sorted

**Justification:** Merge Sort has a guaranteed O(n log n) time complexity in all cases, making it more reliable than Quick Sort (which degrades to O(n²) in the worst case). It is well-suited for sorting the item pool at game startup.

---

### Dijkstra's Shortest Path

**Application:** Calculates the minimum number of steps from the player's current position to the exit, displayed in the HUD each turn.

**How it works:**
1. Represent each grid cell as a node; each adjacent cell is a neighbor with edge weight = 1
2. Initialize distance to all cells as `INT_MAX` except the start cell (distance = 0)
3. Use a min-heap priority queue to always expand the nearest unvisited node
4. Return the distance to the exit cell when reached

**Justification:** Dijkstra's algorithm efficiently finds the shortest path in a weighted graph. On a uniform-cost grid (all edges = 1), it is optimal and guarantees the true minimum step count to the exit. This gives the player meaningful navigation information without revealing the full map.

---

## 10. Big-O Runtime Analysis

| Data Structure | Operation | Time Complexity |
|----------------|-----------|-----------------|
| Stack | push / pop | O(1) |
| Queue | enqueue / dequeue | O(1) |
| BST | insert / in-order display | O(log n) average |
| Hash Table | insert / lookup | O(1) average |
| Heap (Priority Queue) | insert / extract-max | O(log n) |
| Merge Sort | sort items | O(n log n) |
| Dijkstra | find shortest path | O((V + E) log V) |

> On an 8×8 grid: V = 64 cells, E ≤ 256 edges. Dijkstra runs in effectively constant time at this scale.

---

## 11. Input Validation

All player input is read as `std::string` rather than `int` or `char` directly. This prevents `std::cin` from entering a fail state when the user types unexpected characters, which would cause an infinite loop in earlier versions.

Validation applied:

- **Empty input guard** — `input.empty()` is checked before accessing `input[0]`
- **Command parsing** — only `W`, `A`, `S`, `D`, `U`, `I`, `Q` are accepted; all other input prints an error and re-prompts
- **Combat input** — read as string, first character converted to int; non-numeric input is caught and re-prompted
- **Play again prompt** — empty check before `again[0]` to prevent crash on EOF

---

## 12. Building and Running

### Requirements

- `g++` with C++11 support
- macOS or Linux terminal (ANSI color codes required)

### Using Make (recommended)

```bash
make          # compile
make run      # compile and launch
make clean    # remove compiled binary
```

### Manual compile

```bash
g++ -std=c++11 -o game \
  src/main.cpp \
  src/core/Player.cpp \
  src/core/Enemy.cpp \
  src/core/Item.cpp \
  src/core/Room.cpp \
  src/core/Map.cpp \
  src/ds/Stack.cpp \
  src/ds/Queue.cpp \
  src/ds/HashTable.cpp \
  src/ds/BST.cpp \
  src/ds/MergeSort.cpp \
  src/systems/ItemLoader.cpp \
  src/systems/Dijkstra.cpp \
  src/systems/Display.cpp
```

### Run

```bash
./game
```

> **Note:** Run from the project root directory so `data/items.txt` is found correctly.

---

## 13. Project Structure

```
Dungeon-Escape/
├── Makefile
├── README.md
├── .gitignore
│
├── data/
│   └── items.txt              # Item definitions (name + value)
│
└── src/
    ├── main.cpp               # Entry point, game loop, play-again logic
    │
    ├── core/                  # Game objects
    │   ├── Player.h / .cpp    # Position, movement, HP, ATK
    │   ├── Enemy.h  / .cpp    # Enemy stats and combat methods
    │   ├── Item.h   / .cpp    # Item data (name, value)
    │   ├── Room.h   / .cpp    # Room type, visited flag, event logic
    │   └── Map.h    / .cpp    # 2D grid, random exit, room access
    │
    ├── ds/                    # Data structures (all built from scratch)
    │   ├── Stack.h    / .cpp  # Linked-list LIFO — undo system
    │   ├── Queue.h    / .cpp  # Linked-list FIFO — turn order
    │   ├── HashTable.h/ .cpp  # Chaining hash table — item pool
    │   ├── BST.h      / .cpp  # Binary search tree — inventory
    │   └── MergeSort.h/ .cpp  # Merge sort — sort items by value
    │
    ├── systems/               # Game systems
    │   ├── Dijkstra.h  / .cpp # Shortest path to exit (Dijkstra)
    │   ├── ItemLoader.h/ .cpp # Load items.txt into vector<Item>
    │   └── Display.h   / .cpp # All terminal output (HUD, map, menus)
    │
    └── utils/                 # Shared utilities
        ├── Colors.h           # ANSI color/style escape codes
        └── Helpers.h          # Shared inline functions (printBar)
```

---

## 14. Features Implemented

- [x] Player movement (W/A/S/D) with boundary enforcement
- [x] Dynamic map generation (configurable size via `MAP_ROWS` / `MAP_COLS`)
- [x] Random room type assignment (empty, enemy, item)
- [x] Random exit placement (never at start position)
- [x] Visited room tracking and map display (`*` for explored cells)
- [x] Room events (triggered once per room via visited flag)
- [x] Item system — items loaded from `data/items.txt` using `<fstream>`
- [x] Item effects (Potion: +HP, Sword/Axe: +ATK)
- [x] Hash Table — stores item pool with chaining, O(1) average lookup
- [x] Inventory (BST) — sorted by value, displayed with in-order traversal
- [x] Enemy system — three enemy types with randomized spawning
- [x] Difficulty scaling — enemy ATK increases with player's grid depth
- [x] Turn-based combat — attack or run, with combat HP bars
- [x] Critical hit system — 20% chance of double enemy damage
- [x] Progression system — player ATK permanently +2 on every kill
- [x] Turn order Queue — FIFO linked-list queue
- [x] Attack priority — max-heap Priority Queue
- [x] Merge Sort — sorts item pool by value at startup
- [x] Dijkstra's algorithm — step count to exit shown in HUD every turn
- [x] Undo system (Stack) — LIFO linked-list stack, press `U` to undo
- [x] ANSI color UI — red for damage, green for pickups/kills, cyan for HUD
- [x] HP bars — visual progress bars for player and enemy during combat
- [x] Play again loop — fresh dungeon generated on each new run
- [x] Input validation — all input read as string, empty/invalid input handled safely

---

## 15. Known Limitations and Future Work

| Area | Notes |
|------|-------|
| Save / Load | No persistence between sessions; each run starts fresh |
| Enemy variety | Only three enemy types; more could be added with unique abilities |
| Combat depth | No magic, status effects, or multi-target attacks |
| Map visualization | Terminal rendering only; no graphical interface |
| Leaderboard | No score tracking or high-score persistence across runs |
| Pathfinding | Dijkstra recomputes from scratch every turn; could cache when map state hasn't changed |
