/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/02/10 04:19:19 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <mlx.h>
#include "classes/texture.h"
#include "error.h"

t_list	**texture_cache()
{
	static t_list	*cache = NULL;
	return (&cache);
}

static int parse_texture_data(t_texture *texture, int n, char *line)
{
	static int	startn;
	char		**splited;
	
	if (!texture->frames && !ft_strncmp(line, "frames", 6))
	{
		startn = n + 1;
		texture->nb_frames = ft_atoi(line + 6);
		texture->frames = ft_calloc(texture->nb_frames, sizeof(t_frame));
		if (!texture->frames)
			return (ENOMEM);
		return (0);	
	}
	if (texture->frames && !texture->slices && !ft_strncmp(line, "slices", 6))
	{
		startn = n + 1;
		texture->nb_slices = ft_atoi(line + 6);
		texture->slices = ft_calloc(texture->nb_slices, sizeof(t_slice));
		if (!texture->slices)
			return (ENOMEM);
		return (0);	
	}
	splited = ft_split(line, ' ');
	if (!splited)
		return (ENOMEM);
	if (texture->slices)
		texture->slices[n - startn] = (t_slice){
			splited[0],
			ft_atoi(splited[1]),
			ft_atoi(splited[2]),
			ft_atoi(splited[3])
		};
	else if (texture->frames)
		texture->frames[n - startn] = (t_frame){
			(t_int2d){ft_atoi(splited[0]), ft_atoi(splited[1])},
			(t_int2d){ft_atoi(splited[2]), ft_atoi(splited[3])}
		};
	if (ft_arraylen(splited) != 4)
		return (print_cerror("Texture data parsing", "Invalid data, invalid number of arguments"));
	if (splited)
		ft_freearray(splited);
	return (0);	
}

static int	read_texture_data(t_texture **texture, char *path)
{
	int	fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Texture data parsing"));
	i = 0;
	line = (char *)1;
	while (!errno && line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		errno = parse_texture_data(texture, i, line);
		free(line);
		i++;
	}
	if (!(*texture)->frames || !(*texture)->slices)
		return (print_cerror("Texture data parsing", "Invalid data, missing frames or slices"));
	if (errno)
		return (errno);
	return (0);
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
