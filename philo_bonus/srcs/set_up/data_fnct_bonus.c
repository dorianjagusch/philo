/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fnct_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:56 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 19:23:41 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_valid(char *param)
{
	long	nbr;

	nbr = ft_isint(param);
	if (nbr > INT_MAX || nbr <= 0)
		return (-1);
	return ((int) nbr);
}

static int	fill_data(int ac, char **av, t_data *data)
{
	int	i;

	data->n_philo = is_valid(av[1]);
	i = 0;
	while (i < 3 && data->n_philo)
	{
		data->times[i] = is_valid(av[i + 2]);
		if (data->times[i] < 0 || data->n_philo < 0)
		{
			ft_clear(data, NULL);
			ft_error(type_err);
			return (0);
		}
		i++;
	}
	if (ac == 6)
		data->meals = is_valid(av[5]);
	if ((data->meals < 0 && ac == 6))
	{
		free(data);
		ft_error(type_err);
		return (0);
	}
	return (1);
}

t_data	*init_data(int ac, char **av)
{
	t_data			*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	if (!fill_data(ac, av, data))
		return (NULL);
	data->pids = ft_calloc(data->n_philo, sizeof(int));
	if (!data->pids)
		ft_clear(data, NULL);
	return (data);
}
