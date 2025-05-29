/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:43:57 by mafioron          #+#    #+#             */
/*   Updated: 2025/05/20 19:43:59 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	neg;

	i = 0;
	neg = 1;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * neg);
}

unsigned long	get_good_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned long time)
{
	unsigned long	cur;

	cur = get_good_time();
	while ((get_good_time() - cur) * 1000 < time)
		usleep(50);
}

t_id	*init_id(void)
{
	static t_id	*id;

	if (!id)
	{
		id = malloc(sizeof(t_id));
		if (!id)
			return (NULL);
	}
	return (id);
}

void	clean_exit(t_monitor *moni)
{
	if (moni)
	{
		pthread_mutex_destroy(&moni->death);
		pthread_mutex_destroy(&moni->meals);
		pthread_mutex_destroy(&moni->print);
		pthread_mutex_destroy(&moni->sync_lock);
		pthread_mutex_destroy(moni->forks);
		free(moni->info);
		free(moni->phi);
		free(moni->forks);
		free(moni);
	}
	free(init_id());
}
