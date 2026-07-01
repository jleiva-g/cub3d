*This project has been created as part of the 42 curriculum by jleiva-g, gregueir.*

# cub3D

## Description

**cub3D** is a raycasting engine written in C, inspired by the rendering technique used in early first-person games such as *Wolfenstein 3D*.

The goal of the project is to build, from scratch and without a game engine, a program that:

- Parses a custom map file (`.cub`) describing a maze made of walls, empty space, textures, floor/ceiling colors, and a player spawn point.
- Rigorously validates that map (closed perimeter, valid characters, exactly one player, correct texture/color declarations) and rejects anything malformed with a clear error message.
- Opens a graphical window (via **MiniLibX**) and renders, in real time, a first-person 3D-looking view of the map using raycasting: for every column of the screen, a ray is cast from the player into the map, its intersection with the nearest wall is found, and the wall is drawn with a height inversely proportional to its distance from the player, corrected for perspective (fish-eye) distortion.
- Lets the player move and look around smoothly inside the map, with different textures shown depending on which face of a wall (North, South, East, West) is being looked at.

Beyond the graphical result, the project is meant to build a solid understanding of raycasting algorithms and basic vector/trigonometry math, event-driven programming, strict parsing/error handling, and manual memory management in a long-running graphical program (no leaks, clean exit on error, `ESC`, or window close).

The **bonus part** extends the mandatory engine with a real-time **minimap**, **wall collisions** so the player cannot walk through walls, and additional visual features.

## Instructions

### Requirements

- A Unix-like OS (Linux or macOS)
- `gcc`/`cc` and `make`
- **MiniLibX** and its dependencies (on Linux: X11 headers, typically installed via `sudo apt-get install libxext-dev libbsd-dev`)

### Compilation

```bash
make
```

| Rule | Description |
|------|-------------|
| `make` / `make all` | Builds the mandatory part |
| `make bonus` | Builds the project including bonus features |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the executable |
| `make re` | `fclean` + `all` |

### Execution

```bash
./cub3D maps/map.cub
```

The program expects a single argument: the path to a valid `.cub` map file. Example maps are provided in the `maps/` directory.

### Controls

| Key | Action |
|-----|--------|
| `W` / `A` / `S` / `D` | Move forward / left / backward / right |
| `←` / `→` | Rotate camera left / right |
| Mouse | Rotate camera |
| `ESC` or window close button | Quit the program cleanly |

### Map file format (`.cub`)

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111111111
1000000000110001
1011000001110101
1001000000000001
1001000110000001
1000000010000001
1000000010000101
1111111111111111
```

- `NO` / `SO` / `WE` / `EA`: paths to the North/South/West/East wall textures
- `F`: floor color (RGB)
- `C`: ceiling color (RGB)
- `1`: wall — `0`: empty/walkable space
- `N` / `S` / `E` / `W`: player spawn position and initial facing direction

Any malformed map is rejected with an explicit error message and the program exits without crashing or leaking memory.

## Resources

### Classic references

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Permadi's Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [MiniLibX documentation (42 docs)](https://harm-smits.github.io/42docs/libs/minilibx)
- [DDA algorithm — Wikipedia](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- 42 Cub3D subject PDF (provided by the school)

### AI usage

AI assistance (e.g. ChatGPT/Claude) was used during this project for:

- **["Understanding the DDA raycasting algorithm"]** — used to get plain-language explanations of concepts from the subject/references above before implementing them manually.
- **["Debugging"]** — used to help interpret a `valgrind`/`gdb` output on our own code.
- **["Drafting this README"]** — used to generate and format documentation text, reviewed and edited by the team.

AI was **not** used for: Anything else. Really, its not rocket science.

## Authors

| Name |
|------|
| jleiva-g |
| gregueir |
