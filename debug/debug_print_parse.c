/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhvalenc <jhvalenc@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:07:47 by jhvalenc          #+#    #+#             */
/*   Updated: 2026/06/20 17:52:47 by jhvalenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h> // SOLO PARA TESTING

/*
void	debug_print_parse(t_game *game)
{
	printf("\n=== REPORTE DE EXTRACCIÓN (FASE A) ===\n");
	// 1. Comprobar los colores empaquetados
	// Se imprimen en formato Hexadecimal (0xRRGGBB).
	printf("Color Techo (C)  : 0x%06X\n", game->ceil_color);
	printf("Color Suelo (F)  : 0x%06X\n", game->floor_color);
	// 2. Comprobar que los punteros de textura no son nulos
	printf("\n--- Punteros de Píxeles ---\n");
	printf("Textura Norte : %p\n", (void *)game->tex_n);
	printf("Textura Sur   : %p\n", (void *)game->tex_s);
	printf("Textura Este  : %p\n", (void *)game->tex_e);
	printf("Textura Oeste : %p\n", (void *)game->tex_w);
	// 3. Comprobar el primer píxel (Solo si el puntero existe para evitar SegFault)
	if (game->tex_n != NULL)
		printf("\nColor del 1er pixel del Norte: 0x%06X\n", game->tex_n[0]);
	printf("======================================\n\n");
}
*/

#include <stdio.h>

void	debug_print_final_struct(t_game *game)
{
	int	x;
	int	y;
	int	index;

	printf("\n=== REPORTE FINAL DE PARSEO ===\n");
	printf("--- METADATOS ---\n");
	printf("Techo (C) : 0x%06X\n", game->ceil_color);
	printf("Suelo (F) : 0x%06X\n", game->floor_color);
	printf("Texturas  : NO(%p) SO(%p) WE(%p) EA(%p)\n",
		game->tex_n, game->tex_s, game->tex_w, game->tex_e);

	printf("\n--- TOPOLOGÍA ---\n");
	printf("Resolución de la cuadrícula: %d x %d\n", game->map_width, game->map_height);
	printf("Jugador -> Posición: (%.1f, %.1f) | Vector Dir: (%.1f, %.1f)\n",
		game->player_x, game->player_y, game->dir_x, game->dir_y);

	printf("\n--- VOLCADO DE MEMORIA DEL MAPA ---\n");
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			index = (y * game->map_width) + x;
			// Si es un espacio, imprimimos un punto para verlo visualmente
			if (game->map[index] == ' ')
				printf(".");
			else
				printf("%c", game->map[index]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("===============================\n\n");
}
