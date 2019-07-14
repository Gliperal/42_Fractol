/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:12:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 20:26:23 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "minilibx_macos/mlx.h"
#include "complex.h"
#include "param.h"
#include "rendering/rendering.h"
#include "libft/libft.h"
#include "fractals.h"

const t_point g_left = {20, 0};
const t_point g_up = {0, 20};
const t_point g_right = {-20, 0};
const t_point g_down = {0, -20};

static void		on_update1(t_param *param, t_input *input)
{
	if (input->key_states[ESC] == PRESSED)
		exit(0);
	if ((input->mouse_moved.x || input->mouse_moved.y) &&
			!input->mouse_yet_to_move)
	{
		if (key_down(input, SPACE))
		{
			param->julia_c.r = ((float)input->mouse.x / param->screen->width) \
																	* 3.5 - 2.5;
			param->julia_c.i = ((float)input->mouse.y / param->screen->height) \
																		* 2 - 1;
			param->input->exposed = 1;
		}
		if (button_down(input, LCLICK))
		{
			transform_move(param->camera, input->mouse_moved);
			param->input->exposed = 1;
		}
	}
	if (key_down(input, KEY_W))
	{
		transform_move(param->camera, g_up);
		param->input->exposed = 1;
	}
}

static float	on_update2(t_param *param, t_input *input)
{
	if (key_down(input, KEY_A))
	{
		transform_move(param->camera, g_left);
		param->input->exposed = 1;
	}
	if (key_down(input, KEY_S))
	{
		transform_move(param->camera, g_down);
		param->input->exposed = 1;
	}
	if (key_down(input, KEY_D))
	{
		transform_move(param->camera, g_right);
		param->input->exposed = 1;
	}
	if (button_pressed(input, MWHEELDN) || key_down(input, ARROW_DOWN))
		return (0.90);
	if (button_pressed(input, MWHEELUP) || key_down(input, ARROW_UP))
		return (1.11);
	return (0);
}

static void		on_update(void *p)
{
	t_param	*param;
	t_input	*input;
	float	zoom;

	param = p;
	input = param->input;
	on_update1(param, param->input);
	zoom = on_update2(param, param->input);
	if (zoom)
	{
		if (is_in_screen(param->input->mouse, param->screen))
			transform_zoom(param->camera, param->input->mouse, zoom);
		else
			transform_zoom(param->camera, screen_center(param->screen), zoom);
		param->input->exposed = 1;
	}
	if (param->input->exposed)
	{
		(*(param->fractal_render))(param);
		param->input->exposed = 0;
	}
}

static void	fractol(MLX *mlx_ptr, void (*fractal_render)(t_param *param))
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	param->screen = new_screen(mlx_ptr, 1280, 720, "Fract'ol");
	param->camera = malloc(sizeof(t_transform));
	param->camera = transform_new();
	param->julia_c.r = 0.07;
	param->julia_c.i = 0.74;
	param->colors = colors_generator(100);
	if (param->colors == NULL)
	{
		ft_putstr("Failed to allocate colors. Exiting...\n");
		return ;
	}
	param->input = input_new(&on_update, param, param->screen);
	param->fractal_render = fractal_render;
	input_clock_init(param->input);
}

static int	*read_args(int argc, char **argv)
{
	int *types;
	int i;

	types = (int *)malloc((argc - 1) * sizeof(int));
	if (types == NULL)
		exit(1);
	if (argc < 2)
		usage_and_exit();
	i = 0;
	while (i < argc - 1)
	{
		types[i] = get_fractal_by_name(argv[i + 1]);
		if (types[i] == -1)
		{
			ft_printf("error: \"%s\" is not a known fractal type.\n", \
					argv[i + 1]);
			free(types);
			usage_and_exit();
		}
		i++;
	}
	return (types);
}

int			main(int argc, char **argv)
{
	int	*types;
	int	i;
	MLX	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		exit(1);
	types = read_args(argc, argv);
	i = 0;
	while (i < argc - 1)
	{
		fractol(mlx_ptr, g_fractals[types[i]].render);
		i++;
	}
	free(types);
	mlx_loop(mlx_ptr);
}
