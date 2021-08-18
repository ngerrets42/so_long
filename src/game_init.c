/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 20:19:32 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 16:49:23 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
**	Create the window and the image for the window buffer.
*/
static void	game_initialize_window(t_game *game, t_map *map)
{
	game->window_w = MAP_TILE_W * map->width;
	game->window_h = MAP_TILE_H * map->height;
	game->window = mlx_new_window(game->mlx, game->window_w,
			game-> window_h, "so_long");
	if (game->window == NULL)
	{
		free(game);
		game = NULL;
		return ;
	}
	game->map = map;
	game->screen_buf = img_create(game, game->window_w, game->window_h);
	if (game->screen_buf == NULL)
		game = NULL;
}

/*
**	Allocate the game struct and initialize mlx.
*/
t_game	*game_initialize_mlx(t_map *map)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game != NULL)
	{
		game->mlx = mlx_init();
		game->update = 0;
		if (game->mlx == NULL)
		{
			free(game);
			game = NULL;
		}
		else
			game_initialize_window(game, map);
	}
	if (game == NULL)
		put(MSG_ERROR_NOT_INITIALIZED, NULL);
	game->collectibles = map_count(map, MAP_COLLECTIBLE);
	game_get(game);
	return (game);
}

/*
**	This functions holds a static variable designed to point towards the
**	game struct.
*/
t_game	*game_get(t_game *game)
{
	static t_game	*game_struct = NULL;

	if (game != NULL)
		game_struct = game;
	return (game_struct);
}

/*
**	Create all the entities (player and enemies).
*/
void	game_init_entities(t_game *game)
{
	game->dino = dino_create(game);
	if (game->dino == NULL)
	{
		put(MSG_ERROR_BAD_MALLOC, NULL);
		exit(1);
	}
	game->enemies = enemies_create(game);
}
