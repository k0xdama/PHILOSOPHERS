/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:26:00 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

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

// STOP REASON //
# define END 0
# define LAUNCH_ERROR 1
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

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	unsigned int	first_fork;
	unsigned int	second_fork;
	size_t			last_meal;
	unsigned int	meals_count;
	bool			eating;
	bool			is_starving;
	bool			is_dead;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	bool			stop_flag;
	int				stop_reason;
	t_philo			*ph_tab;
	unsigned int	nb_philos;
	unsigned int	created_philos_th;
	bool			checker_is_created;
	unsigned int	initialized_th;
	unsigned int	finished_th;
	size_t			tt_die;
	size_t			tt_eat;
	size_t			tt_sleep;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	stop;
	pthread_mutex_t	dead;
	pthread_mutex_t	init_th;
	pthread_mutex_t	finish_th;
	pthread_mutex_t	write;
	size_t			start;
}	t_data;

typedef struct s_checker
{
	pthread_t		th;
	t_data			*data;
	t_philo			*ph_tab;
}	t_checker;

// INITIALISATION //
int				init_structs_and_philos(t_data *data, t_philo *philos_tab,
					int argc, char **argv);

// SIMULATION //
int				start(t_data *data, t_checker *checker);
int				detach_threads(t_data *data, t_checker *checker,
					t_philo *philos);
void			*philos_routine(void *ptr);
void			*checker_routine(void *ptr);

//ACTIONS
void			eat(t_philo *ph);
void			ft_dodo(t_philo *ph, size_t time, bool print_action);
void			think(t_philo *ph);

// UTILITAIRES //
void			write_action(t_data *data, t_philo *ph, char *str);
void			main_debug(t_data *data, char *str);
void			checker_debug(t_checker *checker, char *str);
void			philo_debug(t_philo *philo, char *str);
size_t			get_timestamp(void);
int				ft_isdigit(int c);
int				ft_mini_atoi(const char *str);
int				checks_args(char **argv);
void			msg_err(char *err);
void			*finish_philo(t_philo *philo);
void			*finish_checker(t_checker *checker);
int				cleaner(t_data *data, int sim_exit_code, char *err);

// EXT_UTILS //
int				ft_strcmp(const char *s1, const char *s2);

#endif