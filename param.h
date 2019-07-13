/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:08:34 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/13 15:54:46 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAM_H
# define PARAM_H

# include "complex.h"
# include "input.h"

typedef struct		s_param
{
	t_input			*input;
	t_screen		*screen;
	t_transform		*camera;
	t_complex		julia_c;
	int				*colors;
	int				fractal_type;
}					t_param;


#endif
