/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:31:53 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/10 19:59:01 by pmateo           ###   ########.fr       */
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

typedef struct s_data
{
	bool			stop_flag;
	pthread_t		*threads_tab;
	unsigned int	nb_th;
	unsigned int	initialized_th;
	unsigned int	finished_th;
	pthread_mutex_t	write;
	pthread_mutex_t stop;
	size_t			start;
}	t_data;

// INITIALISATION //
int				init_structs_and_philos(t_data *data);

// SIMULATION //
void			*philos_routine(void *ptr);
void			*checker_routine(void *ptr);

//ACTIONS
void			eat(t_philo *ph);
void			ft_dodo(t_philo *philo, unsigned int time);
void			think(t_philo *ph);

// UTILITAIRES //
void			write_action(t_data *data, t_philo *ph, char *str);
unsigned int	get_timestamp(void);
int				ft_isdigit(int c);
int				ft_mini_atoi(const char *str);
int				checks_args(char **argv);
void			msg_err(char *err);
int				cleaner(t_data *data, int sim_exit_code, char *err);

// EXT_UTILS //
int	ft_strcmp(const char *s1, const char *s2);





#endif