/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carpet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:09:55 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/14 13:58:19 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering/rendering.h"
#include "complex.h"
#include "param.h"
#include "minilibx_macos/mlx.h"
#include "fractals.h"

static int	pixel_iterations(int x, int y, t_transform *t)
{
	t_complex	z;
	int			iterations;
	int			ok;
	float		box_size;
	float		half_size;

	z = pixel_to_complex(x, y, t);
	box_size = 1.0;
	iterations = 0;
	while (iterations < 20)
	{
		ok = 0;
		half_size = box_size / 2;
		if (z.r > half_size)
			z.r -= box_size;
		else if (z.r < 0 - half_size)
			z.r += box_size;
		else
			ok = 1;
		if (z.i > half_size)
			z.i -= box_size;
		else if (z.i < 0 - half_size)
			z.i += box_size;
		else if (ok)
			break ;
		box_size /= 3;
		iterations++;
	}
	return (iterations);
}

#define ZOOMS_AT_ONCE 7

void		loop_transform(t_transform *t)
{
	t_complex	offset;
	t_complex	*offset2;
	int			i;

	if (t->scale.r < 0.0000001)
	{
		i = 0;
		while (i < ZOOMS_AT_ONCE)
		{
			offset.r = 0;
			offset.i = 0;
			t->scale.r *= 3;
			t->scale.i *= 3;
			t->loc.r *= 3;
			if (t->loc.r > 1.5)
				offset.r = -3;
			else if (t->loc.r < 0 - 1.5)
				offset.r = 3;
			t->loc.i *= 3;
			if (t->loc.i > 1.5)
				offset.i = -3;
			if (t->loc.i < 0 - 1.5)
				offset.i = 3;
// TODO		if (offset.r == 0 && offset.i == 0)
			t->loc.r += offset.r;
			t->loc.i += offset.i;
			ft_arrlst_add(t->zoom_offsets, &offset);
			t->depth++;
			i++;
		}
	}
	else if (t->scale.r > 0.001 && t->depth > 0)
	{
		i = 0;
		while (i < ZOOMS_AT_ONCE)
		{
			offset2 = ft_arrlst_get(t->zoom_offsets, t->depth - 1);
			t->loc.r -= offset2->r;
			t->loc.i -= offset2->i;
			ft_arrlst_remove_last(t->zoom_offsets, 1);
			t->loc.r /= 3;
			t->loc.i /= 3;
			t->scale.r /= 3;
			t->scale.i /= 3;
			t->depth--;
			i++;
		}
	}
}

void		carpet(t_param *param)
{
	int x;
	int y;
	int iterations;

	y = 0;
	while (y < param->screen->height)
	{
		x = 0;
		while (x < param->screen->width)
		{
			iterations = pixel_iterations(x, y, param->camera);
			screen_put(param->screen, x, y, param->colors[100 - ((iterations + 1) % ZOOMS_AT_ONCE) * 5]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, \
			param->screen->img_ptr, 0, 0);
}
