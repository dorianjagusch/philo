/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fnct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:56 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/14 16:00:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(char *param)
{
	long	nbr;

	nbr = ft_isint(param);
	if (nbr > INT_MAX || nbr <= 0)
		return (-1);
	return ((int) nbr);
}

static pthread_mutex_t	*set_mutexes(int number)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = malloc(sizeof(pthread_mutex_t) * number);
	if (!mutexes)
		ft_error(mem_err);
	while (i < number)
	{
		if (pthread_mutex_init(mutexes + i, NULL))
		{
			while (--i > 0)
				free(mutexes + i);
			ft_error(mutex_create_err);
			break ;
		}
		i++;
	}
	return (mutexes);
}

static int	fill_data(int ac, char **av, t_data *data)
{
	int	i;

	data->n_philo = is_valid(av[1]);
	i = 0;
	while (i < ac - 2 && data->n_philo)
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
	size_t			i;
	t_data			*data;

	i = 1;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	if (!fill_data(ac, av, data))
		return (NULL);
	data->forks = set_mutexes(data->n_philo);
	data->lock = set_mutexes(N_MUT);
	if (!data->forks || !data->lock)
		ft_clear(data, NULL);
	return (data);
}
