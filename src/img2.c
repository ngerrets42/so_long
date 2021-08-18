/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img2.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/06 20:25:22 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/08/18 16:57:13 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
**	Gets the pixel trgb-int color from img at given coordinates. 
*/
static int	img_get_pixel_color(t_img *img, int x, int y)
{
	char	*addr;

	addr = img->addr + (y * img->line_len) + x * (img->bypp);
	return (*(int *)addr);
}

/*
**	Create a copy of src between given x-coordinates. For separating frames.
*/
t_img	*img_copy(t_game *game, t_img *src, int x1, int x2)
{
	t_img	*copy;
	int		x;
	int		y;

	copy = img_create(game, x2 - x1, src->height);
	if (copy == NULL)
		return (NULL);
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			if (x >= x1 && x <= x2)
				img_set_pixel(copy, x - x1, y,
					img_get_pixel_color(src, x, y));
			x++;
		}
		y++;
	}
	return (copy);
}

/*
**	Clear the entire img with given trgb-int color.
*/
void	img_clear(t_img *img, int trgb)
{
	int	x;
	int	y;

	if (img == NULL)
		return ;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			img_set_pixel(img, x, y, trgb);
			x++;
		}
		y++;
	}
}

/*
**	Draw src onto target image at given coordinates.
*/
void	img_draw_to_img(t_img *src, t_img *target, int posx, int posy)
{
	int		x;
	int		y;
	int		c;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			c = img_get_pixel_color(src, x, y);
			img_set_pixel(target, posx + x, posy + y, c);
			x++;
		}
		y++;
	}
}
