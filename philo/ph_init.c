/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 01:46:57 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 00:46:47 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "ft_error.h"
#include "philo.h"

/*
Collect philosophe thread and free mutex and philosophe array
*/
int	clear_ph(t_ph_param *params, t_philo *ph_arr)
{
	int	i;

	i = -1;
	while (++i < params->numb_philo)
	{
		if (ph_arr[i].ph_thread)
			pthread_join(ph_arr[i].ph_thread, NULL);
	}
	i = -1;
	while (++i < params->numb_philo)
		ph_mtx_dest(&params->mtx_arr_forks[i]);
	pthread_mutex_destroy(&params->mtx_print);
	free(ph_arr);
	free(params->mtx_arr_forks);
	return (0);
}

/*
Allocate memory for mutex and philosophe array
*/
int	create_pharr(t_ph_param *params, t_philo **ph_arr)
{
	*ph_arr = (t_philo *) malloc(sizeof(t_philo) * params->numb_philo);
	if (!*ph_arr)
		return (ERR_INIT_PH_ARR);
	memset((void *)*ph_arr, 0, sizeof(t_philo) * params->numb_philo);
	params->mtx_arr_forks = (t_ph_mtx *) malloc(sizeof(t_ph_mtx) \
	* params->numb_philo);
	if (!params->mtx_arr_forks)
	{
		free(*ph_arr);
		return (ERR_INIT_PH_ARR);
	}
	if (create_mutex(params))
	{
		free(*ph_arr);
		free(params->mtx_arr_forks);
		return (ERR_INIT_PH_ARR);
	}
	return (0);
}

/*
Init variable and create philosoph thread
*/
int	lunch_ph(t_ph_param *params, t_philo *philo, int ph_num)
{
	philo->ph_num = ph_num + 1;
	philo->param = params;
	philo->mtx_islive = &params->mtx_arr_forks[ph_num].mtx_islive;
	philo->mtx_eatcnt = &params->mtx_arr_forks[ph_num].mtx_eatcnt;
	philo->mtx_lasteat = &params->mtx_arr_forks[ph_num].mtx_lasteat;
	philo->mtx_lforks = &params->mtx_arr_forks[ph_num].mtx_fork;
	philo->mtx_rforks = &params->mtx_arr_forks[(ph_num + 1) % \
	params->numb_philo].mtx_fork;
	philo->is_live = PH_ISLIVE;
	gettimeofday(&philo->last_eat, NULL);
	if (!pthread_create(&philo->ph_thread, NULL, philosoph, philo))
		return (0);
	philo->is_live = PH_NOTLIVE;
	return (ERR_INIT_PTH_ARR);
}

/*
Creates array of philosophe and start simulation
*/
int	init_ph(t_ph_param *params, t_philo **ph_arr)
{
	int	i;

	if (create_pharr(params, ph_arr))
		return (ERR_INIT_PH_ARR);
	i = -1;
	gettimeofday(&params->time_start, NULL);
	while (++i < params->numb_philo)
		if (lunch_ph(params, &(*ph_arr)[i], i))
			break ;
	if (i == params->numb_philo)
		return (0);
	while (--i >= 0)
		set_ph_stat(&(*ph_arr)[i], PH_TODIE);
	clear_ph(params, *ph_arr);
	return (ERR_INIT_PH_ARR);
}
