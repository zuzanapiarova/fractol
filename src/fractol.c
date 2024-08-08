/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:24:52 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/08 19:28:45 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// CALL THE PROGRAM: ./fractol(=arg[0]) mandelbrot(=arg[1])   ==>  argc is 2
// we are basically just setting color to each pixel based on how many
// iterations it takes for point with that coordinates to escape to infinity
// points that are inside the mandelbrot set are black - never escape
// points that are outside based on their color we can tell how many
// iterations it takes for them to escape

// Exit the program as failure
static void	ft_error(void)
{
	printf("%s\n", mlx_strerror(mlx_errno));
	printf("Fractals available for exploration:"
		"\n\tMandelbrot\n\tJulia <real> <imaginary> //best between (-1,1)\n\t"
		"Sierpinski\nPlease specify the name and in case of Julia "
		"parameters as arguments to the program.\nExiting now.");
	exit(EXIT_FAILURE);
}

/* void	set_pixel(int x, int y, t_fractal fractal)
{
	// z = z^2 + c; - both z and  are complex numbers
	// meaning both have real and imaginary part
	// real value is on x axis, imaginary is on y axis
	t_complex	z;
	t_complex	c;
	int		iter_count;
	int		color;

	// 1st point:
	//initially z: first iteration is given that z is 0:
	if (!ft_strncmp(fractal.name, "julia", 5))
	{
		z.real = (scale(x, fractal.xstart, fractal.xend, 0, WIDTH));
		z.imaginary = (scale(y, fractal.ystart, fractal.yend, 0, HEIGHT));
		c.real = fractal.julia_r;
		c.imaginary = fractal.julia_i;
	}
	else
	{
		z.real = 0;
		z.imaginary = 0;
		c.real = scale(x, fractal.xstart, fractal.xend, 0, WIDTH); //z.x
		c.imaginary = scale(y, fractal.ystart, fractal.yend, 0, HEIGHT); //z.y
	}
	// now we move to iterations and apply complex function to our point over
	// until we reach max iterations or it escapes
	iter_count = 0;
	// we perform the complex function for as many iterations as defined
	// the more iterations the more defined the image is
	// we iterate until the number of iterations is done or until point escapes
	while(iter_count < fractal.iterations)
	{
		z = complex_operation(z, c);
		// after each function run we check if the value is not escaped
		// for condition we use vectors-real(x)+imaginary(y) parts form odvesny
		// prepona je ich vektor, all vectors with prepona = 2 are deff escaped
		// - pythagorean theorem compares odvesny squared to prepona squared(4)
		if (pow(z.real, 2) + pow(z.imaginary, 2) > fractal.escape_value)
		{
			color = scale(iter_count, 0, 0xFF00FF, 0, fractal.iterations);
			mlx_put_pixel(fractal.img, x, y, color);
			return;
		}
		iter_count++;
	}
	mlx_put_pixel(fractal.img, x, y, 0xFFFFFFFF);
} */

// for each pixel we perform the mandelbrot set function z = z^2 + c
// and color it dependeing on how many iterations it took for point to escape
// leave white if did not escape in fractal.iterations number of iterations
void	set_pixel(int x, int y, t_fractal f)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.real = 0;
	z.imaginary = 0;
	c.real = scale(x, f.xstart, f.xend, WIDTH);
	c.imaginary = scale(y, f.ystart, f.yend, HEIGHT);
	if (!ft_strncmp(f.name, "julia", 5))
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
			return (mlx_put_pixel(f.img, x, y, scale(i, 0, W, f.iters)));
		i++;
	}
	mlx_put_pixel(f.img, x, y, 0xFFFFFFFF);
}

// iterates through window pixels one by one, each pixel in each row,
// to set its color based on whether it escaped and in how many iteration
void	render_window(t_fractal fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			set_pixel(x, y, fractal);
	}
}

// initialize the fractal struct with the initial data
void	fractal_init(t_fractal *f, char *name)
{
	f->name = name;
	f->iters = 10;
	f->escape_value = 4;
	f->xstart = -2.2;
	f->xend = 0.8;
	f->ystart = 1.2;
	f->yend = -1.8;
	f->window = mlx_init(WIDTH, HEIGHT, f->name, false);
	if (!f->window)
	{
		malloc_error();
		exit(1);
	}
	f->img = mlx_new_image(f->window, WIDTH, HEIGHT);
	if (!f->img || (mlx_image_to_window(f->window, f->img, 0, 0) < 0))
	{
		malloc_error();
		exit(1);
	}
}

int32_t	main(int argc, char *argv[])
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc >= 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractal_init(&fractal, argv[1]);
		if (argv[2] && argv[3])
		{
			fractal.julia_r = atod(argv[2]);
			fractal.julia_i = atod(argv[3]);
		}
		render_window(fractal);
		mlx_key_hook(fractal.window, &my_keyhook, &fractal);
		mlx_scroll_hook(fractal.window, &my_scrollhook, &fractal);
		mlx_close_hook(fractal.window, &my_closehook, &fractal);
		mlx_loop(fractal.window);
		mlx_close_window(fractal.window);
		mlx_terminate(fractal.window);
		return (EXIT_SUCCESS);
	}
	else
		ft_error();
	return (0);
}
// TODO:
// sierpinski
// remove not allowed functions
