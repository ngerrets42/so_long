/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 11:41:18 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 21:03:40 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "../lib/get_next_line/get_next_line.h"
#include "str.h"
#include <fcntl.h>
#include <unistd.h>

static void	map_first_line(t_map **map, char *line)
{
	(*map)->width = ft_strlen(line);
	(*map)->height = 1;
	(*map)->data = malloc(sizeof(char *));
	(*map)->data[0] = line;
}

static void	bad_map_free(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	free(map);
}

static void	map_add_line(t_map **map, char *line)
{
	char	**new_data;
	int		i;

	new_data = malloc(((*map)->height + 1) * sizeof(char *));
	if (new_data == NULL || ft_strlen(line) != (*map)->width)
	{
		put("Error\n- Map needs to be a rectangle. (or mem-err)", NULL);
		free(new_data);
		bad_map_free(*map);
		free(line);
		*map = NULL;
		return ;
	}
	((*map)->height)++;
	i = 0;
	while (i < (*map)->height - 1)
	{
		new_data[i] = (*map)->data[i];
		i++;
	}
	new_data[i] = line;
	free((*map)->data);
	(*map)->data = new_data;
}

void	map_destroy(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		free(map->data[y]);
		y++;
	}
	free(map->data);
	free(map);
}

t_map	*map_get_from_file(char *fname)
{
	int		fd;
	t_map	*map;
	char	*line;
	int		ret;

	fd = open(fname, O_RDONLY);
	if (fd < 2)
		return (NULL);
	ret = get_next_line(fd, &line);
	map = NULL;
	if (ret == 1)
	{
		map = malloc(sizeof(t_map));
		if (map != NULL)
		{
			map_first_line(&map, line);
			while (ret > 0 && map != NULL)
			{
				ret = get_next_line(fd, &line);
				map_add_line(&map, line);
			}
		}
	}
	close(fd);
	return (map);
}
