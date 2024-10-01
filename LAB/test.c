/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmateo <pmateo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:10:53 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/30 18:34:29 by pmateo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/time.h>

size_t	get_timestamp(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("\"gettimeofday\" failed !\n");
		return (EXIT_FAILURE);
	}
	printf ("tv_sec = %ld | tv_usec = %ld\n", t.tv_sec, t.tv_usec);
	printf ("tv_sec * 1000 = %ld | tv_usec / 1000 = %ld\n", t.tv_sec * 1000, t.tv_usec / 1000);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	main(void)
{
	size_t	timestamp;

	timestamp = get_timestamp();
	printf("timestamp = %ld\n", timestamp);
}