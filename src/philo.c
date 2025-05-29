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

void	display(t_monitor *moni, int id, char *str)
{
	unsigned long	time;

	pthread_mutex_lock(&moni->sync_lock);
	time = get_good_time() - moni->start_time;
	pthread_mutex_lock(&moni->print);
	pthread_mutex_lock(&moni->end_lock);
	if (moni->end_sim != true)
		printf("%lu %d %s", time, id, str);
	pthread_mutex_unlock(&moni->end_lock);
	pthread_mutex_unlock(&moni->print);
	pthread_mutex_unlock(&moni->sync_lock);
}

void	*routine(void *arg)
{
	t_monitor	*moni;
	int			id;

	moni = (t_monitor *)arg;
	pthread_mutex_lock(&moni->sync_lock);
	id = init_id()->id;
	pthread_mutex_unlock(&moni->sync_lock);
	if (id % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		pthread_mutex_lock(&moni->end_lock);
		if (moni->end_sim == true)
		{
			pthread_mutex_unlock(&moni->end_lock);
			break ;
		}
		pthread_mutex_unlock(&moni->end_lock);
		philo_eating(moni, id);
		philo_sleeping(moni, id);
		philo_thinking(moni, id);
	}
	return (NULL);
}

int	init_threads(t_monitor *moni)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&moni->sync_lock);
	if (pthread_create(&moni->monitor, NULL, &monitor_thread, moni) != 0)
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
	return (0);
}

int	main(int ac, char **av)
{
	t_info		*info;
	t_phi		*phi;
	t_monitor	*moni;

	if (ac < 5)
		return (1);
	info = init_info(av);
	if (!info)
		return (1);
	phi = init_phi(info);
	if (!phi)
		return (1);
	moni = init_monitor(phi, info);
	if (!moni)
		return (1);
	philo(moni);
	clean_exit(moni);
	return (0);
}
