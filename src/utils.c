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

static int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	neg;

	i = 0;
	neg = 1;
	res = 0;
	while (ft_isspace(nptr[i]) == 1)
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

unsigned long	get_good_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned long time)
{
	unsigned long	cur;

	cur = get_good_time();
	while((get_good_time() - cur) * 1000 < time)
		usleep(50);
}

void	wait_start(bool is_sync, pthread_mutex_t *lock)
{
	while (1)
	{
		pthread_mutex_lock(lock);
		if (is_sync == true)
		{
			pthread_mutex_unlock(lock);
			return ;
		}
			pthread_mutex_unlock(lock);
			ft_usleep(100);
	}
}

t_id	*init_id()
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
	pthread_mutex_destroy(&moni->death);
	pthread_mutex_destroy(&moni->meals);
	pthread_mutex_destroy(&moni->print);
	pthread_mutex_destroy(&moni->sync_lock);
	pthread_mutex_destroy(moni->forks);
	free(moni->info);
	free(moni->phi);
	free(moni);
}
