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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_id
{
	int				id;
}					t_id;

typedef struct s_info
{
	int				nb_philos;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	int				must_eat;
}					t_info;

typedef struct s_phi
{
	pthread_t		thread;
	int				id;
	int				is_eating;
	int				meals_eaten;
	unsigned long	last_meal;
}					t_phi;

typedef struct s_monitor
{
	pthread_mutex_t	*forks;
	bool			end_sim;
	bool			can_display;
	unsigned long	start_time;
	pthread_mutex_t	death;
	pthread_mutex_t	meals;
	pthread_mutex_t	print;
	pthread_mutex_t	sync_lock;
	pthread_mutex_t	end_lock;
	pthread_t		monitor;
	t_phi			*phi;
	t_info			*info;
}					t_monitor;

/****		Parsing		*****/
t_info				*init_info(char **av);
t_phi				*init_phi(t_info *info);
t_monitor			*init_monitor(t_phi *phi, t_info *info);

/****		threads		*****/
int					philo(t_monitor *moni);
void				*monitor_thread(void *arg);

/****		Actions		*****/
void				philo_sleeping(t_monitor *moni, int id);
void				philo_eating(t_monitor *moni, int id);
void				philo_thinking(t_monitor *moni, int id);
void				display(t_monitor *moni, int id, char *str);

/****		utils		*****/
int					ft_atoi(const char *nptr);
unsigned long		get_good_time(void);
void				ft_usleep(unsigned long time);
void				wait_start(bool is_sync, pthread_mutex_t *lock);
t_id				*init_id(void);
void				clean_exit(t_monitor *moni);
void				handle_one(t_monitor *moni);
int					check_args(char **av);

#endif
