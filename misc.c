/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 16:08:39 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 20:51:18 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractals.h"
#include "libft/libft.h"

void	usage_and_exit(void)
{
	int i;

	ft_putstr("usage: ./fractol [");
	i = 0;
	while (g_fractals[i].name != NULL)
	{
		if (i != 0)
			ft_putstr(" | ");
		ft_putstr(g_fractals[i].name);
		i++;
	}
	ft_putstr("]\n");
	exit(1);
}

int		get_fractal_by_name(const char *name)
{
	int i;

	i = 0;
	while (g_fractals[i].name != NULL)
	{
		if (ft_strequi(g_fractals[i].name, name))
			return (i);
		i++;
	}
	return (-1);
}
