/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 11:33:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:28:47 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
**	Allocates an img-struct with width/height and registers it with MLX.
*/
t_img	*img_create(t_game *game, int w, int h)
{
	t_img	*new_img;

	new_img = malloc(sizeof(t_img));
	if (new_img == NULL)
		return (NULL);
	new_img->width = w;
	new_img->height = h;
	new_img->img = mlx_new_image(game->mlx, w, h);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bipp,
			&new_img->line_len, &new_img->endian);
	new_img->bypp = new_img->bipp / 8;
	return (new_img);
}

/*
**	Removes img-struct from MLX and frees the struct.
*/
void	img_destroy(t_game *game, t_img *img)
{
	mlx_destroy_image(game->mlx, img->img);
	free(img);
}

/*
**	Set the pixel at x/y of given img to given trgb value.
*/
void	img_set_pixel(t_img *img, int x, int y, int trgb)
{
	char	*addr;

	addr = img->addr + (y * img->line_len) + x * (img->bypp);
	*(int *)addr = trgb;
}

/*
**	Creates an img from given file
*/
t_img	*img_from_file(t_game *game, char *fname)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL)
		return (NULL);
	img->width = 0;
	img->height = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, fname,
			&(img->width), &(img->height));
	if (img->img == NULL)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bipp,
			&img->line_len, &img->endian);
	img->bypp = img->bipp / 8;
	return (img);
}
