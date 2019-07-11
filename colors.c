/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 20:16:05 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/10 20:20:39 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>

// TODO Make the colors gradient more, make them not too similar, etc.
int	*colors_generator(int how_many)
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
