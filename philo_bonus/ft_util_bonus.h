/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:13:12 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:15:31 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTIL_BONUS_H
# define FT_UTIL_BONUS_H
# include <sys/time.h>

typedef struct timeval	t_timeval;

int		ft_atoi(const char *str);
int		ft_atoi_ovfl(const char *str, int *resault);
long	ft_timestamp(t_timeval tv);
long	ft_msleep(long ms);
int		ft_strlen(const char *s);
int		ft_itoasz(int n);
char	*ft_itoa2buf(int n, char *buf, int pos);
#endif
