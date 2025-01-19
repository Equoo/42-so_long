/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/01/19 14:11:27 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include <mlx_int.h>
# include "vector2d.h"

typedef struct s_slice
{
	char		*name;
	int			animation;
	int			from;
	int			to;
	int			duration;
}				t_slice;

typedef struct s_texture
{
	t_img		*img;
	t_iaabb		*frames;
	t_slice		*slices;
}				t_texture;

void			float2d_add(t_texture *self, t_texture *other);
void			float2d_sub(t_texture *self, t_texture *other);
void			float2d_scale(t_texture *self, float factor);
float			float2d_dot(t_texture *self, t_texture *other);
void			float2d_normalize(t_texture *self);
float			float2d_length(t_texture *self);

void			texture_del(t_texture *self);
t_texture		*ft_texture(float x, float y);

#endif