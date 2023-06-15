/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:17:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 20:11:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static void	ft_sem_barrier(t_philo *philo, sem_t *lock)
// {
// 	int	count = 0;

// 	printf("Piece of shit in barrier\n");
// 	sem_wait(lock);
// 	while (count < 100)
// 	{
// 		sem_post(lock);
// 		usleep(200);
// 		count++;
// 		sem_wait(lock);
// 		// if (*n_active == n_philo + 1)
// 		// 	break ;
// 	}
// 	sem_post(lock);
// 	philo->data->start = get_time();
// }

// static void	update_meals(t_philo *philo)
// {
// 	if (philo->data->meals > 0)
// 	{
// 		if (--philo->meals_left == 0)
// 		{
// 			sem_wait(philo->data->lock);
// 			--philo->data->active;
// 			sem_post(philo->data->lock);
// 		}
// 	}
// }

static void	run_sim(t_philo *philo)
{
	while (1)
	{
		printf("Philo %d tries to eat\n", philo->id);
		philo_eat(philo);
		//update_meals(philo);
		usleep(10);
		// printf("philo %d left eating\n", philo->id);
		philo_action(philo, SLEEP);
		usleep(10);
		philo_wait(philo, philo->data->times[SLEEP]);
		// printf("philo %d done sleeping\n", philo->id);
		philo_action(philo, THINK);
		// printf("philo %d done thinking\n", philo->id);
		sem_wait(philo->lock);
		if (philo->data->ended) //|| philo->data->active <= 1)
			break ;
		sem_post(philo->lock);
	}
	sem_post(philo->lock);
}

void	routine(t_philo	*philo)
{
	int		sleep_time;

	sleep_time = philo->data->times[EAT];//(0.8 - (0.2 * philo->large));
	//ft_sem_barrier(philo, philo->lock);
	// printf("philo %d left barrier\n", philo->id);
	sem_wait(philo->utensils);
	sem_post(philo->utensils);
	set_time(philo, DEATH);
	if (philo->id % 2 == 0)
	{
		philo_action(philo, THINK);
		usleep((int)sleep_time * 0.8);
		//philo_wait(philo, sleep_time);
	}
	run_sim(philo);
	exit (0);
}
