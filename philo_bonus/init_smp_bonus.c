/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_smp_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:16:16 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/17 14:28:37 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semph(t_ph_param *prm)
{
	sem_unlink("phfrks");
	sem_unlink("phprnt");
	prm->sm_print = sem_open("phprnt", O_CREAT | O_EXCL, 0777, 1);
	prm->sm_forks = sem_open("phfrks", O_CREAT | O_EXCL, 0777, prm->numb_philo);
	return (0);
}

int	close_semph(t_ph_param *prm)
{
	sem_close(prm->sm_forks);
	sem_close(prm->sm_print);
	sem_unlink("phfrks");
	sem_unlink("phprnt");
	return (0);
}
