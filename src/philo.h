/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:38:40 by mafioron          #+#    #+#             */
/*   Updated: 2025/03/04 16:38:42 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct	s_info
{
	int				nb_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				must_eat;
	pthread_mutex_t *forks;
}	t_info;

typedef struct s_phi
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				meals_eaten;
	int				last_meal;
	t_info		*info;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
}	t_phi;

typedef struct s_monitor
{
	bool	is_sync;
	bool	end_sim;
	pthread_mutex_t last_meal;
	pthread_mutex_t meals_eaten;
	pthread_mutex_t print;
	t_phi	*phi;
}	t_monitor;

/****		A trier		*****/


/****		utils		*****/
int	ft_atoi(const char *nptr);

#endif
