/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fnct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:41:04 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_data *data, t_philo *philo)
{
		philo->fork1 = data->forks + (philo->id - 1);
		philo->fork2 = data->forks + (philo->id % data->n_philo);
		philo->large = ((LARGE - data->n_philo) >> (sizeof(int) * 8 - 1)) & 1;
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
		set_forks(data, philos[i]);
		i++;
	}
	return (philos);
}
