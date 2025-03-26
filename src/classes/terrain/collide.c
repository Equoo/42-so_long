/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 07:16:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "classes/vector2d.h"
#include <float.h>


double	float_abs(double nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}

t_float2d	terrain_collide(t_terrain *self, t_entity *ent, t_float2d vel, t_float2d newpos)
{
	t_int2d		start_pos;
	t_int2d		end_pos;

	t_float2d g_apos = float2d_add(ent->base->pos, ent->hull.a);
	g_apos.x /= 16;
	g_apos.y /= 16;
	t_float2d g_bpos = float2d_add(ent->base->pos, ent->hull.b);
	(void)g_bpos;

	start_pos = to_int2d(g_apos);
	end_pos = to_int2d(float2d_add(g_apos, vel));

	t_int2d		step = (t_int2d){-1, -1};
	if (vel.x > 0)
		step.x = 1;
	if (vel.y > 0)
		step.y = 1;

	t_float2d t_max = (t_float2d){DBL_MAX, DBL_MAX};
	if (vel.x != 0)
		t_max.x = ((double)(start_pos.x + step.x) - g_apos.x) / vel.x;
	if (vel.y != 0)
		t_max.y = ((double)(start_pos.y + step.y) - g_apos.y) / vel.y;

	t_float2d t_delta = (t_float2d){DBL_MAX, DBL_MAX};
	if (vel.x != 0)
		t_delta.x = float_abs(1 / vel.x);
	if (vel.y != 0)
		t_delta.y = float_abs(1 / vel.y);


	t_int2d	current = start_pos;
	while (current.x < end_pos.x || current.y < end_pos.y)
	{
		if (0 <= current.x && current.x < self->w
				&& 0 <= current.y && current.y < self->h
				&& self->grid[current.y * self->w + current.x] == MAP_WALL)
			return (ent->base->pos);

		if (t_max.x < t_max.y)
		{
			t_max.x += t_delta.x;
			current.x += step.x;
		}
		else
		{
			t_max.y += t_delta.y;
			current.y += step.y;
		}
	}
	return (newpos);
}
