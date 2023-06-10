/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:25:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/10 18:07:37 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	left;
	int	right;

	left = (philo->id + (philo->id & 1)) % philo->data->n_philo;
	right = (philo->id + (philo->id & 0)) % philo->data->n_philo;
	pthread_mutex_lock((philo->data->forks) + left);
	if (philo->data->n_philo == 1)
	{
		philo_wait(philo, DIE);
		pthread_mutex_unlock((philo->data->forks) + left);
		return ;
	}
	philo_action(philo, FORK);
	pthread_mutex_lock(philo->data->forks + right);
	philo_action(philo, FORK);
	philo_action(philo, EAT);
	pthread_mutex_unlock((philo->data->forks) + left);
	pthread_mutex_unlock((philo->data->forks) + right);
}

void	philo_wait(t_philo *philo, int action)
{
	long	start;

	start = philo->cur;
	while (set_time(philo, CUR) < philo->data->times[action] + start)
	{
		if (philo->cur > philo->tod)
		{
			philo_action(philo, DIE);
			return ;
		}
		usleep(10);
	}
	if (action == EAT)
		set_time(philo, DEATH);
	return ;
}

void	philo_action(t_philo *philo, int action)
{
	const char		*actions[] = {
		"died",
		"is eating",
		"is sleeping",
		"is thinking",
		"has taken a fork"
	};

	pthread_mutex_lock(&((philo->data->locks)[DATA]));
	if (philo->data->ended == 0)
	{
		printf("[%lu] %d %s\n", set_time(philo, CUR), philo->id,
			actions[action]);
		if (action == DIE)
		{
			philo->data->ended = 1;
			printf("bitch dies by its own Hand\n");
			pthread_mutex_unlock(&((philo->data->locks)[DATA]));
			return ;
		}
	}
	pthread_mutex_unlock(&((philo->data->locks)[DATA]));
	if (action < THINK)
		philo_wait(philo, action);
	usleep(10);
}
