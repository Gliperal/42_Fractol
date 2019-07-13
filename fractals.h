/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:48:01 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 15:54:08 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALS_H
# define FRACTALS_H

#include "param.h"

void				julia(t_param *param);
void				mandelbrot(t_param *param);

typedef struct		s_foo
{
	const char		*name;
	void			(*render)(t_param *param);
}					t_foo;

extern const t_foo g_fractals[];

#endif
