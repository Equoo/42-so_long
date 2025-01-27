/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 20:49:43 by dderny           ###   ########.fr       */
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
	t_frame		*frames;
	t_slice		*slices;
}				t_texture;

float			texture_draw(t_texture *self, char *slice, float cycle);

t_list			**texture_cache()
void			texture_del(t_texture *self);
t_texture		*ft_texture(char *path);

#endif