/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:56:54 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/11 11:18:22 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	ft_now_ms(void)
{
	struct timeval	tv;

	if((gettimeofday(&tv, NULL)) == -1)
		return(0);
	return ((tv.tv_sec * 1000ULL) + (tv.tv_usec / 1000ULL));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return(0);
	while (str[i])
		i++;
	return (i);
}

void	ft_usleep(uint64_t milli)
{
	uint64_t	now;
	uint64_t	elapsed;

	now = ft_now_ms();
	elapsed = ft_now_ms();
	while (elapsed - now < milli)
	{
		usleep(333);
		elapsed = ft_now_ms();
	}
}
