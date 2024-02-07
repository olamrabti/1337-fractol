/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:23 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/07 18:49:27 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void my_mlx_pixel_put(t_mlx *fract_setup, int x, int y, int color)
{
    char *dst;

    dst = fract_setup->img_pxl_ptr + (y * fract_setup->size_line + x * (fract_setup->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void mandelbrot_or_bs(t_mlx *fract_setup)
{
    t_func_var var;

    var.x = 0;
    while (var.x < WIDTH)
    {
        var.y = 0;
        while (var.y < HEIGHT)
        {
            var.ar = 0;
            var.ai = 0;
            var.cr = ft_interpolate(var.x, -2, 1, 0, 800) * fract_setup->zoom + fract_setup->shift_h;
            var.ci = ft_interpolate(var.y, -1.5, 1.5, 0, 800) * fract_setup->zoom + fract_setup->shift_v;
            if (fract_setup->set == 1)
                ft_do_the_math(fract_setup, &var);
            else
                ft_do_bs_math(fract_setup, &var);
        }
        (var.x)++;
    }
}
void draw_julia(t_mlx *fract_setup)
{
    t_func_var var;

    var.x = 0;
    var.cr = fract_setup->julia_cr;
    var.ci = fract_setup->julia_ci;
    while (var.x < WIDTH)
    {
        var.y = 0;
        while (var.y < HEIGHT)
        {
            var.ar = ft_interpolate(var.x, 2, -2, 0, 800) * fract_setup->zoom + fract_setup->shift_h;
            var.ai = ft_interpolate(var.y, -2, 2, 0, 800) * fract_setup->zoom + fract_setup->shift_v;
            ft_do_the_math(fract_setup, &var);
        }
        (var.x)++;
    }
}
void ft_do_the_math(t_mlx *fract_setup, t_func_var *var)
{
    int i;
    double temp;

    i = 0;
    while (i++ <= fract_setup->max_iter)
    {
        temp = var->ar;
        var->ar = var->ar * var->ar - var->ai * var->ai + var->cr;
        var->ai = 2. * temp * var->ai + var->ci;
        if (var->ar * var->ar + var->ai * var->ai >= 4)
        {
            my_mlx_pixel_put(fract_setup, var->x, (var->y)++, abs(GOLDENROD - (fract_setup->max_iter - i) * 1200));
            break;
        }
        if (i == fract_setup->max_iter)
            my_mlx_pixel_put(fract_setup, var->x, (var->y)++, BLACK);
    }
}
void ft_do_bs_math(t_mlx *fract_setup, t_func_var *var)
{
    int i;
    double temp;

    i = 0;
    while (i++ <= fract_setup->max_iter)
    {
        temp = var->ar;
        var->ar = fabs(var->ar * var->ar - var->ai * var->ai + var->cr);
        var->ai = fabs(2. * temp * var->ai + var->ci);
        if (var->ar * var->ar + var->ai * var->ai >= 4)
        {
            my_mlx_pixel_put(fract_setup, var->x, (var->y)++, abs(BLUE - (fract_setup->max_iter - i) * 1000));
            break;
        }
        if (i == fract_setup->max_iter)
            my_mlx_pixel_put(fract_setup, var->x, (var->y)++, BLACK);
    }
}

int main(int ac, char *av[])
{
    t_mlx fract_setup;

    if (!check_params(ac, av, &fract_setup))
    {
        fract_setup.max_iter = MAX_ITER;
        fract_setup.zoom = 1;
        fract_setup.shift_h = 0;
        fract_setup.shift_v = 0;
        if (initialize_mlx(&fract_setup))
            return 1;
        if (fract_setup.set == 1 || fract_setup.set == 3)
            mandelbrot_or_bs(&fract_setup);
        else
            draw_julia(&fract_setup);
        mlx_put_image_to_window(fract_setup.mlx_ptr, fract_setup.win_ptr, fract_setup.image, 0, 0);
        mlx_loop(&fract_setup.mlx_ptr);
        return 0;
    }
    return 1;
}
// cleaning >>>