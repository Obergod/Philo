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
	// last_meal check death
}

int	philo(t_monitor *moni)
{
	int	i;
	int	err;

	i = -1;
	while (++i < moni->phi->info->nb_philos)
	{
		err = pthread_create(&moni->phi[i].thread, NULL, &routine, NULL);
		if (err != 0)
		{
			printf("thread creation failed\n");
			return (1);
		}
	}
	i = -1;
	while (++i < moni->phi->info->nb_philos)
		pthread_join(moni->phi[i].thread, NULL);
//	clean_up();
	return (0);
}

