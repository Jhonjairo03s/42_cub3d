/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterative_flood_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 11:58:40 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/19 13:25:48 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int	iteractive_flood_fill(t_game *game)
{
	t_u8	*map_clone;
	t_point	*stack;
	int		total_size;
	int		stack_size;
	int		current_x;
	int		current_y;
	int		index;

	total_size = game->map_width * game->map_height;
	map_clone = (t_u8 *)malloc(sizeof(t_u8) * total_size);
	if (map_clone == NULL)
		return (-1);
	// copiar byte a byte desde game->map hacia map_clone
	ft_memcpy(map_clone, game->map, total_size);
	stack = (t_point *)malloc(sizeof(t_point) * total_size);
	if (stack == NULL)
	{
		free(map_clone);
		return (-1);
	}
	stack_size = 0;
	stack[stack_size].x = (int)game->player_x;
	stack[stack_size].y = (int)game->player_y;
	stack_size++;
	// Fase 2:
	while (stack_size > 0)
	{
		// extraer (pop)
		stack_size--;
		current_x = stack[stack_size].x;
		current_y = stack[stack_size].y;
		// Defensa de los limites
		if (current_x < 0 || current_x >= game->map_width || current_y < 0
			|| current_y >= game->map_height)
		{
			free(map_clone);
			free(stack);
			return (err_msg("Limit flood fill", ERROR_LIMIT_FF, -1));
		}
		// Calcular el índice
		index = (current_y * game->map_width + current_x);
		// Evaluar la casilla
		if (map_clone[index] == '1' || map_clone[index] == 'V')
			continue ;
		if (map_clone[index] == ' ')
		{
			free(map_clone);
			free(stack);
			return (err_msg("Limit flood fill", ERROR_LIMIT_FF, -1));
		}
		// Pintar y expandir
		map_clone[index] = 'V';
		stack[stack_size].x = current_x;
		stack[stack_size].y = current_y - 1;
		stack_size++;
		stack[stack_size].x = current_x;
		stack[stack_size].y = current_y + 1;
		stack_size++;
		stack[stack_size].x = current_x + 1;
		stack[stack_size].y = current_y;
		stack_size++;
		stack[stack_size].x = current_x - 1;
		stack[stack_size].y = current_y;
		stack_size++;
	}
	free(map_clone);
	free(stack);
	return (0);
}
