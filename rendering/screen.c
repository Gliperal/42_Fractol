/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:51:17 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 16:14:06 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx_util.h"
#include "../minilibx_macos/mlx.h"
#include "../libft/libft.h"

int			is_in_screen(t_point p, t_screen *screen)
{
	return (
			p.x >= 0 && p.y >= 0 &&
			p.x <= screen->width &&
			p.y <= screen->height);
}

t_point		screen_center(t_screen *screen)
{
	t_point center;

	center.x = screen->width / 2;
	center.y = screen->height / 2;
	return (center);
}

t_screen	*new_screen(MLX *mlx_ptr, int width, int height, char *title)
{
	t_screen	*screen;

	screen = (t_screen *)malloc(sizeof(t_screen));
	if (screen == NULL)
		return (NULL);
	screen->mlx_ptr = mlx_ptr;
	screen->win_ptr = mlx_new_window(mlx_ptr, width, height, title);
	if (screen->win_ptr == NULL)
		return (NULL);
	screen->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (screen->img_ptr == NULL)
		return (NULL);
	screen->data = (void *)mlx_get_data_addr(screen->img_ptr, &screen->bpp, \
			&screen->size_line, &screen->endian);
	if (screen->data == NULL)
		return (NULL);
	screen->width = width;
	screen->height = height;
	return (screen);
}
