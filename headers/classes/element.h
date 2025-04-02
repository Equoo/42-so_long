/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:35 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 19:17:12 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

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
	double		last_anim_time;
	double		cycle;
	t_texture	*texture;
	t_float2d	txt_off_pos;


	void		(*update)(struct s_element *self);
	void		(*draw)(struct s_element *self, t_render *render);
	void		(*del)(struct s_element **self);
}				t_element;

void			element_update(t_element *self);

t_element		*ft_element(t_scene *scene);
t_element		*cast_element(void *element);
void			element_del(t_element **self);

#endif

