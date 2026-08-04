*This project has been created as part of the 42 curriculum by ppaula-s, jhvalenc.*

# cub3D - My first RayCaster with MLX42

## Description
cub3D is a 3D graphical representation of the inside of a maze from a first-person perspective, built using ray-casting principles pioneered by Wolfenstein 3D. The engine renders dynamic 3D wall projections, wall-directional textures (North, South, East, West), floor and ceiling colors, and real-time player navigation inside a 2D grid map.

---

## Instructions

### 1. Cloning & Submodules
This project depends on git submodules (MLX42 / GLFW). Make sure to initialize and fetch all submodules when cloning:

* **When cloning the repository for the first time**:
  ```bash
  git clone --recursive git@vogsphere.42urduliz.com:vogsphere/intra-uuid-740efe13-fdcb-4914-b672-576089b0e7db-7589591-jhvalenc
  ```
* **If you already cloned without submodules**:
  ```bash
  git submodule update --init --recursive
  ```

---

### 2. Compilation

* **Mandatory Project (`cub3D`)**:
  ```bash
  make
  ```
  *(or `make -C cub3d`)*

* **Bonus Project (`cub3D_bonus`)**:
  ```bash
  make bonus
  ```
  *(or `make -C cub3d_bonus`)*

* **Cleaning Build Files**:
  ```bash
  make clean   # Remove object files
  make fclean  # Remove object files and executables
  make re      # Rebuild completely from scratch
  ```

---

### 3. Execution
Run the program by passing a valid `.cub` scene description file as the first argument:

* **Mandatory**:
  ```bash
  ./cub3D maps/valid/prueba.cub
  ```
* **Bonus**:
  ```bash
  ./cub3D_bonus maps/valid/prueba.cub
  ```

---

### 4. Bonus Features
The bonus version (`cub3D_bonus`) extends the core engine with interactive features:

* **2D Overhead Minimap**: Real-time rendering of the 2D grid map with player position, orientation vector, and raycasting overlay in the top-left corner.
* **Mouse Look Camera**: Smooth 360° mouse-driven horizontal camera rotation.
* **Mouse Lock Toggle (`M` key)**: Lock/trap cursor inside the window for seamless FPS gameplay or unlock cursor to move outside the window.
* **Dynamic FPS Counter (`F3` key)**: Displays live frames-per-second performance metrics in the top-right corner, togglable on/off using the `F3` key.
* **Wall Collisions & Sliding**: Player collision detection preventing walking through walls.

---

### 5. Controls

| Control | Action |
| :--- | :--- |
| **W / S** | Move Forward / Backward |
| **A / D** | Strafe Left / Right |
| **Left / Right Arrows** | Rotate Camera View |
| **Mouse Motion** | Smooth Camera Rotation *(Bonus)* |
| **M** | Toggle Mouse Capture On/Off *(Bonus)* |
| **F3** | Toggle FPS Counter Display *(Bonus)* |
| **ESC / Window (X)** | Quit Program Cleanly |

---

## Resources
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [MLX42 Documentation](https://github.com/codam-coding-college/MLX42)
- Wolfenstein 3D Engine Architecture
- AI assistance was used for project structure refactoring and build automation validation.
