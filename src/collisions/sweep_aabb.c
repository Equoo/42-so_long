/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sweep_aabb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:09:07 by dderny            #+#    #+#             */
/*   Updated: 2025/04/22 14:25:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collisions.h"
#include "libft.h"

static int	is_intersecting(t_float2d near_time, t_float2d far_time)
{
	return (near_time.x > far_time.y || near_time.y > far_time.x
		|| ft_fmax(near_time.x, near_time.y) >= 1 || ft_fmin(far_time.x,
			far_time.y) <= 0);
}

t_hit	intersect_segment(t_float2d pos, t_float2d delta, t_float2d padding,
		t_aabb hull)
{
	t_float2d	scale;
	t_float2d	sign;
	t_float2d	near_time;
	t_float2d	far_time;
	t_hit		hit;

	scale = float2d_divide((t_float2d){1, 1}, delta);
	sign = (t_float2d){getsign(scale.x), getsign(scale.y)};
	near_time = float2d_multiply(float2d_sub(float2d_sub(hull.center, pos),
				float2d_multiply(sign, float2d_add(hull.half, padding))),
			scale);
	far_time = float2d_multiply(float2d_add(float2d_sub(hull.center, pos),
				float2d_multiply(sign, float2d_add(hull.half, padding))),
			scale);
	if (is_intersecting(near_time, far_time))
		return ((t_hit){.time = 1});
	hit = (t_hit){.touch = 1, .time = ft_fclamp(ft_fmax(near_time.x,
				near_time.y), 0, 1)};
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

	hit = (t_hit){0, NULL, {0}, {0}, {0}, 1};
	d = float2d_sub(hullb.center, hulla.center);
	p = float2d_sub(float2d_add(hullb.half, hulla.half), float2d_abs(d));
	if (p.x <= 0 || p.y <= 0)
		return (hit);
	hit.touch = 1;
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
	t_sweep	sweep;

	sweep = (t_sweep){.time = 1};
	sweep.pos = hulla.center;
	sweep.hit = intersect_aabb(hulla, hullb);
	if (sweep.hit.touch)
		sweep.time = 0;
	if (sweep.hit.touch)
		sweep.hit.time = 0;
	return (sweep);
}

t_sweep	sweep_aabb(t_aabb hulla, t_aabb hullb, t_float2d delta)
{
	t_sweep		sweep;
	t_float2d	dir;

	if (delta.x == 0 && delta.y == 0)
		return (sweep_aabb_static(hulla, hullb));
	sweep = (t_sweep){0};
	sweep.hit = intersect_segment(hulla.center, delta, hulla.half, hullb);
	if (sweep.hit.touch)
	{
		sweep.time = ft_fclamp(sweep.hit.time - EPSILON, 0, 1);
		sweep.pos = float2d_add(hulla.center, float2d_scaled(delta,
					sweep.time));
		dir = float2d_normalize(delta);
		sweep.hit.pos.x = ft_fclamp(sweep.hit.pos.x + dir.x * hulla.half.x,
				hullb.center.x - hulla.half.x, hullb.center.x + hulla.half.x);
		sweep.hit.pos.y = ft_fclamp(sweep.hit.pos.y + dir.y * hulla.half.y,
				hullb.center.y - hulla.half.y, hullb.center.y + hulla.half.y);
	}
	else
	{
		sweep.hit.pos = float2d_add(hulla.center, delta);
		sweep.time = 1;
	}
	return (sweep);
}
