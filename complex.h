/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:45:21 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/10 19:47:24 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

# include "libft/libft.h"

typedef struct	s_complex
{
	float		r;
	float		i;
}				t_complex;

typedef struct	s_transform
{
	t_complex	loc;
	t_complex	scale;
}				t_transform;

t_complex	pixel_to_complex(int x, int y, t_transform *t);
void	transform_zoom(t_transform *t, t_point invariant, float scale);

#endif
