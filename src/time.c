/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 14:46:50 by dderny            #+#    #+#             */
/*   Updated: 2025/01/13 01:45:43 by dderny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

#define TIME_PARSE "se.avg.last_update_time"
#define TENE9 1000000000

int idproc()
{
	int		fd;
	int		len;
	char	line[64];
	
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	len = read(fd, line, 63);
	close(fd);
	line[len] = 0;
	if (len == -1)
		return (-1);
	return (ft_atoi(line));
}

static char	*getfile(int proc)
{
	char	file[64];
	char	*sproc;

	ft_strlcpy(file, "/proc/", 64);
	sproc = ft_itoa(proc);
	ft_strlcat(file, sproc, 64);
	free(sproc);
	ft_strlcat(file, "/sched", 64);

	return (ft_strdup(file));
}

double	uptime(int proc)
{
	int		fd;
	int		len;
	char	line[2048];
	char	*timestr;
	double	time;
	char	*file;

	file = getfile(proc);
	time = 0;
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
		return (-1);
	len = read(fd, line, 2047);
	close(fd);
	line[len] = 0;
	if (len == -1)
		return (-1);
	timestr = ft_strnstr(line, TIME_PARSE, len);
	if (timestr)
	{
		while (!ft_isdigit(*timestr))
			timestr++;
		time = (double)ft_atoll((const char *)(timestr)) / TENE9;
	}
	return (time);
}
