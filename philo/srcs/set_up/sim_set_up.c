/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_set_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/20 14:59:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->data->print);
	philo->data->n_active += 1;
	pthread_mutex_unlock(philo->data->print);
	while (philo->data->n_active != philo->data->n_philo + 1)
		;
	set_time(philo, DEATH);
	if (philo->id % 2)
	{
		print_action(philo, THINK);
		usleep(50);
	}
	run_sim(philo);
}

static BOOL	set_up_threads(t_philo **philos, int n_philo, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_create(&(threads[i]), NULL, &routine, philos[i]) != 0)
		{
			ft_error(thread_err);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	thread_collection(pthread_t *threads, int n_philo)
{
	size_t	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_join(threads[i], NULL))
			ft_error(join_err);
		i++;
	}
}

void	ft_philo(t_data *data, t_philo **philos)
{
	pthread_t		*threads;
	struct timeval	time;

	threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!threads)
	{
		ft_error(mem_err);
		return ;
	}
	if (!set_up_threads(philos, data->n_philo, threads))
	{
		ft_free(threads);
		return ;
	}
	gettimeofday(&time, NULL);
	data->start = time.tv_sec * 1000 + time.tv_usec / 1000;
	pthread_mutex_lock(data->print);
	data->n_active += 1;
	pthread_mutex_unlock(data->print);
	thread_collection(threads, data->n_philo);
}
