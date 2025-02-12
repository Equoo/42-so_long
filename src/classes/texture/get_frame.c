/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:13:57 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 20:01:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include "classes/texture.h"

t_frame	texture_get_frame(t_texture *self, char *slice)
{
	int		i;
	char 	*name;

	i = 0;
	while (i < self->nb_slices)
	{
		name = self->slices[i].name;
		if (!ft_strncmp(name, slice, ft_strlen(name) + ft_strlen(slice)))
			return (self->frames[self->slices[i].from]);
		i++;
	}
	return ((t_frame){(t_int2d){0, 0}, (t_int2d){0, 0}});
}