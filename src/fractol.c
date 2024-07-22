/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:24:52 by zuzanapiaro       #+#    #+#             */
/*   Updated: 2024/07/21 20:17:44 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
// CALL THE PROGRAM: ./fractol(=arg[0]) mandelbrot(=arg[1])        ==>  argc is 2

/*
cmake [options] <path-to-source>
cmake [options] <path-to-existing-build>
cmake [options] -S <path-to-source> -B <path-to-build>

Specify a source directory to (re-)generate a build system for it in the
current working directory.  Specify an existing build directory to
re-generate its build system.
 */

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// ----- HOOKS ------

// Print the window width and height.
static void my_keyhook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_ESCAPE )
		exit(1);
}

void printsquare(mlx_image_t* img )
{
	int i =  90;
	int y = 240;
	int x = 90;
	while (i <=  y)
	{
		mlx_put_pixel(img, i , x , 0x33cc33FF);
		i++;
	}
}

int32_t	main(void)
{
	// MLX allows you to define its core behaviour before startup.
	//mlx_set_setting(MLX_MAXIMIZED, true);

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

 	printsquare(img);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// void fractal_render(t_fractal fractal)
// {

// }

// int main(int argc, char **argv)
// {
//  	t_fractal fractal;
// 	t_img img;

// 	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10) || argc == 4 && argv[1] == "julia")
// 	{
// 		// store name of fractal received from parameters
// 		fractal.name = argv[1];
// 		//1. start x server connection
// 		fractal.xconnection = mlx_init(); //create new connection to X window server
// 		if (fractal.xconnection == NULL)
// 			malloc_error();
// 		//2. create new window in that connection
// 		fractal.xwindow = mlx_create_new_window(fractal.xconnection, WIDTH, HEIGHT, fractal.name); //create new window
// 		if (fractal.xwindow == NULL)
// 		{
// 			mlx_destroy_display(fractal.xwindow);
// 			free(fractal.xconnection);
// 			malloc_error();
// 		}
// 		//3. create image that fills the entire window
// 		img.img = mlx_new_image(fractal.xwindow, WIDTH, HEIGHT);
// 		img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length); //WHAT IS THIS DATA ADDRESS RETURNING AND WHAT IS IT?
// 		int offset = (HEIGHT * img.line_length + WIDTH * (img.bpp / 8));

// 		//4. actual rendering of the fractal
// 		fractal_render(fractal);

// 		//5. start event loop
// 		mlx_loop(fractal.xconnection);
// 		//6. at end destroy the window and free the connection to handle memory leaks - as they both malloc memory
// 		mlx_destroy_display(fractal.xwindow);
// 		free(fractal.xwindow);
// 	}
// 	else
// 	{

// 	}
// }


// ------ TODO ------
// handle these events - create functions and add hooks to them:
// 1. + and - increase/decrease number of iterations

// 2. left/right/up/down move the screen to the left/right/up/down by 0.1 point

// 3. roll mouse wheel - zoom in/out
