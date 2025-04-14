/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:54:37 by dderny            #+#    #+#             */
/*   Updated: 2025/04/14 22:00:37 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MAPERR_CATEGORY "Loading map"
# define MAPERROR 1000
# define ERRMAPRECT MAPERROR + 1
# define ERRMAPCHAR MAPERROR + 2
# define ERRMAPPLAYER MAPERROR + 3
# define ERRMAPEXIT MAPERROR + 4
# define ERRMAPWALL MAPERROR + 5
# define ERRMAPPATH MAPERROR + 6
# define ERRMAPNOPE MAPERROR + 7

# define TEXTERR_CATEGORY "Loading texture"
# define TEXTERROR 2000
# define ERRTEXARGS TEXTERROR + 1
# define ERRTEXNOFS TEXTERROR + 2

int	print_error(char *category);
int	print_cerror(char *category, int error);

#endif
