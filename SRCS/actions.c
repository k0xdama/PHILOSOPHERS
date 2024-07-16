/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:19:59 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/16 19:47:42 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers.h"

void	think(t_philo *ph)
{
	write_action("is thinking", ph);
}

void	doze(t_philo *ph)
{
	write_action("is sleeping", ph);
	ft_usleep(ph->data->tt_sleep);
}

void	eat(t_philo *ph)
{
	
}