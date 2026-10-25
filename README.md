# so_long

A small 2D game in C: collect every item on the map, then reach the exit in as few moves as possible.

## Build and run

```bash
make                     # requires X11 development headers (MiniLibX)
./so_long maps/test.ber
```

Maps are `.ber` text files: walls, floor, collectibles, exit and a player start. The program checks that a map is closed, rectangular and solvable before loading it.

## Technical points

- Rendering with MiniLibX only: images, window and input hooks, without any game library.
- Code organised like a small engine: a game loop (`tick_game`), scenes, rendering, inputs and a 2D vector type.
- Collisions with swept AABB tests, and a path search that rejects maps where the exit or an item cannot be reached.
- Error handling for invalid maps with explicit messages.

## What I learned

Structuring a C program of several thousand lines into modules, and managing a game loop with timing and input.
