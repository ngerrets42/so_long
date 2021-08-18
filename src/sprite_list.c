/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 13:02:05 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 17:02:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
**	Hardcoded list of sprites used. enums are used to connect the sprite-
**	resource to the appropriate "entities".
*/
t_spr	**sprite_get_list(t_game *game)
{
	t_spr	**sprites;

	sprites = malloc(sizeof(t_spr *) * (LAST + 1));
	sprites[PLAYER] = sprite_from_file(game, "sprites/dino_run.xpm");
	sprites[WALL] = sprite_from_file(game, "sprites/wall.xpm");
	sprites[COLLECTIBLE] = sprite_from_file(game, "sprites/apple.xpm");
	sprites[EXIT] = sprite_from_file(game, "sprites/door.xpm");
	sprites[ENEMY] = sprite_from_file(game, "sprites/enemy.xpm");
	sprites[LAST] = NULL;
	return (sprites);
}
