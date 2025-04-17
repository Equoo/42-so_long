/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:00:27 by dderny            #+#    #+#             */
/*   Updated: 2025/04/17 22:25:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_H
# define COLLISIONS_H

# include "classes/terrain.h"
#include "ft_bool.h"
# include "vector2d.h"

#define TR_STEP_SIZE 0.01
#define TR_GRID_SIZE 16

typedef struct s_trace
{
	t_float2d	from;
	t_float2d	to;
	t_faabb		hull;
	int			mask;
	int			ignore;
	t_bool		hit;
	t_float2d	hitpos;
	t_float2d	normal;
}	t_trace;

typedef struct s__bresenham
{
	t_float2d	pos;
	t_float2d	last_pos;
	t_float2d	delta;
	t_int2d		step;
	double		err;
}	t__bresenham;

float	aabb_w(t_faabb hull);
float	aabb_h(t_faabb hull);

t_trace	collide_aabb(t_scene *scene, t_trace traceinfo);
t_trace	swept_aabb(t_scene *scene, t_trace trace);

#endif
