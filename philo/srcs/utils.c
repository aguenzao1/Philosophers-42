/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:11:12 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/11 11:18:47 by aguenzao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isspace(int c)
{
	if (c != '\t' && c != '\n' && c != '\v' \
		&& c != '\f' && c != '\r' && c != ' ')
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	sum;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	sum = 0;
	while (ft_isdigit(str[i]))
	{
		sum = sum * 10 + (str[i] - '0');
		if (sum < 0)
			return ((sign != -1) * -1);
		i++;
	}
	return (sum * sign);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

bool    ft_isint(char *str)
{
    int		i;
    long    num;

    i = 0;
    num = 0;
    if (!str[i])
        return (false);
    if (str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (false);
        num = (num * 10) + (str[i] - '0');
        if (num > INT_MAX)
            return (false);
        i++;
    }
    return (true);
}
