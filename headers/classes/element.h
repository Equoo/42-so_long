/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:35 by dderny            #+#    #+#             */
/*   Updated: 2025/04/18 16:46:39 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

#include "ft_bool.h"
# include "scene.h"
# include "texture.h"
# include "vector2d.h"
# include "render.h"

# include <mlx_int.h>
# include <unistd.h>

typedef struct s_element
{
	void		*base;
	void		*parent;
	t_class		class;
	int			id;
	t_scene		*scene;
	t_float2d	pos;
	int			zindex;
	char		*anim;
	double		force_anim_time;
	double		last_anim_time;
	double		cycle;
	t_texture	*texture;
	t_float2d	txt_off_pos;

	void		(*play_anim)(struct s_element *self, char *anim_name);
	void		(*internal_update)(struct s_element *self);
	void		(*update)(struct s_element *self);
	void		(*anim_coroutine)(struct s_element *self, t_render *render);
	void		(*draw)(struct s_element *self, t_render *render);
	void		(*del)(struct s_element **self);
}				t_element;

void			element_internal_update(t_element *self);
void			element_play_anim(t_element *self, char *anim_name);

t_element		*ft_element(t_scene *scene);
t_element		*cast_element(void *element);
void			element_del(t_element **self);

#endif

