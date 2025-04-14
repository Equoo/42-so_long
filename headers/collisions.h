/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 22:00:27 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:28 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_H
# define COLLISIONS_H

# include "classes/terrain.h"
# include "vector2d.h"

#define TR_STEP_SIZE 0.01
#define TR_GRID_SIZE 16

typedef struct s__trace
{
	t_float2d	gpos;
	t_float2d	delta;
	t_float2d	last_pos;
	t_int2d		step;
	double		err;
}	t__trace;

int trace_grid(t_float2d start, t_float2d end, t_terrain *terrain,
	t_float2d *res);
int	swept_aabb_grid(t_faabb from_to, t_faabb hull, t_terrain *terrain,
	t_float2d *res, t_float2d *normal);

#endif
