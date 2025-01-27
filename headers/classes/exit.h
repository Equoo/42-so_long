/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:32 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 14:37:30 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "entity.h"

typedef struct s_entity t_exit;

t_exit			*ft_exit(void);

void			exit_del(void);

#endif