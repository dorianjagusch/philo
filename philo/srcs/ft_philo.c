/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/19 06:40:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_up_threads(t_philo **philo, int n_philo, pthread_t *threads)
{
	size_t	i;

	i = 0;
	while (i < n_philo)
	{
		if (pthread_create(&(threads[i]), NULL, &routine, philo[i]) != 0)
		{
			ft_error(thread_err);
			return (0);
		}
		i++;
	}
	return (1);
}

void	thread_collection(pthread_t *threads, int n_philo)
{
	size_t	i;

	i = 0;
	
	while (i < n_philo)
	{
		pthread_detach
	}
}

void	ft_philo(t_data *data, t_philo **philo)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!threads)
	{
		ft_error(mem_err);
		return ;
	}
	if (!set_up_threads(philo, data->n_philo, threads))
	{
		ft_free(threads);
		return ;
	}
	set_time(data->start);
	pthread_mutex_lock(&(data->print));
	*(data->n_active) += 1;
	pthread_mutex_unlock(&(data->print));
	thread_collection(threads, data->n_philo);
}
