/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:00:00 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 19:17:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector2d.h"
#include <libft.h>
#include <stdlib.h>

void	float2d_del(t_float2d *vector)
{
	if (vector)
		free(vector);
}

/*
** Create a new float2d
** @param x: the x value
** @param y: the y value
** @return the float2d
*/
t_float2d	*ft_float2d(float x, float y)
{
	t_float2d	*vector;

	vector = ft_calloc(1, sizeof(t_float2d));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

void	int2d_del(t_int2d *vector)
{
	if (vector)
		free(vector);
}

/*
** Create a new int2d
** @param x: the x value
** @param y: the y value
** @return the float2d
*/
t_int2d	*ft_int2d(int x, int y)
{
	t_int2d	*vector;

	vector = ft_calloc(1, sizeof(t_int2d));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}
