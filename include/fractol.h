/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:18:45 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/01 22:51:14 by zuzanapiaro      ###   ########.fr       */
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
# define HEIGHT	1000
# define WIDTH	1000

typedef struct	s_fractal {
	void		*fractal;
	mlx_t		*window;
	mlx_image_t	*img;
	char		*name;
	double		escape_value;
	int			iterations;
	// xend - xstart and yend - ystart must be the same so that proportions to the window which is square are the same
	double		xstart;
	double		xend;
	double		ystart;
	double		yend;
}				t_fractal;

typedef struct	s_complex {
	double		real;
	double		imaginary;
}				t_complex;

// main logic
void render_window(t_fractal fractal);

// hooks
void my_keyhook(mlx_key_data_t keydata, void *fractal);
void my_scrollhook(double xdelta, double ydelta, void *fractal);
void my_closehook(void *fractal);

// utils
int	ft_strncmp(char *s1, char *s2, int n);
void malloc_error(void);
double scale(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex complex_operation(t_complex z, t_complex c);

#endif
