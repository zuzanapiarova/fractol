/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:18:45 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/07/23 15:38:00 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdlib.h>	// malloc free
#include <unistd.h>	// write
#include <stdio.h>	// printf
#include <math.h>	//
#include "../MLX42/include/MLX42/MLX42.h" //minilibx

# define ERROR_MESSAGE = "Only valid input is \"./fractol mandelbrot\" or \"./fractol julia <real-value> <imaginary-value>\"\n"
# define HEIGHT 800
# define WIDTH 800

typedef struct	s_fractal {
	void	*fractal;
	mlx_t	*window;
	mlx_image_t	*img;
	char	*name;
}			t_fractal;

// utils
int	ft_strncmp(char *s1, char *s2, int n);
void malloc_error(void);

#endif
