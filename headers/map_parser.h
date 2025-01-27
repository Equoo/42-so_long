/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:12:45 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 15:45:35 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSER_H
# define MAP_PARSER_H
# include "classes/vector2d.h"

# define MAP_CHARS "01CEP"
# define TLRD_POS {{0, -1}, {-1, 0}, {1, 0}, {0, 1}}

typedef struct s_map
{
	char	*grid;
	int		w;
	int		h;
	int		spawn;
	int		exit;
}			t_map;

int			has_access_to(t_map *map, int *checkedmap, t_int2d pos, t_int2d last);
t_map		*load_map(char *path);

#endif