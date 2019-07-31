/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:33:32 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/31 13:12:35 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

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

typedef struct	s_thread_args
{
	int			thread_index;
	int			from_y;
	int			to_y;
	t_param		*param;
}				t_thread_args;

#define NUM_THREADS 4

static void	*render_thread(void *p)
{
	t_thread_args	*thread_args;
	t_param *param;
	int x;
	int y;
	int iterations;

	thread_args = p;
	param = thread_args->param;
	y = thread_args->thread_index;
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
	pthread_t	thread_ids[NUM_THREADS];
	t_thread_args	*thread_args[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		thread_args[i] = malloc(sizeof(t_thread_args));
		thread_args[i]->param = param;
		thread_args[i]->thread_index = i;
		thread_args[i]->from_y = (param->screen->height / NUM_THREADS) * i;
		thread_args[i]->to_y = (param->screen->height / NUM_THREADS) * (i + 1) - 10;
	}
	for (int i = 0; i < NUM_THREADS; i++)
	{
		int status = pthread_create(thread_ids + i, NULL, render_thread, thread_args[i]);
		if (status)
			return;
	}
	for (int i = 0; i < NUM_THREADS; i++)
		pthread_join(thread_ids[i], NULL);
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, \
			param->screen->img_ptr, 0, 0);
}
