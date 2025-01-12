/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:43:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/09 10:40:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "classes/vector2d.h"
#include "libft.h"

void	vector2d_del(t_vector2d *vector)
{
	if (vector)
		free(vector);
}

t_vector2d	*ft_vector2d(float x, float y)
{
	t_vector2d	*vector;

	vector = ft_calloc(1, sizeof(t_vector2d));
	if (!vector)
        return (NULL);
    vector->x = x;
    vector->y = y;
    vector->add = &vector2d_add;
    vector->sub = &vector2d_sub;
    vector->scale = &vector2d_scale;
    vector->dot = &vector2d_dot;
    vector->normalize = &vector2d_normalize;
    vector->length = &vector2d_length;
	return (vector);
}
