/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:58:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/08/31 18:32:02 by pmateo           ###   ########.fr       */
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


typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	tt_die;
	unsigned int	tt_eat;
	unsigned int	tt_sleep;
	unsigned int	must_eat;
	size_t			start;
}	t_data;

typedef struct s_fork
{
	int		available;
	pthread_mutex_t lock;
}	t_fork;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	unsigned int	meals_count;
	bool			eating;
	t_data			*data
}	t_philo;

void	init_and_fill_struct(t_data *data, int argc, char **argv);
int		ft_isdigit(int c);
int		ft_mini_atoi(const char *str);

//tableau de fork
//tableau de philos
//bool isdead
//



















#endif