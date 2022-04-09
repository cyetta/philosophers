/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:13:12 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/02 19:27:40 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTIL_H
# define FT_UTIL_H
# define ERR_ARGUMENT 1

int	ft_strlen(char *str);
int	ft_puts(char *str);
int	ft_putsn(char *str);
int	ft_atoi(const char *str);
int	ft_atoi_ovfl(const char *str, int *resault);
#endif
