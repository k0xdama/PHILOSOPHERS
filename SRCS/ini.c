/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:15:14 by pmateo            #+#    #+#             */
/*   Updated: 2024/11/06 20:27:58 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

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

static	void	give_forks(t_data *d)
{
	size_t	i;

	i = 0;
	while (i < d->nb_philos)
	{
		if (d->ph_tab[i].id % 2 == 0)
		{
			d->ph_tab[i].first_fork = d->ph_tab[i].id - 1;
			d->ph_tab[i].second_fork = (d->ph_tab[i].id) % d->nb_philos;
		}
		else
		{
			d->ph_tab[i].first_fork = (d->ph_tab[i].id) % d->nb_philos;
			d->ph_tab[i].second_fork = d->ph_tab[i].id - 1;
		}
		i++;
	}
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
		i++;
	}
	give_forks(d);
}

int	init_structs_and_philos(t_data *d, t_philo *ph_tab, int argc, char **argv)
{	
	d->ph_tab = ph_tab;
	d->stop_flag = false;
	d->stop_reason = END;
	d->nb_philos = 0;
	d->created_philos_th = 0;
	d->checker_is_created = false;
	d->initialized_th = 0;
	d->finished_th = 0;
	d->tt_die = 0;
	d->tt_eat = 0;
	d->tt_sleep = 0;
	d->must_eat = -1;
	d->start = get_timestamp();
	if (checks_args(argv) == FAILURE)
		return (msg_err(ERR_BAD_ARGS), FAILURE);
	if (fill_struct(d, argc, argv) == FAILURE)
		return (cleaner(d, FAILURE, NULL));
	init_philos(d);
	if (create_forks(d) == FAILURE)
		return (cleaner(d, FAILURE, NULL));
	return (SUCCESS);
}
