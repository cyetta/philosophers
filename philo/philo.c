/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:39:59 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/23 17:30:08 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ft_error.h"
#include "ft_util.h"
#include "philo.h"

int	end_smltn_check(t_philo *ph)
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
		// if (ph->param->numb_ph_eat)
		// 	if (ph->eat_cnt++ >= ph->param->numb_ph_eat)
		// 		break ;
void	*philosoph(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	pthread_detach(ph->ph_thread);
	// ph_msg(ph, "philosoph start");
	ph->is_live = 1;
	if (ph->ph_num % 2)
	  	usleep(1000);
	while (!ph->param->end_smltn && ph->is_live)
	{
		take_a_fork(ph);
		gettimeofday(&ph->last_eat, NULL);
		ph_msg(ph, "is eating\n");
		ft_msleep(ph->param->time_to_eat);
		ph->eat_cnt++;
		put_a_fork(ph);
		ph_msg(ph, "is sleeping\n");
		ft_msleep(ph->param->time_to_sleep);
		ph_msg(ph, "is thinking\n");
	}
	ph->is_live = 0;
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
	if (params->numb_philo < 1 || params->time_to_die < 1 || \
	params->time_to_eat < 1 || params->time_to_sleep < 1)
		return (1);
	if (argc == 6 && ft_atoi_ovfl(argv[5], &params->numb_ph_eat))
		return (1);
	if (argc == 6 && params->numb_ph_eat < 0)
		return (1);
	if (argc == 5)
		params->numb_ph_eat = 0;
	params->end_smltn = 0;
	return (0);
}

int	ph_control(t_ph_param *params, t_philo *ph_arr)
{
	int			i;
	int			all_eat;
	int			t_lasteat;

	while (!params->end_smltn)
	{
		i = -1;
		all_eat = 0;
		while (++i < params->numb_philo)
		{
			t_lasteat = ft_timestamp(ph_arr[i].last_eat);
			if (t_lasteat > params->time_to_die)
			{
				ph_msg_died(&ph_arr[i]);
				return (0);
			}
			if (params->numb_ph_eat)
				if (ph_arr[i].eat_cnt >= params->numb_ph_eat)
					all_eat++;
		}
		if (all_eat == params->numb_philo)
			params->end_smltn = 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_ph_param	params;
	t_philo		*ph_arr;

	ph_arr = NULL;
	if (argc != 5 && argc != 6)
		return (ft_error(ERR_ARGUMENT));
	if (load_parameters(&params, argc, argv))
		return (ft_error(ERR_ARGUMENT));
	if (init_ph(&params, &ph_arr))
		return (ft_error(ERR_INIT_PH_ARR));
	ph_control(&params, ph_arr);
	clear_ph(&params, ph_arr);
}
	// while (++i < params.numb_philo)
	// 	pthread_create;

	// int i;
	// i = -1;
	// while (++i < 20)
	// 	printf("Sleep %ld ms\n", ft_msleep(1500));
/*
printf("Number_of_philosophers %d\ntime_to_die %d\ntime_to_eat %d\n\
time_to_sleep %d\n[number_of_times_each_philosopher_must_eat] %d\n", \
params.numb_philo, params.time_to_die, params.time_to_eat, \
params.time_to_sleep, params.numb_ph_eat);
*/
