/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:35 by dderny            #+#    #+#             */
/*   Updated: 2025/01/28 13:48:42 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H
# include "vector2d.h"

typedef struct s_element
{
	char		*name;
	int			id;
	t_float2d	pos;
	int			z;

	void		(*draw)(t_element *self);
	void		(*del)(t_element *self);
}				t_element;

t_element		*ft_element(void);
void			element_del(t_element *self);

#endif