/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_slice_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:39:46 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include <linux/limits.h>

double			texture_slice_time(t_texture *texture, char *slice)
{
	int		i;
	char 	*name;

	i = 0;
	while (i < texture->nb_slices)
	{
		name = texture->slices[i].name;
		if (!ft_strncmp(name, slice, ft_strlen(name) + ft_strlen(slice)))
			return ((double)(texture->slices[i].to - texture->slices[i].from)
					* ((double)1 / (double)texture->slices[i].framerate));
		i++;
	}
	return (0);
}
