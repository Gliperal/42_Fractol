/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:12:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/10 21:25:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "minilibx_macos/mlx.h"
#include "complex.h"

t_screen	*new_screen(int width, int height, char *title);
t_transform	*transform_new();

typedef struct	s_param
{
	t_input		*input;
	t_screen	*screen;
	t_transform	*camera;
	t_complex	julia_c;
	int			*colors;
}				t_param;

int		key_down(t_input *input, int key)
{
	return (input->key_states[key] == HELD ||
			input->key_states[key] == PRESSED);
}

int		key_pressed(t_input *input, int key)
{
	return (input->key_states[key] == PRESSED);
}

int		button_down(t_input *input, int button)
{
	return (input->button_states[button] == HELD ||
			input->button_states[button] == PRESSED);
}

int		button_pressed(t_input *input, int button)
{
	return (input->button_states[button] == PRESSED);
}

static int	iterations_for_pixel(int x, int y, t_transform *t, t_complex c)
{
	t_complex z;

	z = pixel_to_complex(x, y, t);
	int i = 0;
	while (i < 100 && z.r * z.r + z.i * z.i < 4)
	{
		// z = z^2 + c
		float tmp = z.r * z.r - z.i * z.i;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp + c.r;
		i++;
	}
	return (i);
}

// TODO REMOVE
#include <stdio.h>

#include "rendering/rendering.h"
int	*colors_generator(int how_many);
static void	julia(t_param *param)
{
//	printf("Zoom depth: %e\n", param->camera->scale.r);
	for (int x = 0; x < param->screen->width; x++)
		for (int y = 0; y < param->screen->height; y++)
		{
			int iterations = iterations_for_pixel(x, y, param->camera, param->julia_c);
			screen_put(param->screen, x, y, param->colors[iterations]);
		}
	mlx_put_image_to_window(param->screen->mlx_ptr, param->screen->win_ptr, param->screen->img_ptr, 0, 0);
}

// TODO only re-render once on multiple updated things
static void	on_update(void *p)
{
	t_param *param = p;
	t_input *input = param->input;
	if (param->input->key_states[ESC] == PRESSED)
		exit(0);
	if (
			key_down(input, SPACE) &&
			!param->input->mouse_yet_to_move &&
			(param->input->mouse_moved.x ||
			param->input->mouse_moved.y)
	   )
	{
		param->julia_c.r = ((float) param->input->mouse.x / param->screen->width) * 3.5 - 2.5;
		param->julia_c.i = ((float) param->input->mouse.y / param->screen->height) * 2 - 1;
		julia(param);
	}
	float zoom = 0;
	if (button_pressed(input, MWHEELDN) || key_down(input, ARROW_DOWN))
		zoom = 0.90;
	if (button_pressed(input, MWHEELUP) || key_down(input, ARROW_UP))
		zoom = 1.11;
	if (zoom)
	{
		if (is_in_screen(param->input->mouse, param->screen))
			transform_zoom(param->camera, param->input->mouse, zoom);
		else
			transform_zoom(param->camera, screen_center(param->screen), zoom);
		julia(param);
	}
	if (param->input->exposed)
	{
		param->input->exposed = 0;
		julia(param);
	}
}

int	main(int argc, char **argv)
{
	t_param *param = malloc(sizeof(t_param));
	param->screen = new_screen(640, 480, "Fract'ol");
	param->camera = malloc(sizeof(t_transform));
	param->camera = transform_new();
	param->julia_c.r = 0.07;
	param->julia_c.i = 0.74;
	param->colors = colors_generator(100);
	if (param->colors == NULL)
		return (1);
	param->input = input_new(&on_update, param, param->screen);
	input_clock_init(param->input);
	mlx_loop(param->screen->mlx_ptr);
	argc = 0;
	argv = 0;
}
