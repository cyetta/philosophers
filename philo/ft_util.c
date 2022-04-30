/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:12:58 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/30 21:28:23 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_util.h"

/*
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_puts(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	ft_putsn(char *str)
{
	int	cnt;

	cnt = write(1, str, ft_strlen(str));
	return (cnt + write(1, "\n", 1));
}
*/
/*
return ms elapsed since tv
 */
long	ft_timestamp(t_timeval tv)
{
	t_timeval	ctv;
	t_timeval	dtv;

	gettimeofday(&ctv, NULL);
	dtv.tv_sec = ctv.tv_sec - tv.tv_sec;
	dtv.tv_usec = ctv.tv_usec - tv.tv_usec;
	if (dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	// dtv.tv_usec += 500;
	dtv.tv_sec += ((dtv.tv_usec + 500) / 1000000);
	dtv.tv_usec = (dtv.tv_usec + 500) % 1000000;
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

/*
return ms elapsed since tv with precision delta (0..999)usec
 */
long	ft_timestamp_p(t_timeval tv, unsigned int delta)
{
	t_timeval	ctv;
	t_timeval	dtv;

	gettimeofday(&ctv, NULL);
	dtv.tv_sec = ctv.tv_sec - tv.tv_sec;
	dtv.tv_usec = ctv.tv_usec - tv.tv_usec;
	if (dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	if (1000 - dtv.tv_usec % 1000 < delta)
	{
		if (dtv.tv_usec + 1000 > 1000000)
			dtv.tv_sec++;
		dtv.tv_usec = (dtv.tv_usec + 1000) % 1000000;
	}
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

/*
usleep ms millisecond
*/
long	ft_msleep(long ms)
{
	t_timeval	ctv;
	long		dt;
	useconds_t	delta;

	if (ms <= 0)
		return (0);
	gettimeofday(&ctv, NULL);
	if (ms > 5)
		usleep((ms - 5) * 1000);
	delta = 50;
	dt = ft_timestamp(ctv);
	while (dt < ms)
	{
		usleep(delta);
		dt = ft_timestamp(ctv);
	}
	return (dt);
}
