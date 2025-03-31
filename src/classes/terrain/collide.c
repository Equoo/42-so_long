/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:17:32 by dderny            #+#    #+#             */
/*   Updated: 2025/03/31 19:34:23 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "classes/vector2d.h"
#include "collisions.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <libft.h>

t_float2d	terrain_collide(t_terrain *self, t_entity *ent, t_float2d vel, t_float2d newpos)
{
	t_float2d	res;
	(void)vel;
	(void)ent;
	(void)self;
	(void)res;

	res = (t_float2d){0, 0};
	if (swept_aabb_grid((t_faabb){ent->base->pos, newpos}, ent->hull, self, &res))
	{
		newpos = res;
		ent->velocity = float2d_multiply(ent->velocity, float2d_abs(float2d_normalize(float2d_sub(newpos, ent->base->pos))));
	}
	return (newpos);
}
