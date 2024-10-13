/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:06:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/14 00:34:59 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

static	void	monitor_meal_count(t_checker *checker)
{
	unsigned	int	i;

	i = 0;
	pthread_mutex_lock(&checker->data->meal);
	while (i < checker->data->nb_philos)
	{
		if ((int)checker->data->ph_tab[i].meals_count == checker->data->must_eat)
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
	pthread_mutex_lock(&checker->data->stop);
	philo->is_dead = true;
	checker->data->stop_flag = true;
	pthread_mutex_unlock(&checker->data->stop);
	write_action(checker->data, philo, PRINT_DIED);
}

static	void	monitor_time_to_die(t_checker *checker)
{
	unsigned int	i;

	i = 0;
	while (i < checker->data->nb_philos)
	{
		pthread_mutex_lock(&checker->data->meal);
		if (get_timestamp() >= checker->data->ph_tab[i].last_meal + checker->data->tt_die)
		{
			dprintf(2, "last meal = %u ; tt_die = %u\n", checker->data->ph_tab[i].last_meal, checker->data->tt_die);
			pthread_mutex_unlock(&checker->data->meal);
			kill(checker, &checker->ph_tab[i]);
			break;
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
	pthread_mutex_lock(&checker->data->stop);
	checker->data->initialized_th += 1;
	pthread_mutex_unlock(&checker->data->stop);
	while (true)
	{
		pthread_mutex_lock(&checker->data->stop);
		if (checker->data->initialized_th == checker->data->nb_philos + 1)
		{
			pthread_mutex_unlock(&checker->data->stop);
			break;
		}
		if (checker->data->stop_flag == true)
		{
			pthread_mutex_unlock(&checker->data->stop);
			return (FAILURE);
		}
		pthread_mutex_unlock(&checker->data->stop);
		usleep(500);
	}
	return (SUCCESS);
}

void	*checker_routine(void *ptr)
{
	t_checker	*checker;

	checker = (t_checker *)ptr;
	checker_debug(checker, "checker has been created !");
	if (wait_for_philos(checker) == FAILURE)
		return (checker->data->finished_th++, NULL);
	while (true)
	{
		usleep(500);
		pthread_mutex_lock(&checker->data->stop);
		if (checker->data->stop_flag == true)
		{
			pthread_mutex_unlock(&checker->data->stop);
			break;
		}
		pthread_mutex_unlock(&checker->data->stop);
		monitor_time_to_die(checker);
		if (checker->data->must_eat != -1)
			monitor_meal_count(checker);
	}
	return (checker->data->finished_th++, NULL);
}

// ROUTINE DE SURVEILLANCE DE CHAQUE PHILO :
// - La simulation s'arrête si le dernier repas d'un philo est supérieur ou égal au tt_die
//   ou si le nombre de repas demandé à été atteint ou si l'initialisation d'un autre thread a échouer.
// - Si un des philos doit être tuer le flag is_dead passera à true et un message sera afficher, la simulation s'arretera
// - Si le nombre de repas à été atteint la simulation s'arrête.