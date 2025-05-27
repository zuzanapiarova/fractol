/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:43:21 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/27 11:04:26 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// clone MLX42: git clone https://github.com/codam-coding-college/MLX42.git

// accepts the start and end y of a thread's section
// for each pixel we perform the mandelbrot set function z = z^2 + c
// and color it dependeing on how many iterations it took for point to escape
// set to fractal->inside color if point didnt escape in less than fractal.iterations
void	set_pixel(int x, int y, t_fractal *f)
{
	t_complex	z;
	t_complex	c;
	int			i;

	z.real = 0;
	z.imaginary = 0;
	c.real = scale(x, f->xstart, f->xend, WIDTH);
	c.imaginary = scale(y, f->ystart, f->yend, HEIGHT);
	if (!ft_strncmp(f->name, "julia\0", 6))
	{
		z.real = (scale(x, f->xstart, f->xend, WIDTH));
		z.imaginary = (scale(y, f->ystart, f->yend, HEIGHT));
		c.real = f->julia_r;
		c.imaginary = f->julia_i;
	}
	i = 0;
	while (i < f->iters)
	{
		z = complex_operation(z, c);
		if (pow(z.real, 2) + pow(z.imaginary, 2) > f->escape_value)
		{
			f->pixels_buffer[y * WIDTH + x] = coloring_algorithm(z, i, f);
			return ;
		}
		i++;
	}
	f->pixels_buffer[y * WIDTH + x] = f->inside;
}

// thread routine - renders the pixels for given number of rows
// iterates through window pixels one by one, each pixel in each row,
// to set its color based on whether it escaped and in how many iteration
// end_row is not rendered, as it is also teh start_row for the next section
void	*render_section(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	
	data = (t_thread_data *)arg;
	y = data->start_row;
	while (y < data->end_row)
	{
		x = 0;
		while (x < WIDTH)
		{
			set_pixel(x, y, data->f);
			x++;
		}
		y++;
	}
	return (NULL);
}

// separates the window into same-size sections of rows 
// and passes each section to rendering function
// the last section has the leftover rows
void render_window(t_fractal *fractal)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;
	int				i;

	i = 0;
	rows_per_thread = HEIGHT / NUM_THREADS;
	while (i < NUM_THREADS)
	{
		thread_data[i].start_row = i * rows_per_thread;
		thread_data[i].end_row = (i + 1) * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_row = HEIGHT;
		thread_data[i].f = fractal;
		pthread_create(&threads[i], NULL, render_section, &thread_data[i]);
		i++;
	}
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(threads[i], NULL);
	draw_image(fractal);
}

// initialize the fractal struct with the initial data
void fractal_init(t_fractal *f, char **argv)
{
	f->name = argv[1];
	if (!ft_strncmp(f->name, "julia\0", 6))
	{
		f->julia_r = atod(argv[2]);
		f->julia_i = atod(argv[3]);
	}
	f->iters = 25;
	f->escape_value = DIVERGENT_VALUE;
	f->colorway = "tropic";
	get_colorway_tropic(&f->colorway, f->colors);
	f->inside = B;
	f->xstart = -2.2;
	f->xend = 0.8;
	f->ystart = 1.2;
	f->yend = -1.8;
	f->pixels_buffer = malloc(WIDTH * HEIGHT * sizeof(uint32_t));
	if (!f->pixels_buffer)
		exit(ft_error("Malloc error for pixels buffer.\n"));
	f->window = mlx_init(WIDTH, HEIGHT, f->name, false);
	if (!f->window)
		clean_exit(f, EXIT_FAILURE, "Error creating window.\n");
	f->img = mlx_new_image(f->window, WIDTH, HEIGHT);
	if (!f->img || (mlx_image_to_window(f->window, f->img, 0, 0) < 0))
		clean_exit(f, EXIT_FAILURE, "Error putting image to window.\n");
}

int32_t main(int argc, char *argv[])
{
	t_fractal fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot\0", 11))
		|| (argc >= 4 && !ft_strncmp(argv[1], "julia\0", 6)
		&& parse_arg(argv[2]) == SUCCESS && parse_arg(argv[3]) == SUCCESS))
		fractal_init(&fractal, argv);
	else 
	{
		write(2, "Fractals available for exploration:\n", 36);
		write(2, "./fractol mandelbrot\n", 21);
		write(2,"./fractol julia real<-1,1> imaginary<-1,1>\n", 43);
		exit(EXIT_FAILURE);
	}
	render_window(&fractal);
	mlx_key_hook(fractal.window, &my_keyhook, &fractal);
	mlx_scroll_hook(fractal.window, &my_scrollhook, &fractal);
	mlx_close_hook(fractal.window, &my_closehook, &fractal);
	mlx_loop(fractal.window);
	mlx_close_window(fractal.window);
	mlx_terminate(fractal.window);
	free(fractal.pixels_buffer);
	return (SUCCESS);
}
