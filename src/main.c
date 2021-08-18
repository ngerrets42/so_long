/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 12:10:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 17:05:31 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "so_long.h"

/*
**	Parse and return the map with given file-name.
*/
static t_map	*parse_map(char *fname)
{
	t_map	*map;
	int		i;

	i = 0;
	while (fname[i])
		i++;
	if (i < 4 || fname[i - 1] != 'r' || fname[i - 2] != 'e'
		|| fname[i - 3] != 'b' || fname[i - 4] != '.')
	{
		put(MSG_ERROR_BAD_FILE_EXTENSION, NULL);
		return (NULL);
	}
	map = map_get_from_file(fname);
	if (map == NULL || map_check_map(map) == 0)
	{
		if (map != NULL)
			map_destroy(map);
		else
			put(MSG_ERROR_BAD_MAP, NULL);
		return (NULL);
	}
	return (map);
}

/*
**	Apply all the hooks.
*/
static void	apply_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->window, 2, (1L << 0), hook_key_pressed, game);
	mlx_hook(game->window, 17, (1L << 17), hook_press_x, game);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (argc != 2)
	{
		put("Error\n- Wrong number of arguments", NULL);
		return (1);
	}
	map = parse_map(argv[1]);
	if (map == NULL)
		return (1);
	game = game_initialize_mlx(map);
	if (game == NULL)
		return (1);
	apply_hooks(game);
	game->spr_list = sprite_get_list(game);
	game_draw_background(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->screen_buf->img, 0, 0);
	game_init_entities(game);
	mlx_loop(game->mlx);
	return (0);
}
