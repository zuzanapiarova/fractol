/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:18:45 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/07/27 21:18:32 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdlib.h>	// malloc free
#include <unistd.h>	// write
#include <stdio.h>	// printf
#include <math.h>	// math functions
#include "../MLX42/include/MLX42/MLX42.h" //minilibx

# define ERROR_MESSAGE = "Only valid input is \"./fractol mandelbrot\" or \"./fractol julia <real-value> <imaginary-value>\"\n"
# define HEIGHT 1000
# define WIDTH 1000

typedef struct	s_fractal {
	void	*fractal;
	mlx_t	*window;
	mlx_image_t	*img;
	char	*name;
	double escape_value;
	int iterations;
	// xend - xstart and yend - ystart must be the same so that proportions to the window which is square are the same
	double xstart;
	double xend;
	double ystart;
	double yend;
}			t_fractal;

typedef struct	s_complex {
	double real;
	double imaginary;
}				t_complex;

//////// utils
int	ft_strncmp(char *s1, char *s2, int n);
void malloc_error(void);

#endif
