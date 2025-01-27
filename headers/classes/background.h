/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 09:28:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_H
# define BACKGROUND_H
# include "element.h"

typedef struct s_background
{
	t_element	*base;
	char		*texture;

	void		(*del)(t_background *self);
}				t_background;

t_background	*ft_background(void);

void			background_del(void);

#endif