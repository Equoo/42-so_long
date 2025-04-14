/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 19:17:04 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "vector2d.h"
#include "collisions.h"
#include <libft.h>
#include <math.h>

static t__trace	init_trace_vars(t_float2d start, t_float2d end, t_faabb hull)
{
	t__trace	data;

	data.gpos = float2d_scale_dived(float2d_add(start, hull.a), TR_GRID_SIZE);
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

float	aabb_w(t_faabb hull)
{
	return (ft_fabs(hull.b.x - hull.a.x));
}


float	aabb_h(t_faabb hull)
{
	return (ft_fabs(hull.b.y - hull.a.y));
}

static int	aabb_intersect_grid(t_float2d pos, t_faabb a, t_int2d b, t_float2d *normal)
{
	t_faabb		bb;
	t_float2d	overlap;
	float		overlapmin;

	bb.a = (t_float2d){b.x * TR_GRID_SIZE, b.y * TR_GRID_SIZE};
	bb.b = (t_float2d){(b.x + 1) * TR_GRID_SIZE, (b.y + 1) * TR_GRID_SIZE};
	a.a = float2d_add(a.a, pos);
	a.b = float2d_add(a.b, pos);
	overlap.x = fmin(a.b.x, bb.b.x) - fmax(a.a.x, bb.a.x);
	overlap.y = fmin(a.b.y, bb.b.y) - fmax(a.a.y, bb.a.y);
	if (overlap.x < 0 || overlap.y < 0)
		return (0);
	overlapmin = fmin(overlap.x, overlap.y);
	if (overlapmin == overlap.y)
	{
		if ((a.a.y + a.b.y) / 2 < (bb.a.y + bb.b.y) / 2)
			normal->y = 1;
		else
			normal->y = -1;
	}
	else
	{
		if ((a.a.x + a.b.x) / 2 < (bb.a.x + bb.b.x) / 2)
			normal->x = -1;
		else
			normal->x = 1;
	}
	return (1);
}

int	swept_aabb_grid(t_faabb from_to, t_faabb hull, t_terrain *terrain,
		t_float2d *res, t_float2d *normal)
{
	t__trace	a;

	*normal = (t_float2d){0, 0};
	a = init_trace_vars(from_to.a, from_to.b, hull);
	while (1)
	{
		int	i = 0;
		while (i < (aabb_w(hull) + TR_GRID_SIZE) * (aabb_h(hull) + TR_GRID_SIZE) / (TR_GRID_SIZE * TR_GRID_SIZE))
		{
			t_int2d	grid_pos = (t_int2d){(int)floor(a.gpos.x) + i % ((int)(aabb_w(hull) + TR_GRID_SIZE) / TR_GRID_SIZE), (int)floor(a.gpos.y) + i / ((int)(aabb_w(hull) + TR_GRID_SIZE) / TR_GRID_SIZE)};
			if (a.gpos.x >= 0 && a.gpos.x < terrain->w && a.gpos.y >= 0
				&& a.gpos.y < terrain->h && terrain->grid[grid_pos.y * terrain->w + grid_pos.x] == MAP_WALL && aabb_intersect_grid(from_to.a, hull, grid_pos, normal))
			{
				*res = a.last_pos;
				__builtin_printf("collide %d %f %f\n", i, normal->x, normal->y);
				//if (normal->x != 0)
					//__builtin_printf("");
				//return (1);
			}
			i++;
		}
		if (res->x == a.last_pos.x && res->y == a.last_pos.y)
			return (1);

		if (from_to.a.x == from_to.b.x && from_to.a.y == from_to.b.y)
			break ;
		if (ft_fabs(from_to.a.x - from_to.b.x) < TR_STEP_SIZE && ft_fabs(from_to.a.y
				- from_to.b.y) < TR_STEP_SIZE)
		{
			a.last_pos = from_to.a;
			from_to.a = from_to.b;
			a.gpos = float2d_scale_dived(float2d_add(from_to.a, hull.a), TR_GRID_SIZE);
			continue ;
		}
		bresenham_algorithm(&a, &from_to.a);
	}
	return (0);
}
