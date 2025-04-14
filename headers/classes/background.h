/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:50 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_H
# define BACKGROUND_H

# include "classes/element.h"
#include "render.h"
# include "texture.h"

typedef struct s_background
{
	t_element	*base;
	t_texture	*back_1;
	t_texture	*back_2;
}				t_background;

void			background_draw(t_element *self, t_render *render);

t_background	*ft_background(t_scene *scene);
void			background_del(t_element **self);

#endif
