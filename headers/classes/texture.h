/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:50:41 by dderny            #+#    #+#             */
/*   Updated: 2025/02/13 11:52:02 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# include <libft.h>
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
	void		*mlx;
	t_img		*img;
	t_img		*invert;
	t_frame		*frames;
	t_slice		*slices;
	int			nb_frames;
	int			nb_slices;
	int 		width;
	int			height;
}			t_texture;

void			texture_draw_slice(t_texture *self, t_img *buffer, t_int2d pos, char *slice);
void			texture_draw_anim(t_texture *self, t_img *buffer, t_int2d pos, char *slice, double cycle);
void			texture_blend_slice(t_texture *self, t_img *buffer, t_int2d pos, char *slice);
void			texture_blend_anim(t_texture *self, t_img *buffer, t_int2d pos, char *slice, double cycle);
t_frame			texture_get_frame(t_texture *self, char *slice);
t_frame			texture_get_cycle_frame(t_texture *self, char *slice, double cycle);
int				read_texture_data(t_texture *texture, char *path);

t_list			**texture_cache();
void			texture_del(t_texture **self);
t_texture		*ft_texture(char *path, void *mlx);

#endif