/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:15:14 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 05:07:10 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

static 	int	init_others_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->meal, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	if (pthread_mutex_init(&data->stop, NULL) != 0)
		return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
	return (SUCCESS);
}

static	int	create_forks(t_data *data)
{
	unsigned int	i;
	unsigned int 	nb_fork;
	pthread_mutex_t	*forks_tab;

	i = 0;
	nb_fork = data->nb_philos;
	forks_tab = malloc(nb_fork * sizeof(pthread_mutex_t));
	if (forks_tab == NULL)
		return (cleaner(data, FAILURE, ERR_MALLOC));
	data->forks = forks_tab;
	while (i < (int)data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while ((i - 1) >= 0)
				pthread_mutex_destroy(&data->forks[i--]);
			data->forks = NULL;
			destroy_others_mutex(data);
			return (cleaner(data, FAILURE, ERR_INIT_MUTEX));
		}
		i++;
	}
	return (SUCCESS);
}

static	int	fill_struct(t_data *data, int argc, char **argv)
{
	data->nb_philos = (unsigned int)ft_mini_atoi(argv[1]);
	data->tt_die = (unsigned int)ft_mini_atoi(argv[2]);
	data->tt_eat = (unsigned int)ft_mini_atoi(argv[3]);
	data->tt_sleep = (unsigned int)ft_mini_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = (unsigned int)ft_mini_atoi(argv[5]);
	return (init_others_mutex(data));
}

static	void	init_philos(t_data *d)
{
	unsigned int	i;

	i = 0;
	while (i < d->nb_philos)
	{
		d->ph_tab[i].th = 0;
		d->ph_tab[i].id = i + 1;
		d->ph_tab[i].first_fork = 0;
		d->ph_tab[i].second_fork = 0;
		d->ph_tab[i].last_meal = 0;
		d->ph_tab[i].meals_count = 0;
		d->ph_tab[i].eating = false;
		d->ph_tab[i].is_starving = false;
		d->ph_tab[i].is_dead = false;
		d->ph_tab[i].data = d;
		d->ph_tab[i].first_fork = d->ph_tab[i].id;
		d->ph_tab[i].second_fork = (d->ph_tab[i].id + 1) % d->nb_philos;
		i++;
	}
}

int	init_structs_and_philos(t_data *data, t_philo *philos_tab, int argc, char **argv)
{	
	data->ph_tab = philos_tab;
	data->stop_flag = false;
	data->nb_philos = 0;
	data->initialized_th = 0;
	data->finished_th = 0;
	data->tt_die = 0;
	data->tt_eat = 0;
	data->tt_sleep = 0;
	data->must_eat = -1;
	if (checks_args(argv) == FAILURE)
		return (cleaner(data, ERR_BAD_ARGS, FAILURE));
	if (fill_struct(data, argc, argv) == FAILURE)
		return (cleaner(data, FAILURE, NULL));
	init_philos(data);
	if (create_forks(data) == FAILURE)
		return (cleaner(data, FAILURE, NULL));
	return (SUCCESS);
}
