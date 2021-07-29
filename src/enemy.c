/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 17:53:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:43:30 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define ENEMY_SPEED 0.0003

static t_enemy	*enemy_new(int x, int y, float hspeed, float vspeed)
{
	t_enemy	*enemy;
	t_game	*game;

	game = game_get(NULL);
	enemy = malloc(sizeof(t_enemy));
	if (enemy == NULL)
		exit(1);
	enemy->spr = game->spr_list[ENEMY];
	enemy->ani_frame = 0;
	enemy->ani_progress = 0;
	enemy->hspeed = hspeed;
	enemy->vspeed = vspeed;
	enemy->hprog = 0;
	enemy->vprog = 0;
	enemy->x = x;
	enemy->y = y;
	return (enemy);
}

t_list	*enemies_create(t_game *game)
{
	t_list	*list;
	int		x;
	int		y;

	list = NULL;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->data[y][x] == MAP_ENEMY_H)
				ft_lstadd_front(&list,
					ft_lstnew(enemy_new(x, y, ENEMY_SPEED, 0)));
			else if (game->map->data[y][x] == MAP_ENEMY_V)
				ft_lstadd_front(&list,
					ft_lstnew(enemy_new(x, y, 0, ENEMY_SPEED)));
			x++;
		}
		y++;
	}
	return (list);
}

static void	enemy_change_direction(t_game *game, t_enemy *enemy)
{
	int	sign;

	sign = -1;
	if (enemy->hspeed != 0)
	{
		if (enemy->hspeed > 0)
			sign = 1;
		if (game->map->data[enemy->y][enemy->x + sign] == MAP_WALL)
			enemy->hspeed *= -1;
	}
	else
	{
		if (enemy->vspeed > 0)
			sign = 1;
		if (game->map->data[enemy->y + sign][enemy->x] == MAP_WALL)
			enemy->vspeed *= -1;
	}
}

static void	enemy_animate(t_game *game, t_enemy *enemy)
{
	enemy->ani_progress += enemy->spr->ani_speed;
	if (enemy->ani_progress >= 1.0)
	{
		enemy->ani_progress -= 1.0;
		enemy->ani_frame++;
		game->update = 1;
		if (enemy->ani_frame >= enemy->spr->image_count)
			enemy->ani_frame = 0;
	}
}

void	enemy_update(t_game *game, t_enemy *enemy)
{
	enemy_change_direction(game, enemy);
	enemy->hprog += enemy->hspeed;
	enemy->vprog += enemy->vspeed;
	if (enemy->hprog > 1 || enemy->hprog < -1)
	{
		enemy->x += (int)enemy->hprog;
		enemy->hprog = 0;
	}
	else if (enemy->vprog > 1 || enemy->vprog < -1)
	{
		enemy->y += (int)enemy->vprog;
		enemy->vprog = 0;
	}
	enemy_animate(game, enemy);
	if (game->dino->x == enemy->x && game->dino->y == enemy->y)
	{
		put("Oh no! You got eaten by an enemy dinosaur. Game Over!", NULL);
		game_quit(game);
	}
}
