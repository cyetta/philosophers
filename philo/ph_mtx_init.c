/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mtx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 01:44:43 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 00:43:42 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "philo.h"

int	ph_mtx_init(t_ph_mtx *mtx)
{
	if (pthread_mutex_init(&mtx->mtx_fork, NULL))
		return (ERR_INIT_PTH_ARR);
	else if (pthread_mutex_init(&mtx->mtx_islive, NULL))
	{
		pthread_mutex_destroy(&mtx->mtx_fork);
		return (ERR_INIT_PTH_ARR);
	}
	else if (pthread_mutex_init(&mtx->mtx_eatcnt, NULL))
	{
		pthread_mutex_destroy(&mtx->mtx_islive);
		pthread_mutex_destroy(&mtx->mtx_fork);
		return (ERR_INIT_PTH_ARR);
	}
	else if (pthread_mutex_init(&mtx->mtx_lasteat, NULL))
	{
		pthread_mutex_destroy(&mtx->mtx_eatcnt);
		pthread_mutex_destroy(&mtx->mtx_islive);
		pthread_mutex_destroy(&mtx->mtx_fork);
		return (ERR_INIT_PTH_ARR);
	}
	return (0);
}

int	ph_mtx_dest(t_ph_mtx *mtx)
{
	pthread_mutex_destroy(&mtx->mtx_lasteat);
	pthread_mutex_destroy(&mtx->mtx_eatcnt);
	pthread_mutex_destroy(&mtx->mtx_islive);
	pthread_mutex_destroy(&mtx->mtx_fork);
	return (0);
}

int	create_mutex(t_ph_param *params)
{
	int	i;

	if (pthread_mutex_init(&params->mtx_print, NULL))
		return (ERR_INIT_PH_ARR);
	i = -1;
	while (++i < params->numb_philo)
		if (ph_mtx_init(&params->mtx_arr_forks[i]))
			break ;
	if (i != params->numb_philo)
	{
		while (--i >= 0)
			ph_mtx_dest(&params->mtx_arr_forks[i]);
		pthread_mutex_destroy(&params->mtx_print);
		return (ERR_INIT_PH_ARR);
	}
	return (0);
}
