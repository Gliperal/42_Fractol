/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:33:32 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 14:36:09 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering/rendering.h"
#include "complex.h"
#include "param.h"
#include "minilibx_macos/mlx.h"

static int	pixel_iterations(int x, int y, t_transform *t)
{
	t_complex	z;
	t_complex	c;
	int			iterations;
	float		tmp;

	c = pixel_to_complex(x, y, t);
	z.r = 0; z.i = 0;
	iterations = 0;
	while (iterations < 100 && z.r * z.r + z.i * z.i < 4)
	{
		tmp = z.r * z.r - z.i * z.i;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp + c.r;
		iterations++;
	}
	return (iterations);
}

void		mandelbrot(t_param *param)
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
			screen_put(param->screen, x, y, param->colors[iterations]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, \
			param->screen->img_ptr, 0, 0);
}
