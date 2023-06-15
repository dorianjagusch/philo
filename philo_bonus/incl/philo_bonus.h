/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:40:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/15 20:11:24 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include "ft_error_bonus.h"
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <limits.h>
# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>        /* For mode constants */
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <sys/time.h>

# define BOOL int
# define DATA 0
# define GAME 1

# define LARGE 30

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
	long	start;
	int		active;
	int		n_philo;
	long	times[3];
	int		ended;
	int		meals;
	int		*pids;
	int		error;
}			t_data;

typedef struct s_philo
{
	int		id;
	long	cur;
	int		large;
	long	tod;
	sem_t	*lock;
	sem_t	*utensils;
	int		meals_left;
	t_data	*data;
}			t_philo;

t_data	*init_data(int ac, char **av);
t_philo	**init_philos(t_data *data);
void	routine(t_philo *philo);
int		ft_philo(t_data *data, t_philo **philos);
void	philo_action(t_philo *philo, int action);
void	philo_eat(t_philo *philo);
void	philo_wait(t_philo *philo, int ms);
long	set_time(t_philo *philo, int mode);
long	get_time(void);
long	ft_lmax(long a, long b);
void	ft_clear(t_data *data, t_philo **philos);
int		ft_error(int error);
int		ft_strcmp(char const *s1, char const *s2);
long	ft_isint(char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_free_array(void ***array, size_t index);

#endif