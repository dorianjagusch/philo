/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fnct_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 11:31:33 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		i++;
	}
	return (philos);
}
