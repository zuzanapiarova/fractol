/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpiarova <zpiarova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:18:14 by zpiarova          #+#    #+#             */
/*   Updated: 2025/05/26 19:41:52 by zpiarova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

// creates array of colors based on stored colorway
// it is given by 5 control points
void	get_colorway_tropic(char **colorway, t_color *colors)
{
    *colorway = "tropic";
    colors[0] = (t_color){0.00, 0, 128, 128};     // Teal
    colors[1] = (t_color){0.14, 0, 200, 120};     // Aqua-green
    colors[2] = (t_color){0.28, 0, 255, 100};     // Bright green
    colors[3] = (t_color){0.42, 128, 255, 50};    // Lime-yellow
    colors[4] = (t_color){0.56, 255, 255, 0};     // Yellow
    colors[5] = (t_color){0.70, 255, 150, 0};     // Tropical orange
    colors[6] = (t_color){0.84, 255, 60, 60};     // Pink-orange
    colors[7] = (t_color){1.00, 255, 0, 127};     // Hot pink
}

void get_colorway_sunset(char **colorway, t_color *colors)
{
    *colorway = "sunset";
    colors[0] = (t_color){0.00, 10, 0, 30};       // Deep twilight
    colors[1] = (t_color){0.14, 100, 0, 60};      // Purple dusk
    colors[2] = (t_color){0.28, 200, 40, 90};     // Crimson
    colors[3] = (t_color){0.42, 255, 100, 50};    // Burnt orange
    colors[4] = (t_color){0.56, 255, 160, 0};     // Amber
    colors[5] = (t_color){0.70, 255, 200, 100};   // Peach
    colors[6] = (t_color){0.84, 255, 230, 180};   // Light beige
    colors[7] = (t_color){1.00, 255, 255, 255};   // White
}

void get_colorway_cosmic(char **colorway, t_color *colors)
{
    *colorway = "cosmic";
    colors[0] = (t_color){0.00, 5, 0, 20};        // Near-black violet
    colors[1] = (t_color){0.12, 30, 0, 60};       // Deep indigo
    colors[2] = (t_color){0.25, 60, 20, 100};     // Dark bluish purple
    colors[3] = (t_color){0.42, 100, 80, 200};    // Muted neon blue
    colors[4] = (t_color){0.58, 180, 60, 180};    // Muted magenta
    colors[5] = (t_color){0.72, 220, 100, 255};   // Bright violet-pink
    colors[6] = (t_color){0.86, 255, 180, 255};   // Soft light pink
    colors[7] = (t_color){1.00, 220, 220, 255};   // Dim starlight (off-white)
}

void get_colorway_oceans(char **colorway, t_color *colors)
{
    *colorway = "oceans";
    colors[0] = (t_color){0.00, 0, 0, 30};        // Deep navy
    colors[1] = (t_color){0.14, 0, 30, 90};       // Dark blue
    colors[2] = (t_color){0.28, 0, 80, 150};      // Ocean blue
    colors[3] = (t_color){0.42, 0, 160, 200};     // Aqua
    colors[4] = (t_color){0.56, 50, 220, 200};    // Soft turquoise
    colors[5] = (t_color){0.70, 150, 255, 255};   // Sky blue
    colors[6] = (t_color){0.84, 200, 255, 255};   // Light sky
    colors[7] = (t_color){1.00, 255, 255, 255};   // White
}

void get_colorway_purple(char **colorway, t_color *colors)
{
    *colorway = "purple";
    colors[0] = (t_color){0.00, 20, 0, 40};        // Deep violet
    colors[1] = (t_color){0.14, 60, 0, 90};        // Purple night
    colors[2] = (t_color){0.28, 100, 30, 150};     // Grape
    colors[3] = (t_color){0.42, 160, 80, 200};     // Violet
    colors[4] = (t_color){0.56, 200, 120, 220};    // Lilac
    colors[5] = (t_color){0.70, 230, 180, 240};    // Soft lavender
    colors[6] = (t_color){0.84, 245, 210, 250};    // Powdered pink-lavender
    colors[7] = (t_color){1.00, 255, 240, 255};    // Pale lavender white
}

void get_colorway_trippy(char **colorway, t_color *colors)
{
    *colorway = "trippy";
    colors[1] = (t_color){0.00, 255, 0, 0};        // Red
    colors[2] = (t_color){0.14, 255, 0, 255};      // Magenta
    colors[3] = (t_color){0.28, 255, 128, 0};      // Neon orange
    colors[4] = (t_color){0.42, 255, 255, 0};      // Yellow
    colors[5] = (t_color){0.56, 0, 255, 0};        // Bright green
    colors[6] = (t_color){0.70, 0, 255, 255};      // Cyan
    colors[7] = (t_color){0.84, 0, 0, 255};        // Blue
    colors[8] = (t_color){1.00, 255, 255, 255};    // White
}

void get_colorway_electric(char **colorway, t_color *colors)
{
    *colorway = "electric";
    colors[0] = (t_color){0.00, 0, 0, 0};          // Pure black
    colors[1] = (t_color){0.14, 0, 30, 0};         // Faint green glow
    colors[2] = (t_color){0.28, 0, 80, 0};         // Dim green
    colors[3] = (t_color){0.42, 30, 200, 30};      // Bright green
    colors[4] = (t_color){0.56, 80, 255, 80};      // Electric lime
    colors[5] = (t_color){0.70, 180, 255, 120};    // Pale green highlight
    colors[6] = (t_color){0.84, 0, 255, 100};      // Greenish cyan
    colors[7] = (t_color){1.00, 0, 0, 0};          // Back to black
}



