/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:23 by mafioron          #+#    #+#             */
/*   Updated: 2025/03/04 16:38:26 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*routine(void *arg)
{
	t_monitor	*moni;
	int			err;

	err = 0;
	moni = (t_monitor *)arg;
	wait_start(moni->is_sync, &moni->sync_lock);
	if (moni->phi->id % 2 == 0)
		ft_usleep(50);
	pthread_mutex_lock(&moni->print);
	printf("print\n");
	pthread_mutex_unlock(&moni->print);
	return (NULL);
}

int	philo(t_monitor *moni)
{
	int	i;
	int	err;

	i = -1;
	while (++i < moni->phi->info->nb_philos)
	{
		if (pthread_create(&moni->phi[i].thread, NULL, &routine, moni) != 0)
		{
			printf("thread creation failed\n");
			return (1);
		}
	}
	pthread_mutex_lock(&moni->sync_lock);
	moni->is_sync = true;
	pthread_mutex_unlock(&moni->sync_lock);
	i = -1;
	while (++i < moni->phi->info->nb_philos)
		pthread_join(moni->phi[i].thread, NULL);
	pthread_mutex_destroy(&moni->sync_lock);
	pthread_mutex_destroy(&moni->print);
//	clean_up();
	return (0);
}

