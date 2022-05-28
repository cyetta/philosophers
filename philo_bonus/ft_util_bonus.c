/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:12:58 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:18:43 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_util_bonus.h"

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
	if (ms > 5)
		usleep((ms - 5) * 1000);
	dt = ft_timestamp(ctv);
	while (dt < ms)
	{
		usleep(100);
		dt = ft_timestamp(ctv);
	}
	return (dt);
}

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*s++)
		++len;
	return (len);
}

int	ft_itoasz(int n)
{
	unsigned int	uint;
	int				size;

	size = 0;
	if (n <= 0)
	{
		size = 1;
		uint = -n;
	}
	else
		uint = n;
	while (uint)
	{
		++size;
		uint = uint / 10;
	}
	return (size);
}

char	*ft_itoa2buf(int n, char *buf, int pos)
{
	int				size;
	unsigned int	uint;

	size = ft_itoasz(n);
	if (n < 0)
		uint = -n;
	else
		uint = n;
	buf[pos + size] = '\0';
	while (uint)
	{
		buf[--size + pos] = uint % 10 + '0';
		uint = uint / 10;
	}
	if (n == 0)
		buf[pos] = '0';
	if (n < 0)
		buf[pos] = '-';
	return (buf);
}
