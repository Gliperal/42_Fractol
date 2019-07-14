/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:48:01 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 21:47:09 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALS_H
# define FRACTALS_H

# include "param.h"

typedef struct		s_fractal
{
	const char		*name;
	void			(*render)(t_param *param);
	void			(*loop_transform)(t_transform *t);
}					t_fractal;

void				julia(t_param *param);
void				mandelbrot(t_param *param);
void				julia3(t_param *param);
void				juliasqrt(t_param *param);
void				carpet(t_param *param);
void				loop_transform(t_transform *t);

extern const t_fractal	g_fractals[];

#endif
