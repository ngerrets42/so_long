/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 10:35:40 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/11 16:13:06 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "map.h"

void	game_destroy_sprites(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->spr_list[i] != NULL)
	{
		j = 0;
		while (j < game->spr_list[i]->image_count)
		{
			mlx_destroy_image(game->mlx, game->spr_list[i]->images[j]->img);
			free(game->spr_list[i]->images[j]);
			j++;
		}
		free(game->spr_list[i]->images);
		free(game->spr_list[i]);
		i++;
	}
	free(game->spr_list);
}

void	game_quit(t_game *game)
{
	if (game != NULL)
	{
		mlx_destroy_window(game->mlx, game->window);
		img_destroy(game, game->screen_buf);
		map_destroy(game->map);
		game_destroy_sprites(game);
		ft_lstclear(&(game->enemies), free);
		free(game->dino);
		free(game);
	}
	exit(0);
}

void	game_draw_background(t_game *game)
{
	int		x;
	int		y;
	t_img	*img;

	img_clear(game->screen_buf, BACKGROUND_COLOR);
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			img = NULL;
			if (game->map->data[y][x] == MAP_WALL)
				img = game->spr_list[WALL]->images[0];
			else if (game->map->data[y][x] == MAP_EXIT)
				img = game->spr_list[EXIT]->images[0];
			else if (game->map->data[y][x] == MAP_COLLECTIBLE)
				img = game->spr_list[COLLECTIBLE]->images[0];
			if (img != NULL)
				img_draw_to_img(img, game->screen_buf,
					x * MAP_TILE_W, y * MAP_TILE_H);
			x++;
		}
		y++;
	}
}

void	game_draw_enemies(t_game *game)
{
	t_list	*enemy;

	enemy = game->enemies;
	while (enemy != NULL)
	{
		if (enemy->content == NULL)
		{
			put(MSG_ERROR_BAD_MALLOC, NULL);
			exit(1);
		}
		enemy_draw(game, (t_enemy *)enemy->content);
		enemy = enemy->next;
	}
}

int	game_loop(t_game *game)
{
	if (game->update)
	{
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window,
			game->screen_buf->img, 0, 0);
		dino_put_to_screen(game, game->dino);
		game_draw_enemies(game);
		game->update = 0;
	}
	dino_update_animation(game, game->dino);
	game_update_enemies(game);
	return (0);
}
