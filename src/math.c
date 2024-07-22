/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:04:01 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/07/21 20:04:02 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//function to map window size to the size in which mandelbrot is located --> map from <0-800) to <-2, 2>

//function to sum numbers

//function to square numbers

//function to calculate mandelbrot: z^2 + c

//function to calculate how many iterations i need to know if the point escaped - so it is black(inside) or color(outside )
/*
explanation: the less iterations there are we cannot be sure that the point escapes or not - so in few iterations the point is black as it has not escaped yet
so it seems stable for now, the more iterations we add the more points escape and the image becomes more and more precise
so in less iterations the mandelbrot looks like a big blob, in more iterations it is refines into smaller and more precise shape
*/

// function to color in outside of the mandelbrot set based on how many iterations it takes until it goes out of bounds 
