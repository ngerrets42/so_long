/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 10:59:09 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/06/29 16:14:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "keycodes.h"

int	hook_key_pressed(int key, t_game *game)
{
	if (key == KEY_ESC)
		game_quit(game);
	if (key == KEY_A || key == KEY_W || key == KEY_D || key == KEY_S)
	{
		dino_move(game, game->dino, (key == KEY_D) - (key == KEY_A),
			(key == KEY_S) - (key == KEY_W));
	}
	return (0);
}

int	hook_press_x(t_game *game)
{
	game_quit(game);
	return (0);
}
