/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:24:52 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/08/01 20:11:33 by zuzanapiaro      ###   ########.fr       */
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
	z.real = 0.0; //z.x
	z.imaginary = 0.0; //z.y
	// initially c: we map/scale the c constant to the values closer to our set so we can see more clearly - so c(real) is the first x value and c(imaginary is the first y value)
	c.real = scale(x, fractal.xstart, fractal.xend, 0, WIDTH);
	c.imaginary = scale(y, fractal.ystart, fractal.yend, 0, HEIGHT);

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

// ----- HOOKS ------
// listen for keypress events for ESC, arrows, plus and minus
static void my_keyhook(mlx_key_data_t keydata, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 0)
	{
		mlx_close_window(f->window);
		mlx_terminate(f->window);
		exit(1);
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == 0)
	{
		f->xstart += 0.3;
		f->xend += 0.3;
	}
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == 0)
	{
		f->xstart -= 0.3;
		f->xend -= 0.3;
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == 0)
	{
		f->ystart -= 0.3;
		f->yend -= 0.3;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == 0)
	{
		f->ystart += 0.3;
		f->yend += 0.3;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == 0)
	{
		f->ystart += 0.3;
		f->yend += 0.3;
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
static void my_scrollhook(double xdelta, double ydelta, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	printf("xdelta: %f, ydelta: %f\n", xdelta, ydelta);
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

static void my_closehook(void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	mlx_close_window(f->window);
	mlx_terminate(f->window);
	exit(1);
}

int32_t	main(int argc, char *argv[])
{
	t_fractal fractal;


	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10) || argc == 4 && !ft_strncmp(argv[1], "julia", 5))
 	{
 		// store name of fractal received from parameters
		fractal.name = argv[1];
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
//
