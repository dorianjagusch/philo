/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:39:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/11 16:00:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex_array(pthread_mutex_t *mutexes, int n_mutexes)
{
	int	i;

	i = -1;
	if (mutexes)
	{
		while (++i < n_mutexes)
		{
			if (pthread_mutex_destroy(mutexes + i) != 0)
				ft_error(mutex_destroy_err);
		}
		free(mutexes);
	}
}

void	ft_clear(t_data *data, t_philo **philo)
{
	int	n_philo;

	if (data)
	{
		n_philo = data->n_philo;
		if (data->forks)
			free_mutex_array(data->forks, n_philo);
		if (data->lock)
			free_mutex_array(data->lock, N_MUT);
		if (philo)
			ft_free_array((void *)&philo, n_philo);
		if (data)
			free(data);
	}
}

int	main(int ac, char **av)
{
	t_philo	**philos;
	t_data	*data;
	int		error;

	error = 0;
	if (ac < 5)
		error = ft_error(farg_err);
	if (ac > 6)
		error = ft_error(barg_err);
	if (error)
		return (error);
	data = 0;
	philos = 0;
	data = init_data(ac, av);
	if (data)
		philos = init_philos(data);
	if (philos)
		error = ft_philo(data, philos);
	ft_clear(data, philos);
	return (error);
}
