/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:10:30 by mafioron          #+#    #+#             */
/*   Updated: 2025/05/30 16:10:31 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	handle_one(t_monitor *moni)
{
	display(moni, 1, "has taken a fork\n");
	ft_usleep(moni->info->t_to_die * 1000);
	printf("%lu 1 died\n", get_good_time() - moni->start_time);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
