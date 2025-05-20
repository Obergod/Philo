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

typedef struct	phi_info_s
{
	int				nb_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				must_eat;
	pthread_mutex_t *forks;
}	phi_info_t;

typedef struct phi_s
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				meals_eaten;
	phi_info_t		*phi_info;
	pthread_mutex_t	fork_l;
	pthread_mutex_t	fork_r;
} phi_t;

/****		A trier		*****/


/****		utils		*****/
int	ft_atoi(const char *nptr);

#endif
