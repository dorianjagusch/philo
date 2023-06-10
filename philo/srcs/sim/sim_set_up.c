/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_set_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/10 17:54:03 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	data->n_active += 1;
	pthread_mutex_unlock(&((data->locks)[PRINT]));
	usleep(1000);
	pthread_mutex_lock(&((data->locks)[DATA]));
	while (!data->ended)
	{
		pthread_mutex_unlock(&((data->locks)[DATA]));
		usleep(50);
		pthread_mutex_lock(&((data->locks)[DATA]));
		if (philo[i]->tod < get_time() - data->start)
		{
			if (!data->ended)
			{
				data->ended = 1;
				printf("[%ld] %d died by parent\n", set_time(philo[i], CUR), i + 1);
			}
			pthread_mutex_unlock(&((data->locks)[DATA]));
			printf("Parent murdered %d\n", i + 1);
			break ;
		}
		i = (i + 1) % data->n_philo;
	}
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
	if (!set_up_threads(philos, data->n_philo, threads))
	{
		free(threads);
		return (data->error);
	}
	gettimeofday(&time, NULL);
	data->start = time.tv_sec * 1000 + time.tv_usec / 1000;
	pthread_mutex_lock(&((data->locks)[PRINT]));
	printf("parent at monitoring\n");
	monitor_threads(data, philos);
	printf("parent monitoring done\n");
	thread_collection(threads, data->n_philo);
	printf("parent collecting done\n");
	return (data->error);
}
