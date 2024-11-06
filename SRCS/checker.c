/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:06:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 18:45:04 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static	void	monitor_meal_count(t_checker *checker)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&checker->data->meal);
	while (i < checker->data->nb_philos)
	{
		if ((int)checker->data->ph_tab[i].meals_count
			>= checker->data->must_eat)
			i++;
		else
		{
			pthread_mutex_unlock(&checker->data->meal);
			return ;
		}
	}
	pthread_mutex_unlock(&checker->data->meal);
	pthread_mutex_lock(&checker->data->stop);
	checker->data->stop_flag = true;
	pthread_mutex_unlock(&checker->data->stop);
	return ;
}

static	void	kill(t_checker *checker, t_philo *philo)
{
	write_action(checker->data, philo, PRINT_DIED);
	pthread_mutex_lock(&checker->data->dead);
	pthread_mutex_lock(&checker->data->stop);
	philo->is_dead = true;
	checker->data->stop_flag = true;
	pthread_mutex_unlock(&checker->data->dead);
	pthread_mutex_unlock(&checker->data->stop);
}

static	void	monitor_time_to_die(t_checker *checker)
{
	unsigned int	i;

	i = 0;
	while (i < checker->data->nb_philos)
	{
		pthread_mutex_lock(&checker->data->meal);
		if (get_timestamp()
			>= checker->data->ph_tab[i].last_meal + checker->data->tt_die)
		{
			pthread_mutex_unlock(&checker->data->meal);
			kill(checker, &checker->ph_tab[i]);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&checker->data->meal);
			i++;
		}
	}
}

static	int	wait_for_philos(t_checker *checker)
{
	pthread_mutex_lock(&checker->data->init_th);
	checker->data->initialized_th += 1;
	pthread_mutex_unlock(&checker->data->init_th);
	while (true)
	{
		pthread_mutex_lock(&checker->data->init_th);
		if (checker->data->initialized_th == checker->data->nb_philos + 1)
		{
			pthread_mutex_unlock(&checker->data->init_th);
			break ;
		}
		pthread_mutex_unlock(&checker->data->init_th);
		pthread_mutex_lock(&checker->data->stop);
		if (checker->data->stop_flag == true)
		{
			pthread_mutex_unlock(&checker->data->stop);
			return (FAILURE);
		}
		pthread_mutex_unlock(&checker->data->stop);
		usleep((checker->data->nb_philos % 10) * 100);
	}
	return (SUCCESS);
}

void	*checker_routine(void *ptr)
{
	t_checker	*checker;

	checker = (t_checker *)ptr;
	if (wait_for_philos(checker) == FAILURE)
		return (checker->data->finished_th++, NULL);
	while (true)
	{
		usleep(500);
		pthread_mutex_lock(&checker->data->stop);
		if (checker->data->stop_flag == true)
		{
			pthread_mutex_unlock(&checker->data->stop);
			break ;
		}
		pthread_mutex_unlock(&checker->data->stop);
		monitor_time_to_die(checker);
		if (checker->data->must_eat != -1)
			monitor_meal_count(checker);
	}
	return (finish_checker(checker));
}
