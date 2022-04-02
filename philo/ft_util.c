/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:12:58 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/02 18:20:23 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
