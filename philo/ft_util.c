/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:12:58 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/14 23:34:53 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_util.h"

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
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

/*
usleep ms millisecond
*/
long	ft_msleep(long ms)
{
	t_timeval	ctv;
	long		dt;

	if (ms <= 0)
		return (0);
	gettimeofday(&ctv, NULL);
	if (ms > 10)
		usleep((ms - 10) * 1000);
	dt = ft_timestamp(ctv);
	while (dt < ms)
	{
		usleep(300);
		dt = ft_timestamp(ctv);
	}
	return (dt);
}
