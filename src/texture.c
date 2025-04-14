/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <mlx.h>
#include "texture.h"
#include "render.h"
#include "error.h"

void	texture_del(void *self)
{
	t_texture	*tex;

	tex = (t_texture *)self;
	if (tex->frames)
		free(tex->frames);
	if (tex->slices)
	{
		while (tex->nb_slices-- > 0)
			free(tex->slices[tex->nb_slices].name);
		free(tex->slices);
	}
	if (tex->img)
		mlx_destroy_image(tex->mlx, tex->img);
	if (tex->path)
		free(tex->path);
	free(tex);
}

static t_texture	*get_from_cache(t_render *render, char *path)
{
	t_list	*cache;
	t_texture	*tex;

	cache = render->textures;
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
t_texture	*ft_texture(t_render *render, char *path)
{
	t_texture	*tex;

	tex = get_from_cache(render, path);
	if (tex)
		return (tex);
	errno = 0;
	tex = ft_calloc(1, sizeof(t_texture));
	if (!tex && print_error("Texture creation"))
		return (NULL);
	tex->mlx = render->mlx;
	tex->path = ft_strdup(path);
	tex->img = mylx_xpm_to_img(render->mlx, path, &tex->width, &tex->height);
	if (errno)
		print_error("Texture data parsing");
	if (!tex->path || !tex->img || read_texture_data(tex, path))
	{
		texture_del(tex);
		return (NULL);
	}
	else
		ft_lstadd_front(&render->textures, ft_lstnew(tex));
	return (tex);
}
