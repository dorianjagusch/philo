/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:17:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/14 22:00:37 by djagusch         ###   ########.fr       */
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
			pthread_mutex_lock(philo->data->lock + DATA);
			--philo->data->active;
			pthread_mutex_unlock(philo->data->lock + DATA);
		}
	}
}

static void	run_sim(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->data->lock + DATA);
		if (philo->data->ended || philo->data->active <= 1)
			break ;
		pthread_mutex_unlock(philo->data->lock + DATA);
		philo_eat(philo);
		update_meals(philo);
		usleep(10);
		pthread_mutex_lock(philo->data->lock + DATA);
		if (philo->data->ended || philo->data->active <= 1)
			break ;
		pthread_mutex_unlock(philo->data->lock + DATA);
		philo_action(philo, SLEEP);
		usleep(1);
		philo_wait(philo, philo->data->times[SLEEP]);
		pthread_mutex_lock(philo->data->lock + DATA);
		if (philo->data->ended || philo->data->active <= 1)
			break ;
		pthread_mutex_unlock(philo->data->lock + DATA);
		philo_action(philo, THINK);
		usleep(1);
	}
	pthread_mutex_unlock(philo->data->lock + DATA);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	ft_mutex_barrier(&(philo->data->active), philo->data->n_philo,
		philo->data->lock + GAME);
	set_time(philo, DEATH);
	if (philo->id % 2 == 0)
	{
		philo_action(philo, THINK);
		philo_wait(philo, philo->data->times[EAT] * 0.1);
	}
	run_sim(philo);
	return ((void *) NULL);
}
