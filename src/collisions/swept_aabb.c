/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swept_aabb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:25:58 by dderny            #+#    #+#             */
/*   Updated: 2025/04/20 14:52:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/element.h"
#include "classes/entity.h"
#include "classes/terrain.h"
#include "collisions.h"
#include "libft.h"
#include "render.h"
#include "scene.h"
#include "vector2d.h"

#include <math.h>
#include <stdint.h>

float clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static float getsign(float value)
{
	return value < 0 ? -1 : 1;
}


t_hit	intersect_segment(t_float2d pos, t_float2d delta, t_float2d padding, t_aabb hull)
{
	t_float2d	scale;
	t_float2d	sign;
	t_float2d	near_time;
	t_float2d	far_time;
	t_hit		hit;

	hit = (t_hit){0};
	scale = float2d_divide((t_float2d){1, 1}, delta);
	sign = (t_float2d){getsign(scale.x), getsign(scale.y)};
	near_time = float2d_multiply(float2d_sub(float2d_sub(hull.center,
		float2d_multiply(sign, float2d_add(hull.half, padding))), pos), scale);
	far_time = float2d_multiply(float2d_add(float2d_add(hull.center,
		float2d_multiply(sign, float2d_add(hull.half, padding))), pos), scale);
	if (near_time.x > far_time.y || near_time.y > far_time.x || ft_fmax(
		near_time.x, near_time.y) >= 1 || ft_fmin(far_time.x, far_time.y) <= 0)
		return (hit);
	hit.time = clamp(ft_fmax(near_time.x, near_time.y), 0, 1);
	if (near_time.x > near_time.y)
		hit.normal.x = -sign.x;
	else
	 	hit.normal.y = -sign.y;
	hit.delta = float2d_scaled(delta, -(1 - hit.time));
	hit.pos = float2d_add(pos, float2d_scaled(delta, hit.time));
	return (hit);
}

t_hit	intersect_aabb(t_aabb hulla, t_aabb hullb)
{
	t_float2d	d;
	t_float2d	p;
	t_hit		hit;

	hit = (t_hit){0};
	d = float2d_sub(hulla.center, hullb.center);
	p = float2d_sub(float2d_add(hulla.half, hullb.half), float2d_abs(d));
	if (p.x <= 0 || p.y <= 0)
		return (hit);
	if (p.x < p.y)
	{
		hit.normal.x = getsign(d.x);
		hit.delta.x = p.x * hit.normal.x;
		hit.pos.x = hullb.center.x + (hulla.half.x * hit.normal.x);
		hit.pos.y = hulla.center.y;
	}
	else
	{
		hit.normal.y = getsign(d.y);
		hit.delta.y = p.y * hit.normal.y;
		hit.pos.x = hulla.center.x;
		hit.pos.y = hullb.center.y + (hulla.half.y * hit.normal.y);
	}
	return (hit);
}

static t_sweep	sweep_aabb_static(t_aabb hulla, t_aabb hullb)
{
	t_sweep		sweep;

	sweep = (t_sweep){0};
	sweep.pos = hulla.center;
	sweep.hit = intersect_aabb(hulla, hullb);
	if (sweep.hit.touch)
		sweep.time = 0;
	if (sweep.hit.touch)
		sweep.hit.time = 0;
	return (sweep);
}

t_render	*debug_rd;
t_scene	*debug_sc;

t_sweep	sweep_aabb(t_aabb hulla, t_aabb hullb, t_float2d delta)
{
	t_sweep		sweep;
	t_float2d	dir;

	if (delta.x == 0 && delta.y == 0)
		return (sweep_aabb_static(hulla, hullb));
	sweep = (t_sweep){0};
	sweep.hit = intersect_segment(hulla.center, delta, hulla.half, hullb);

	t_float2d pos = float2d_sub((t_float2d){0},debug_sc->cam_pos);

	if (pos.x + sweep.hit.pos.x >= 0 && pos.x + sweep.hit.pos.x < debug_rd->buffer->width && pos.y + sweep.hit.pos.y >= 0 && pos.y + sweep.hit.pos.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer, pos.x + sweep.hit.pos.x, pos.y + sweep.hit.pos.y, 0x00FFFF);

	if (pos.x + hulla.center.x >= 0 && pos.x + hulla.center.x < debug_rd->buffer->width
		&& pos.y + hulla.center.y >= 0 && pos.y + hulla.center.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer,pos.x + hulla.center.x,pos.y + hulla.center.y, 0xb112b1);
	if (pos.x + hulla.half.x >= 0 && pos.x + hulla.half.x < debug_rd->buffer->width
		&& pos.y + hulla.half.y >= 0 && pos.y + hulla.half.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer,pos.x + hulla.half.x,pos.y + hulla.half.y, 0xFF00FF);

	if (pos.x + hullb.center.x >= 0 && pos.x + hullb.center.x < debug_rd->buffer->width
		&& pos.y + hullb.center.y >= 0 && pos.y + hullb.center.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer,pos.x + hullb.center.x,pos.y + hullb.center.y, 0xECBE00);
	if (pos.x + hullb.half.x >= 0 && pos.x + hullb.half.x < debug_rd->buffer->width
		&& pos.y + hullb.half.y >= 0 && pos.y + hullb.half.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer,pos.x + hullb.half.x,pos.y + hullb.half.y, 0xECFF00);

	__builtin_printf("COL %f ht %f, %f %f, Touch: %d\n", sweep.time, sweep.hit.time, sweep.hit.pos.x, sweep.hit.pos.y, sweep.hit.touch);

	if (sweep.hit.touch)
	{
		sweep.time = clamp(sweep.hit.time - EPSILON, 0, 1);
		sweep.pos = float2d_add(hulla.center, float2d_scaled(delta, sweep.time));
		dir = float2d_normalize(delta);
		sweep.hit.pos.x = clamp(sweep.hit.pos.x + dir.x * hulla.half.x,
				hullb.center.x - hulla.half.x, hullb.center.x + hulla.half.x);
		sweep.hit.pos.y = clamp(sweep.hit.pos.y + dir.y * hulla.half.y,
			hullb.center.y - hulla.half.y, hullb.center.y + hulla.half.y);
	}
	else
	{
		sweep.hit.pos = float2d_add(hulla.center, delta);
		sweep.time = 1;
	}
	return (sweep);
}



static t_sweep	sweep_aabb_entities(t_entity *entity, t_trace *trace)
{
	t_aabb	hulla;
	t_aabb	hullb;

	if (!entity)
		return ((t_sweep){{0}, {0}, 1});
	hulla = trace->hull;
	hulla.min = float2d_add(hulla.min, trace->from);
	hulla.max = float2d_add(hulla.max, trace->from);
	hulla = aabb_from_mm(hulla.min, hulla.max);
	hullb = entity->hull;
	hullb.min = float2d_add(hullb.min, entity->base->pos);
	hullb.max = float2d_add(hullb.max, entity->base->pos);
	hulla = aabb_from_mm(hullb.min, hullb.max);
	return (sweep_aabb(hulla, hullb, float2d_sub(trace->to, trace->from)));
}

static t_sweep	sweep_aabb_terrain(t_terrain *terrain, t_trace *trace)
{
	t_aabb	hulla;
	t_aabb	hullb;
	t_sweep	sweep;
	t_sweep	nearest;
	uint	gridindex;
	uint	i;

	debug_rd = &terrain->base->scene->env->render;
	debug_sc = terrain->base->scene;

	nearest = (t_sweep){{0}, {0}, 1};
	hulla = trace->hull;
	hulla.min = float2d_add(hulla.min, trace->from);
	hulla.max = float2d_add(hulla.max, trace->from);
	hulla = aabb_from_mm(hulla.min, hulla.max);

	t_float2d pos = float2d_sub((t_float2d){0},debug_sc->cam_pos);
	//if (pos.x + hulla.min.x >= 0 && pos.x + hulla.min.x < debug_rd->buffer->width
	//	&& pos.y + hulla.min.y >= 0 && pos.y + hulla.min.y < debug_rd->buffer->height)
	//	mylx_pixel_put(debug_rd->buffer, pos.x + hulla.min.x, pos.y + hulla.min.y, 0xb112b1);
	//if (pos.x + hulla.max.x >= 0 && pos.x + hulla.max.x < debug_rd->buffer->width
	//	&& pos.y + hulla.max.y >= 0 && pos.y + hulla.max.y < debug_rd->buffer->height)
	//	mylx_pixel_put(debug_rd->buffer,pos.x + hulla.max.x,pos.y + hulla.max.y, 0xFF00FF);

	if (pos.x + hulla.center.x >= 0 && pos.x + hulla.center.x < debug_rd->buffer->width
		&& pos.y + hulla.center.y >= 0 && pos.y + hulla.center.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer,pos.x + hulla.center.x,pos.y + hulla.center.y, 0xb112b1);
	if (pos.x + hulla.center.x + hulla.half.x >= 0 && pos.x + hulla.center.x + hulla.half.x < debug_rd->buffer->width
		&& pos.y + hulla.center.y + hulla.half.y >= 0 && pos.y + hulla.center.y + hulla.half.y < debug_rd->buffer->height)
		mylx_pixel_put(debug_rd->buffer,pos.x + hulla.center.x + hulla.half.x,pos.y + hulla.center.y + hulla.half.y, 0xFF00FF);

	uint	voxels = ceil(aabb_w(hulla) * aabb_h(hulla) / (TR_GRID_SIZE * TR_GRID_SIZE)) * 2;
	uint	voxelsW = ceil(aabb_w(hulla) / TR_GRID_SIZE);
	i = -1;
	while (++i < voxels)
	{
		gridindex = (int)floor(trace->from.x / TR_GRID_SIZE) + i % voxelsW +
			((int)floor(trace->from.y / TR_GRID_SIZE) + i / voxelsW) * terrain->w;
		if (terrain->grid[gridindex] != MAP_WALL)
			continue ;
		hullb = (t_aabb){{gridindex % terrain->w * TR_GRID_SIZE, gridindex / terrain->w * TR_GRID_SIZE},
				{TR_GRID_SIZE, TR_GRID_SIZE}, {0}, {0}};
		hullb.max = float2d_add(hullb.min, hullb.min);
		hullb = aabb_from_mm(hullb.min, hullb.max);
		sweep = sweep_aabb(hulla, hullb, float2d_sub(trace->to, trace->from));
		__builtin_printf("@%d: %f ht %f, %f %f\n", i, sweep.time, sweep.hit.time, sweep.hit.normal.x, sweep.hit.normal.y);
		if (sweep.time < nearest.time)
			nearest = sweep;
	}
	return (nearest);
}

t_sweep	world_sweep_aabb(t_scene *scene, t_trace trace)
{
	t_list		*current;
	t_element	*element;
	t_sweep		sweep;
	t_sweep		act;

	sweep = (t_sweep){0};
	sweep.time = 1;
	current = scene->elements;
	while (current)
	{
		element = current->content;
		if (!(element->class && trace.mask) && trace.ignore != element->id)
		{
			act = (t_sweep){{0}, {0}, 1};
			if (element->class == CLASS_TERRAIN)
				act = sweep_aabb_terrain((t_terrain *)element->parent, &trace);
			else if (element->class & CGROUP_ENTITY)
				act = sweep_aabb_entities(cast_entity(element->parent), &trace);
			act.hit.element = element;
			__builtin_printf("T: %f ht %f, %f %f\n", act.time, act.hit.time, act.hit.normal.x, act.hit.normal.y);
			if (act.time < sweep.time)
				sweep = act;
		}
		current = current->next;
	}
	return (sweep);
}
