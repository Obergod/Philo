/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:37:52 by mafioron          #+#    #+#             */
/*   Updated: 2025/05/28 18:37:53 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_monitor *moni, int id)
{

}

int	all_eaten(t_monitor *moni)
{
	int	i;

	i = -1;
	while (++i < moni->info->nb_philos)
	{
		pthread_mutex_lock(&moni->meals);
		if (moni->phi[i].meals_eaten < moni->info->must_eat)
		{
			pthread_mutex_unlock(&moni->meals);
			return (0);
		}
		pthread_mutex_unlock(&moni->meals);
	}
	pthread_mutex_lock(&moni->print);
	moni->end_sim = true;
	pthread_mutex_unlock(&moni->print);
	return (1);
}

int	moni_loop(t_monitor *moni, int id)
{
	pthread_mutex_lock(&moni->death);
	if (moni->end_sim != true)
	{
		pthread_mutex_unlock(&moni->death);
		if (all_eaten(moni) == 1)
			return (1);
		ft_usleep(50);
		return (0);
	}
	pthread_mutex_unlock(&moni->death);
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_monitor	*moni;
	int			id;

	moni = (t_monitor *)arg;
	pthread_mutex_lock(&moni->sync_lock);
	id = init_id()->id;
	pthread_mutex_unlock(&moni->sync_lock);
	while (moni_loop(moni, id) != 1)
		;
	return (NULL);
}

