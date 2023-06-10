/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:17:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/10 17:48:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_mutex_barrier(int *n_active, int n_philo, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*n_active += 1;
	while (1)
	{
		pthread_mutex_unlock(lock);
		pthread_mutex_lock(lock);
		if (*n_active == n_philo + 1)
			break ;
	}
	pthread_mutex_unlock(lock);
}

void	run_sim(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&((philo->data->locks)[DATA]));
		if (philo->data->ended)
			break ;
		pthread_mutex_unlock(&((philo->data->locks)[DATA]));
		philo_eat(philo);
		philo->meals_eaten += 1;
		pthread_mutex_lock(&((philo->data->locks)[DATA]));
		if (philo->data->ended)
			break ;
		pthread_mutex_unlock(&((philo->data->locks)[DATA]));
		philo_action(philo, SLEEP);
		pthread_mutex_lock(&((philo->data->locks)[DATA]));
		if (philo->data->ended)
			break ;
		pthread_mutex_unlock(&((philo->data->locks)[DATA]));
		philo_action(philo, THINK);
	}
	pthread_mutex_unlock(&((philo->data->locks)[DATA]));
	printf("Philo %d done\n", philo->id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	ft_mutex_barrier(&(philo->data->n_active), philo->data->n_philo,
		&((philo->data->locks)[PRINT]));
	set_time(philo, DEATH);
	philo_action(philo, THINK);
	if (philo->id & 1)
		usleep(20);
	usleep(1);
	run_sim(philo);
	return ((void *) NULL);
}
