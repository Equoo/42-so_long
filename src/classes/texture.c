/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/28 16:21:40 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "texture.h"

t_list	**texture_cache()
{
	static t_list	*cache = NULL;
	return (&cache);
}

static void parse_texture_data(t_texture *texture, int n, char *line)
{
	static int	startn;
	char		**splited;
	
	if (!texture->frames && !ft_strncmp(line, "frames", 6))
	{
		startn = n + 1;
		texture->frames = malloc(sizeof(t_frame) * ft_atoi(line + 6));
		return ;	
	}
	if (texture->frames && !texture->slices && !ft_strncmp(line, "slices", 6))
	{
		startn = n + 1;
		texture->slices = malloc(sizeof(t_slice) * ft_atoi(line + 6));
		return ;
	}
	splited = ft_split(line, ' ');
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
}

static void	read_texture_data(t_texture **texture, char *path)
{
	int	fd;
	char	*line;
	int		i;

	errno = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		perror("Loading data texture");
		*texture = NULL;
		return ;
	}
	i = 0;
	line = (char *)1;
	while (!errno && line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_texture_data(texture, i, line);
		i++;
	}
	if (errno)
		*texture = NULL;
}

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
		read_texture_data(&texture, path);
	}
	return (texture);
}
