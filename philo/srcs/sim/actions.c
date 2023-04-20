/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:25:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/20 15:42:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	left;
	int	right;

	pthread_mutex_unlock(philo->data->print);
	left = philo->id - 1;
	right = philo->id % philo->data->n_philo;
	pthread_mutex_lock((philo->data->forks) + left);
	philo->fork_l = 1;
	if (philo->data->n_philo == 1)
	{
		philo_wait(philo, DIE);
		return ;
	}
	philo_action(philo, FORK);
	pthread_mutex_lock(philo->data->forks + right);
	philo->fork_r = 1;
	philo_action(philo, FORK);
	philo_action(philo, EAT);
	philo->fork_l = 0;
	philo->fork_r = 0;
	pthread_mutex_unlock((philo->data->forks) + left);
	pthread_mutex_unlock((philo->data->forks) + right);
}

static int	philo_wait(t_philo *philo, int action)
{
	while (set_time(philo, CUR) < philo->data->times[action])
	{
		if (philo->cur > philo->data->times[DIE])
		{
			philo_action(philo, DIE);
			return (0);
		}
		usleep(50);
	}
	return (1);
}

void	philo_action(t_philo *philo, int action)
{
	struct timeval	time;
	const char		*actions[] = {
		"died",
		"is eating",
		"is sleeping",
		"is thinking",
		"has taken a fork"
	};

	pthread_mutex_lock(philo->data->print);
	printf("[%lu] %d %s\n",
		set_time(philo, CUR), philo->id, actions[action]);
	if (action == EAT && (!philo->fork_l || !philo->fork_r))
		philo_eat(philo);
	else if (action != DIE && action != THINK)
	{
		pthread_mutex_unlock(philo->data->print);
		philo_wait(philo, action);
		return ;
	}
	else if (action == DIE)
		philo->data->ended = 1;
	pthread_mutex_unlock(philo->data->print);
}
