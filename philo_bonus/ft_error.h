/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:06:48 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/24 13:49:10 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H
# define ERR_OK 0
# define ERR_ARGUMENT 1
# define ERR_ATOI_NOTVALUE 2
# define ERR_ATOI_OVER 3
# define ERR_INIT_PH_ARR 4
# define ERR_INIT_PTH_ARR 5
# define ERR_WAITPID 6
# define ERR_UNKNOWN 27

int	ft_error(int errnum);
#endif
