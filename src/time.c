/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:46:50 by dderny            #+#    #+#             */
/*   Updated: 2025/01/12 16:46:17 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <get_next_line.h>

#define TIME_PARSE "now at "
#define TENE9 1000000000

double	ft_uptime()
{
	int		fd;
	int		len;
	char	line[128];
	char	*timestr;
	double	time;

	time = 0;
	fd = open("/proc/timer_list", O_RDONLY);
	if (fd < 0)
		return (-1);
	len = read(fd, line, 127);
	line[len] = 0;
	if (len == -1)
		return (-1);
	timestr = ft_strnstr(line, TIME_PARSE, len);
	if (timestr)
		time = (double)ft_atoll((const char *)(timestr + 7)) / TENE9;
	close(fd);
	return (time);
}