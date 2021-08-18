/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 20:16:57 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 16:47:14 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
**	Draw the correct frame of the enemy sprite to the screen at the correct pos.
*/
void	enemy_draw(t_game *game, t_enemy *enemy)
{
	mlx_put_image_to_window(game->mlx, game->window,
		game->spr_list[ENEMY]->images[enemy->ani_frame]->img,
		enemy->x * MAP_TILE_W, enemy->y * MAP_TILE_H);
}
