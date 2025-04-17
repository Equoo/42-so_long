/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide_aabb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:25:58 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 00:51:57 by dderny           ###   ########.fr       */
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
#include <stdlib.h>

float sign(float value)
{
	return value < 0 ? -1 : 1;
}

static int	aabb_intersect(t_faabb a, t_faabb b,
		t_trace *trace)
{
	t_float2d 	delta;
	t_faabb 	abox;
	t_faabb 	bbox;
	t_float2d 	p;
	t_float2d 	s;

	abox.a = float2d_scale_dived(float2d_add(a.a, a.b), 2);
	abox.b = float2d_sub(abox.a, a.a);
	bbox.a = float2d_scale_dived(float2d_add(b.a, b.b), 2);
	bbox.b = float2d_sub(bbox.a, b.a);
	delta = float2d_sub(bbox.a, abox.a);
	p.x = bbox.b.x + abox.b.x - ft_abs(delta.x);
	p.y = bbox.b.y + abox.b.y - ft_abs(delta.y);
	if (p.x <= 0 || p.y <= 0)
		return (0);
	if (p.x < p.y)
	{
		s.x = sign(delta.x);
		trace->delta.x = p.x * s.x;
		trace->normal.x = s.x;
		trace->hitpos.x = abox.a.x + (abox.b.x * s.x);
		trace->hitpos.y = bbox.a.y;
	}
	else
	{
		s.y = sign(delta.y);
		trace->delta.y = p.y * s.y;
		trace->normal.y = s.y;
		trace->hitpos.x = bbox.a.x;
		trace->hitpos.y = abox.a.y + (abox.b.y * s.y);
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
	if (aabb_intersect(hulla, hullb, trace))
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
		if (aabb_intersect(hulla, hullb, trace))
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
