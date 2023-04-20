/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:40:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/20 15:36:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include "ft_error.h"
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define BOOL int
# define CUR 0
# define DEATH 1

// ACTIONS
# define DIE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4

typedef struct s_data
{
	long			start;
	int				n_active;
	int				n_philo;
	long			times[3];
	int				meals;
	int				ended;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int		id;
	long	cur;
	long	tod;
	BOOL	fork_l;
	BOOL	fork_r;
	int		meals_eaten;
	t_data	*data;
}			t_philo;

t_data	*init_data(int ac, char **av);
long	ft_isint(char *str);
t_philo	**init_philos(t_data *data, t_philo **philos);
void	ft_philo(t_data *data, t_philo **philos);
long	ft_lmax(long a, long b);
void	ft_clear(t_data *data, t_philo **philos);
long	set_time(t_philo *philo, int mode);
void	philo_action(t_philo *philo, int action);

#endif