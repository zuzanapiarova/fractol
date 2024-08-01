/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:04:01 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/01 22:48:38 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//function to calculate how many iterations i need to know if the point escaped - so it is black(inside) or color(outside )
/* explanation: the less iterations there are we cannot be sure that the point escapes or not - so in few iterations the point is black as it has not escaped yet
so it seems stable for now, the more iterations we add the more points escape and the image becomes more and more precise
so in less iterations the mandelbrot looks like a big blob, in more iterations it is refines into smaller and more precise shape */

// mandelbrot math:
//point is in mandelbrot if z = z^2 + c
// z and c are both complex numbers - both have a real and an imaginary part
// initially - in the first iteration: z is 0, c is the actual pixel in window with its passed x and y coordinates
// we can illustrate the real value as value at x axis and imaginary value(without the i) as value at the y axis

// linear interpolation function = maps/scales points proportionate and linearly to other points to keep the proportions but scaled in/out
double scale(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min);
}

// this function does the operation z = z^2 + c
t_complex complex_operation(t_complex z, t_complex c)
{
	t_complex z_squared;
	t_complex result;

	// squaring complex number - z^2
	// math: complex number is basically : cnum(real) + cnum(imaginary) --> rnum + inum --> rnum + inum*i
	// so squaring cnum^2 = (cnum(real) + cnum(imaginary))^2 = cnum(real)^2 + 2*cnum(real)*cnum(imaginary) + cnum(imaginary)^2
	// 			   cnum^2 = (rnum + inum*i)^2 = rnum^2 + 2*rnum*inum*i + inum^2*i^2
	// but i^2 is -1 so this imaginary component turns into real component and only imaginary number left is 2*rnum*inum*i
	// --> cnum^2 = rnum^2 - inum^2 + 2*rnum*inum*i
	//             |------real-----| |--imaginary--| --> we get new real and new imaginary parts

	z_squared.real = pow(z.real, 2) - pow(z.imaginary, 2);
	z_squared.imaginary = 2 * z.real * z.imaginary;

	// adding two complex numbers - z^2 + c
	result.real = z_squared.real + c.real;
	result.imaginary = z_squared.imaginary + c.imaginary;
	return result;
}
