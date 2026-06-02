/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 23:59:32 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/01 12:03:39 by jhvalenc         ###   ########.fr       */
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

# define BUFFER_SIZE 4096

// Error Messages
# define ERROR_USAGE "./cub3D <maps/*name_map*.cub>\n"
# define ERROR_LENGTH "Minimum length 5 characters\n"
# define ERROR_EXTENSION "It must end in .cub\n"
# define ERROR_FD_OPEN "Error opening the file\n"
# define ERROR_FD_DIR_OPEN "It's a directory, not a map\n"

typedef uint8_t		t_u8;	// usigned char
typedef uint32_t	t_u32;	// usigned int
typedef int32_t		t_i32;	// int

typedef struct s_game
{
	// Punteros (8 bytes)
	void	*mlx_ptr;
	void	*win_ptr;
	t_u32	*tex_n;
	t_u32	*tex_s;
	t_u32	*tex_e;
	t_u32	*tex_w;
	t_u8	*map;
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

/*
 * utils/
*/
void	init_game(t_game *game);
int		err_msg(const char *msg, char *str, int code);
char	*parser_map(const char *buf);
char	*explore_map_north(char *map);
char	*explore_map_south(char *map);
char	*explore_map_east(char *map);
char	*explore_map_west(char *map);
char	*texture_extraction_north(char *extraction);
char	*texture_extraction_south(char *extraction);
char	*texture_extraction_east(char *extraction);
char	*texture_extraction_west(char *extraction);
char	*explore_map(char *map, const char *prefix);
char	*extract_texture_path(char *extraction);

/*
 * libft/ 
*/
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_strjoin(char *s1, char *s2);

#endif
