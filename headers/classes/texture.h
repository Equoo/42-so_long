/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/01/18 22:50:09 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include <mlx_int.h>
typedef struct s_texture
{
	t_img		*img;
	
}				t_texture;

void			float2d_add(t_texture *self, t_texture *other);
void			float2d_sub(t_texture *self, t_texture *other);
void			float2d_scale(t_texture *self, float factor);
float			float2d_dot(t_texture *self, t_texture *other);
void			float2d_normalize(t_texture *self);
float			float2d_length(t_texture *self);

void			float2d_del(t_texture *self);
t_texture		*ft_texture(float x, float y);

#endif