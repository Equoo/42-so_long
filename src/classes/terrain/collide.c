/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/27 17:43:31 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "classes/vector2d.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <libft.h>
#include <math.h>

#define STEP_SIZE 0.1
#define GRID_SIZE 16

int trace_grid(t_float2d start, t_float2d end, t_terrain *terrain, t_float2d *res)
{
	t_float2d pos0 = float2d_scale_dived(start, GRID_SIZE);
	t_float2d last_pos = start;

	t_float2d	delta = float2d_sub(end, start);
	delta.x = ft_fabs(delta.x);
	delta.y = ft_fabs(delta.y);

	t_int2d	step = (t_int2d){1, 1};
	if (start.x >= end.x)
		step.x = -1;
	if (start.y >= end.y)
		step.y = -1;

	double err = delta.x - delta.y;

	while (1) {
		// Check if current grid cell is a wall
		if (pos0.x >= 0 && pos0.x < terrain->w && pos0.y >= 0 && pos0.y < terrain->h
			&& terrain->grid[(int)floor(pos0.y) * terrain->w + (int)floor(pos0.x)] == MAP_WALL)
		{
			*res = last_pos;  // Convert back to world coordinates
			return 1;  // Collision detected
		}

		if (start.x == end.x && start.y == end.y)
			break; // Reached the destination

		if (ft_fabs(start.x - end.x) < STEP_SIZE && ft_fabs(start.y - end.y) < STEP_SIZE)
		{
			start = end;
			pos0 = float2d_scale_dived(start, GRID_SIZE);
			continue ;
		}

		last_pos = start;
		double e2 = 2 * err;
		if (e2 > -delta.y)
		{
			err -= delta.y;
			pos0.x += step.x * STEP_SIZE / GRID_SIZE;
			start.x += step.x * STEP_SIZE;
		}
		if (e2 < delta.x)
		{
			err += delta.x;
			pos0.y += step.y * STEP_SIZE / GRID_SIZE;
			start.y += step.y * STEP_SIZE;
		}
	}

	return 0; // No collision
}


t_float2d	terrain_collide(t_terrain *self, t_entity *ent, t_float2d vel, t_float2d newpos)
{
	t_float2d	res;
	(void)vel;
	(void)ent;
	(void)self;
	(void)res;

	res = (t_float2d){0, 0};
	if (trace_grid(ent->base->pos, newpos, self, &res))
		//(void)newpos;
		newpos = res;

	//newpos = ent->base->pos;

	return (newpos);
}
