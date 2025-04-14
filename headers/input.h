/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:41:03 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "so_long.h"
# include <sys/types.h>

typedef enum e_key_state
{
	KEY_NONE,
	KEY_PRESSED,
	KEY_DOWN,
	KEY_RELEASED
}	t_key_state;

void	tick_inputs(t_gameenv *env);
int		down_key(int keycode, t_gameenv *env);
int		up_key(int keycode, t_gameenv *env);

int		input_isdown(u_int keycode, t_gameenv *env);
int		input_ispressed(u_int keycode, t_gameenv *env);
int		input_isreleased(u_int keycode, t_gameenv *env);

#endif
