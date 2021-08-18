/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 11:40:41 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 17:24:29 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "stddef.h"	

# define MAP_EMPTY '0'
# define MAP_PLAYER 'P'
# define MAP_WALL '1'
# define MAP_COLLECTIBLE 'C'
# define MAP_EXIT 'E'
# define MAP_ENEMY_H 'H'
# define MAP_ENEMY_V 'V'
# define MAP_TILE_W 48
# define MAP_TILE_H 48

typedef struct s_map
{
	int		width;
	int		height;
	char	**data;
}			t_map;

t_map	*map_get_from_file(char *fname);
int		map_check_map(t_map *map);
void	map_destroy(t_map *map);
int		map_count(t_map *map, char c);

#endif
