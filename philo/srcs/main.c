/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:39:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/20 14:59:02 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_forks(t_data *data, int n_philo)
{
	int	i;

	i = -1;
	if (data->forks)
	{
		while (++i < n_philo)
		{
			if (pthread_mutex_destroy(&(data->forks[i])) != 0)
				ft_error(mutex_destroy_err);
		}
		ft_free(data->forks);
	}
}

void	ft_clear(t_data *data, t_philo **philo)
{
	int	n_philo;

	if (data)
	{
		n_philo = data->n_philo;
		if (data->forks)
			free_forks(data, n_philo);
		if (data->print)
			if (pthread_mutex_destroy(&(data->print)) != 0)
				ft_error(mutex_destroy_err);
		if (data->n_active)
			ft_free(data->n_active);
		if (philo)
			ft_free_array((void *)&philo, n_philo);
		if (data)
			ft_free(data);
	}
}

int	main(int ac, char **av)
{
	t_philo	**philos;
	t_data	*data;

	if (ac < 5)
		ft_error(farg_err);
	if (ac > 6)
		ft_error(barg_err);
	data = NULL;
	philos = NULL;
	init_data(ac, av);
	if (data)
		init_philo(data, philos);
	if (philos)
		ft_philo(data, philos);
	ft_clear(data, philos);
	return (0);
}
