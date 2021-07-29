/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 11:24:55 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:43:03 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/mlx_mac/mlx.h"
# include "list.h"
# include "map.h"
# include "str.h"
# include <stddef.h>
# include <stdlib.h>

# define SPR_DEFAULT_ANI_SPEED 0.001
# define BACKGROUND_COLOR 0x000000

typedef enum e_sprtype
{
	PLAYER,
	WALL,
	COLLECTIBLE,
	ENEMY,
	EXIT,
	LAST
}	t_sprtype;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bipp;
	int		bypp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_sprite
{
	t_img	**images;
	float	ani_speed;
	int		image_count;
}			t_spr;

typedef struct s_dino
{
	t_spr	*spr;
	int		x;
	int		y;
	float	ani_progress;
	int		ani_frame;
	int		apples;
	int		steps;
}			t_dino;

typedef struct s_enemy
{
	t_spr	*spr;
	int		x;
	int		y;
	float	ani_progress;
	int		ani_frame;
	float	hspeed;
	float	hprog;
	float	vspeed;
	float	vprog;
}			t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	int		window_w;
	int		window_h;
	int		collectibles;
	t_img	*screen_buf;
	t_map	*map;
	t_spr	**spr_list;
	t_dino	*dino;
	t_list	*enemies;
	int		update;
}			t_game;

char	*ft_itoa(int n);

/*
**	IMG
*/

t_img	*img_create(t_game *game, int w, int h);
void	img_destroy(t_game *game, t_img *img);
void	img_set_pixel(t_img *img, int x, int y, int trgb);
t_img	*img_from_file(t_game *game, char *fname);
t_img	*img_copy(t_game *game, t_img *src, int x1, int x2);
void	img_clear(t_img *img, int trgb);
void	img_draw_to_img(t_img *src, t_img *target, int posx, int posy);

/*
**	HOOKS
*/

int		hook_key_pressed(int key, t_game *game);
int		hook_press_x(t_game *game);

/*
**	GAME
*/

t_game	*game_initialize_mlx(t_map *map);
void	game_init_entities(t_game *game);
int		game_loop(t_game *game);
void	game_quit(t_game *game);
void	game_draw_background(t_game *game);
void	game_update_map(t_game *game);
void	game_update_enemies(t_game *game);
t_game	*game_get(t_game *game);

/*
**	SPRITES
*/

t_spr	*sprite_from_file(t_game *game, char *fname);
t_spr	**sprite_get_list(t_game *game);

/*
**	DINO
*/

t_dino	*dino_create(t_game *game);
void	dino_update_animation(t_game *game, t_dino *dino);
void	dino_put_to_screen(t_game *game, t_dino *dino);
void	dino_move(t_game *game, t_dino *dino, int movex, int movey);

/*
**	ENEMIES
*/

t_list	*enemies_create(t_game *game);
void	enemy_update(t_game *game, t_enemy *enemy);
void	enemy_draw(t_game *game, t_enemy *enemy);

#endif
