/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:59:29 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 17:45:20 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/scene.h"
#include "classes/terrain.h"

#include <ft_vector.h>
#include <libft.h>

void	scene_del(t_scene **self)
{
	t_scene	*scene;

	scene = *self;
	if (scene->elements.data)
		vec_destroy(&scene->elements);
	if (scene->terrain)
		terrain_del(&scene->terrain);
	if (scene->name)
		free(scene->name);
	free(*self);
	*self = NULL;
}

t_scene	*ft_scene(void *env, char *name)
{
	t_scene	*scene;

	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	*scene = (t_scene){0};
	scene->env = env;
	scene->name = ft_strdup(name);
	if (scene->name)
		scene->elements = vec_new(128, sizeof(t_element));
	if (!scene->name || !scene->elements.data)
	{
		scene_del(&scene);
		return (NULL);
	}
	return (scene);
}
