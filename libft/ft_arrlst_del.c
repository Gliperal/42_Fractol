/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwhitlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:15:31 by nwhitlow          #+#    #+#             */
/*   Updated: 2019/06/03 20:17:23 by nwhitlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrlst_del(t_arrlst **arrlst)
{
	free((*arrlst)->data);
	free(*arrlst);
	*arrlst = NULL;
}
