/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_set_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 09:04:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	data->active += 1;
	pthread_mutex_unlock(data->lock + DATA);
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(data->lock + DATA);
		if (philo[i]->tod < get_time() - data->start || data->ended)
		{
			printf("Parent detected death of %d at %ld and should die at %ld\n", i + 1,
				get_time() - data->start, philo[i]->tod);
			if (!data->ended)
			{
				data->ended = 1;
				printf("Parent murdered %d at %ld and should die at %ld\n", i + 1,
					get_time() - data->start, philo[i]->tod);
			}
			pthread_mutex_unlock(data->lock + DATA);
			break ;
		}
		i = (i + 1) % data->n_philo;
		pthread_mutex_unlock(data->lock + DATA);
	}
}

static BOOL	set_up_threads(t_philo **philos, t_data *data, int n_philo,
		pthread_t *threads)
{
	size_t	i;
	long	death_time;

	i = 0;
	death_time = data->times[DIE];
	while (i < n_philo)
	{
		philos[i]->tod = death_time;
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
		if (pthread_join(threads[i], NULL) != 0)
			ft_error(join_err);
		printf("parent collected %ld\n", i + 1);
		i++;
	}
	free(threads);
}

int	ft_philo(t_data *data, t_philo **philos)
{
	pthread_t		*threads;
	struct timeval	time;

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
	pthread_mutex_lock(data->lock + DATA);
	gettimeofday(&time, NULL);
	data->start = time.tv_sec * 1000 + time.tv_usec / 1000;
	printf("parent at monitoring\n");
	monitor_threads(data, philos);
	printf("parent monitoring done\n");
	thread_collection(threads, data->n_philo);
	printf("parent collecting done\n");
	return (data->error);
}
