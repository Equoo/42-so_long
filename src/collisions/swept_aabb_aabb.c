/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb_aabb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:40 by dderny            #+#    #+#             */
/*   Updated: 2025/04/16 21:46:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collisions.h"
#include "vector2d.h"
#include <math.h>

static int	aabb_intersect(t_float2d pos, t_faabb a, t_faabb b,
		t_float2d *normal)
{
	t_float2d	overlap;
	float		overlapmin;

	a.a = float2d_add(a.a, pos);
	a.b = float2d_add(a.b, pos);
	overlap.x = fmin(a.b.x, b.b.x) - fmax(a.a.x, b.a.x);
	overlap.y = fmin(a.b.y, b.b.y) - fmax(a.a.y, b.a.y);
	if (overlap.x < 0 || overlap.y < 0)
		return (0);
	overlapmin = fmin(overlap.x, overlap.y);
	if (overlapmin == overlap.y)
	{
		if ((a.a.y + a.b.y) / 2 < (b.a.y + b.b.y) / 2)
			normal->y = 1;
		else
			normal->y = -1;
	}
	else
	{
		if ((a.a.x + a.b.x) / 2 < (b.a.x + b.b.x) / 2)
			normal->x = -1;
		else
			normal->x = 1;
	}
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

int	swept_aabb_aabb(t_faabb from_to, t_faabb hulla, t_faabb hullb,
		t_float2d *res, t_float2d *normal)
{
	t__trace	a;

	a = init_trace_vars(from_to.a, from_to.b);
	while (1)
	{
		if (!aabb_intersect(from_to.a, hulla, hullb, normal))
		{
			*res = a.last_pos;
			return (1);
		}
		if (from_to.a.x == from_to.b.x && from_to.a.y == from_to.b.y)
			break ;
		if (ft_fabs(from_to.a.x - from_to.b.x) < TR_STEP_SIZE
			&& ft_fabs(from_to.a.y - from_to.b.y) < TR_STEP_SIZE)
		{
			a.last_pos = from_to.a;
			from_to.a = from_to.b;
			continue ;
		}
		bresenham_algorithm(&a, &from_to.a);
	}
	return (0);
}
