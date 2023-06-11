/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fnct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/11 17:13:08 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_philo *philo)
{
	if (philo->data->n_philo & 1)
	{
		philo->fork1 = philo->id - (philo->id & 1);
		philo->fork2 = (philo->id - ((philo->id & 1) ^ 1))
			% philo->data->n_philo;
	}
	else
		philo->fork1 = philo->id - 1;
		philo->fork2 = philo->id % philo->data->n_philo;
}

t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = ft_calloc(data->n_philo, sizeof(t_philo *));
	if (!philos)
		return (0);
	while (i < data->n_philo)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!philos[i])
		{
			ft_free_array((void *)&philos, i);
			ft_error(mem_err);
			break ;
		}
		philos[i]->id = i + 1;
		philos[i]->data = data;
		philos[i]->meals_left = data->meals;
		get_forks(philos[i]);
		i++;
	}
	return (philos);
}
