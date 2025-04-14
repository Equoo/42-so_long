/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:44:26 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "render.h"
# include <libft.h>

# ifndef TICK
#  define TICK 240
# endif

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_gameenv
{
	t_render	render;
	double		time;
	double		frametime;
	u_int		internal_keys[32];
	u_int		internal_last_keys[32];
	u_int		keys_states[32][2];

	void		*scene;
	t_list		*scenes_lst;
}			t_gameenv;

int			render_init(t_gameenv *env);
int			game_init(t_gameenv *env, char *mappath);
int			update(t_gameenv *env);
void		tick(t_gameenv *env);
void		tick_game(t_gameenv *env);
void		tick_render(t_gameenv *env, t_render *render);

int			process_close(t_gameenv *env);

#endif
