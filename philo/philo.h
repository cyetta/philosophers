/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:04:40 by cyetta            #+#    #+#             */
/*   Updated: 2022/04/02 19:55:16 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_philo
{
	int	numb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	numb_ph_eat;
}	t_philo;

#endif
