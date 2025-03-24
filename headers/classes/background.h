/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:56:50 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 17:25:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_H
# define BACKGROUND_H

# include "classes/element.h"
# include "classes/texture.h"

typedef struct s_background
{
	t_element	*base;
	t_texture	*back_1;
	t_texture	*back_2;
}				t_background;

void			background_draw(t_element *self, t_img *buffer);

t_background	*ft_background(t_scene *scene);
void			background_del(t_element **self);

#endif
