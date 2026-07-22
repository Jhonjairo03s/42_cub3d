/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
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

# include "../lib/mlx/mlx.h"
# include "structs.h"

# define BUFFER_SIZE 4096
# define RESX 1280
# define RESY 720

// Error Messages
// ----------------------------------------------------------------------------
# define ERROR_USAGE "./cub3D <maps/*name_map*.cub>\n"
# define ERROR_LENGTH "Minimum length 5 characters\n"
# define ERROR_EXTENSION "It must end in .cub\n"
# define ERROR_FD_OPEN "Error opening the file\n"
# define ERROR_FD_DIR_OPEN "It's a directory, not a map\n"
# define ERROR_TEXTURE "Error loading texture\n"
# define ERROR_RGB "RGB extraction error\n"
# define ERROR_RANGE_RGB "Out of RGB range [0-255]\n"
# define ERROR_COMMAS "Without commas in color extraction\n"
# define ERROR_NOT_PLAYER "Player not found\n"
# define ERROR_MULTI_PLAYER "Multiple players\n"
# define ERROR_LIMIT_FF "The map is open\n"
# define ERROR_SIZE_MAP "Empty map\n"
# define ERROR_INCOMPLETE_MAP "Incomplete map\n"
// ----------------------------------------------------------------------------

/*
 * src/init/
*/
void	init_game(t_game *game);
int		init_graphics(t_game *game);
int		init_player(t_game *game);
void	init_vector_n(t_game *game);
void	init_vector_s(t_game *game);
void	init_vector_e(t_game *game);
void	init_vector_w(t_game *game);

/*
 * src/parse/
*/
int		program_validation(int ac, const char *arg);
char	*scanning_and_extraction(t_game *game, const char *arg);
int		topology_and_map_memory(t_game *game, char *parser_tex_color);
char	*parser_map(const char *buf);
char	*master_cursor(char *cursor);
char	*parse_path(t_game *game, char *map);
int		parse_texture(t_game *game, char **cursor, t_img **tex);
int		parse_color(char **cursor, t_u32 *color);
int		ft_atoi_rgb(char **str);
int		parser_map_width(char *scout);
int		parser_map_height(char *scout);
t_u8	*map_measurement(char *map_start_cursor, t_game *game);
t_u8	*dump_and_fill(char *cursor, t_game *game);
int		iteractive_flood_fill(t_game *game);

/*
 * src/raycast/
*/
void	ray_init(t_game *game, t_ray *ray, int x);
void	ray_init_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_dist(t_ray *ray);

/*
 * src/render/
*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_wall_slice(t_game *game, t_ray *ray, int x);
void	render(t_game *game);
void	draw_background(t_game *game);
void	draw_fps(t_game *game);
char	*framecalc(t_game *game);
void	render_enemy(t_game *game);
void	update_enemy(t_game *game, long long elapsed);
t_img	*load_texture(void *mlx_ptr, char *path);
t_img	*select_texture(t_game *game, t_ray *ray);

/*
 * src/events/
*/
int		key_press_hook(int keycode, t_game *game);
int		key_release_hook(int keycode, t_game *game);
int		close_hook(t_game *game);
void	update_player(t_game *game, double delta_time);
void	rotate_player(t_game *game, double rot_speed);
int		mouse_cb(int x, int y, t_game *game);
int64_t	get_time_in_ms(void);

/*
 * src/utils/
*/
int		err_msg(const char *msg, char *str, int code);
int		free_and_return(t_u8 *map, t_point *stack, int code);
void	clean_exit(t_game *game);

/*
 * libft prototypes
*/
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t nbr);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t len);
char	*ft_itoa(int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
