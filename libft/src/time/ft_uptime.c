/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uptime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:28:29 by dderny            #+#    #+#             */
/*   Updated: 2025/02/12 15:00:16 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_time.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

double	ft_uptime(void)
{
	int		fd;
	int		len;
	char	line[256];
	char	*timestr;
	double	time;

	time = 0;
	fd = open("/proc/self/sched", O_RDONLY);
	if (fd < 0)
		return (-1);
	len = read(fd, line, 255);
	close(fd);
	line[len] = 0;
	if (len == -1)
		return (-1);
	timestr = ft_strnstr(line, TIME_PARSE, len);
	if (timestr)
	{
		while (!ft_isdigit(*timestr))
			timestr++;
		time = ft_atof((const char *)(timestr)) / 1000;
	}
	return (time);
}
