/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fnct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/10 14:00:02 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo *) * data->n_philo);
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
		i++;
	}
	return (philos);
}
