/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:18:45 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/07/21 21:26:46 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define ERROR_MESSAGE = "Only valid input is \"./fractol mandelbrot\" or \"./fractol julia <real-value> <imaginary-value>\"\n"
# define HEIGHT 800
# define WIDTH 800

#include <stdlib.h> //malloc free
#include <unistd.h> //write
#include <stdio.h> //printf
#include <math.h> //
#include "../MLX42/include/MLX42/MLX42.h" //minilibx

// typedef struct	s_fractal {
// 	void	*fractal;
// 	void	*xconnection;
// 	void	*xwindow;
// 	void	*ximage;
// 	char	*name;

// }				t_fractal;

// typedef struct	s_img {
// 	void	*img;
// 	char	*addr;
// 	int		bpp;
// 	int		line_length;
// }				t_img;

// utils
int	ft_strncmp(char *s1, char *s2, int n);
void malloc_error(void);

#endif
