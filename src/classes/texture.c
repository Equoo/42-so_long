/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/02/07 01:44:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
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
		texture->frames = malloc(sizeof(t_frame) * ft_atoi(line + 6));
		if (!texture->frames)
			return (ENOMEM);
		return (0);	
	}
	if (texture->frames && !texture->slices && !ft_strncmp(line, "slices", 6))
	{
		startn = n + 1;
		texture->slices = malloc(sizeof(t_slice) * ft_atoi(line + 6));
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
	if (splited)
		ft_destroy2darray(splited);
	return (0);	
}

static int	read_texture_data(t_texture **texture, char *path)
{
	int	fd;
	char	*line;
	int		i;

	errno = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Loading data texture"));
	i = 0;
	line = (char *)1;
	while (!errno && line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		errno = parse_texture_data(texture, i, line);
		i++;
	}
	if (errno)
		return (errno);
	return (0);
}

/*
** Create a new texture
** @param path: the path of the texture
** @return the texture
*/
t_texture	*ft_texture(char *path)
{
	t_texture	*texture;
	t_list		*cache;

	texture = NULL;
	cache = *texture_cache();
	while (cache)
	{
		texture = (t_texture *)cache->content;
		if (!ft_strncmp(texture->path, path, ft_strlen(texture->path)))
			break ;
		cache = cache->next;
	}
	if (!texture)
	{
		texture = ft_calloc(1, sizeof(t_texture));
		if (!texture)
			return (NULL);
		if (read_texture_data(&texture, path))
		{
			if (texture->frames)
				free(texture->frames);
			if (texture->slices)
				free(texture->slices);
			free(texture);
		}
	}
	return (texture);
}
