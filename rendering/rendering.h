/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:09:23 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 15:44:31 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "mlx_util.h"
# include "../libft/libft.h"
# include "quaternion.h"
# include "vertex.h"
# include "matrix.h"
# include "camera.h"
# include "cpoint.h"

t_screen	*new_screen(MLX *mlx_ptr, int width, int height, char *title);
void		screen_put(t_screen *screen, int x, int y, int color);
void		ft_draw_line(t_screen *screen, t_cpoint src, t_cpoint dst);
int			is_in_screen(t_point p, t_screen *screen);
t_point		screen_center(t_screen *screen);

#endif
