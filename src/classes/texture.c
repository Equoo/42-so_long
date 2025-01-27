/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 01:14:36 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 21:43:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include <fcntl.h>
#include "texture.h"

static void	texture_lstdel(t_list *lst)
{
	free(lst);
}

t_list	**texture_cache()
{
	static t_list	*cache = NULL;
	return (&cache);
}

static void	read_texture_data(t_texture *texture, char *path)
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
		return (NULL);
	}
	i = 0;
	line = (char *)1;
	while (!errno && line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		
		i++;
	}
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
		read_texture_data(texture, path);
	}
	return ();
}
