/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/01 20:18:17 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <threads.h>
# include <pthread.h>
# include <stdbool.h>

// ERRORS //
# define ERR_BAD_ARGS "one or several ARGS are false !"
# define ERR_MALLOC "a malloc attempt failed !"
# define ERR_CREATE_THREAD "failed to create a thread !"
# define ERR_INIT_MUTEX "failed to init a mutex !"
# define ERR_TIMESTAMP "a problem occured when trying to get timestamp !"
// OUTPUT //
# define PRINT_EATING "is eating"
# define PRINT_SLEEPING "is sleeping"
# define PRINT_THINKING "is thinking"
# define PRINT_TOOK_FORK "has taken a fork"
# define PRINT_DIED "died"

typedef struct s_data
{
	pthread_t		checker;
	unsigned int	nb_philo;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	size_t			start;
}	t_data;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	unsigned int	fork_left;
	unsigned int	fork_right;
	unsigned int	meals_count;
	bool			eating;
	bool			is_dead;
	t_data			*data;
}	t_philo;

typedef struct s_checker
{
	pthread_t		th;
	t_data			*data;
	t_philo			**ph_tab;
}	t_checker;


// INITIALISATION //
void	init_struct_and_philos(t_data *data, t_philo **philo_tab, int argc, char **argv);

// UTILITAIRES //
int		ft_isdigit(int c);
int		ft_mini_atoi(const char *str);
void	clean_exit(t_data *data, t_philo **ph_tab, char *err, int exit_code);

// SIMULATION //
void	start(t_data *data, t_philo **philos);





#endif