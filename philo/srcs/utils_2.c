/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:56:54 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/15 17:30:28 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	ft_now_ms(void)
{
	struct timeval	tv;

	if ((gettimeofday(&tv, NULL)) == -1)
		return (0);
	return ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL));
}

void	ft_usleep(uint64_t milli, t_philo	*philo)
{
	uint64_t	now;
	uint64_t	elapsed;

	now = ft_now_ms();
	elapsed = ft_now_ms();
	while (elapsed - now < milli)
	{
		if (ft_should_stop(philo))
			break ;
		usleep(333);
		elapsed = ft_now_ms();
	}
}
