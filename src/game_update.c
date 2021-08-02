/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 20:21:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:21:49 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_update_map(t_game *game)
{
	mlx_destroy_image(game->mlx, game->screen_buf->img);
	free(game->screen_buf);
	game->screen_buf = img_create(game, game->window_w, game->window_h);
	if (game->screen_buf == NULL)
		game_quit(game);
	game_draw_background(game);
}

void	game_update_enemies(t_game *game)
{
	t_list	*enemy;

	enemy = game->enemies;
	while (enemy != NULL)
	{
		enemy_update(game, (t_enemy *)enemy->content);
		enemy = enemy->next;
	}
}