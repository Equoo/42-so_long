/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seed.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:00:53 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 20:07:11 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEED_H
# define SEED_H

/**
** @brief Get the seed
**
** @return int* The seed
*/
int	*getseed(void);

/**
** @brief return a random number
**
** @return int the random number
*/
int	rand_int(void);

#endif