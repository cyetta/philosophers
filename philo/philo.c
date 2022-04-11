/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:39:59 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/11 21:28:20 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include "ft_error.h"
#include "ft_util.h"
#include "philo.h"

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

void	ph_msg(t_philo *ph, char *msg)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	if (!ph->param->end_smltn)
		printf("%ld %d %s\n", ft_timestamp(ph->param->start), ph->ph_num, msg);
	pthread_mutex_unlock(&ph->param->mtx_print);
}

void	take_a_fork(t_philo *ph)
{
	if (ph->ph_num == ph->param->numb_philo)
	{
		pthread_mutex_lock(ph->mtx_lforks);
		pthread_mutex_lock(ph->mtx_rforks);
	}
	else
	{
		pthread_mutex_lock(ph->mtx_rforks);
		pthread_mutex_lock(ph->mtx_lforks);
	}
	ph_msg(ph, "take a fork\n");
}

void	put_a_fork(t_philo *ph)
{
	pthread_mutex_unlock(ph->mtx_rforks);
	pthread_mutex_unlock(ph->mtx_lforks);
}

void	*ph_msg_died(t_philo *ph)
{
	pthread_mutex_lock(&ph->param->mtx_print);
	put_a_fork(ph);
	ph->param->end_smltn = 1;
	ph->is_die = 1;
	printf("%ld %d is died\n", ft_timestamp(ph->param->start), ph->ph_num);
	pthread_mutex_unlock(&ph->param->mtx_print);
	return (NULL);
}

int	end_smltn_chek(t_philo *ph)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&ph->param->mtx_smltn);
	if (ph->param->end_smltn)
		ret++;
	pthread_mutex_unlock(&ph->param->mtx_smltn);
	return (ret);
}

		// if (ft_timestamp(ph->last_eat) > ph->param->time_to_die)
		// 	return (ph_msg_died(ph));
void	*philosoph(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	pthread_detach(ph->ph_thread);
	ph_msg(ph, "philosoph live");
	if (ph->ph_num % 2)
		usleep(1000);
	while (!end_smltn_chek(ph))
	{
		take_a_fork(ph);
		gettimeofday(&ph->last_eat, NULL);
		ph_msg(ph, "is eating\n");
		usleep(ph->param->time_to_eat * 1000);
		put_a_fork(ph);
		if (ph->param->numb_ph_eat)
			ph->eat_cnt++;
		ph_msg(ph, "is sleeping\n");
		usleep(ph->param->time_to_sleep * 1000);
		ph_msg(ph, "is thinking\n");
	}
	return (NULL);
}

int	load_parameters(t_ph_param *params, int argc, char **argv)
{
	memset(params, 0, sizeof(t_ph_param));
	if (ft_atoi_ovfl(argv[1], &params->numb_philo) || \
	ft_atoi_ovfl(argv[2], &params->time_to_die) || \
	ft_atoi_ovfl(argv[3], &params->time_to_eat) || \
	ft_atoi_ovfl(argv[4], &params->time_to_sleep))
		return (1);
	if (params->numb_philo < 2 || params->time_to_die < 1 || \
	params->time_to_eat < 1 || params->time_to_sleep < 1)
		return (1);
	if (argc == 6 && ft_atoi_ovfl(argv[5], &params->numb_ph_eat))
		return (1);
	if (argc == 6 && params->numb_ph_eat < 1)
		return (1);
	if (argc == 5)
		params->numb_ph_eat = -1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_ph_param	params;
	t_philo		*ph_arr;
	int			i;

	ph_arr = NULL;
	if (argc != 5 && argc != 6)
		return (ft_error(ERR_ARGUMENT));
	if (load_parameters(&params, argc, argv))
		return (ft_error(ERR_ARGUMENT));
	printf("Number_of_philosophers %d\ntime_to_die %d\ntime_to_eat %d\n\
time_to_sleep %d\n[number_of_times_each_philosopher_must_eat] %d\n", \
params.numb_philo, params.time_to_die, params.time_to_eat, \
params.time_to_sleep, params.numb_ph_eat);
	if (init_ph(&params, &ph_arr))
		return (ft_error(ERR_INIT_PH_ARR));
	i = -1;


	usleep(1000000);
	clear_ph(&params, ph_arr);
}
	// while (++i < params.numb_philo)
	// 	pthread_create;
