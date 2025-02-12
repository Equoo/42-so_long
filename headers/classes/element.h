/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:35 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 18:28:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H
# include <mlx_int.h>
# include "vector2d.h"

typedef struct s_element
{
	void		*parent;
	char		*name;
	int			id;
	t_float2d	pos;
	int			z;

	void		(*draw)(struct s_element *self, t_img *buffer);
	void		(*del)(struct s_element *self);
}				t_element;

t_element		*ft_element(void);
void			element_draw(t_element *self, t_img *buffer);
void			element_del(t_element *self);

#endif