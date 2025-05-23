/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:40 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/23 10:30:36 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>	// malloc free
# include <unistd.h>	// write
# include <stdio.h>	// printf
# include <math.h>	// math functions
# include "../MLX42/include/MLX42/MLX42.h" //minilibx

// preprocessor macros
# define HEIGHT	1000
# define WIDTH	1000
# define ERROR 1
# define SUCCESS 0
# define W 0xffffffff
# define B 0x000000ff
# define A 0x01ffffff
# define R 0xd91116ff
# define Y 0xfff700ff
# define P 0x590067ff
# define BA 0x00264Dff
# define BB 0x003366ff
# define BC 0x004080ff
# define BE 0x0059B3ff
# define BF 0x0066CCff
# define BG 0x0073E6ff
# define BH 0x0080FFff
# define BI 0x3399FFff
# define BJ 0x66B2FFff
# define A1 0xFF00FFFF
# define A2 0xFF0066FF
# define A3 0xFF3300FF
# define A5 0xFF9900FF
# define A6 0xFFCC00FF
# define A7 0xCCFF00FF
# define A8 0x66FF00FF
# define A9 0x00FF66FF
# define A0 0x00FFFFFF
# define COLORWAY_SIZE 9

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
int			ft_strncmp(char *s1, char *s2, int n);
double		atod(char *str);
int			set_color(int i, char *color);
int			ft_isdigit(int c);
int			ft_error(char *msg);
size_t		ft_strlen(const char *str);
void		ft_exit(void);

// math
double		scale(double num, double new_min, double new_max, double old_max);
t_complex	complex_operation(t_complex z, t_complex c);

#endif
