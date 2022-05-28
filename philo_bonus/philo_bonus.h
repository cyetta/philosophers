/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:04:40 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 16:43:02 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# define PHILO_ATE 1
# define PHILO_DIE 2

typedef struct timeval	t_timeval;

typedef struct s_ph_param
{
	int				numb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				numb_ph_eat;
	t_timeval		time_start;
	pid_t			*a_philo;
	pid_t			ate_monitor;
	sem_t			**a_sm_lasteat;
	sem_t			*sm_aph_accss;
	sem_t			*sm_eatcnt;
	sem_t			*sm_forks;
	sem_t			*sm_print;
}	t_ph_param;

typedef struct s_philo
{
	t_ph_param		*param;
	int				ph_num;
	t_timeval		last_eat;
	int				eat_cnt;
	sem_t			*sm_lsteat;
}	t_philo;

int			init_semph(t_ph_param *prm);
int			close_semph(t_ph_param *prm);
int			init_ph(t_ph_param *params, t_philo *philo);
int			clean_ph(t_ph_param *params);
int			lunch_ph(t_philo *philo);
int			ate_monitor(t_ph_param	*params);
void		phil_start(t_philo *philo);
int			ph_msg(t_philo *ph, char *msg);
int			ph_msg_died(t_philo *ph);
int			get_eatcnt(t_philo *philo);
t_timeval	get_lasteat(t_philo *philo);
void		set_eatcnt(t_philo *philo, int a);
void		set_lasteat(t_philo *philo);
#endif
