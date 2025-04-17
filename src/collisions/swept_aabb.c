/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:46:27 by dderny            #+#    #+#             */
/*   Updated: 2025/04/17 16:18:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collisions.h"
#include "libft.h"
#include "scene.h"
#include "vector2d.h"

#include <stdint.h>

static void	bresenham_algorithm(t__bresenham *data, t_float2d *pos, t_float2d *last_pos)
{
	double	e2;

	*last_pos = *pos;
	e2 = 2 * data->err;
	if (e2 > -data->delta.y)
	{
		data->err -= data->delta.y;
		pos->x += data->step.x * TR_STEP_SIZE;
	}
	if (e2 < data->delta.x)
	{
		data->err += data->delta.x;
		pos->y += data->step.y * TR_STEP_SIZE;
	}
}

static int	test_collide(t_float2d pos, t_float2d last_pos,
		t_scene *scene, t_trace *trace)
{
	t_trace		traceinfo;
	t_float2d	init_pos;

	init_pos = trace->from;
	trace->from = pos;
	traceinfo = collide_aabb(scene, *trace);
	if (traceinfo.hit)
	{
		trace->hit = TRUE;
		trace->normal = traceinfo.normal;
		trace->from = init_pos;
		trace->hitpos = last_pos;
		return (1);
	}
	return (0);
}

static void	init_bresenham(t__bresenham *data, t_trace trace)
{
	data->delta = (t_float2d){ft_fabs(trace.to.x - trace.from.x),
		ft_fabs(trace.to.y - trace.from.y)};
	data->step = (t_int2d){1, 1};
	if (trace.from.x >= trace.to.x)
		data->step.x = -1;
	if (trace.from.y >= trace.to.y)
		data->step.y = -1;
	data->err = data->delta.x - data->delta.y;
}

t_trace	swept_aabb(t_scene *scene, t_trace trace)
{
	t_float2d		last_pos;
	t_float2d		pos;
	t__bresenham	step;

	pos = trace.from;
	last_pos = trace.from;
	init_bresenham(&step, trace);
	while (1)
	{
		if (test_collide(pos, last_pos, scene, &trace))
			return (trace);
		if (trace.from.x == trace.to.x && trace.from.y == trace.to.y)
			break ;
		if (ft_fabs(pos.x - trace.to.x) < TR_STEP_SIZE
			&& ft_fabs(pos.y - trace.to.y) < TR_STEP_SIZE)
		{
			last_pos = pos;
			pos = trace.to;
			continue ;
		}
		bresenham_algorithm(&step, &pos, &last_pos);
	}
	return (trace);
}
