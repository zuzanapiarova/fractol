/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:40 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/27 10:42:52 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>	// malloc free
# include <unistd.h>	// write
# include <stdint.h> // uint types
# include <stdio.h>	// printf
# include <math.h>	// math functions
# include <stdint.h> // unit_32 type
# include <pthread.h> // threads
# include "../MLX42/include/MLX42/MLX42.h" //minilibx

// preprocessor macros
# define HEIGHT	1000 // height should be divisible by 10 for threads 
# define WIDTH	1000
# define ERROR 1
# define SUCCESS 0
# define W 0xffffffff
# define B 0x000000ff
# define COLORS_SIZE 8
# define DIVERGENT_VALUE 8
# define NUM_THREADS 10

typedef struct s_complex
{
	double		real;
	double		imaginary;
}				t_complex;

// pos represents position is in gradient between [0.0, 1.0]
typedef struct s_color
{
	double		pos;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
}				t_color;

typedef struct s_fractal
{
	mlx_t		*window;
	mlx_image_t	*img;
	char		*name;
	double		escape_value;
	int			iters;
	char		*colorway;
	uint32_t	inside;
	double		xstart;
	double		xend;
	double		ystart;
	double		yend;
	double		diff;
	double		julia_r;
	double		julia_i;
	t_color		colors[COLORS_SIZE];
	uint32_t	*pixels_buffer;
}				t_fractal;

typedef struct s_thread_data
{
	t_fractal	*f;
	int			start_row;
	int			end_row;
}				t_thread_data;

// main logic
void		render_window(t_fractal *fractal);

// hooks
void		my_keyhook(mlx_key_data_t keydata, void *fractal);
void		my_scrollhook(double xdelta, double ydelta, void *fractal);
void		my_closehook(void *fractal);

// math
double		scale(double num, double new_min, double new_max, double old_max);
t_complex	complex_operation(t_complex z, t_complex c);
uint32_t	interpolate_color_hsv(t_fractal *f, double t);
uint32_t	coloring_algorithm(t_complex z, int i, t_fractal *f);

// utils
int			ft_error(char *msg);
void		clean_exit(t_fractal *f, int , char *msg);
int			ft_strncmp(char *s1, char *s2, int n);
double		atod(char *str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *str);
int 		parse_arg(char *argv1);
void		hsv_to_rgb(double h, double s, double v, t_color *final);
void		rgb_to_hsv(t_color color, double *h, double *s, double *v);

// colorways
void	get_colorway_tropic(char **colorway, t_color colors[8]);
void 	get_colorway_sunset(char **colorway, t_color *colors);
void 	get_colorway_cosmic(char **colorway, t_color *colors);
void 	get_colorway_oceans(char **colorway, t_color *colors);
void	get_colorway_purple(char **colorway, t_color *colors);
void	get_colorway_trippy(char **colorway, t_color *colors);
void	get_colorway_electric(char **colorway, t_color *colors);

#endif
