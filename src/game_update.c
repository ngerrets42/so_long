/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 20:21:31 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 17:25:52 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
**	Update the screen buffer to display the updated background.
*/
void	game_update_map(t_game *game)
{
	mlx_destroy_image(game->mlx, game->screen_buf->img);
	free(game->screen_buf);
	game->screen_buf = img_create(game, game->window_w, game->window_h);
	if (game->screen_buf == NULL)
		game_quit(game);
	game_draw_background(game);
}

/*
**	Loop through and update all the enemies.
*/
void	game_update_enemies(t_game *game)
{
	t_list	*enemy;

	enemy = game->enemies;
	while (enemy != NULL)
	{
		if (enemy->content == NULL)
		{
			put("Error\n - Bad malloc.", NULL);
			exit(1);
		}
		enemy_update(game, (t_enemy *)enemy->content);
		enemy = enemy->next;
	}
}
