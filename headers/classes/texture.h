/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/01/28 13:48:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include <mlx_int.h>
# include "vector2d.h"

typedef struct s_iaabb t_frame;

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
	char		*path;
	t_img		*img;
	t_img		*invert;
	t_frame		*frames;
	t_slice		*slices;
}				t_texture;

//void			float2d_add(t_texture *self, t_texture *other);
//void			float2d_sub(t_texture *self, t_texture *other);
//void			float2d_scale(t_texture *self, float factor);
//float			float2d_dot(t_texture *self, t_texture *other);
//void			float2d_normalize(t_texture *self);
//float			float2d_length(t_texture *self);

t_list			**texture_cache()
void			texture_del(t_texture *self);
t_texture		*ft_texture(char *path);

#endif