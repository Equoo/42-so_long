/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:52:01 by dderny            #+#    #+#             */
/*   Updated: 2025/02/10 19:57:24 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include <fcntl.h>
#include "classes/texture.h"

static int parse_data_line(t_texture *tex, int n, char *line)
{
	static int	startn;
	char		**splited;
	
	if (!tex->frames && !ft_strncmp(line, "frames", 6))
	{
		startn = n + 1;
		tex->nb_frames = ft_atoi(line + 6);
		tex->frames = ft_calloc(tex->nb_frames, sizeof(t_frame));
		if (!tex->frames)
			return (ENOMEM);
		return (0);	
	}
	if (tex->frames && !tex->slices && !ft_strncmp(line, "slices", 6))
	{
		startn = n + 1;
		tex->nb_slices = ft_atoi(line + 6);
		tex->slices = ft_calloc(tex->nb_slices, sizeof(t_slice));
		if (!tex->slices)
			return (ENOMEM);
		return (0);	
	}
	return (parse_data_lineargs(tex, n, startn, line));
}

static int parse_data_lineargs(t_texture *tex, int n, int startn, char *line)
{
	char		**splited;

	splited = ft_split(line, ' ');
	if (!splited)
		return (ENOMEM);
	if (tex->slices)
		tex->slices[n - startn] = (t_slice){
			splited[0],
			ft_atoi(splited[1]),
			ft_atoi(splited[2]),
			ft_atoi(splited[3])
		};
	else if (tex->frames)
		tex->frames[n - startn] = (t_frame){
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
