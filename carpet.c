/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carpet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 21:09:55 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/14 14:16:46 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering/rendering.h"
#include "complex.h"
#include "param.h"
#include "minilibx_macos/mlx.h"
#include "fractals.h"

static int	thanks_norme(t_complex *z, float box_size, float half_size)
{
	if (z->r > half_size)
		z->r -= box_size;
	else if (z->r < 0 - half_size)
		z->r += box_size;
	else
		return (1);
	return (0);
}

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
		half_size = box_size / 2;
		ok = thanks_norme(&z, box_size, half_size);
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

/*
** TODO if (offset.r == 0 && offset.i == 0)
*/

static void	loop_transform_zoom_out(t_transform *t)
{
	t_complex	offset;
	int			i;

	i = -1;
	while (++i < ZOOMS_AT_ONCE)
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
		t->loc.r += offset.r;
		t->loc.i += offset.i;
		ft_arrlst_add(t->zoom_offsets, &offset);
		t->depth++;
	}
}

void		loop_transform(t_transform *t)
{
	t_complex	*offset;
	int			i;

	if (t->scale.r < 0.0000001)
		loop_transform_zoom_out(t);
	else if (t->scale.r > 0.001 && t->depth > 0)
	{
		i = 0;
		while (i < ZOOMS_AT_ONCE)
		{
			offset = ft_arrlst_get(t->zoom_offsets, t->depth - 1);
			t->loc.r -= offset->r;
			t->loc.i -= offset->i;
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
			screen_put(param->screen, x, y, param->colors[\
					100 - ((iterations + 1) % ZOOMS_AT_ONCE) * 5]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, \
			param->screen->img_ptr, 0, 0);
}
