/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:12:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/09 20:03:27 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "minilibx_macos/mlx.h"

t_screen	*new_screen(int width, int height, char *title);

typedef struct	s_param
{
	t_input		*input;
	t_screen	*screen;
}				t_param;

#include "complex.h"
static int	iterations_for_pixel(int x, int y)
{
	t_complex z;
	t_complex c = {-0.7269, 0.1889};

	int i = 0;
	z.r = x / 182.857 - 2.5;
	z.i = y / 240.0 - 1.0;
	while (i < 8 && z.r * z.r + z.i * z.i < 4)
	{
		// z = z^2 + c
		float tmp = z.r * z.r - z.i * z.i;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp + c.r;
		i++;
	}
	return (i);
}

# define BLACK 0x000000
#include "rendering/rendering.h"
int colors[] = {0xFFFFFF, 0xDDDDDD, 0xBBBBBB, 0x999999, 0x777777, 0x555555, 0x333333, 0x111111};
static void	fractol(t_screen *screen)
{
	screen_put(screen, 50, 100, 0xFF00FF);
	for (int x = 0; x < screen->width; x++)
		for (int y = 0; y < screen->height; y++)
		{
			int iterations = iterations_for_pixel(x, y);
			if (iterations == 8)
				screen_put(screen, x, y, BLACK);
			else
				screen_put(screen, x, y, colors[iterations]);
		}
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img_ptr,\
	0, 0);
}

static void	on_update(void *p)
{
	t_param *param = p;
	if (param->input->key_states[ESC] == PRESSED)
		exit(0);
}

int	main(int argc, char **argv)
{
	t_param *param = malloc(sizeof(t_param));
	param->screen = new_screen(640, 480, "Fract'ol");
	param->input = input_new(&on_update, param, param->screen);
	input_clock_init(param->input);
	fractol(param->screen);
	mlx_loop(param->screen->mlx_ptr);
	argc = 0;
	argv = 0;
}
