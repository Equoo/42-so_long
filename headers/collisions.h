/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:00:27 by dderny            #+#    #+#             */
/*   Updated: 2025/04/22 14:19:39 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_H
# define COLLISIONS_H

# include "classes/element.h"
# include "ft_bool.h"
# include "scene.h"
# include "vector2d.h"
# include <X11/Xutil.h>

# define TR_STEP_SIZE 0.01
# define TR_GRID_SIZE 16
# define MAX_SWEEP_ITERATIONS 4

typedef struct s_aabb
{
	t_float2d	min;
	t_float2d	max;
	t_float2d	center;
	t_float2d	half;
}				t_aabb;

typedef struct s_hit
{
	t_bool		touch;
	t_element	*element;
	t_float2d	pos;
	t_float2d	normal;
	t_float2d	delta;
	float		time;
}				t_hit;

typedef struct s_sweep
{
	t_hit		hit;
	t_float2d	pos;
	float		time;
}				t_sweep;

typedef struct s_trace
{
	t_float2d	from;
	t_float2d	to;
	t_aabb		hull;
	int			mask;
	int			ignore;
}				t_trace;

float			getsign(float value);
float			aabb_w(t_aabb hull);
float			aabb_h(t_aabb hull);
t_aabb			aabb_from_mm(t_float2d min, t_float2d max);
t_aabb			aabb_from_ch(t_float2d center, t_float2d half);

t_sweep			sweep_aabb(t_aabb hulla, t_aabb hullb, t_float2d delta);
t_sweep			world_sweep_aabb(t_scene *scene, t_trace trace);

#endif
