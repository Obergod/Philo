/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:11:13 by mafioron          #+#    #+#             */
/*   Updated: 2025/05/20 20:11:15 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_monitor *moni, int id)
{
	int	left;
	int	right;

	right = id - 1;
	if (id == 1)
		left = moni->info->nb_philos - 1;
	else
		left = right - 1;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&moni->forks[left]);
		display(moni, id, "has taken a fork\n");
		pthread_mutex_lock(&moni->forks[right]);
		display(moni, id, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&moni->forks[right]);
		display(moni, id, "has taken a fork\n");
		pthread_mutex_lock(&moni->forks[left]);
		display(moni, id, "has taken a fork\n");
	}
}

void	leave_fork(t_monitor *moni, int id)
{
	int	left;
	int	right;

	right = id - 1;
	if (id == 1)
		left = moni->info->nb_philos - 1;
	else
		left = right - 1;
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&moni->forks[right]);
		pthread_mutex_unlock(&moni->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&moni->forks[left]);
		pthread_mutex_unlock(&moni->forks[right]);
	}
}

void	philo_eating(t_monitor *moni, int id)
{
	pthread_mutex_lock(&moni->end_lock);
	if (moni->end_sim == true)
	{
		pthread_mutex_unlock(&moni->end_lock);
		return ;
	}
	pthread_mutex_unlock(&moni->end_lock);
	take_fork(moni, id);
	display(moni, id, "is eating\n");
	pthread_mutex_lock(&moni->meals);
	moni->phi[id - 1].meals_eaten += 1;
	moni->phi[id - 1].last_meal = get_good_time();
	pthread_mutex_unlock(&moni->meals);
	ft_usleep(moni->info->t_to_eat * 1000);
	leave_fork(moni, id);
}

void	philo_thinking(t_monitor *moni, int id)
{
	pthread_mutex_lock(&moni->end_lock);
	if (moni->end_sim == true)
	{
		pthread_mutex_unlock(&moni->end_lock);
		return ;
	}
	pthread_mutex_unlock(&moni->end_lock);
	display(moni, id, "is thinking\n");
	if (moni->info->t_to_eat >= moni->info->t_to_sleep)
		ft_usleep((moni->info->t_to_eat - moni->info->t_to_sleep + 1) * 1000);
}

void	philo_sleeping(t_monitor *moni, int id)
{
	pthread_mutex_lock(&moni->end_lock);
	if (moni->end_sim == true)
	{
		pthread_mutex_unlock(&moni->end_lock);
		return ;
	}
	pthread_mutex_unlock(&moni->end_lock);
	display(moni, id, "is sleeping\n");
	ft_usleep(moni->info->t_to_sleep * 1000);
}
