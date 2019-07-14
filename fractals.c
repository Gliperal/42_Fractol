/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:52:29 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 21:50:10 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"

const t_fractal g_fractals[] =
{
	{"julia", &julia, 0},
	{"mandelbrot", &mandelbrot, 0},
	{"julia3", &julia3, 0},
	{"julia0.5", &juliasqrt, 0},
	{"sierpinski", &carpet, &loop_transform},
	{0, 0, 0}
};
