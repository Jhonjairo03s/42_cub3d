*This project has been created as part of the 42 curriculum by ppaula-s, jhvalenc.*

# cub3D - My first RayCaster with miniLibX

## Description
cub3D is a 3D graphical representation of the inside of a maze from a first-person perspective, built using the ray-casting principles pioneered by Wolfenstein 3D. The engine renders dynamic 3D wall projections, textures depending on wall orientations (North, South, East, West), floor and ceiling colors, and player interaction inside a 2D map.

## Instructions

### Compilation
To compile the project on Linux, run:
```bash
make
```
This will compile `libft`, `miniLibX`, and generate the `cub3D` executable.

### Execution
Run the executable with a `.cub` scene description file:
```bash
./cub3D maps/valid/prueba.cub
```

### Controls
- **W / A / S / D**: Move forward, left, backward, right.
- **Left / Right Arrows**: Rotate the camera view.
- **Mouse**: Rotate camera view left or right.
- **ESC** or **Window Close (X)**: Quit the program cleanly.
- **F3**: Toggle FPS counter display.

## Resources
- Lode's Raycasting Tutorial (https://lodev.org/cgtutor/raycasting.html)
- MiniLibX Linux Documentation
- Wolfenstein 3D Engine Architecture
- AI assistance was used for project structure refactoring and build automation validation.
