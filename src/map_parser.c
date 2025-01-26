/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:59:33 by dderny            #+#    #+#             */
/*   Updated: 2025/01/25 10:59:34 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <get_next_line.h>
#include <fcntl.h>

typedef struct s_map {
	int	*grid;
	int	w;
	int	h;
}	t_map;

t_map	*load_map(char *path)
{
	t_map	*map;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while ()
	{

	}
	close(fd);
}