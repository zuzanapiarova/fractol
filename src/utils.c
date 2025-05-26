/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuzanapiarova <zuzanapiarova@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:56:45 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/26 11:24:31 by zuzanapiaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (ERROR);
}

// checks if argument is only digits with one dot, possibly starts with 1 minus
int parse_arg(char *argv1)
{
	char *copy;
	int dot;

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
		printf("c: %c", *copy);
			copy++;
	}
	return (SUCCESS);
}

// uint32_t red   = 0xFF0000;
// uint32_t green = 0x00FF00;
// uint32_t blue  = 0x0000FF;
// uint32_t white = 0xFFFFFF;
// int	set_color(t_fractal *f, double re, double im, int iter)
// {
// 	uint32_t color;

// 	double smoothed = Math.Log2(Math.Log2(re * re + im * im) / 2);  // log_2(log_2(|p|))
// 	int colorI = (int)(Math.Sqrt(iter + 10 - smoothed) * gradient.Scale) % colors.Length;
// 	Color color = colors[colorI];
// }

// // access(extract) individual color components using bitwise operations
// int	change_channel()
// {
// 	if (channel == 'r')
// 		uint8_t r = (color >> 16) & 0xFF;
// 	uint8_t g = (color >> 8) & 0xFF;
// 	uint8_t b = color & 0xFF;
// }

// // pack separate chanels back into single int
// uint32_t make_color(uint8_t r, uint8_t g, uint8_t b)
// {
//     return (r << 16) | (g << 8) | b;
// }

#include <stdint.h>
#include <math.h>

uint32_t hsv_to_rgb(float h, float s, float v)
{
    float r, g, b;

    if (s == 0.0f) {
        // Grayscale
        r = g = b = v;
    } else {
        h = fmodf(h, 1.0f); // Keep hue in [0,1)
        h *= 6.0f;          // Hue sector (0 to 6)
        int i = (int)floorf(h);
        float f = h - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));

        switch (i) {
            case 0: r = v; g = t; b = p; break;
            case 1: r = q; g = v; b = p; break;
            case 2: r = p; g = v; b = t; break;
            case 3: r = p; g = q; b = v; break;
            case 4: r = t; g = p; b = v; break;
            case 5: default: r = v; g = p; b = q; break;
        }
    }

    // Convert to 0-255 and pack to 0xRRGGBB
    uint8_t rr = (uint8_t)(r * 255.0f);
    uint8_t gg = (uint8_t)(g * 255.0f);
    uint8_t bb = (uint8_t)(b * 255.0f);

    return (rr << 16) | (gg << 8) | bb;
}

#include <stdint.h>
#include <math.h>

typedef struct {
    double pos; // range [0.0, 1.0]
    uint8_t r, g, b;
} ColorStop;

static const ColorStop color_stops[] = {
    {0.00, 0x00, 0x00, 0xFF}, // Blue
    {0.10, 0x33, 0xCC, 0xFF}, // Light Blue
    {0.35, 0xFF, 0xFF, 0x99}, // Butter
    {0.50, 0xFF, 0xFF, 0x00}, // Yellow
    {0.65, 0xFF, 0x99, 0x00}, // Orange
    {0.78, 0x99, 0x66, 0x33}, // Brown
    {0.90, 0x33, 0x11, 0x00}, // Dark Brown
    {1.00, 0x66, 0x00, 0x66}, // Purple
};

uint32_t interpolate_color(double t)
{
    int i;
    const int num_stops = sizeof(color_stops) / sizeof(color_stops[0]);

    if (t <= color_stops[0].pos)
        return (color_stops[0].r << 16) | (color_stops[0].g << 8) | color_stops[0].b;

    if (t >= color_stops[num_stops - 1].pos)
        return (color_stops[num_stops - 1].r << 16) | (color_stops[num_stops - 1].g << 8) | color_stops[num_stops - 1].b;

    // Find the two stops surrounding t
    for (i = 0; i < num_stops - 1; i++) {
        if (t >= color_stops[i].pos && t <= color_stops[i + 1].pos) {
            double local_t = (t - color_stops[i].pos) / (color_stops[i + 1].pos - color_stops[i].pos);

            uint8_t r = (uint8_t)((1.0 - local_t) * color_stops[i].r + local_t * color_stops[i + 1].r);
            uint8_t g = (uint8_t)((1.0 - local_t) * color_stops[i].g + local_t * color_stops[i + 1].g);
            uint8_t b = (uint8_t)((1.0 - local_t) * color_stops[i].b + local_t * color_stops[i + 1].b);

            return (r << 16) | (g << 8) | b;
        }
    }

    return 0; // Fallback
}



int	set_color(double t, int i, char *color)
{
	(void)i;
	(void)color;
	// Hue shifts as t goes from 0.0 to 1.0
	float hue = fmod(0.95 + 10 * t, 1.0);
	return hsv_to_rgb(hue, 0.6f, 1.0f);
	// int	palette[COLORWAY_SIZE];

	// palette[0] = A1;
	// palette[1] = A2;
	// palette[2] = A3;
	// palette[3] = A5;
	// palette[4] = A6;
	// palette[5] = A7;
	// palette[6] = A8;
	// palette[7] = A9;
	// palette[8] = A0;
	// if (!ft_strncmp(color, "blue", 4))
	// {
	// 	palette[0] = BA;
	// 	palette[1] = BB;
	// 	palette[2] = BC;
	// 	palette[3] = BE;
	// 	palette[4] = BF;
	// 	palette[5] = BG;
	// 	palette[6] = BH;
	// 	palette[7] = BI;
	// 	palette[8] = BJ;
	// }
	// return (palette[i]);
}


