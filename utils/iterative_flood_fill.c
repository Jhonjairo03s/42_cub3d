/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_flood_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:58:40 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/07/28 17:40:16 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/**
 * @brief Custom memory copy function tailored for the unsigned 8-bit map array.
 *
 * @param s1 Destination array.
 * @param s2 Source array.
 * @param len Number of bytes to copy.
 * @return t_u8* Pointer to the beginning of the destination array.
 */
static t_u8	*ft_memcpy(t_u8 *s1, t_u8 *s2, int len)
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

/**
 * @brief Inspects a specific coordinate to determine if the flood fill can
 *        continue, if it hit a barrier, or if it leaked out of the map.
 *
 * @param game Pointer to the main game structure.
 * @param map The cloned map array being modified.
 * @param x The X coordinate to check.
 * @param y The Y coordinate to check.
 * @return int 1 if the tile is walkable and successfully marked as 
 *		   visited ('V').
 *         0 if it hits a wall ('1') or a previously visited tile ('V').
 *         -1 if it goes out of bounds or hits the void (' '), 
 *         indicating a leak.
 */
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

/**
 * @brief Pushes the four adjacent neighboring coordinates 
 *	      (North, South, East, West) onto the custom stack to be processed in 
 *	      subsequent iterations.
 *
 * @param stack The heap-allocated array holding coordinates to visit.
 * @param s_size Pointer to the current size/top of the stack.
 * @param x The current X coordinate.
 * @param y The current Y coordinate.
 */
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

/**
 * @brief Core loop of the iterative flood fill algorithm. Spreads outward
 *        from the player's initial position like virtual water.
 *
 * @param game Pointer to the main game structure.
 * @param map_clone The temporary map used to track visited tiles without
 *        ruining the original game map.
 * @param stack The custom stack array managing the coordinates to check.
 * @return int 0 if the "water" is completely contained by walls ('1').
 *         -1 if the water ever touches the void (' ') or the map boundary.
 */
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

/**
 * @brief Orchestrates the security check to ensure the map is perfectly 
 *	      enclosed.
 *
 * @param game Pointer to the main game structure.
 * @return int 0 if the map geometry is valid and fully sealed, -1 if a leak
 *         is found or if memory allocation fails.
 *
 * @note This function avoids the OS Stack Overflow issues of recursive flood
 *       fills by allocating a custom LIFO (Last-In-First-Out) stack 
 *       on the Heap.
 *       The temporary memory is rigorously cleaned up via free_and_return().
 */
int	iteractive_flood_fill(t_game *game)
{
	t_u8	*map_clone;
	t_point	*stack;
	int		ret;

	map_clone = malloc(sizeof(t_u8) * (game->map_width * game->map_height));
	stack = malloc(sizeof(t_point) * (game->map_width * game->map_height * 8));
	if (stack == NULL || map_clone == NULL)
		return (free_and_return(map_clone, stack, -1));
	ft_memcpy(map_clone, game->map, game->map_width * game->map_height);
	ret = run_flood_fill(game, map_clone, stack);
	return (free_and_return(map_clone, stack, ret));
}
