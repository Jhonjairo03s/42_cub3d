# Funciones de MLX42 para cub3D

Este documento detalla las funciones de la librería MLX42 que son útiles para el desarrollo del proyecto cub3D, divididas en las necesidades de un **Menú Principal** y el **Juego tipo Doom (Raycasting)**.

## 1. Gestión de Ventana e Inicio
Funciones básicas para levantar el entorno gráfico.

*   **`mlx_init(int32_t width, int32_t height, const char* title, bool resize)`**: Inicializa MLX42 y crea la ventana. Es el primer paso para cualquier aplicación.
*   **`mlx_loop(mlx_t* mlx)`**: Inicia el bucle principal de renderizado. No retorna hasta que se cierra la ventana.
*   **`mlx_terminate(mlx_t* mlx)`**: Limpia la memoria y cierra MLX42. Esencial para evitar fugas de memoria al salir.

---

## 2. Para el Menú Principal
El menú requiere interactividad con el ratón, carga de imágenes decorativas y renderizado de texto.

*   **`mlx_put_string(mlx_t* mlx, const char* str, int32_t x, int32_t y)`**: Dibuja texto en la pantalla. Útil para las opciones del menú ("Start", "Settings", "Exit").
*   **`mlx_load_png(const char* path)`** / **`mlx_load_xpm42(const char* path)`**: Carga imágenes desde archivos. Ideal para el fondo del menú o logos.
*   **`mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture)`**: Convierte una textura cargada en una imagen que se puede poner en la ventana.
*   **`mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y)`**: Dibuja la imagen en coordenadas específicas.
*   **`mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param)`**: Detecta clics del ratón. Permite ejecutar funciones cuando el usuario pulsa en una opción.
*   **`mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y)`**: Obtiene la posición actual del ratón. Útil para efectos de "hover" (cuando el cursor pasa por encima de un botón).

---

## 3. Para el Juego (Doom / Raycasting)
El juego requiere renderizado rápido píxel a píxel y un movimiento fluido del jugador.

*   **`mlx_new_image(mlx_t* mlx, uint32_t width, uint32_t height)`**: Crea un buffer de imagen vacío. Aquí es donde "pintarás" cada frame del raycasting.
*   **`mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)`**: Dibuja un píxel individual. Es la función principal para dibujar las paredes, el suelo y el techo.
*   **`mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param)`**: Ejecuta una función en cada frame. Aquí es donde debe ir la lógica de movimiento y el dibujado del mapa.
*   **`mlx_is_key_down(mlx_t* mlx, keys_t key)`**: Detecta si una tecla está pulsada en el momento actual. Permite un movimiento suave (WASD) sin el retardo de los eventos de teclado estándar.
*   **`mlx->delta_time`**: No es una función, sino una variable del struct `mlx`. Permite que el movimiento sea independiente de los FPS del ordenador.
*   **`mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode)`**: Puede ocultar el ratón (`MLX_MOUSE_DISABLED`) mientras juegas paraa que no estorbe en la vista.

---

## 4. Gestión de Texturas de Paredes
*   **`mlx_texture_t`**: Estructura que contiene los píxeles de una textura cargada. Accederás a `texture->pixels` para obtener los colores de las paredes durante el raycasting.
*   **`mlx_delete_texture(mlx_texture_t* texture)`**: Libera la memoria de una textura cuando ya no sea necesaria (al cerrar el juego o cambiar de nivel).

---

## Resumen de utilidad
| Función | Uso en Menú | Uso en Juego | Por qué es importante |
| :-----: | :---------: | :----------: | :-------------------: |
| `mlx_init` | ✅       |     ✅       | Necesaria para empezar. |
| `mlx_put_string` | ✅ | ❌ | Facilita mostrar texto sin imágenes. |
| `mlx_new_image` | ❌ | ✅ | Crea el lienzo para el raycasting. |
| `mlx_put_pixel` | ❌ | ✅ | Dibuja la vista 3D. |
| `mlx_loop_hook` | ✅ | ✅ | Corazón del juego (frames). |
| `mlx_is_key_down` | ❌ | ✅ | Movimiento fluido del jugador. |
| `mlx_mouse_hook` | ✅ | ❌ | Interactividad en el menú. |
| `mlx_load_png` | ✅ | ✅ | Carga texturas y arte. |

---

## 5. Optimización de Bajo Nivel (Super Eficiencia)
Si quieres el máximo rendimiento para tu motor de raycasting, puedes evitar llamar a `mlx_put_pixel` miles de veces por frame (lo cual tiene coste de llamadas a funciones y comprobaciones).

En su lugar, puedes manipular directamente el array de píxeles:

*   **Acceso Directo**: El buffer `image->pixels` es un `uint8_t*` que contiene datos **RGBA**.
*   **Aritmética de Píxeles**: Cada píxel ocupa 4 bytes. La fórmula para encontrar la posición exacta de un píxel `(x, y)` es:
    ```c
    int indice = (y * image->width + x) * 4;
    image->pixels[indice]     = r; // Rojo
    image->pixels[indice + 1] = g; // Verde
    image->pixels[indice + 2] = b; // Azul
    image->pixels[indice + 3] = a; // Alpha (transparencia)
    ```
*   **Truco de 32 bits**: Puedes castear el puntero a `uint32_t*` para escribir el color completo de un solo golpe, lo cual es mucho más rápido para la CPU:
    ```c
    uint32_t* buffer = (uint32_t*)image->pixels;
    buffer[y * image->width + x] = color;
    ```
    *Nota: Ten cuidado con el "endianness" (el orden de los bytes) dependiendo de si el color lo guardas como ARGB o RGBA.*

### ¿Por qué es más eficiente?
1.  **Eliminas el overhead**: No hay llamadas a funciones constantes.
2.  **Localidad de datos**: Al dibujar columnas (raycasting), puedes calcular el índice una vez e ir incrementándolo, lo que ayuda a la caché de la CPU.
3.  **Renderizado en un paso**: Solo cuando termina el loop del juego, MLX42 envía todo el buffer a la tarjeta gráfica de una vez.
