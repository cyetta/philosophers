/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:39:59 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 17:30:38 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include "philo.h"
#include "ft_error.h"
#include "ft_util.h"

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
	return (0);
}

void	*philosoph(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if ((ph->ph_num - 1) % 2)
		usleep(300);
	set_ph_lasteat(ph);
	while (get_ph_stat(ph) == PH_ISLIVE)
	{
		if (take_a_fork(ph))
			break ;
		if (ph_msg(ph, "is eating\n"))
			break ;
		ft_msleep(ph->param->time_to_eat);
		set_ph_lasteat(ph);
		set_ph_eatcnt(ph, ph->eat_cnt + 1);
		put_a_fork(ph);
		if (ph_msg(ph, "is sleeping\n"))
			break ;
		ft_msleep(ph->param->time_to_sleep);
		ph_msg(ph, "is thinking\n");
	}
	set_ph_stat(ph, PH_NOTLIVE);
	return (NULL);
}

int	end_simulation(t_ph_param *params, t_philo *ph_arr)
{
	int	i;

	i = -1;
	while (++i < params->numb_philo)
		set_ph_stat(&ph_arr[i], PH_TODIE);
	return (0);
}

int	ph_control(t_ph_param *params, t_philo *ph_arr)
{
	int			i;
	int			all_eat;
	int			t_lasteat;

	while (1)
	{
		usleep(500);
		i = -1;
		all_eat = 0;
		while (++i < params->numb_philo)
		{
			t_lasteat = ft_timestamp(get_ph_lasteat(&ph_arr[i]));
			if (t_lasteat > params->time_to_die)
				return (ph_msg_died(params, ph_arr, i));
			if (params->numb_ph_eat)
				if (get_ph_eatcnt(&ph_arr[i]) >= params->numb_ph_eat)
					all_eat++;
		}
		if (all_eat == params->numb_philo)
			return (end_simulation(params, ph_arr));
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
	return (0);
}
