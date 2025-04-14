/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:39:12 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"
#include "collisions.h"
#include <libft.h>
#include <math.h>

static t__trace	init_trace_vars(t_float2d start, t_float2d end)
{
	t__trace	data;

	data.gpos = float2d_scale_dived(start, TR_GRID_SIZE);
	data.delta = (t_float2d){ft_fabs(end.x - start.x), ft_fabs(end.y
			- start.y)};
	data.last_pos = start;
	data.step = (t_int2d){1, 1};
	if (start.x >= end.x)
		data.step.x = -1;
	if (start.y >= end.y)
		data.step.y = -1;
	data.err = data.delta.x - data.delta.y;
	return (data);
}

static void	bresenham_algorithm(t__trace *a, t_float2d *start)
{
	double	e2;

	a->last_pos = *start;
	e2 = 2 * a->err;
	if (e2 > -a->delta.y)
	{
		a->err -= a->delta.y;
		a->gpos.x += a->step.x * TR_STEP_SIZE / TR_GRID_SIZE;
		start->x += a->step.x * TR_STEP_SIZE;
	}
	if (e2 < a->delta.x)
	{
		a->err += a->delta.x;
		a->gpos.y += a->step.y * TR_STEP_SIZE / TR_GRID_SIZE;
		start->y += a->step.y * TR_STEP_SIZE;
	}
}

int	trace_grid(t_float2d start, t_float2d end, t_terrain *terrain,
		t_float2d *res)
{
	t__trace	a;

	a = init_trace_vars(start, end);
	while (1)
	{
		if (a.gpos.x >= 0 && a.gpos.x < terrain->w && a.gpos.y >= 0
			&& a.gpos.y < terrain->h && terrain->grid[(int)floor(a.gpos.y)
				* terrain->w + (int)floor(a.gpos.x)] == MAP_WALL)
		{
			*res = a.last_pos;
			return (1);
		}
		if (start.x == end.x && start.y == end.y)
			break ;
		if (ft_fabs(start.x - end.x) < TR_STEP_SIZE && ft_fabs(start.y
				- end.y) < TR_STEP_SIZE)
		{
			a.last_pos = start;
			start = end;
			a.gpos = float2d_scale_dived(start, TR_GRID_SIZE);
			continue ;
		}
		bresenham_algorithm(&a, &start);
	}
	return (0);
}

