/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 00:10:48 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2D_H
# define VECTOR2D_H

# define FOUR_2D_DIRS {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}
# define DIR_BOTTOM 3
# define DIR_LEFT 1
# define DIR_RIGHT 2
# define DIR_TOP 0

typedef struct s_float2d
{
	float		x;
	float		y;
}				t_float2d;

typedef struct s_faabb
{
	t_float2d	a;
	t_float2d	b;
}				t_faabb;

typedef struct s_int2d
{
	int			x;
	int			y;
}				t_int2d;

typedef struct s_iaabb
{
	t_int2d		a;
	t_int2d		b;
}				t_iaabb;

typedef struct s_transform
{
	t_int2d		pos;
	t_int2d		scale;
	int			angle;
}				t_transform;

t_float2d		float2d_add(t_float2d self, t_float2d other);
void			float2d_sub(t_float2d *self, t_float2d *other);
void			float2d_scale(t_float2d *self, float factor);
float			float2d_dot(t_float2d *self, t_float2d *other);
void			float2d_normalize(t_float2d *self);
float			float2d_length(t_float2d *self);

void			float2d_del(t_float2d *self);
t_float2d		*ft_float2d(float x, float y);

t_int2d			int2d_add(t_int2d self, t_int2d other);
void			int2d_sub(t_int2d *self, t_int2d *other);
void			int2d_scale(t_int2d *self, int factor);
int				int2d_dot(t_int2d *self, t_int2d *other);
void			int2d_normalize(t_int2d *self);
int				int2d_length(t_int2d *self);

void			int2d_del(t_int2d *self);
t_int2d			*ft_int2d(int x, int y);

#endif
