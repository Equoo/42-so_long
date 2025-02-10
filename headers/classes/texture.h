/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/02/10 04:03:17 by dderny           ###   ########.fr       */
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
	int			nb_frames;
	int			nb_slices;
	int 		width;
	int			height;
}				t_texture;

t_list			**texture_cache();
void			texture_del(t_texture *self, void *mlx);
t_texture		*ft_texture(char *path, void *mlx);

#endif