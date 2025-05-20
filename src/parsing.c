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

phi_info_t	*init_phi_info(char **av)
{
	phi_info_t	*phi_info;
	int			i;

	i = -1;
	phi_info = malloc(sizeof(phi_info_t));
	if (!phi_info)
		return (NULL);
	phi_info->nb_philos = ft_atoi(av[1]);
	phi_info->t_to_die = ft_atoi(av[2]);
	phi_info->t_to_eat = ft_atoi(av[3]);
	phi_info->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		phi_info->must_eat = ft_atoi(av[5]);
	else
		phi_info->must_eat = 0;
	phi_info->forks = malloc(sizeof(pthread_mutex_t) * phi_info->nb_philos);
	if (!phi_info->forks)
		return (free(phi_info), NULL);
	while (++i < phi_info->nb_philos)
	{
		if (pthread_mutex_init(&phi_info->forks[i], NULL) != 0)
			return (free(phi_info->forks), free(phi_info), NULL);
	}
	return (phi_info);
}

phi_t	*init_phi(phi_info_t *info)
{
	phi_t	*phi;
	int		i;

	i = -1;
	phi = malloc(sizeof(phi_t) * info->nb_philos);
	if (!phi)
		return (NULL);
	while (++i < info->nb_philos)
	{
		phi[i].id = i + 1;
		phi[i].is_eating = 0;
		phi[i].meals_eaten = 0;
		phi[i].phi_info = info;
		phi[i].fork_l = info->forks[i];
		phi[i].fork_r = info->forks[(i + 1) % info->nb_philos];
	}
	return (phi);
}

int	main(int ac, char **av)
{
	phi_info_t	*info;
	phi_t		*phi;

	if (ac < 5)
		return (1);
	info = init_phi_info(av);
	if (!info)
		return (1);
	phi = init_phi(info);
//	if (!phi)
//		clean_exit()
}
