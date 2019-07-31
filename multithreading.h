/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:19:09 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/07/31 13:20:26 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_H
# define MULTITHREADING_H

# include <pthread.h>

# include "param.h"

# define NUM_THREADS 4

typedef struct	s_thread_args
{
	int			index;
	t_param		*param;
}				t_thread_args;

#endif
