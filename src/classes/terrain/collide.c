/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/26 23:12:25 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "classes/vector2d.h"
#include <X11/Xutil.h>
#include <libft.h>
#include <math.h>

#define GRID_SIZE 16

int swept_aabb_grid(t_float2d start, t_float2d end, t_terrain *terrain, t_float2d *res)
{
	t_float2d pos0 = float2d_scale_dived(start, GRID_SIZE);
	t_float2d pos1 = float2d_scale_dived(end, GRID_SIZE);

	t_float2d	delta = float2d_sub(pos1, pos0);
	delta.x = ft_fabs(delta.x);
	delta.y = ft_fabs(delta.y);

	t_int2d	step = (t_int2d){1, 1};
	if (pos0.x >= pos1.x)
		step.x = -1;
	if (pos0.y >= pos1.y)
		step.y = -1;
	
    double err = delta.x - delta.y;

    while (1) {
        // Check if current grid cell is a wall
		__builtin_printf("Checking: %f %f\n", pos0.x, pos0.y);
        if (pos0.x >= 0 && pos0.x < terrain->w && pos0.y >= 0 && pos0.y < terrain->h
			&& terrain->grid[(int)floor(pos0.y) * terrain->w + (int)floor(pos0.x)] == MAP_WALL)
		{
            *res = float2d_scaled(pos0, GRID_SIZE);  // Convert back to world coordinates
            return 1;  // Collision detected
        }

        if (ft_fabs(pos0.x - pos1.x) < 1e-6 && ft_fabs(pos0.y - pos1.y) < 1e-6)
            break; // Reached the destination

        double e2 = 2 * err;
        if (e2 > -delta.y)
		{
            err -= delta.y;
            pos0.x += step.x * 0.01;
        }
        if (e2 < delta.x)
		{
            err += delta.x;
            pos0.y += step.y * 0.01;
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
	//if (swept_aabb_grid(ent->base->pos, newpos, self, &res))
		//(void)newpos;
		//newpos = res;

	__builtin_printf("Collision: %f %f\n", res.x, res.y);

	//newpos = ent->base->pos;
	
	return (newpos);
}
