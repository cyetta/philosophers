/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_smp_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:16:16 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/25 15:55:17 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"
#include "ft_util.h"
#include "ft_error.h"

char	*crt_smphname(char *base, int num)
{
	int		num_sz;
	int		base_sz;
	int		i;
	char	*str;

	base_sz = ft_strlen(base);
	num_sz = ft_itoasz(num);
	str = malloc(sizeof(char) * (base_sz + num_sz + 1));
	if (!str)
		return (str);
	i = -1;
	while (++i < base_sz)
		str[i] = base[i];
	return (ft_itoa2buf(num, str, base_sz));
}

void	unlink_smp(t_ph_param *prm)
{
	int		i;
	char	*str;

	sem_unlink("phfrks");
	sem_unlink("phprnt");
	i = -1;
	while (++i < prm->numb_philo)
	{
		str = crt_smphname("pheatcnt", i);
		sem_unlink(str);
		free(str);
		str = crt_smphname("phlsteat", i);
		sem_unlink(str);
		free(str);
	}
}

int	init_semph(t_ph_param *prm)
{
	int		i;
	char	*str;

	unlink_smp(prm);
	prm->a_ph_smph = (t_ph_sem *)malloc(sizeof(t_ph_sem) * prm->numb_philo);
	if (!prm->a_ph_smph)
		return (ft_error(ERR_INIT_PTH_ARR));
	i = -1;
	while (++i < prm->numb_philo)
	{
		str = crt_smphname("pheatcnt", i);
		prm->a_ph_smph[i].sm_eatcnt = \
	sem_open("pheatcnt", O_CREAT | O_EXCL, 0777, 1);
		free(str);
		str = crt_smphname("phlsteat", i);
		(prm->a_ph_smph)[i].sm_eatcnt = \
	sem_open("phlsteat", O_CREAT | O_EXCL, 0777, 1);
		free(str);
	}
	prm->sm_print = sem_open("phprnt", O_CREAT | O_EXCL, 0777, 1);
	prm->sm_forks = sem_open("phfrks", O_CREAT | O_EXCL, 0777, prm->numb_philo);
	return (0);
}

int	close_semph(t_ph_param *prm)
{
	int	i;

	i = -1;
	while (++i < prm->numb_philo)
	{
		sem_close(prm->a_ph_smph[i].sm_eatcnt);
		sem_close(prm->a_ph_smph[i].sm_lasteat);
	}
	sem_close(prm->sm_forks);
	sem_close(prm->sm_print);
	unlink_smp(prm);
	return (0);
}
