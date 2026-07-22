/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/21 19:58:11 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdint.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

//# include "minilibx-linux/mlx.h"
# include "MLX42/include/MLX42/MLX42.h"

# define BUFFER_SIZE 4096

// Error Messages
// ----------------------------------------------------------------------------
# define ERROR_USAGE "./cub3D <maps/*name_map*.cub>\n"
# define ERROR_LENGTH "Minimum length 5 characters\n"
# define ERROR_EXTENSION "It must end in .cub\n"
# define ERROR_FD_OPEN "opening the file\n"
# define ERROR_FD_DIR_OPEN "It's a directory, not a map\n"
# define ERROR_TEXTURE "loading texture\n"
# define ERROR_RGB "RGB extraction\n"
# define ERROR_RANGE_RGB "Out of RGB range [0-255]\n"
# define ERROR_COMMAS "Without commas, in the color extraction\n"
// # define ERROR_PARSER_MAP "loading file\n"
# define ERROR_NOT_PLAYER "Player not found\n"
# define ERROR_MULTI_PLAYER "Multiple players\n"
# define ERROR_LIMIT_FF "The map is open\n"
# define ERROR_SIZE_MAP "Empty map\n"
# define ERROR_INCOMPLETE_MAP "incomplete map\n"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
typedef uint8_t		t_u8;	// usigned char
typedef uint32_t	t_u32;	// usigned int
typedef int32_t		t_i32;	// int
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
typedef struct s_game
{
	// Punteros (8 bytes)
	/*
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_n;
	void	*img_s;
	void	*img_e;
	void	*img_w;
	t_u32	*tex_n;
	t_u32	*tex_s;
	t_u32	*tex_e;
	t_u32	*tex_w;
	*/
	mlx_t	*mlx;
	mlx_texture_t	*tex_n;
	mlx_texture_t	*tex_s;
	mlx_texture_t	*tex_e;
	mlx_texture_t	*tex_w;
	t_u8	*map;
	char	*raw_data;
	// Variables con coma flotante (8 bytes)
	double	player_x;
	double	player_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	// Enteros 32 bits (4 bytes)
	t_u32	floor_color;
	t_u32	ceil_color;
	t_i32	map_width;
	t_i32	map_height;
}	t_game;

typedef struct s_texture
{
	// Punteros (8 bytes)
	void	*img_ptr;
	t_u32	*pixels;
	// Enteros (4 bytes)
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_point
{
	// Enteros (4 bytes)
	int	x;
	int	y;
}	t_point;
// ----------------------------------------------------------------------------

/*
 * parser/
*/
// ----------------------------------------------------------------------------
char	*scanning_and_extraction(t_game *game, const char *arg);
int		topology_and_map_memory(t_game *game, char *parser_tex_color);
int		program_validation(int ac, const char *arg);
// ----------------------------------------------------------------------------

/*
 * utils/
*/
// ----------------------------------------------------------------------------
void	init_game(t_game *game);
int		err_msg(const char *msg, char *str, int code);
int		free_and_return(t_u8 *map, t_point *stack, int code);
void	clean_exit(t_game *game);
char	*parser_map(const char *buf);
char	*master_cursor(char *cursor);
char	*parse_path(t_game *game, char *map);
int		ft_atoi_rgb(char **str);
//int		parse_texture(t_game *game, char **cursor, t_u32 **tex, void **img);
int		parse_texture(char **cursor, mlx_texture_t **tex);
int		parse_color(char **cursor, t_u32 *color);
int		parser_map_width(char *scout);
int		parser_map_height(char *scout);
t_u8	*map_measurement(char *map_start_cursor, t_game *game);
t_u8	*dump_and_fill(char *cursor, t_game *game);
int		init_player(t_game *game);
void	init_vector_n(t_game *game);
void	init_vector_s(t_game *game);
void	init_vector_e(t_game *game);
void	init_vector_w(t_game *game);
int		iteractive_flood_fill(t_game *game);
// ----------------------------------------------------------------------------

/*
 * usage_mlx/
*/
// ----------------------------------------------------------------------------
//t_u32	*load_texture(t_game *game, char *path, void **save_img_ptr);
mlx_texture_t	*load_texture_agnostic(char *path);
// ----------------------------------------------------------------------------

/*
 * libft/ 
*/
// ----------------------------------------------------------------------------
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t nbr);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t len);
// ----------------------------------------------------------------------------

/*
 * debug
*/
void	debug_print_final_struct(t_game *game);

#endif
