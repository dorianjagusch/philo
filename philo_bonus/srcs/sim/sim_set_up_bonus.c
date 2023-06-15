/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_set_up_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 17:15:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static BOOL	set_up_procs(t_philo **philos, t_data *data, int n_philo)
{
	size_t	i;
	long	death_time;

	i = 0;
	death_time = data->times[DIE];
	while (i < n_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
		{
			ft_error(proc_err);
			printf("Procs set up failed\n");
			return (0);
		}
		if (data->pids[i] == 0)
		{
			// printf("Child gets to work\n");
			philos[i]->tod = death_time;
			routine(philos[i]);
		}
		// printf("Procs set up successfully\n");
		i++;
	}
	return (1);
}

static void	proc_collection(t_data *data, int n_philo)
{
	if (waitpid(-1, NULL, 0))
		kill(0, SIGKILL);
}

int	ft_philo(t_data *data, t_philo **philos)
{
	sem_wait(data->lock);
	set_up_procs(philos, data, data->n_philo);
	printf("Parent set up procs\n");
	sem_post(data->lock);
	proc_collection(data, data->n_philo);
	printf("Parent collected procs2\n");
	return (data->error);
}
