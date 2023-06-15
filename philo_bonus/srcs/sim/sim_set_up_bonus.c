/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_set_up_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 04:12:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 20:18:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static BOOL	set_up_procs(t_philo **philos, t_data *data, int n_philo)
{
	size_t	i;
	long	death_time;

	i = 0;
	death_time = data->times[DIE];
	data->start = get_time();
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

static void	proc_collection(t_data *data, int n_philo,
	sem_t *utensils, sem_t *lock)
{
	if (waitpid(-1, NULL, 0))
		kill(0, SIGTERM);
	if (sem_close(utensils) < 0)
		data->error = ft_error(sem_destroy_err);
	if (sem_unlink("/utensils") < 0)
		data->error = ft_error(sem_unlink_err);
	if (sem_close(lock) < 0)
		data->error = ft_error(sem_destroy_err);
	if (sem_unlink("/game_lock") < 0)
		data->error = ft_error(sem_unlink_err);
	
}

void	set_sems(t_philo **philos, sem_t *utensils, sem_t *lock, int n_philo)
{
	int	i;
	
	i = -1;
	while (++i < n_philo)
	{
		philos[i]->utensils = utensils;
		philos[i]->lock = lock;
	}
}


int	ft_philo(t_data *data, t_philo **philos)
{
	sem_t	*lock;
	sem_t	*utensils;

	
	printf("Philos %d\n", data->n_philo);
	lock = sem_open("/game_lock", O_CREAT, 0644, 1);
	if (lock == SEM_FAILED)
		data->error = ft_error(sem_create_err);
	utensils = sem_open("/utensils", O_CREAT, 0644, data->n_philo);
	if (utensils == SEM_FAILED)
		data->error = ft_error(sem_create_err);
	set_sems(philos, utensils, lock, data->n_philo);
	sem_wait(lock);
	set_up_procs(philos, data, data->n_philo);
	printf("Parent set up procs\n");
	sem_post(lock);
	proc_collection(data, data->n_philo, utensils, lock);
	printf("Parent collected procs2\n");
	return (data->error);
}
