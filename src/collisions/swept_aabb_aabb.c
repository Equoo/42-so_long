/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb_aabb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:40 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 18:30:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collisions.h"

static int	test_aabb(t_faabb hull, t_float2d *res)
{
	if (hull.a.x > hull.b.x || hull.a.y > hull.b.y)
		return (0);
	res->x = (hull.a.x + hull.b.x) / 2;
	res->y = (hull.a.y + hull.b.y) / 2;
	return (1);
}

static t__trace	init_trace_vars(t_float2d start, t_float2d end)
{
	t__trace	data;

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
		start->x += a->step.x * TR_STEP_SIZE;
	}
	if (e2 < a->delta.x)
	{
		a->err += a->delta.x;
		start->y += a->step.y * TR_STEP_SIZE;
	}
}

int	swept_aabb_aabb(t_faabb from_to, t_faabb hull, t_faabb hull2,
	t_float2d *res)
{
	t__trace	a;

	
}