////////////////////////////////////////////////////////////////////////////////////////
KEYPRESS

/**
 * Callback function used to handle key presses.
 *
 * @param[in] keydata The callback data, contains info on key, action, ...
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param);


/**
 * This function sets the key callback, which is called when a key is pressed
 * on the keyboard. Useful for single keypress detection.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The keypress callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param);

// HOW TO PROPERLY CALL FUNCTION THAT LISTENS FOR KEY PRESSES AND DOES SPECIFIED ACTION - AND HOW TO PROPERLY PASS PARAMETERS IN THIS FUNC
mlx_key_hook(fractal.window, &my_keyhook, &fractal);

static void my_keyhook(mlx_key_data_t keydata, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	if (keydata.key == MLX_KEY_ESCAPE )
		exit(1);
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		f->xstart += 0.3;
		f->xend += 0.3;
		printf("start: %f, end: %f\n", f->xstart, f->xend);
	}
	render_window(*f);
}

////////////////////////////////////////////////////////////////////////////////////////
ZOOMING - SCROLLING

/**
 * Callback function used to handle scrolling.
 *
 * @param[in] xdelta The mouse x delta.
 * @param[in] ydelta The mouse y delta.
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);
/**
 * This function sets the scroll callback, which is called when a scrolling
 * device is used, such as a mouse wheel.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The scroll wheel callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);


mlx_scroll_hook(fractal.window, &my_scrollhook, &fractal);

static void my_scrollhook(double xdelta, double ydelta, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	if (ydelta > 0)
		puts("Up!");
	else if (ydelta < 0)
		puts("Down!");
	if (xdelta < 0)
		puts("Sliiiide to the left!");
	else if (xdelta > 0)
		puts("Sliiiide to the right!");
	render_window(*f);
}

////////////////////////////////////////////////////////////////////////////////////////
CLOSING
/**
 * This function sets the close callback, which is called in attempt to close
 * the window device such as a close window widget used in the window bar.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The close callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param);

/**
 * Callback function used to handle window closing which is called when
 * the user attempts to close the window, for example by clicking the
 * close widget in the title bar.
 *
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_closefunc)(void* param);


/**
 * Notifies MLX that it should stop rendering and exit the main loop.
 * This is not the same as terminate, this simply tells MLX to close the window.
 *
 * @param[in] mlx The MLX instance handle.
 */
void mlx_close_window(mlx_t* mlx);


/**
 * Terminates MLX and cleans up any of its used resources.
 * Using any functions that require mlx afterwards will
 * be considered undefined behaviour, beware of segfaults.
 *
 * @param[in] mlx The MLX instance handle.
 */
void mlx_terminate(mlx_t* mlx);

mlx_close_hook(fractal.window, &my_close, &fractal);

static void my_close(double xdelta, double ydelta, void *fractal)
{
	t_fractal *f = (t_fractal *)fractal;

	mlx_close_window(f->window);
	mlx_terminate(f->window);
	exit(1);
}

////////////////////////////////////////////////////////////////////////////////////////
MOUSE KEYS

/**
 * The mouse button keycodes.
 * @param LEFT The left mouse button.
 * @param RIGHT The right mouse button.
 * @param MIDDLE The middle mouse button, aka the Scrollwheel.
 */
typedef enum mouse_key
{
	MLX_MOUSE_BUTTON_LEFT	= 0,
	MLX_MOUSE_BUTTON_RIGHT	= 1,
	MLX_MOUSE_BUTTON_MIDDLE	= 2,
}	mouse_key_t;

/**
 * Callback function used to handle mouse actions.
 *
 * @param[in] button The mouse button/key pressed.
 * @param[in] action The mouse action that took place.
 * @param[in] mods The modifier keys pressed together with the mouse key.
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_mousefunc)(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

/**
 * Callback function used to handle raw mouse movement.
 *
 * @param[in] xpos The mouse x position.
 * @param[in] ypos The mouse y position.
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);

/**
 * Checks whether a mouse button is pressed or not.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] key A specific mouse key. e.g MLX_MOUSE_BUTTON_0
 * @returns True or false if the mouse key is down or not.
 */
bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key);

/**
 * This function sets the mouse callback, which is called when a mouse
 * does any sort of action such as pressing a key.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The mouse callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param);

/**
 * This function sets the cursor callback, which is called when the
 * mouse position changes. Position is relative to the window.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The cursor callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param);
