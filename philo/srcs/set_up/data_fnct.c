/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fnct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:56 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/20 14:58:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

BOOL	is_valid(char *param)
{
	long	nbr;

	nbr = ft_isint(param);
	if (nbr > INT_MAX && nbr > 0)
		return (-1);
	return (nbr);
}

static pthread_mutex_t	*set_forks(int n_philo)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n_philo);
	if (!forks)
		ft_error(mem_err);
	while (i < n_philo)
	{
		if (pthread_mutex_init(forks + i, NULL) != 0)
		{
			while (--i > 0)
				ft_free(forks + i);
			ft_error(mutex_create_err);
			break ;
		}
		i++;
	}
	return (forks);
}

int	fill_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->n_philo = is_valid(av[1]);
	while (i < 3)
	{
		data->times[i] = is_valid(av[i]);
		if (data->times[i] < 0)
		{
			ft_clear(data, NULL);
			ft_error(type_err);
			return (0);
		}
	}
	if (ac == 6)
		data->meals = is_valid(av[5]);
	if (data->meals < 0 && ac == 6)
	{
		ft_free(data);
		ft_error(type_err);
		return (0);
	}
	return (1);
}

t_data	*init_data(int ac, char **av)
{
	size_t			i;
	int				value;
	t_data			*data;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;

	i = 1;
	data = ft_calloc(1, sizeof(data));
	if (!data)
		return (NULL);
	if (!fill_data(ac, av, data))
		return (NULL);
	data->forks = set_mutexes(data->n_philo);
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
	{
		ft_clear(data, NULL);
		return (NULL);
	}
	if (pthread_mutex_init(data->print, NULL) != 0)
	{
		ft_free(data);
		return (NULL);
	}
	return (data);
}
