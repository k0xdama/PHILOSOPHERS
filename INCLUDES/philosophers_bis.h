/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bis.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:31:53 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/11 22:42:59 by pmateo           ###   ########.fr       */
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
	bool			stop_flag;
	pthread_t		*threads_tab;
	unsigned int	nb_th;
	unsigned int	initialized_th;
	unsigned int	finished_th;
	pthread_mutex_t	write;
	pthread_mutex_t stop;
	size_t			start;
}	t_data;

void	write_status(t_data *data, char *str);
void	*routine_bis(void *ptr);


#endif