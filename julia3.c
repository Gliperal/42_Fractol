/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:16:44 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 20:45:51 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering/rendering.h"
#include "complex.h"
#include "param.h"
#include "minilibx_macos/mlx.h"
#include "fractals.h"

static int	pixel_iterations(int x, int y, t_transform *t, t_complex c)
{
	t_complex	z;
	int			iterations;
	float		tmp;

	z = pixel_to_complex(x, y, t);
	iterations = 0;
	while (iterations < 100 && z.r * z.r + z.i * z.i < 4)
	{
		tmp = z.r * z.r * z.r - 3 * z.r * z.i * z.i + c.r;
		z.i = 3 * z.r * z.r * z.i - z.i * z.i * z.i + c.i;
		z.r = tmp;
		iterations++;
	}
	return (iterations);
}

void		julia3(t_param *param)
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
