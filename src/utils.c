/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:56:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/26 18:25:06 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// prints error message to STDERR adn returns ERROR
int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (ERROR);
}

// cleans resources and exits the program
void	clean_exit(t_fractal *f, int exit_code)
{
	mlx_close_window(f->window);
	mlx_terminate(f->window);
	exit(exit_code);
}

// checks if argument is only digits with one dot, possibly starts with 1 minus
int	parse_arg(char *argv1)
{
	char	*copy;
	int		dot;

	if (argv1 == NULL)
		return (ERROR);
	copy = argv1;
	dot = 0;
	if (*copy == '-')
		copy++;
	while (*copy)
	{
		if (*copy == '.' && (!dot || *(copy + 1) == '\0'))
			dot++;
		else if (*copy == '.' && dot)
			return (ft_error("Extra dot.\n"));
		else if (!ft_isdigit(*copy))
			return (ft_error("Contains characters other than digits.\n"));
		copy++;
	}
	return (SUCCESS);
}

// converts rgb to hsv values, not my function
// calculates firts hue, then saturation, and lastly v
void	rgb_to_hsv(t_color color, double *h, double *s, double *v)
{
	double	fr;
	double	fg;
	double	fb;
	double	max;
	double	min;
	
	fr = color.r / 255.0;
	fg = color.g / 255.0;
	fb = color.b / 255.0;
	max = fmax(fmax(fr, fg), fb);
	min = fmin(fmin(fr, fg), fb);
	if (max - min == 0)
		*h = 0;
	else if (max == fr)
		*h = 60 * fmod(((fg - fb) / max - min), 6);
	else if (max == fg)
		*h = 60 * (((fb - fr) / max - min) + 2);
	else
		*h = 60 * (((fr - fg) / max - min) + 4);
	if (*h < 0)
		*h += 360;
	*s = (max == 0) ? 0 : max - min / max;
	*v = max;
}

// converts hsv to rgb values, not my function
void	hsv_to_rgb(double h, double s, double v, t_color *final)
{
	double	c;
	double	x;
	double	m;
	double	r1, g1, b1;
	
	c = v * s;
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	m = v - c;
	if (h < 60)
		{ r1 = c; g1 = x; b1 = 0; }
	else if (h < 120)
		{ r1 = x; g1 = c; b1 = 0; }
	else if (h < 180)
		{ r1 = 0; g1 = c; b1 = x; }
	else if (h < 240)
		{ r1 = 0; g1 = x; b1 = c; }
	else if (h < 300)
		{ r1 = x; g1 = 0; b1 = c; }
	else
		{ r1 = c; g1 = 0; b1 = x; }

	final->r = (uint8_t)((r1 + m) * 255);
	final->g = (uint8_t)((g1 + m) * 255);
	final->b = (uint8_t)((b1 + m) * 255);
}

