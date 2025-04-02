/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@42lyon.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:06:41 by dderny            #+#    #+#             */
/*   Updated: 2025/04/02 19:18:38 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "so_long.h"
# include "vector2d.h"
# include <ft_bool.h>
# include <libft.h>

enum e_scene
{
	SCENE_GAME,
	SCENE_MENU
};

typedef enum e_class
{
	CLASS_ELEMENT,
	CLASS_ENTITY,
	CLASS_ACTOR,
	CLASS_PLAYER,
	CLASS_ENEMY,
	CLASS_ITEM,
	CLASS_HUD,
	CLASS_TERRAIN,
	CLASS_BACKGROUND
}	t_class;

typedef struct s_scene
{
	t_gameenv	*env;
	char		*name;
	t_list		*elements;
	t_float2d	cam_pos;
	void		*terrain;
	void		*ply;
	int			seed;
	t_bool		removed;

	void		(*update)(struct s_scene *self);
}	t_scene;

void	scene_del(void *self);
t_scene	*ft_scene(void *env, char *name);

int		scene_add(t_scene *self, void *element);

#endif
