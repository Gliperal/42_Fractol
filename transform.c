/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 19:16:27 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/14 13:24:49 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "complex.h"
#include "libft/libft.h"

t_complex	pixel_to_complex(int x, int y, t_transform *t)
{
	t_complex z;

	z.r = x * t->scale.r + t->loc.r;
	z.i = y * t->scale.i + t->loc.i;
	return (z);
}

void		transform_zoom(t_transform *t, t_point invariant, float scale)
{
	t_complex old_scale;

	old_scale = t->scale;
	t->scale.r = old_scale.r * scale;
	t->scale.i = old_scale.i * scale;
	t->loc.r += invariant.x * (old_scale.r - t->scale.r);
	t->loc.i += invariant.y * (old_scale.i - t->scale.i);
}

t_transform	*transform_new(void)
{
	t_transform *new;

	new = (t_transform *)malloc(sizeof(t_transform));
	new->loc.r = -2.5;
	new->loc.i = -1.0;
	new->scale.r = 0.005;
	new->scale.i = 0.005;
	new->depth = 0;
	new->zoom_offsets = ft_arrlst_new(sizeof(t_complex));
	if (new->zoom_offsets != NULL)
		return (new);
	free(new);
	return (NULL);
}

void		transform_move(t_transform *t, t_point distance)
{
	t->loc.r -= t->scale.r * distance.x;
	t->loc.i -= t->scale.i * distance.y;
}
