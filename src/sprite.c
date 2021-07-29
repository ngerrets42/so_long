/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 14:06:03 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:31:45 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_spr	*sprite_create(t_img *img)
{
	t_spr	*spr;

	spr = malloc(sizeof(t_spr));
	if (spr == NULL)
		return (NULL);
	spr->images = malloc(sizeof(t_img *));
	if (spr->images == NULL)
		return (NULL);
	spr->images[0] = img;
	spr->image_count = 1;
	spr->ani_speed = SPR_DEFAULT_ANI_SPEED;
	return (spr);
}

void	sprite_add_img(t_spr *spr, t_img *img)
{
	t_img	**new_images;
	int		i;

	if (spr == NULL)
		return ;
	(spr->image_count)++;
	new_images = malloc(spr->image_count * sizeof(char *));
	if (new_images == NULL)
	{
		spr = NULL;
		return ;
	}
	i = 0;
	while (i < spr->image_count - 1)
	{
		new_images[i] = spr->images[i];
		i++;
	}
	new_images[i] = img;
	free(spr->images);
	spr->images = new_images;
}

t_spr	*sprite_from_file(t_game *game, char *fname)
{
	t_spr	*spr;
	t_img	*img;
	t_img	*frame;
	int		i;

	img = img_from_file(game, fname);
	if (img == NULL)
		return (NULL);
	if (img->width <= MAP_TILE_W)
		spr = sprite_create(img);
	else
	{
		frame = img_copy(game, img, 0, MAP_TILE_W);
		spr = sprite_create(frame);
		i = 1;
		while (i < img->width / MAP_TILE_W - 1)
		{
			frame = img_copy(game, img, i * MAP_TILE_W, (1 + i) * MAP_TILE_W);
			sprite_add_img(spr, frame);
			i++;
		}
		mlx_destroy_image(game->mlx, img->img);
		free(img);
	}
	return (spr);
}
