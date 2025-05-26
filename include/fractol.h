/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:40 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/26 15:07:17 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>	// malloc free
# include <unistd.h>	// write
# include <stdint.h> // uint types
# include <stdio.h>	// printf
# include <math.h>	// math functions
#include <stdint.h> // unit_32 type
# include "../MLX42/include/MLX42/MLX42.h" //minilibx

// preprocessor macros
# define HEIGHT	1000
# define WIDTH	1000
# define ERROR 1
# define SUCCESS 0

typedef struct s_fractal
{
	mlx_t		*window;
	mlx_image_t	*img;
	char		*name;
	double		escape_value;
	int			iters;
	char		*colorway;
	int			inside;
	double		xstart;
	double		xend;
	double		ystart;
	double		yend;
	double		diff;
	double		julia_r;
	double		julia_i;
}				t_fractal;

typedef struct s_complex
{
	double		real;
	double		imaginary;
}				t_complex;

// main logic
void		render_window(t_fractal fractal);
// hooks
void		my_keyhook(mlx_key_data_t keydata, void *fractal);
void		my_scrollhook(double xdelta, double ydelta, void *fractal);
void		my_closehook(void *fractal);
// utils
uint32_t	interpolate_color(double t);
int			ft_strncmp(char *s1, char *s2, int n);
double		atod(char *str);
int			set_color(double t, int i, char *color);
int			ft_isdigit(int c);
int			ft_error(char *msg);
size_t		ft_strlen(const char *str);
int 		parse_arg(char *argv1);

// math
double		scale(double num, double new_min, double new_max, double old_max);
t_complex	complex_operation(t_complex z, t_complex c);

#endif
