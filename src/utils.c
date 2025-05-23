/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:56:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/23 10:30:23 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (ERROR);
}

// Exit the program when given wrong input
void ft_exit(void)
{
	write(1, "Fractals available for exploration:\n", 36);
	write(1, "./fractol Mandelbrot\n", 21);
	write(1,"./fractol julia real<-1,1> imaginary<-1,1>\n", 43);
	exit(EXIT_FAILURE);
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
