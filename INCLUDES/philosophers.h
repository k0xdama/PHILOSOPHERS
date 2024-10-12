/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 04:45:34 by pmateo           ###   ########.fr       */
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
# define SUCCESS 0
# define FAILURE 1
# define ERR_BAD_ARGS "one or several ARGS are false !"
# define ERR_MALLOC "a malloc attempt failed !"
# define ERR_CREATE_THREAD "failed to create a thread !"
# define ERR_DETACH_THREAD "failed to detach a thread !"
# define ERR_INIT_MUTEX "failed to init a mutex !"
# define ERR_TIMESTAMP "a problem occured when trying to get timestamp !"
// OUTPUT //
# define PRINT_EATING "is eating"
# define PRINT_SLEEPING "is sleeping"
# define PRINT_THINKING "is thinking"
# define PRINT_TOOK_FORK "has taken a fork"
# define PRINT_DIED "died"

typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	unsigned int	first_fork;
	unsigned int	second_fork;
	unsigned int	last_meal;
	unsigned int	meals_count;
	bool			eating;
	bool			is_starving;
	bool			is_dead;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	bool			stop_flag;
	t_philo			*ph_tab;
	unsigned int	nb_philos;
	unsigned int	initialized_th;
	unsigned int	finished_th;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	stop;
	pthread_mutex_t	write;
	size_t			start;
}	t_data;

typedef struct s_checker
{
	pthread_t		th;
	t_data			*data;
	t_philo			**ph_tab;
}	t_checker;


// INITIALISATION //
int				init_structs_and_philos(t_data *data, int argc, char **argv);

// SIMULATION //
void			*philos_routine(void *ptr);
void			*checker_routine(void *ptr);

//ACTIONS
void			eat(t_philo *ph);
void			ft_dodo(t_philo *philo, unsigned int time);
void			think(t_philo *ph);

// UTILITAIRES //
void			write_action(t_data *data, t_philo *ph, char *str);
void			write_debug(t_data *data, char *str);
unsigned int	get_timestamp(void);
int				ft_isdigit(int c);
int				ft_mini_atoi(const char *str);
int				checks_args(char **argv);
void			msg_err(char *err);
int				cleaner(t_data *data, int sim_exit_code, char *err);

// EXT_UTILS //
int	ft_strcmp(const char *s1, const char *s2);





#endif