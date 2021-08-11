/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dino.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:01:00 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/11 16:16:38 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	dino_update_animation(t_game *game, t_dino *dino)
{
	dino->ani_progress += dino->spr->ani_speed;
	if (dino->ani_progress >= 1.0)
	{
		dino->ani_progress -= 1.0;
		dino->ani_frame++;
		game->update = 1;
		if (dino->ani_frame >= dino->spr->image_count)
			dino->ani_frame = 0;
	}
}

static void	dino_set_vars(t_game *game, t_dino *dino)
{
	dino->y = 0;
	while (dino->y < game->map->height)
	{
		dino->x = 0;
		while (dino->x < game->map->width)
		{
			if (game->map->data[dino->y][dino->x] == MAP_PLAYER)
				break ;
			dino->x++;
		}
		if (game->map->data[dino->y][dino->x] == MAP_PLAYER)
			break ;
		dino->y++;
	}
	dino->ani_progress = 0.0;
	dino->ani_frame = 0;
	dino->spr = game->spr_list[0];
	dino->apples = 0;
	dino->steps = 0;
}

t_dino	*dino_create(t_game *game)
{
	t_dino	*dino;

	dino = malloc(sizeof(t_dino));
	if (dino == NULL)
		return (NULL);
	dino_set_vars(game, dino);
	return (dino);
}

void	dino_put_to_screen(t_game *game, t_dino *dino)
{
	char	*str_apples;
	char	*str_steps;

	str_apples = ft_itoa(dino->apples);
	str_steps = ft_itoa(dino->steps);
	mlx_put_image_to_window(game->mlx, game->window,
		game->spr_list[PLAYER]->images[dino->ani_frame]->img,
		dino->x * MAP_TILE_W, dino->y * MAP_TILE_H);
	mlx_string_put(game->mlx, game->window, 4, 10, 0x00FFFFFF, "Apples:");
	mlx_string_put(game->mlx, game->window, 74, 10, 0x00FFFFFF, str_apples);
	mlx_string_put(game->mlx, game->window, game->screen_buf->width - 92,
		10, 0x00FFFFFF, "Steps:");
	mlx_string_put(game->mlx, game->window, game->screen_buf->width - 32,
		10, 0x00FFFFFF, str_steps);
	free(str_apples);
	free(str_steps);
}

void	dino_move(t_game *game, t_dino *dino, int movex, int movey)
{
	if (game->map->data[dino->y + movey][dino->x + movex] != MAP_WALL)
	{
		dino->x += movex;
		dino->y += movey;
		dino->steps++;
		put("Steps taken: ", &(dino->steps));
	}
	if (game->map->data[dino->y][dino->x] == MAP_COLLECTIBLE)
	{
		dino->apples++;
		game->map->data[dino->y][dino->x] = MAP_EMPTY;
		game_update_map(game);
	}
	else if (game->map->data[dino->y][dino->x] == MAP_EXIT)
	{
		if (game->collectibles <= dino->apples)
		{
			put("You win! Collected apples: ", &(dino->apples));
			game_quit(game);
		}
	}
}
