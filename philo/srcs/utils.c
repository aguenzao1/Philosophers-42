/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguenzao <aguenzao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:11:12 by aguenzao          #+#    #+#             */
/*   Updated: 2025/03/08 11:57:56 by aguenzao         ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	tmp = malloc(size * count);
	if (!tmp)
		return (NULL);
	return (memset(tmp, 0, size * count));
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

bool	ft_isint(char *str)
{
	char	*max_int;
	size_t	str_len;

	max_int = "2147483647";
	if (*str == '+')
		str++;
	str_len = ft_strlen(str);
	if (str_len > 10)
		return (false);
	if (str_len == 10)
		while (ft_isdigit(*str) && *str <= *max_int++)
			str++;
	else
		while (ft_isdigit(*str))
			str++;
	return (!*str && true);
}
