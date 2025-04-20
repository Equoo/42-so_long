/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:33:50 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2D_H
# define VECTOR2D_H

# define DIR_BOTTOM 3
# define DIR_LEFT 1
# define DIR_RIGHT 2
# define DIR_TOP 0
# define EPSILON 0.001

typedef struct s_float2d
{
	float		x;
	float		y;
}				t_float2d;

typedef struct s_2float2d
{
	t_float2d	a;
	t_float2d	b;
}				t_2float2d;

typedef struct s_int2d
{
	int			x;
	int			y;
}				t_int2d;

typedef struct s_2int2d
{
	t_int2d		a;
	t_int2d		b;
}				t_2int2d;

typedef struct s_transform
{
	t_int2d		pos;
	t_int2d		scale;
	int			angle;
}				t_transform;

t_float2d		float2d_add(t_float2d self, t_float2d other);
t_float2d		float2d_sub(t_float2d self, t_float2d other);
t_float2d		float2d_multiply(t_float2d self, t_float2d other);
t_float2d		float2d_divide(t_float2d self, t_float2d other);
t_float2d		float2d_scale_dived(t_float2d self, float factor);
t_float2d		float2d_scaled(t_float2d self, float factor);
void			float2d_scale(t_float2d *self, float factor);
float			float2d_dot(t_float2d *self, t_float2d *other);
t_float2d		float2d_normalize(t_float2d self);
t_float2d		float2d_abs(t_float2d self);
float			float2d_length(t_float2d self);

void			float2d_del(t_float2d *self);
t_float2d		*ft_float2d(float x, float y);

t_int2d			int2d_add(t_int2d self, t_int2d other);
t_int2d			int2d_sub(t_int2d self, t_int2d other);
t_int2d			int2d_multiply(t_int2d self, t_int2d other);
t_int2d			int2d_divide(t_int2d self, t_int2d other);
t_int2d			int2d_scale_dived(t_int2d self, int factor);
t_int2d			int2d_scaled(t_int2d self, int factor);
void			int2d_scale(t_int2d *self, int factor);
int				int2d_dot(t_int2d *self, t_int2d *other);
t_int2d			int2d_normalize(t_int2d self);
t_int2d			int2d_abs(t_int2d self);
int				int2d_length(t_int2d self);

void			int2d_del(t_int2d *self);
t_int2d			*ft_int2d(int x, int y);

t_int2d	to_int2d(t_float2d vec);
t_float2d	to_float2d(t_int2d vec);

t_transform		t_from_pos(t_int2d pos);

#endif
