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

int	xXx_terminator_xXx(t_monitor *moni)
{
	int	i;
	long unsigned	time;

	i = -1;
	while (++i < moni->info->nb_philos)
	{
		pthread_mutex_lock(&moni->meals);
		if (moni->phi[i].last_meal == 0)
			return (pthread_mutex_unlock(&moni->meals), 0);
		pthread_mutex_lock(&moni->death);
		time = get_good_time() - moni->phi[i].last_meal;
		if (time >= moni->info->t_to_die)
		{
			display(moni, i + 1, "died\n");
			pthread_mutex_lock(&moni->end_lock);
			moni->end_sim = true;
			pthread_mutex_unlock(&moni->meals);
			pthread_mutex_unlock(&moni->end_lock);
			pthread_mutex_unlock(&moni->death);
			return (1);
		}
		pthread_mutex_unlock(&moni->meals);
		pthread_mutex_unlock(&moni->death);
	}
	return (0);
}

int	all_eaten(t_monitor *moni)
{
	int	i;

	i = -1;
	if (!moni->info->must_eat)
		return (0);
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
	pthread_mutex_lock(&moni->death);
	moni->end_sim = true;
	pthread_mutex_unlock(&moni->death);
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
		else if (xXx_terminator_xXx(moni) == 1)
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

