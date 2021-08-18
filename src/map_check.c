/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 11:23:08 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 17:23:47 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "str.h"

/*
**	Returns 1 if given character is a legal map-character.
*/
static int	map_char_islegal(char c)
{
	if (c == MAP_COLLECTIBLE || c == MAP_EMPTY || c == MAP_EXIT
		|| c == MAP_PLAYER || c == MAP_WALL || c == MAP_ENEMY_H
		|| c == MAP_ENEMY_V)
		return (1);
	return (0);
}

/*
**	Check if the player count == 1, exit count == 1 and if collectibles > 1
*/
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
		put("Error\n- Map needs ONE player, ONE exit and 1+ apples.", NULL);
		return (0);
	}
	return (1);
}

/*
**	Check if map is surrounded by walls.
*/
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
				put("Error\n- Map needs to be surrounded by walls.", NULL);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/*
**	Check validity of map.
*/
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
				put("Error\n- Illegal characters in map.", NULL);
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

/*
**	Count number of appearances of char c within the map.
*/
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
