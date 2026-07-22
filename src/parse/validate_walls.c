/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:58:40 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/22 15:45:00 by ppaula-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	program_validation(int ac, const char *arg)
{
	size_t	len;
	int		fd;
	int		fd_dir;

	if (ac != 2)
		return (err_msg("Usage", ERROR_USAGE, -1));
	len = ft_strlen(arg);
	if (len < 5)
		return (err_msg("Length", ERROR_LENGTH, -1));
	if (ft_strcmp(arg + (len - 4), ".cub") != 0)
		return (err_msg("Extension", ERROR_EXTENSION, -1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg("fd open", ERROR_FD_OPEN, -1));
	fd_dir = open(arg, O_RDONLY | O_DIRECTORY);
	if (fd_dir != -1)
	{
		close(fd_dir);
		close(fd);
		return (err_msg("fd open dir", ERROR_FD_DIR_OPEN, -1));
	}
	close(fd);
	return (0);
}

static t_u8	*dump_machine(char *src, t_game *game)
{
	int	index;
	int	x;
	int	y;

	index = 0;
	x = 0;
	y = 0;
	while (*src != '\0' && y < game->map_height)
	{
		if (*src == '1' || *src == '0' || *src == 'N' || *src == 'S'
			|| *src == 'E' || *src == 'W' || *src == ' ' || *src == '\t')
		{
			index = (y * game->map_width) + x;
			game->map[index] = *src;
			x++;
		}
		if (*src == '\n')
		{
			y++;
			x = 0;
		}
		src++;
	}
	return (game->map);
}

t_u8	*dump_and_fill(char *cursor, t_game *game)
{
	char	*src;
	t_u8	*map_fill;

	src = cursor;
	while (*src == '\n')
		src++;
	map_fill = dump_machine(src, game);
	return (map_fill);
}

int	topology_and_map_memory(t_game *game, char *parser_tex_color)
{
	int	player;

	if (map_measurement(parser_tex_color, game) == NULL)
		return (-1);
	if (dump_and_fill(parser_tex_color, game) == NULL)
		return (-1);
	player = init_player(game);
	if (player != 0)
		return (-1);
	return (0);
}

static t_u8	*ft_memcpy_u8(t_u8 *s1, t_u8 *s2, int len)
{
	t_u8	*start_s1;
	int		index;

	start_s1 = s1;
	index = 0;
	while (index < len)
	{
		s1[index] = s2[index];
		index++;
	}
	return (start_s1);
}

static int	validate_and_fill(t_game *game, t_u8 *map, int x, int y)
{
	int	index;

	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (-1);
	index = (y * game->map_width + x);
	if (map[index] == '1' || map[index] == 'V')
		return (0);
	if (map[index] == ' ')
		return (-1);
	map[index] = 'V';
	return (1);
}

static void	paint_and_expand(t_point *stack, int *s_size, int x, int y)
{
	stack[*s_size].x = x;
	stack[*s_size].y = y - 1;
	(*s_size)++;
	stack[*s_size].x = x;
	stack[*s_size].y = y + 1;
	(*s_size)++;
	stack[*s_size].x = x + 1;
	stack[*s_size].y = y;
	(*s_size)++;
	stack[*s_size].x = x - 1;
	stack[*s_size].y = y;
	(*s_size)++;
}

static int	run_flood_fill(t_game *game, t_u8 *map_clone, t_point *stack)
{
	int	s_size;
	int	x;
	int	y;
	int	status;

	s_size = 0;
	stack[s_size].x = (int)game->player_x;
	stack[s_size++].y = (int)game->player_y;
	while (s_size > 0)
	{
		s_size--;
		x = stack[s_size].x;
		y = stack[s_size].y;
		status = validate_and_fill(game, map_clone, x, y);
		if (status == -1)
			return (err_msg("Limit flood fill", ERROR_LIMIT_FF, -1));
		if (status == 1)
			paint_and_expand(stack, &s_size, x, y);
	}
	return (0);
}

int	iteractive_flood_fill(t_game *game)
{
	t_u8	*map_clone;
	t_point	*stack;
	int		ret;

	map_clone = malloc(sizeof(t_u8) * (game->map_width * game->map_height));
	stack = malloc(sizeof(t_point) * (game->map_width * game->map_height));
	if (stack == NULL || map_clone == NULL)
		return (free_and_return(map_clone, stack, -1));
	ft_memcpy_u8(map_clone, game->map, game->map_width * game->map_height);
	ret = run_flood_fill(game, map_clone, stack);
	return (free_and_return(map_clone, stack, ret));
}
