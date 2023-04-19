/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_fnct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 03:02:56 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/19 06:03:12 by djagusch         ###   ########.fr       */
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

static void	set_forks(pthread_mutex_t *forks, int n_philo)
{
	int	i;

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
}

int	fill_data(int ac, char **av, t_data *data)
{
	data->n_philo = is_valid(av[1]);
	data->time_to_die = is_valid(av[2]);
	data->time_to_eat = is_valid(av[3]);
	data->time_to_sleep = is_valid(av[4]);
	if (ac == 6)
		data->meals = is_valid(av[5]);
	if (data->n_philo < 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (data->meals < 0 && ac == 6))
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

	i = 1;
	data = ft_calloc(1, sizeof(data));
	if (!data)
		return (NULL);
	if (!fill_data(ac, av, data))
		return (NULL);
	set_mutexes(forks);
	if (pthread_mutex_init(&(data->print), NULL) != 0)
	{
		ft_free(data);
		ft_free_array((void *)&forks);
		return (NULL);
	}
	return (data);
}
