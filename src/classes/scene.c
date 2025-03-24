/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:59:29 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 03:16:47 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/scene.h"
#include "classes/element.h"

#include <ft_vector.h>
#include <libft.h>

void	scene_del(void *self)
{
	t_scene		*scene;
	t_element	*terrain;
	int 		i;

	scene = (t_scene *)self;
	i = 0;
	while (scene->elements.data && i < scene->elements.size)
	{
		((t_element *)scene->elements.data + i * sizeof(t_element *))->del(
				(void *)scene->elements.data + i * sizeof(t_element *));
		i++;
	}
	if (scene->elements.data)
		vec_destroy(&scene->elements);
	terrain = cast_element(scene->terrain);
	if (terrain)
		terrain->del(&terrain);
	if (scene->name)
		free(scene->name);
	free(scene);
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
		scene_del(scene);
		return (NULL);
	}
	return (scene);
}

t_scene	*cast_scene(void *scene)
{
	if (!scene)
		return (NULL);
	return ((t_scene *)(((uint64_t *)scene))[1]);
}
