/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:56:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/24 13:44:15 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (ERROR);
}

// checks if argument is only digits with one dot, possibly starts with 1 minus
int parse_arg(char *argv1)
{
	char *copy;
	int dot;

	if (argv1 == NULL)
		return (ERROR);
	copy = argv1;
	dot = 0;
	if (*copy == '-')
		copy++;
	while (*copy)
	{
		if (*copy == '.' && (!dot || *(copy + 1) == '\0'))
			dot++;
		else if (*copy == '.' && dot)
			return (ft_error("Extra dot.\n"));
		else if (!ft_isdigit(*copy))
			return (ft_error("Contains characters other than digits.\n"));
		printf("c: %c", *copy);
			copy++;
	}
	return (SUCCESS);
}

int	set_color(int i, char *color)
{
	int	palette[COLORWAY_SIZE];

	palette[0] = A1;
	palette[1] = A2;
	palette[2] = A3;
	palette[3] = A5;
	palette[4] = A6;
	palette[5] = A7;
	palette[6] = A8;
	palette[7] = A9;
	palette[8] = A0;
	if (!ft_strncmp(color, "blue", 4))
	{
		palette[0] = BA;
		palette[1] = BB;
		palette[2] = BC;
		palette[3] = BE;
		palette[4] = BF;
		palette[5] = BG;
		palette[6] = BH;
		palette[7] = BI;
		palette[8] = BJ;
	}
	return (palette[i % COLORWAY_SIZE]);
}
