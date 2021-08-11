/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 11:23:08 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/11 16:03:45 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "str.h"

static int	map_char_islegal(char c)
{
	if (c == MAP_COLLECTIBLE || c == MAP_EMPTY || c == MAP_EXIT
		|| c == MAP_PLAYER || c == MAP_WALL || c == MAP_ENEMY_H
		|| c == MAP_ENEMY_V)
		return (1);
	return (0);
}

static int	map_check_player_and_exit(t_map *map)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	player_count = map_count(map, MAP_PLAYER);
	exit_count = map_count(map, MAP_EXIT);
	collectible_count = map_count(map, MAP_COLLECTIBLE);
	if (player_count != 1 || exit_count != 1 || collectible_count < 1)
	{
		put(MSG_ERROR_REQUIRE_ESSENTIALS, NULL);
		return (0);
	}
	return (1);
}

static int	map_check_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if ((x == 0 || x == map->width - 1 || y == 0
					|| y == map->height - 1) && (map->data[y][x] != MAP_WALL))
			{
				put(MSG_ERROR_BAD_WALLS, NULL);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	map_check_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!map_char_islegal(map->data[y][x]))
			{
				put(MSG_ERROR_ILLEGAL_CHARS, NULL);
				return (0);
			}
			x++;
		}
		y++;
	}
	if (map_check_walls(map) == 0 || map_check_player_and_exit(map) == 0)
		return (0);
	return (1);
}

int	map_count(t_map *map, char c)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->data[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
