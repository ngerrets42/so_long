/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 10:59:09 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 16:54:39 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "keycodes.h"

/*
**	Key pressed hook. Used to exit the game (esc) or move the player (wasd).
*/
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

/*
**	Press the window X hook. Used to exit the game.
*/
int	hook_press_x(t_game *game)
{
	game_quit(game);
	return (0);
}
