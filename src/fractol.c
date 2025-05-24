/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:21 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/24 13:26:12 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// clone MLX42: git clone https://github.com/codam-coding-college/MLX42.git

// for each pixel we perform the mandelbrot set function z = z^2 + c
// and color it dependeing on how many iterations it took for point to escape
// leave white if point did not escape in fractal.iterations num of iterations
void set_pixel(int x, int y, t_fractal f)
{
	t_complex z;
	t_complex c;
	int i;

	z.real = 0;
	z.imaginary = 0;
	c.real = scale(x, f.xstart, f.xend, WIDTH);
	c.imaginary = scale(y, f.ystart, f.yend, HEIGHT);
	if (!ft_strncmp(f.name, "julia\0", 6))
	{
		z.real = (scale(x, f.xstart, f.xend, WIDTH));
		z.imaginary = (scale(y, f.ystart, f.yend, HEIGHT));
		c.real = f.julia_r;
		c.imaginary = f.julia_i;
	}
	i = 0;
	while (i < f.iters)
	{
		z = complex_operation(z, c);
		if (pow(z.real, 2) + pow(z.imaginary, 2) > f.escape_value)
			return (mlx_put_pixel(f.img, x, y, set_color(i, f.colorway)));
		i++;
	}
	mlx_put_pixel(f.img, x, y, f.inside);
}

// iterates through window pixels one by one, each pixel in each row,
// to set its color based on whether it escaped and in how many iteration
void *render_window(void *arg)
{
	int x;
	int y;
	t_fractal *fractal;

	fractal = (t_fractal *)arg;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			set_pixel(x, y, *fractal);
	}
}

// initialize the fractal struct with the initial data
void fractal_init(t_fractal *f, char *name, char *arg1, char *arg2)
{
	f->name = name;
	if (!ft_strncmp(name, "julia\0", 6))
	{
		f->julia_r = atod(arg1);
		f->julia_i = atod(arg2);
	}
	f->iters = 15;
	f->escape_value = 8;
	f->colorway = "multi";
	f->inside = W;
	f->xstart = -2.2;
	f->xend = 0.8;
	f->ystart = 1.2;
	f->yend = -1.8;
	f->running = true;
	f->window = mlx_init(WIDTH, HEIGHT, f->name, false);
	if (!f->window)
		clean_exit(f, EXIT_FAILURE);
	f->img = mlx_new_image(f->window, WIDTH, HEIGHT);
	if (!f->img || (mlx_image_to_window(f->window, f->img, 0, 0) < 0))
		clean_exit(f, EXIT_FAILURE);
	pthread_mutex_init(&(f->running_lock), NULL);
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		if (pthread_create(&f->threads[i], NULL, render_window, (void *)f) == ERROR)
			clean_exit(f, EXIT_FAILURE);
	}
}

int32_t main(int argc, char *argv[])
{
	t_fractal fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot\0", 11))
		|| (argc >= 4 && !ft_strncmp(argv[1], "julia\0", 6) 
		&& parse_arg(argv[2]) == SUCCESS && parse_arg(argv[3]) == SUCCESS))
		fractal_init(&fractal, argv[1], argv[2], argv[3]);
	else
	{
		write(1, "Fractals available for exploration:\n", 36);
		write(1, "./fractol Mandelbrot\n", 21);
		write(1,"./fractol julia real<-1,1> imaginary<-1,1>\n", 43);
		return (ERROR);
	}
	mlx_key_hook(fractal.window, &my_keyhook, &fractal);
	mlx_scroll_hook(fractal.window, &my_scrollhook, &fractal);
	mlx_close_hook(fractal.window, &my_closehook, &fractal);
	mlx_loop(fractal.window);
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}
	clean_exit(&fractal, EXIT_SUCCESS);
}
