/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:52:01 by dderny            #+#    #+#             */
/*   Updated: 2025/03/21 20:19:51 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/texture.h"
#include "error.h"
#include <errno.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <libft.h>

static int	parse_data_lineargs(t_texture *tex, int n, int startn, char *line)
{
	char	**splited;
	char	*name;

	splited = ft_split(line, ' ');
	name = NULL;
	if (!splited)
		return (print_error("Texture data parsing"));
	if (ft_arraylen((void **)splited) != 4)
		return (print_cerror("Texture data parsing", ERRTEXARGS));
	if (tex->slices)
	  name = ft_strdup(splited[0]);
	if (!errno && name && tex->slices)
		tex->slices[n - startn] = (t_slice){name, ft_atoi(splited[1]),
			ft_atoi(splited[2]), ft_atoi(splited[3])};
	else if (!errno && tex->frames)
		tex->frames[n - startn] = (t_frame){(t_int2d){ft_atoi(splited[0]),
			ft_atoi(splited[1])}, (t_int2d){ft_atoi(splited[2]),
			ft_atoi(splited[3])}};
	ft_freearray((void **)splited);
	return (errno);
}

static int	parse_data_line(t_texture *tex, int n, char *line)
{
	static int	startn;

	if (!tex->frames && !ft_strncmp(line, "frames", 6))
	{
		startn = n + 1;
		tex->nb_frames = ft_atoi(line + 6);
		tex->frames = ft_calloc(tex->nb_frames, sizeof(t_frame));
		if (!tex->frames)
			return (errno);
		return (0);
	}
	if (tex->frames && !tex->slices && !ft_strncmp(line, "slices", 6))
	{
		startn = n + 1;
		tex->nb_slices = ft_atoi(line + 6);
		tex->slices = ft_calloc(tex->nb_slices, sizeof(t_slice));
		if (!tex->slices)
			return (errno);
		return (0);
	}
	return (parse_data_lineargs(tex, n, startn, line));
}

static char	*get_data_path(char *path)
{
	char	*data_path;

	path = ft_strdup(path);
	if (!path)
		return (NULL);
	path[ft_strlen(path) - 4] = 0;
	data_path = ft_strjoin(path, ".data.xpm");
	free(path);
	return (data_path);
}

int	read_texture_data(t_texture *tex, char *path)
{
	int		fd;
	char	*line;
	int		i;

	path = get_data_path(path);
	if (path)
		fd = open(path, O_RDONLY);
	if (!path || fd == -1)
		return (print_error("Texture data parsing"));
	i = 0;
	line = (char *)1;
	while (!errno && line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		errno = parse_data_line(tex, i, line);
		free(line);
		i++;
	}
	if (!errno && (!tex->frames || !tex->slices))
		print_cerror("Texture data parsing", ERRTEXNOFS);
	free(path);
	return (errno);
}
