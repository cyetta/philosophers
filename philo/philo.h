/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:04:40 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/10 20:23:15 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_timeval;

typedef struct s_ph_param
{
	int				numb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				numb_ph_eat;
	int				end_smltn;
	t_timeval		start;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	*mtx_forks;
}	t_ph_param;

typedef struct s_philo
{
	t_ph_param		*param;
	int				ph_num;
	pthread_t		ph_thread;
	t_timeval		last_eat;
	pthread_mutex_t	*mtx_rforks;
	pthread_mutex_t	*mtx_lforks;
	int				is_die;
	int				eat_cnt;
}	t_philo;

int		clear_ph(t_ph_param *params, t_philo *ph_arr);
int		init_ph(t_ph_param *params, t_philo **ph_arr);
void	*philosoph(void *ph);
#endif
