/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 20:16:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 14:53:15 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>

int			*colors_generator_simple(int how_many)
{
	int *colors;
	int i;

	colors = (int *)malloc((how_many + 1) * sizeof(int));
	if (colors == NULL)
		return (NULL);
	srand(time(0));
	i = 0;
	while (i < how_many)
	{
		colors[i] = rand() & 0xFFFFFF;
		i++;
	}
	colors[how_many] = 0x000000;
	return (colors);
}

static int	gradient(int color1, int color2, float dist)
{
	int rgba1[4];
	int rgba2[4];
	int rgba3[4];

	rgba1[0] = color1 >> 24;
	rgba1[1] = (color1 >> 16) & 0xFF;
	rgba1[2] = (color1 >> 8) & 0xFF;
	rgba1[3] = color1 & 0xFF;
	rgba2[0] = color2 >> 24;
	rgba2[1] = (color2 >> 16) & 0xFF;
	rgba2[2] = (color2 >> 8) & 0xFF;
	rgba2[3] = color2 & 0xFF;
	rgba3[0] = rgba1[0] * (1 - dist) + rgba2[0] * dist;
	rgba3[1] = rgba1[1] * (1 - dist) + rgba2[1] * dist;
	rgba3[2] = rgba1[2] * (1 - dist) + rgba2[2] * dist;
	rgba3[3] = rgba1[3] * (1 - dist) + rgba2[3] * dist;
	return (rgba3[0] << 24 | rgba3[1] << 16 | rgba3[2] << 8 | rgba3[3]);
}

int			*colors_generator(int how_many)
{
	int		*colors;
	int		i;
	int		key_colors[2];
	float	dist_between_keys;

	dist_between_keys = 1.0;
	key_colors[1] = 0;
	colors = (int *)malloc((how_many + 1) * sizeof(int));
	if (colors == NULL)
		return (NULL);
	srand(time(0));
	i = how_many;
	while (i >= 0)
	{
		if (dist_between_keys >= 1)
		{
			key_colors[0] = key_colors[1];
			key_colors[1] = rand() & 0xFFFFFF;
			dist_between_keys = 0;
		}
		colors[i] = gradient(key_colors[0], key_colors[1], dist_between_keys);
		dist_between_keys += 0.2;
		i--;
	}
	return (colors);
}
