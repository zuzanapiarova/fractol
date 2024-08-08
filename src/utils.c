/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:04:40 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/08 19:32:35 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
// #include "../include/fractol.h"

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

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
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

void	malloc_error(void)
{
	perror("Memory allocation failed. Exiting now.");
	exit(EXIT_FAILURE);
}
