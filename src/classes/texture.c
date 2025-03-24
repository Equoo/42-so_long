/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/03/24 04:49:19 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <mlx.h>
#include "classes/texture.h"
#include "render.h"
#include "error.h"

t_list	**texture_cache()
{
	static t_list	*cache = NULL;
	return (&cache);
}

void	texture_del(t_texture **self)
{
	t_texture	*tex;

	tex = *self;
	if (tex->frames)
		free(tex->frames);
	if (tex->slices)
	{
		while (tex->nb_slices--)
      free(tex->slices[tex->nb_slices].name);
    free(tex->slices);
	}
	if (tex->img)
		mlx_destroy_image(tex->mlx, tex->img);
	if (tex->invert)
		mlx_destroy_image(tex->mlx, tex->invert);
	if (tex->path)
		free(tex->path);
	free(tex);
	*self = NULL;
}

static t_texture	*get_from_cache(char *path)
{
	t_list	*cache;
	t_texture	*tex;

	cache = *texture_cache();
	while (cache)
	{
		tex = (t_texture *)cache->content;
		if (!ft_strncmp(tex->path, path, ft_strlen(tex->path) + 1))
			return (tex);
		cache = cache->next;
	}
	return (NULL);
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

	tex = get_from_cache(path);
	if (tex)
		return (tex);
	errno = 0;
	tex = ft_calloc(1, sizeof(t_texture));
	if (!tex && print_error("Texture creation"))
		return (NULL);
	tex->mlx = mlx;
	tex->path = ft_strdup(path);
	tex->img = mylx_xpm_to_img(mlx, path, &tex->width, &tex->height);
	if (errno)
		print_error("Texture data parsing");
	if (!tex->path || !tex->img || read_texture_data(tex, path))
		texture_del(&tex);
	else
		ft_lstadd_front(texture_cache(), ft_lstnew(tex));
	return (tex);
}
