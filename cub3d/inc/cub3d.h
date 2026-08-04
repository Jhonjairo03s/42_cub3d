/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/08/04 16:04:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/time.h>
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "structs.h"

// Game Configurations & Parameters
// ----------------------------------------------------------------------------
# define RESX 1280
# define RESY 720
# define FOV_SCALE 0.66
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0
# define BUFFER_SIZE 4096
// ----------------------------------------------------------------------------

// Error Messages
// ----------------------------------------------------------------------------
# define ERROR_USAGE "./cub3D <maps/*name_map*.cub>\n"
# define ERROR_LENGTH "Minimum length 5 characters\n"
# define ERROR_EXTENSION "It must end in .cub\n"
# define ERROR_FD_OPEN "opening the file\n"
# define ERROR_FD_DIR_OPEN "It's a directory, not a map\n"
# define ERROR_METADATA "Invalid character in the textures/colors section\n"
# define ERROR_IDENTIFIERS "The map does not include the 6 identifiers\n"
# define ERROR_TEXTURE "loading texture\n"
# define ERROR_RGB "RGB extraction\n"
# define ERROR_RANGE_RGB "Out of RGB range [0-255]\n"
# define ERROR_COMMAS "Without commas, in the color extraction\n"
# define ERROR_INIT_MAP "Beginning of the map contains an invalid character\n"
# define ERROR_NOT_PLAYER "Player not found\n"
# define ERROR_MULTI_PLAYER "Multiple players\n"
# define ERROR_LIMIT_FF "The map is open\n"
# define ERROR_SIZE_MAP "Empty map\n"
# define ERROR_INCOMPLETE_MAP "incomplete map\n"
// ----------------------------------------------------------------------------

/*
 * Init
*/
void			init_game(t_game *game);
t_i32			init_graphics(t_game *game);
t_i32			init_player(t_game *game);
void			set_player_direction(t_game *game, char dir);
void			init_vector_n(t_game *game);
void			init_vector_s(t_game *game);
void			init_vector_e(t_game *game);
void			init_vector_w(t_game *game);

/*
 * Parser
*/
t_i32			program_validation(t_i32 ac, const char *arg);
char			*scanning_and_extraction(t_game *game, const char *arg);
t_i32			topology_and_map_memory(t_game *game, char *parser_tex_color);
t_i32			check_global_closure(t_game *game);
char			*parser_map(const char *buf);
char			*master_cursor(char *cursor);
char			*parse_path(t_game *game, char *map);
t_i32			parse_texture(char **cursor, mlx_texture_t **tex);
t_i32			parse_color(char **cursor, t_u32 *color);
t_i32			ft_atoi_rgb(char **str);
t_i32			parser_map_width(char *scout);
t_i32			parser_map_height(char *scout);
t_u8			*map_measurement(char *map_start_cursor, t_game *game);
t_u8			*dump_and_fill(char *cursor, t_game *game);
t_i32			iteractive_flood_fill(t_game *game);

/*
 * MLX Usage & Textures
*/
mlx_texture_t	*load_texture_agnostic(char *path);

/*
 * Raycast & Render
*/
void			ray_init(t_game *game, t_ray *ray, t_i32 x);
void			ray_init_dist(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_dist(t_ray *ray);

void			my_mlx_pixel_put(mlx_image_t *img,
					t_i32 x, t_i32 y, t_u32 color);
void			draw_wall_slice(t_game *game, t_ray *ray, t_i32 x);
void			render(t_game *game);
mlx_texture_t	*select_texture(t_game *game, t_ray *ray);

/*
 * Events & Loop
*/
void			game_loop(void *param);
void			handle_keys(t_game *game);
void			close_callback(void *param);
void			update_player(t_game *game, double delta_time);
void			rotate_player(t_game *game, double rot_speed);

/*
 * Utils & Errors
*/
t_i32			err_msg(const char *msg, char *str, t_i32 code);
t_i32			free_and_return(t_u8 *map, t_point *stack, t_i32 code);
void			clean_exit(t_game *game);

/*
 * Libft prototypes
*/
size_t			ft_strlen(const char *str);
t_i32			ft_strcmp(const char *str1, const char *str2);
t_i32			ft_strncmp(const char *str1, const char *str2, size_t nbr);
char			*ft_strjoin(char *s1, char *s2);
void			*ft_memset(void *s, t_i32 c, size_t len);
char			*ft_strrchr(const char *str, t_i32 c);

#endif
