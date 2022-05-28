/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:54:25 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:18:28 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error_bonus.h"
#include "ft_util_bonus.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\r' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*
return
0 if no digit found
1 found fist symbol of digit and sign is positive
-1  found fist symbol of digit and sign is negative
str point to fist digit in the string or \0
*/
static int	ft_skip_to_dig(char **str)
{
	int	sign;

	sign = 1;
	while (ft_isspace(**str) && **str)
		(*str)++;
	if (**str == '-' || **str == '+' || ft_isdigit(**str))
	{
		if (ft_isdigit(**str))
			return (sign);
		else if (**str == '-')
			sign = -sign;
		(*str)++;
		if (ft_isdigit(**str))
			return (sign);
	}
	return (0);
}

/*
Converting ascii numbers in the string to integer
If no numbers found returned 2 and result=0
If int32 overflowed returned 1 and result undefined.
If conversion error free, 0 and int32 value are returned.
Conversion ends on last number in the string or on resault overflow,
rest symbols in string not parsed.
*/
int	ft_atoi_ovfl(const char *str, int *result)
{
	unsigned int	res;
	int				sign;
	char			*s;
	int				overflow;

	s = (char *)str;
	res = 0;
	*result = 0;
	sign = ft_skip_to_dig(&s);
	if (sign == 0)
		return (ERR_ATOI_NOTVALUE);
	overflow = ERR_OK;
	while (ft_isdigit(*s) && !overflow)
	{
		if ((res >= 214748364) && \
		((sign == 1 && *s > '7') || (sign == -1 && *s > '8')))
			overflow = ERR_ATOI_OVER;
		res = res * 10 + (unsigned int)(*s - '0');
		s++;
	}
	*result = sign * (int)res;
	if (!ft_isspace(*s) && *s != '\0')
		overflow = ERR_ATOI_NOTVALUE;
	return (overflow);
}

/*
classic atoi
*/
int	ft_atoi(const char *str)
{
	long long int	res;
	int				sign;
	char			*s;

	s = (char *)str;
	res = 0;
	sign = ft_skip_to_dig(&s);
	if (sign == 0)
		return (res);
	while (ft_isdigit(*s))
	{
		res = res * 10 + (long long int)(*s - '0');
		s++;
	}
	return (sign * (int)res);
}
