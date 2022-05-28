/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_smp_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:16:16 by cyetta            #+#    #+#             */
/*   Updated: 2022/05/28 17:19:45 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"
#include "ft_util_bonus.h"
#include "ft_error_bonus.h"

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

	sem_unlink("pharraccess0");
	sem_unlink("pheatcnt0");
	sem_unlink("phfrks0");
	sem_unlink("phprnt0");
	i = -1;
	while (++i < prm->numb_philo)
	{
		str = crt_smphname("phlasteat", i);
		sem_unlink(str);
		free(str);
	}
}

static int	open_smph(sem_t	**smph, char *base, int base_idx, int smp_lvl)
{
	char	*str;

	str = crt_smphname(base, base_idx);
	*smph = sem_open(str, O_CREAT | O_EXCL, 0777, smp_lvl);
	free(str);
	if (*smph == NULL || *smph == ((void *)-1))
		return (ERR_SEMAPHOREINIT);
	return (0);
}

int	init_semph(t_ph_param *prm)
{
	int		i;

	unlink_smp(prm);
	prm->a_sm_lasteat = (sem_t **)malloc(sizeof(sem_t *) * prm->numb_philo);
	if (!prm->a_sm_lasteat)
		return (ft_error(ERR_INIT_PTH_ARR));
	if (open_smph(&prm->sm_aph_accss, "pharraccess", 0, 1))
		return (ERR_SEMAPHOREINIT);
	if (open_smph(&prm->sm_eatcnt, "pheatcnt", 0, 0))
		return (ERR_SEMAPHOREINIT);
	if (open_smph(&prm->sm_print, "phprnt", 0, 1))
		return (ERR_SEMAPHOREINIT);
	if (open_smph(&prm->sm_forks, "phfrks", 0, prm->numb_philo))
		return (ERR_SEMAPHOREINIT);
	i = -1;
	while (++i < prm->numb_philo)
	{
		if (open_smph(&prm->a_sm_lasteat[i], "phlasteat", i, 1))
			return (ERR_SEMAPHOREINIT);
	}
	return (0);
}

int	close_semph(t_ph_param *prm)
{
	int	i;

	i = -1;
	while (++i < prm->numb_philo)
		if (prm->a_sm_lasteat[i])
			sem_close(prm->a_sm_lasteat[i]);
	if (prm->sm_aph_accss)
		sem_close(prm->sm_aph_accss);
	if (prm->sm_eatcnt)
		sem_close(prm->sm_eatcnt);
	if (prm->sm_forks)
		sem_close(prm->sm_forks);
	if (prm->sm_print)
		sem_close(prm->sm_print);
	unlink_smp(prm);
	return (0);
}
