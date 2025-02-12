/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:58:57 by dderny            #+#    #+#             */
/*   Updated: 2025/02/11 02:33:04 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <errno.h>
#include <string.h>

/*
** Print a custom error message
** @param category: the category of the error
** @param error: the error message
** @return 1
*/
int	print_cerror(char *category, char *error)
{
	ft_printf("Error\n%s: %s\n", category, error);
	return (1);
}

/*
** Print an error message
** @param category: the category of the error
** @return errno
*/
int	print_error(char *category)
{
	print_cerror(category, strerror(errno));
	return (errno);
}
