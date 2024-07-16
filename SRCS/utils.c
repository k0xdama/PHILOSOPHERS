/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:39:38 by pmateo            #+#    #+#             */
/*   Updated: 2024/07/16 19:43:03 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../INCLUDES/philosophers.h"

void	write_action(char *str, t_philo *ph)
{
	size_t	time;

	time = get_timestamp() - ph->data->start;
	pthread_mutex_lock(?);
	if (life_line(ph))
		printf("%lu %d %s\n", time, ph->id, str);
	pthread_mutex_unlock(?);
}

size_t	get_timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		printf("\"gettimeofday\" failed !\n");
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_mini_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

