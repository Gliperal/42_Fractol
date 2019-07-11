/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:12:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/10 20:10:20 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "minilibx_macos/mlx.h"
#include "complex.h"

t_screen	*new_screen(int width, int height, char *title);

typedef struct	s_param
{
	t_input		*input;
	t_screen	*screen;
	t_transform	*camera;
}				t_param;

static int	iterations_for_pixel(int x, int y, t_transform *t, t_complex c)
{
	t_complex z;

	z = pixel_to_complex(x, y, t);
	int i = 0;
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
static void	julia(t_param *param)
{
	t_complex c;
	if (param->input->mouse_yet_to_move)
	{
		c.r = 0.07;
		c.i = 0.74;
	}
	else
	{
		c.r = ((float) param->input->mouse.x / param->screen->width) * 3.5 - 2.5;
		c.i = ((float) param->input->mouse.y / param->screen->height) * 2 - 1;
	}
	for (int x = 0; x < param->screen->width; x++)
		for (int y = 0; y < param->screen->height; y++)
		{
			int iterations = iterations_for_pixel(x, y, param->camera, c);
			if (iterations == 8)
				screen_put(param->screen, x, y, BLACK);
			else
				screen_put(param->screen, x, y, colors[iterations]);
		}
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}

// TODO only re-render once on multiple updated things
static void	on_update(void *p)
{
	t_param *param = p;
	if (param->input->key_states[ESC] == PRESSED)
		exit(0);
	if (param->input->button_states[MWHEELUP] == PRESSED)
	{
		transform_zoom(param->camera, param->input->mouse, 1.11);
		julia(param);
	}
	if (param->input->button_states[MWHEELDN] == PRESSED)
	{
		transform_zoom(param->camera, param->input->mouse, 0.90);
		julia(param);
	}
	if (param->input->mouse_moved.x || param->input->mouse_moved.y)
		julia(param);
	if (param->input->exposed)
		julia(param);
}

int	main(int argc, char **argv)
{
	t_param *param = malloc(sizeof(t_param));
	param->screen = new_screen(640, 480, "Fract'ol");
	param->camera = malloc(sizeof(t_transform));
	param->camera->loc.r = -2.5;
	param->camera->loc.i = -1.0;
	param->camera->scale.r = 0.005468;
	param->camera->scale.i = 0.004166;
	param->input = input_new(&on_update, param, param->screen);
	input_clock_init(param->input);
	mlx_loop(param->screen->mlx_ptr);
	argc = 0;
	argv = 0;
}
