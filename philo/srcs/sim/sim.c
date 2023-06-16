/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:17:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/16 10:22:01 by djagusch         ###   ########.fr       */
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

static void	update_meals(t_philo *philo)
{
	if (philo->data->meals > 0)
	{
		if (--philo->meals_left == 0)
		{
			pthread_mutex_lock(&(philo->data->lock[DATA]));
			--philo->data->active;
			pthread_mutex_unlock(&(philo->data->lock[DATA]));
		}
	}
}

static void	run_sim(t_philo *philo)
{
	while (1)
	{
		philo_eat(philo);
		update_meals(philo);
		usleep(1);
		philo_action(philo, SLEEP);
		usleep(1);
		philo_wait(philo, philo->data->times[SLEEP]);
		philo_action(philo, THINK);
		pthread_mutex_lock(&(philo->data->lock[DATA]));
		if (philo->data->ended || philo->data->active <= 1)
			break ;
		pthread_mutex_unlock(&(philo->data->lock[DATA]));
	}
	pthread_mutex_unlock(&(philo->data->lock[DATA]));
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		sleep_time;

	philo = arg;
	sleep_time = philo->data->times[EAT] * (0.8 - (0.5 * philo->large));
	ft_mutex_barrier(&(philo->data->active), philo->data->n_philo,
		philo->data->lock + GAME);
	set_time(philo, DEATH);
	if (philo->id % 2 == 0)
	{
		philo_action(philo, THINK);
		philo_wait(philo, sleep_time);
	}
	run_sim(philo);
	return ((void *) NULL);
}
