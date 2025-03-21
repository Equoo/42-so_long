/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_frame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:13:57 by dderny            #+#    #+#             */
/*   Updated: 2025/03/20 23:51:06 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
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

t_frame	texture_get_cycle_frame(t_texture *self, char *slice, double cycle)
{
	int		i;
	int		frame;
	char 	*name;

	i = 0;
	while (i < self->nb_slices)
	{
		name = self->slices[i].name;
		if (!ft_strncmp(name, slice, ft_strlen(name) + ft_strlen(slice)))
		{
			frame = self->slices[i].from + (int)((double)
				(self->slices[i].to - self->slices[i].from) * cycle);
			return (self->frames[frame]);
		}
		i++;
	}
	return ((t_frame){(t_int2d){0, 0}, (t_int2d){0, 0}});
}
