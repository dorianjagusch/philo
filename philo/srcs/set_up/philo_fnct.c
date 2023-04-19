/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fnct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/19 04:07:51 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo *) * data->n_philo);
	if (!philo)
		return (0);
	while (i < data->n_philo)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
		{
			ft_free_array((void *)&philo, i);
			ft_error(mem_err);
			break ;
		}
		philo[i]->id = i + 1;
		philo[i]->data = data;
		i++;
	}
}
