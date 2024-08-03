/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:24:52 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/03 17:29:59 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
// CALL THE PROGRAM: ./fractol(=arg[0]) mandelbrot(=arg[1])   ==>  argc is 2

// we are basically just setting color to each pixel based on how many iterations it takes for point with that coordinates to escape to infinity
// points that are inside the mandelbrot set are black - never escape, points that are outside based on their color we can tell how many iterations it takes for them to escape

// Exit the program as failure
static void ft_error(void)
{
	printf("Fractals available for exploration: Mandelbrot, Julia, Sierpinski. Please specify the name as argument to the program. Exiting now.");
	printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// for each pixel we call this function that checks if the mandelbrot function used on that pixel escapes in given amount of iterations
void set_pixel(int x, int y, t_fractal fractal) // ERROR: WE ARE NOT USING X AND Y PARAMETERS PASSED
{
	// z = z^2 + c; - both z and  are complex numbers - both have real and imaginary part
	// real value is on x axis, imaginary is on y axis
	t_complex z;
	t_complex c;
	int i;
	int color;

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

	// now we move to iterations and apply the complex function to our point over and over until we reach max iterations or it escapes
	i = 0;
	// we perform the complex function for as many iterations as defined - the more iterations the more defined the image is
	// we iterate until the number of iterations is done or until the point escapes
	while(i < fractal.iterations)
	{
		z = complex_operation(z, c);
		// after each function run we check if the value is not escaped - for the condition we use vectors - real(x) and imaginary(y) parts form odvesny, prepona je ich vektor
		// all the vectors with prepona = 2 are definitelly escaped - pythagorean theorem compares the odvesny squared to prepona squared which is 4
		if (pow(z.real, 2) + pow(z.imaginary, 2) > fractal.escape_value)
		{
			color = scale(i, 0, 0xFF00FF, 0, fractal.iterations);
			mlx_put_pixel(fractal.img, x, y, color);
			return;
		}
		i++;
	}
	mlx_put_pixel(fractal.img, x, y, 0xFFFFFFFF);
}

// iterates through window pixels one by one, each pixel in each row, to set its color based on whether it escaped and in how many iteration
void render_window(t_fractal fractal)
{
	int x;
	int y;

	y = -1;
	while(++y < HEIGHT)
	{
		x = -1;
		while(++x < WIDTH)
			set_pixel(x, y, fractal);
	}
}

int32_t	main(int argc, char *argv[])
{
	t_fractal fractal;

	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10) || argc >= 4 && !ft_strncmp(argv[1], "julia", 5))
 	{
 		// get info from arguments and store it properly
		fractal.name = argv[1];
		if (argv[2] && argv[3])
		{
			fractal.julia_r = atod(argv[2]);
			fractal.julia_i = atod(argv[3]);
		}
		fractal.iterations = 10;
		fractal.escape_value = 4;
		fractal.xstart = -2.2;
		fractal.xend = 0.8;
		fractal.ystart = 1.2;
		fractal.yend = -1.8;
		fractal.window = mlx_init(WIDTH, HEIGHT, fractal.name, true);
		if (!fractal.window)
			malloc_error();
// 		//3. create image that fills the entire window
		fractal.img = mlx_new_image(fractal.window, WIDTH, HEIGHT);
		if (!fractal.img || (mlx_image_to_window(fractal.window, fractal.img, 0, 0) < 0))
			malloc_error();
//		//4. actual rendering of the fractal
		render_window(fractal);
//		// 5. Register hooks and pass window as optional param and which function should be called
		// NOTE: Do this before calling mlx_loop!
		mlx_key_hook(fractal.window, &my_keyhook, &fractal);
		mlx_scroll_hook(fractal.window, &my_scrollhook, &fractal);
		mlx_close_hook(fractal.window, &my_closehook, &fractal);
// 		//6. start event loop
		mlx_loop(fractal.window);
// 		//7. at end destroy the window and free the connection to handle memory leaks - as they both malloc memory
		mlx_terminate(fractal.window);
		return (EXIT_SUCCESS);
	}
	else
	{
		// print error messsage
		ft_error();
	}
}

// TODO:
// julia
// sierpinski
// handle resizing the window
// click and drag
// zoom follows mouse position
//
