/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide_aabb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:25:58 by dderny            #+#    #+#             */
/*   Updated: 2025/04/17 21:26:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "classes/terrain.h"
#include "collisions.h"
#include "libft.h"
#include "scene.h"
#include "vector2d.h"

#include <math.h>
#include <stdint.h>

static int	aabb_intersect(t_faabb a, t_faabb b,
		t_float2d *normal)
{
	t_float2d	overlap;
	float		overlapmin;

	overlap.x = fmin(a.b.x, b.b.x) - fmax(a.a.x, b.a.x);
	overlap.y = fmin(a.b.y, b.b.y) - fmax(a.a.y, b.a.y);
	if (overlap.x < 0 || overlap.y < 0)
		return (0);
	overlapmin = fmin(overlap.x, overlap.y);
	if (!normal)
		return (1);
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

static int	collide_aabb_entities(t_entity *entity, t_trace *trace)
{
	t_faabb	hulla;
	t_faabb	hullb;

	if (!entity)
		return (0);
	hulla = trace->hull;
	hulla.a = float2d_add(hulla.a, trace->from);
	hulla.b = float2d_add(hulla.b, trace->from);
	hullb = entity->hull;
	hullb.a = float2d_add(hullb.a, entity->base->pos);
	hullb.b = float2d_add(hullb.b, entity->base->pos);
	if (aabb_intersect(hulla, hullb, &trace->normal))
	{
		trace->hit = 1;
		trace->hitpos = trace->from;
		return (1);
	}
	return (0);
}

static int	collide_aabb_terrain(t_terrain *terrain, t_trace *trace)
{
	t_faabb	hulla;
	t_faabb	hullb;
	uint	gridindex;
	uint	i;

	hulla = trace->hull;
	hulla.a = float2d_add(hulla.a, trace->from);
	hulla.b = float2d_add(hulla.b, trace->from);

	uint	voxels = ceil(aabb_w(hulla) * aabb_h(hulla) / (TR_GRID_SIZE * TR_GRID_SIZE));
	i = -1;
	while (++i < voxels)
	{
		gridindex = (int)floor(trace->from.x / TR_GRID_SIZE) + i % voxels +
			((int)floor(trace->from.y / TR_GRID_SIZE) + i / voxels) * terrain->w;
		if (terrain->grid[gridindex] != MAP_WALL)
			continue ;
		hullb = (t_faabb){{gridindex % terrain->w * TR_GRID_SIZE, gridindex / terrain->w * TR_GRID_SIZE},
				{TR_GRID_SIZE, TR_GRID_SIZE}};
		hullb.b = float2d_add(hullb.b, hullb.a);
		if (aabb_intersect(hulla, hullb, &trace->normal))
			trace->hit = 1;
	}
	if (trace->hit)
	{
		trace->hitpos = trace->from;
		return (1);
	}
	return (0);
}

t_trace	collide_aabb(t_scene *scene, t_trace traceinfo)
{
	t_list		*current;
	t_element	*element;

	current = scene->elements;
	while (current)
	{
		element = current->content;
		if (!(element->class && traceinfo.mask) && traceinfo.ignore != element->id)
		{
			if (element->class == CLASS_TERRAIN)
				collide_aabb_terrain((t_terrain *)element->parent, &traceinfo);
			else if (element->class & CGROUP_ENTITY)
				collide_aabb_entities(cast_entity(element->parent), &traceinfo);
		}
		current = current->next;
	}
	return (traceinfo);
}
