/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:40:06 by dderny            #+#    #+#             */
/*   Updated: 2025/03/28 16:48:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISIONS_H
# define COLLISIONS_H

# include "classes/terrain.h"
# include "classes/vector2d.h"

#define TR_STEP_SIZE 0.1
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
	t_float2d *res);

#endif
