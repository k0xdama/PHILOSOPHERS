/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:39:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/10/12 03:09:44 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

void	write_debug(t_data *data, char *str)
{
	pthread_t	thread_id = pthread_self();
	pthread_mutex_lock(&data->write);
	dprintf(2, "TH : %ld | %s %u\n", thread_id, str, data->initialized_th);
	pthread_mutex_unlock(&data->write);
}

void	write_action(t_data *data, t_philo *ph, char *str)
{
	size_t	time;

	time = get_timestamp() - ph->data->start;
	pthread_mutex_lock(&data->write);
	printf("%lu %d %s\n", time, ph->id, str);
	pthread_mutex_unlock(&data->write);
}

unsigned int	get_timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("\"gettimeofday\" failed !\n");
		return (0);
	}
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}
//gestion d'erreur lors de la création des threads :
// - 
// INT MAX DANS LES ARGUMENTS

