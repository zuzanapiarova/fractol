/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:58 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/27 10:51:48 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// linear interpolation function = maps/scales points proportionate and
// linearly to other points to keep the proportions but scaled in/out
double	scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / ((old_max)) + new_min);
}

// performs the function  = z^2 + c for when z, c are complex numbers
t_complex	complex_operation(t_complex z, t_complex c)
{
	t_complex	z_squared;
	t_complex	result;

	z_squared.real = pow(z.real, 2) - pow(z.imaginary, 2);
	z_squared.imaginary = 2 * z.real * z.imaginary;
	result.real = z_squared.real + c.real;
	result.imaginary = z_squared.imaginary + c.imaginary;
	return (result);
}

// interpolation function to get nice gradient colors, not mine
uint32_t interpolate_color_hsv(t_fractal *f, double t)
{
	int			i;
	double		local_t;

	if (t <= f->colors[0].pos)
		return (f->colors[0].r << 24) | (f->colors[0].g << 16) | f->colors[0].b << 8 | 0xFF;
	if (t >= f->colors[COLORS_SIZE - 1].pos)
		return (f->colors[COLORS_SIZE - 1].r << 24) | (f->colors[COLORS_SIZE - 1].g << 16) | f->colors[COLORS_SIZE - 1].b << 8 | 0xFF;
	i = -1;
	while (++i < COLORS_SIZE - 1)
	{
		if (t >= f->colors[i].pos && t <= f->colors[i + 1].pos)
		{
			local_t = (t - f->colors[i].pos) / (f->colors[i + 1].pos - f->colors[i].pos);
			double h1, s1, v1, h2, s2, v2;
			rgb_to_hsv(f->colors[i], &h1, &s1, &v1);
			rgb_to_hsv(f->colors[i + 1], &h2, &s2, &v2);
			// Interpolate hue properly
			double dh = h2 - h1;
			if (fabs(dh) > 180.0)
				dh = (dh > 0) ? dh - 360.0 : dh + 360.0;
			double h = fmod(h1 + local_t * dh + 360.0, 360.0);
			double s = (1.0 - local_t) * s1 + local_t * s2;
			double v = (1.0 - local_t) * v1 + local_t * v2;
			// Convert back to RGB
			t_color final;
			hsv_to_rgb(h, s, v, &final);
			return (final.r << 24) | (final.g << 16) | (final.b << 8) | 0xFF;
		}
	}
	return 0xFFFF00FF;
}

// smoothly colors a fractal point based on how fast it escapes (or doesn’t)
// by computing a smoothed iteration value and mapping it to a color
// @params t_complex = last computed value of fractal formula
// @params int i = number of iterations the point took to escape
// zn = magnitude (absolute value) of the complex number z
// nu = smoothing term for more accurate iteration counts(avoids color banding)
// smooth_i = computes a smooth version of the iteration count
// t = normalizes smooth_i to the range [0.0, 1.0] so it fits into the gradient
// squaring t helps use more of the palette  from the upper parts
uint32_t	coloring_algorithm(t_complex z, int i, t_fractal *f)
{
	double		zn;
	double		nu;
	double		smooth_i;
	double		t;
	
	zn = sqrt(z.real * z.real + z.imaginary * z.imaginary);
	nu = log(log(zn)) / log(2.0);
	smooth_i = i + 1 - nu;
	t = smooth_i / f->iters;
	t = pow(t, 0.4);
	return (interpolate_color_hsv(f, t));
}
