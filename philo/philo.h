/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:04:40 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/07 22:22:13 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <>

typedef struct s_ph_param
{
	int			numb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			numb_ph_eat;
	int			*mtx_print;
	int			*mx_forks;
}	t_ph_param;

typedef struct s_philo
{
	t_ph_param	*param;
	int			ph_num;
	long		last_eat_usec;
	int			is_die;
	pthread_t	ph_thread;
}	t_philo;

#endif
