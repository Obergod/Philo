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
	int			id;

	moni = (t_monitor *)arg;
	pthread_mutex_lock(&moni->sync_lock);
	id = init_id()->id;
	pthread_mutex_unlock(&moni->sync_lock);
	while (moni->end_sim != true)
	{
		if (id % 2 == 0)
			ft_usleep(50);
		philo_eating(moni, id);
		philo_sleeping(moni, id);
	}
	return (NULL);
}

int	init_threads(t_monitor *moni)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&moni->sync_lock);
	pthread_create(&moni->monitor, NULL, &monitor_thread, moni);
	if (pthread_create(&moni->phi[i].thread, NULL, &routine, moni) != 0)
	{
		printf("thread creation failed\n");
		return (1);
	}
	pthread_mutex_unlock(&moni->sync_lock);
	while (++i < moni->info->nb_philos)
	{
		ft_usleep(100);
		pthread_mutex_lock(&moni->sync_lock);
		init_id()->id = i + 1;
		if (pthread_create(&moni->phi[i].thread, NULL, &routine, moni) != 0)
		{
			printf("thread creation failed\n");
			return (1);
		}
		pthread_mutex_unlock(&moni->sync_lock);
	}
	return (0);
}

int	philo(t_monitor *moni)
{
	int	i;

	i = -1;
	if (init_threads(moni) != 0)
		return (1);
	ft_usleep(1000);
	while (++i < moni->info->nb_philos)
		pthread_join(moni->phi[i].thread, NULL);
	pthread_join(moni->monitor, NULL);
	clean_exit(moni);
//	clean_up();
	return (0);
}

