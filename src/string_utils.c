/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:25:21 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2025/05/23 10:26:33 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (s1 == NULL || s2 == NULL || n <= 0)
		return (0);
	while (*s1 == *s2 && n != 0 && *s1 != 0)
	{
		s1++;
		s2++;
		n--;
	}
	return (*s1 - *s2);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

double	atod(char *str)
{
	long	in;
	double	d;
	double	pow;
	int		sign;

	in = 0;
	d = 0;
	pow = 1;
	sign = 1;
	while (*str == 32 || *str == '+' || *str == '-')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
		in = in * 10 + (*str++ - '0');
	if (*str == '.' || *str == ',')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		pow = pow / 10;
		d = d + ((*str++ - '0') * pow);
	}
	return ((in + d) * sign);
}
