/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/02/10 19:52:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <mlx.h>
#include "classes/texture.h"
#include "error.h"

t_list	**texture_cache()
{
	static t_list	*cache = NULL;
	return (&cache);
}

void	texture_del(t_texture *self, void *mlx)
{
	if (self->frames)
		free(self->frames);
	if (self->slices)
		free(self->slices);
	if (self->img)
		mlx_destroy_image(mlx, self->img);
	if (self->invert)
		mlx_destroy_image(mlx, self->invert);
	if (self->path)
		free(self->path);
	free(self);
}

/**
** Create a new texture
** @param path: the path of the texture
** @param mlx: the mlx pointer
** @return the texture
*/
t_texture	*ft_texture(char *path, void *mlx)
{
	t_texture	*tex;
	t_list		*cache;

	tex = NULL;
	cache = *texture_cache();
	while (cache)
	{
		tex = (t_texture *)cache->content;
		if (!ft_strncmp(tex->path, path, ft_strlen(tex->path)))
			break ;
		cache = cache->next;
	}
	if (!tex)
	{
		errno = 0;
		tex = ft_calloc(1, sizeof(t_texture));
		if (!tex)
			return (NULL);
		tex->path = ft_strdup(path);
		tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
		if (errno)
			print_error("Texture data parsing");
		if (!tex->path || !tex->img || read_texture_data(&tex, path))
			delete_texture(tex);
	}
	return (tex);
}
