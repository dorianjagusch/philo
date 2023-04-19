/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:39:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/19 04:11:08 by djagusch         ###   ########.fr       */
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

void	ft_clear(t_philo **philo, t_data *data)
{
	int	n_philo;

	if (data)
	{
		n_philo = data->n_philo;
		free_forks(data, n_philo);
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
	t_philo	**philo;
	t_data	*data;

	if (ac < 5)
		ft_error(farg_err);
	if (ac > 6)
		ft_error(barg_err);
	data = NULL;
	philo = NULL;
	init_data(ac, av);
	if (data)
		init_philo(data, philo);
	if (philo)
		ft_philo(data, philo);
	ft_clear(philo, data);
	return (0);
}
