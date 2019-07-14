/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   juliasqrt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:53:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 21:06:13 by nwhitlow         ###   ########.fr       */
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
	float		ang;
	float		size;

	z = pixel_to_complex(x, y, t);
	iterations = 0;
	while (iterations < 100)
	{
		ang = atan2(z.i, z.r);
		ang /= 2;
		size = z.r * z.r + z.i * z.i;
		size = sqrt(size);
		new.r = size * cos(ang) + c.r;
		new.i = size * sin(ang) + c.i;
		z.r -= new.r;
		z.i -= new.i;
		if (z.r * z.r + z.i * z.i < 0.05)
			break ;
		z = new;
		iterations++;
	}
	return (iterations);
}

void		juliasqrt(t_param *param)
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
