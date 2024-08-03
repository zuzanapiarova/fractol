/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:45:53 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/03 16:23:29 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// ----- HOOKS ------
// listen for keypress events for ESC, arrows, plus and minus
void my_keyhook(mlx_key_data_t keydata, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;
	double diff;

	diff = f->xend - f->xstart;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 0)
	{
		mlx_close_window(f->window);
		mlx_terminate(f->window);
		exit(1);
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == 0)
	{
		f->xstart += diff / 5;
		f->xend += diff / 5;
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == 0)
	{
		f->xstart -= diff / 5;
		f->xend -= diff / 5;
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == 0)
	{
		f->ystart -= diff / 5;
		f->yend -= diff / 5;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == 0)
	{
		f->ystart += diff / 5;
		f->yend += diff / 5;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == 0)
	{
		f->ystart += diff / 5;
		f->yend += diff / 5;
	}
	else if (keydata.key == MLX_KEY_EQUAL && keydata.action == 0)
	{
		f->iterations += 5;
	}
	else if (keydata.key == MLX_KEY_MINUS && keydata.action == 0)
	{
		f->iterations -= 5;
	}
	render_window(*f);
}
// SCALUJEME NA MOUSE MOVEMENT
void my_scrollhook(double xdelta, double ydelta, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	double diff = (f->yend - f->ystart);
	//zoom in
	if (ydelta < 0)
	{
		f->ystart -= 0.1 * diff;
		f->yend += 0.1 * diff;
		f->xstart += 0.1 * diff;
		f->xend -= 0.1 * diff;
	}
	//zoom out
	if (ydelta > 0)
	{
		f->ystart += 0.1 * diff;
		f->yend -= 0.1 * diff;
		f->xstart -= 0.1 * diff;
		f->xend += 0.1 * diff;
	}
	render_window(*f);
}

void my_closehook(void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	mlx_close_window(f->window);
	mlx_terminate(f->window);
	exit(1);
}
