/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:59:33 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 09:13:54 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include <errno.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <get_next_line.h>
#include <libft.h>
#include <stdio.h>

static int	map_error(int error)
{
	if (!error)
		return (0);
	ft_printf("Error\n");
	ft_printf("Invalid map: ");
	if (error == 1)
		ft_printf("Map isn't rectangular.");
	if (error == 2)
		ft_printf("Characters invalid.");
	if (error == 3)
		ft_printf("Double player.");
	if (error == 4)
		ft_printf("Double exit.");
	if (error == 5)
		ft_printf("Not closed by walls.");
	if (error == 6)
		ft_printf("No available path.");
	if (error == 7)
		ft_printf("No player or exit.");
	return (1);
}

static void	check_line(t_map *map, int y, char *line)
{
	int	x;

	x = -1;
	while (!errno && ++x + 1 && line[x] && line[x] != '\n')
	{
		if ((!map->grid || !line[map->w] || !x || line[x + 1] == '\n')
			&& line[x] != '1')
			errno = 5;
		if (!ft_strchr(MAP_CHARS, line[x]))
			errno = 2;
		if (line[x] == 'P' && !map->spawn)
			map->spawn = y * map->w + x;
		else if (line[x] == 'P')
			errno = 3;
		if (line[x] == 'E' && !map->exit)
			map->exit = y * map->w + x;
		else if (line[x] == 'E')
			errno = 4;
	}
	if (!map->w)
		map->w = x;
	else if (!errno && map->w != x)
		errno = 1;
	if (!errno)
		line[map->w] = 0;
}

static void	read_map(int fd, t_map *map)
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
		errno = 1;
	if (!errno && (!map->spawn || !map->exit))
		errno = 7;
	i = 0;
}

int	has_access_to(t_map *map, int *checkedmap, t_int2d pos, t_int2d last)
{
	const int	dir[4][2] = TLRD_POS;
	int			i;
	int			x;
	int			y;

	i = 0;
	while (i < 4)
	{
		x = pos.x + dir[i][0];
		y = pos.y + dir[i][1];
		if (((last.x == x && last.y == y) || checkedmap[map->w * y + x]) && ++i)
			continue ;
		checkedmap[map->w * y + x] = 1;
		if (map->grid[map->w * y + x] == 'P')
			return (1);
		if (map->grid[map->w * y + x] != '1')
			if (has_access_to(map, checkedmap, (t_int2d){x, y}, pos))
				return (1);
		i++;
	}
	return (0);
}

static int	check_access(t_map *map)
{
	const int	size = map->w * map->h;
	int			*checkedmap;
	t_int2d		pos;
	int			i;

	i = 0;
	checkedmap = malloc(size * sizeof(int));
	while (i < size)
	{
		if (map->grid[i] != 'C' && map->grid[i] != 'E' && ++i)
			continue ;
		ft_memset(checkedmap, 0, size * sizeof(int));
		pos = (t_int2d){i % map->w, i / map->w};
		if (!has_access_to(map, checkedmap, pos, pos))
			break ;
		i++;
	}
	free(checkedmap);
	if (i < size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_map	*load_map(char *path) // VERIFY IF THERE ONE COLLECTIBLE
{
	t_map	*map;
	int		fd;

	errno = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		perror("Loading map");
		return (NULL);
	}
	map = ft_calloc(1, sizeof(t_map));
	read_map(fd, map);
	if (errno && map_error(errno))
		return (NULL);
	close(fd);
	if (check_access(map) == EXIT_FAILURE && map_error(6))
		return (NULL);
	return (map);
}
