/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:33:32 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/31 13:23:30 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering/rendering.h"
#include "complex.h"
#include "param.h"
#include "minilibx_macos/mlx.h"
#include "multithreading.h"

static int	pixel_iterations(int x, int y, t_transform *t)
{
	t_complex	z;
	t_complex	c;
	int			iterations;
	float		tmp;

	c = pixel_to_complex(x, y, t);
	z.r = 0;
	z.i = 0;
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

static void	*render_thread(void *p)
{
	t_thread_args	*thread_args;
	t_param			*param;
	int				x;
	int				y;
	int				iterations;

	thread_args = p;
	param = thread_args->param;
	y = thread_args->index;
	while (y < param->screen->height)
	{
		x = 0;
		while (x < param->screen->width)
		{
			iterations = pixel_iterations(x, y, param->camera);
			screen_put(param->screen, x, y, param->colors[iterations]);
			x++;
		}
		y += NUM_THREADS;
	}
	free(thread_args);
	pthread_exit(NULL);
}

void		mandelbrot(t_param *param)
{
	pthread_t		thread_ids[NUM_THREADS];
	t_thread_args	*thread_args[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		thread_args[i] = malloc(sizeof(t_thread_args));
		thread_args[i]->param = param;
		thread_args[i]->index = i;
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_create(thread_ids + i, NULL, render_thread, thread_args[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(thread_ids[i++], NULL);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, \
			param->screen->img_ptr, 0, 0);
}
