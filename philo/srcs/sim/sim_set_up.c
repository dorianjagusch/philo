/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_set_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/16 16:22:31 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static BOOL	set_up_threads(t_philo **philos, t_data *data, int n_philo,
		pthread_t *threads)
{
	int		i;
	long	death_time;

	i = 0;
	death_time = data->times[DIE];
	while (i < n_philo)
	{
		philos[i]->tod = death_time;
		if (pthread_create(&(threads[i]), NULL, &routine, philos[i]) != 0)
		{
			data->error = ft_error(thread_err);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	thread_collection(pthread_t *threads, int n_philo)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < n_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			error = ft_error(join_err);
		i++;
	}
	free(threads);
	return (error);
}

int	ft_philo(t_data *data, t_philo **philos)
{
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!threads)
	{
		data->error = ft_error(mem_err);
		return (data->error);
	}
	if (!set_up_threads(philos, data, data->n_philo, threads))
	{
		free(threads);
		return (data->error);
	}
	pthread_mutex_lock(&(data->lock[GAME]));
	data->start = get_time();
	data->active += 1;
	pthread_mutex_unlock(&(data->lock[GAME]));
	data->error = thread_collection(threads, data->n_philo);
	return (data->error);
}
