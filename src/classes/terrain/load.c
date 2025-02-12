/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:45:56 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 18:30:10 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "classes/terrain.h"
#include "error.h"
#include <errno.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <get_next_line.h>
#include <libft.h>
#include <stdio.h>

static void	check_line(t_terrain *map, int y, char *line)
{
	int	x;

	x = -1;
	while (!errno && ++x + 1 && line[x] && line[x] != '\n')
	{
		if ((!map->grid || !line[map->w] || !x || line[x + 1] == '\n')
			&& line[x] != MAP_WALL)
			errno = ERRMAPWALL;
		if (!ft_strchr(MAP_CHARS, line[x]))
			errno = ERRMAPCHAR;
		if (line[x] == MAP_PLAYER && !map->spawn)
			map->spawn = y * map->w + x;
		else if (line[x] == MAP_PLAYER)
			errno = ERRMAPPLAYER;
		if (line[x] == MAP_EXIT && !map->exit)
			map->exit = y * map->w + x;
		else if (line[x] == MAP_EXIT)
			errno = ERRMAPEXIT;
	}
	if (!map->w)
		map->w = x;
	else if (!errno && map->w != x)
		errno = ERRMAPRECT;
	if (!errno)
		line[map->w] = 0;
}

static void	read_map(int fd, t_terrain *map)
{
	char	*line;
	int		i;

	i = 0;
	line = (char *)1;
	while (!errno && line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		check_line(map, i, line);
		if (!map->grid)
			map->grid = line;
		else
			map->grid = ft_stradd(map->grid, line);
		i++;
	}
	map->h = i;
	if (!errno && map->h < 3)
		errno = ERRMAPWALL;
	if (!errno && (!map->spawn || !map->exit))
		errno = ERRMAPNOPE;
	i = 0;
}

static int	check_access(t_terrain *map)
{
	const int	size = map->w * map->h;
	int			*checkedmap;
	t_int2d		pos;
	int			i;

	i = 0;
	checkedmap = malloc(size * sizeof(int));
	if (!checkedmap)
		return (EXIT_FAILURE);
	while (i < size)
	{
		if (map->grid[i] != MAP_COIN && map->grid[i] != MAP_EXIT && ++i)
			continue ;
		ft_memset(checkedmap, 0, size * sizeof(int));
		pos = (t_int2d){i % map->w, i / map->w};
		if (!terrain_findpath(map, checkedmap, pos, pos))
			break ;
		i++;
	}
	free(checkedmap);
	if (i < size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	terrain_load(t_terrain *map, char *path)
		// VERIFY IF THERE ONE COLLECTIBLE
{
	int fd;

	errno = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1 && print_error(MAPERR_CATEGORY))
		return ;
	read_map(fd, map);
	if (errno && print_error(MAPERR_CATEGORY))
		return ;
	close(fd);
	if (check_access(map) && print_cerror(MAPERR_CATEGORY, ERRMAPPATH))
		return ;
}
