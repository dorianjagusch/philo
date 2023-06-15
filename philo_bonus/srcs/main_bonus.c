/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:39:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 19:42:37 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_clear(t_data *data, t_philo **philo)
{
	int	n_philo;

	if (data)
	{
		n_philo = data->n_philo;
		if (philo)
			ft_free_array((void *)&philo, n_philo);
		printf("freed philos\n");
		if (data->pids)
			free(data->pids);
		printf("freed pids\n");
		if (data)
			free(data);
		printf("freed data\n");
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
