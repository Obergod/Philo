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

phi_t	*init_phi(char **av)
{
	phi_t	*phi;

	phi = malloc(sizeof(phi_t));
	if (!phi)
		return (NULL);
	phi->nb_philo = ft_atoi(av[1]);
	phi->t_to_die = ft_atoi(av[2]);
	phi->t_to_eat = ft_atoi(av[3]);
	phi->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
		phi->must_eat = ft_atoi(av[5]);
	else
		phi->must_eat = 0;
	return (phi);
}
