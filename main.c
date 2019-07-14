/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:12:53 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/14 14:30:36 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "param.h"
#include "libft/libft.h"
#include "fractals.h"
#include "main.h"

static int	*read_args(int argc, char **argv)
{
	int *types;
	int i;

	types = (int *)malloc((argc - 1) * sizeof(int));
	if (types == NULL)
		exit(1);
	if (argc < 2)
		usage_and_exit();
	i = 0;
	while (i < argc - 1)
	{
		types[i] = get_fractal_by_name(argv[i + 1]);
		if (types[i] == -1)
		{
			ft_printf("error: \"%s\" is not a known fractal type.\n", \
					argv[i + 1]);
			free(types);
			usage_and_exit();
		}
		i++;
	}
	return (types);
}

int			main(int argc, char **argv)
{
	int		*types;
	int		i;
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		exit(1);
	types = read_args(argc, argv);
	i = 0;
	while (i < argc - 1)
	{
		fractol(mlx_ptr, g_fractals + types[i]);
		i++;
	}
	free(types);
	mlx_loop(mlx_ptr);
}
