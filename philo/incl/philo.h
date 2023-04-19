/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:40:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/19 04:18:37 by djagusch         ###   ########.fr       */
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

typedef struct s_data
{
	long			start;
	int				*n_active;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				ended;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int		id;
	long	tod;
	BOOL	fork_l;
	BOOL	fork_r;
	int		meals_eaten;
	t_data	*data;
}			t_philo;

t_data	*init_data(int ac, char **av);
long	ft_isint(char *str);
t_philo	**init_philo(t_data *data, t_philo **philo);
void	ft_philo(t_data *data, t_philo **philo);

#endif