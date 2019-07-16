/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_neg1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:31:57 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/15 19:36:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "rendering/rendering.h"
#include "complex.h"
#include "param.h"
#include "minilibx_macos/mlx.h"
#include "fractals.h"

static int	pixel_iterations(int x, int y, t_transform *t, t_complex c)
{
	t_complex	z;
	t_complex	new;
	int			iterations;
	float		magnitude;

	z = pixel_to_complex(x, y, t);
	iterations = 0;
	while (iterations < 100)
	{
		/*
		tmp = z.r * z.r - z.i * z.i;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp + c.r;
		*/
		// (a + bi)(a - bi) = a^2 + b^2
		magnitude = z.r * z.r + z.i * z.i;
		new.r = z.r / magnitude + c.r;
		new.i = 0 - z.i / magnitude + c.i;
		z.r -= new.r;
		z.i -= new.i;
		if (z.r * z.r + z.i * z.i < 0.05)
			break ;
		z = new;
		iterations++;
	}
	return (iterations);
}

void		julia_neg1(t_param *param)
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
			iterations = pixel_iterations(x, y, param->camera, param->julia_c);
			screen_put(param->screen, x, y, param->colors[iterations]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, \
			param->screen->img_ptr, 0, 0);
}
