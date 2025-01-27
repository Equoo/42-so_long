/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:46:50 by dderny            #+#    #+#             */
/*   Updated: 2025/01/27 15:45:53 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

#define TIME_PARSE "se.exec_start"

double	ft_atof(const char *str)
{
	long long	nbr;
	long long	precision;
	long long	precc;
	int			len;

	nbr = ft_atoll(str);
	while (*str != '.')
		str++;
	str++;
	precision = ft_atoll(str);
	precc = precision;
	len = 1;
	while (precc != 0)
	{
		precc /= 10;
		len *= 10;
	}
	return ((double)nbr + ((double)precision / len));
}

double	uptime(void)
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
