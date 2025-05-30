/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:28:11 by mafioron          #+#    #+#             */
/*   Updated: 2025/03/04 18:28:12 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*init_info(char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->nb_philos = ft_atoi(av[1]);
	info->t_to_die = ft_atoi(av[2]);
	info->t_to_eat = ft_atoi(av[3]);
	info->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->must_eat = ft_atoi(av[5]);
	else
		info->must_eat = 0;
	return (info);
}

t_phi	*init_phi(t_info *info)
{
	t_phi	*phi;
	int		i;

	i = -1;
	phi = malloc(sizeof(t_phi) * info->nb_philos);
	if (!phi)
		return (NULL);
	while (++i < info->nb_philos)
	{
		phi[i].id = i + 1;
		phi[i].is_eating = 0;
		phi[i].meals_eaten = 0;
		phi[i].last_meal = 0;
	}
	return (phi);
}

int	init_mutexes(t_monitor *monitor)
{
	if (pthread_mutex_init(&monitor->meals, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&monitor->death, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&monitor->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&monitor->sync_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&monitor->end_lock, NULL) != 0)
		return (1);
	return (0);
}

t_monitor	*init_monitor(t_phi *phi, t_info *info)
{
	t_monitor	*monitor;
	int			i;

	i = -1;
	if (!init_id())
		return (NULL);
	init_id()->id = 0;
	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->info = info;
	monitor->end_sim = false;
	monitor->can_display = true;
	monitor->start_time = get_good_time();
	monitor->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philos);
	if (!monitor->forks)
		return (free(monitor), NULL);
	while (++i < info->nb_philos)
	{
		if (pthread_mutex_init(&monitor->forks[i], NULL) != 0)
			return (free(monitor->forks), free(monitor), NULL);
	}
	if (init_mutexes(monitor) == 1)
		return (free(monitor), NULL);
	return (monitor->phi = phi, monitor);
}
