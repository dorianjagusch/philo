/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:05:50 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/02 15:18:50 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (philo[i]->tod < get_time())
		{
			pthread_mutex_lock(data->print);
			data->ended = 1;
			printf("[%ld] %d has died\n", get_time(), i);
			pthread_mutex_unlock(data->print);
		}
	}
}
