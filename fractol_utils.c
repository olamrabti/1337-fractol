/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:03:26 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/07 18:25:15 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
    if (!s1 || !s2)
        return -1;
    while (n > 0 && (*s1 || *s2))
    {
        if (*s1 != *s2)
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
        n--;
    }
    return (0);
}

int initialize_mlx(t_mlx *fract_setup)
{
    fract_setup->mlx_ptr = mlx_init();
    if (!fract_setup->mlx_ptr)
        return 1;
    fract_setup->win_ptr = mlx_new_window(fract_setup->mlx_ptr, WIDTH, HEIGHT, fract_setup->title);
    if (!fract_setup->win_ptr)
        return 1;
    fract_setup->image = mlx_new_image(fract_setup->mlx_ptr, WIDTH, HEIGHT);
    if (!fract_setup->image)
        return 1;
    fract_setup->img_pxl_ptr = mlx_get_data_addr(fract_setup->image, &fract_setup->bits_per_pixel, &fract_setup->size_line, &fract_setup->endian);
    if (!fract_setup->img_pxl_ptr)
        return 1;
    mlx_mouse_hook(fract_setup->win_ptr, &mouse_event_handler, fract_setup);
    mlx_key_hook(fract_setup->win_ptr, &key_event_handler, fract_setup);
    mlx_hook(fract_setup->win_ptr, 17, 0, &handle_window_close, fract_setup);
    return 0;
}

int mouse_event_handler(int move, int x, int y, t_mlx *fract_setup)
{
    (void)x;
    (void)y;

    if (move == 4)
    {
        fract_setup->zoom *= 1.1;
        if (fract_setup->max_iter > 50)
            fract_setup->max_iter -= 1;
    }
    if (move == 5)
    {
        fract_setup->zoom *= 0.9;
        fract_setup->max_iter += 1;
    }
    if (fract_setup->set == 1 || fract_setup->set == 3)
        mandelbrot_or_bs(fract_setup);
    else if (fract_setup->set == 2)
        draw_julia(fract_setup);
    mlx_put_image_to_window(fract_setup->mlx_ptr, fract_setup->win_ptr, fract_setup->image, 0, 0);
    return (0);
}

int key_event_handler(int move, t_mlx *fract_setup)
{
    if (move == 126)
        fract_setup->shift_v += fract_setup->zoom;
    if (move == 125)
        fract_setup->shift_v -= fract_setup->zoom;
    if (move == 124)
        fract_setup->shift_h += fract_setup->zoom;
    if (move == 123)
        fract_setup->shift_h -= fract_setup->zoom;
    if (move == 24)
        fract_setup->max_iter += 2;
    if (move == 27)
        fract_setup->max_iter -= 2;
    if (move == 53)
        exit(0);
    if (fract_setup->set == 1 || fract_setup->set == 3)
        mandelbrot_or_bs(fract_setup);
    else if (fract_setup->set == 2)
        draw_julia(fract_setup);
    mlx_put_image_to_window(fract_setup->mlx_ptr, fract_setup->win_ptr, fract_setup->image, 0, 0);
    return (0);
}

int handle_window_close()
{
    exit(0);
    return 0;
}

double ft_interpolate(double coord, double new_min, double new_max, double old_min, double old_max)
{
    return (new_max - new_min) * (coord - old_min) / (old_max - old_min) + new_min;
}

int check_params(int ac, char *av[], t_mlx *fract_setup)
{
    if ( ac == 2 && !ft_strncmp(av[1], "m", 1))
    {
        fract_setup->set = 1;
        fract_setup->title = "Mandelbrot";
        return 0;
    }
    else if (ac == 2 && !ft_strncmp(av[1], "b", 1))
    {
        fract_setup->set = 3;
        fract_setup->title = "Burning Ship";
        return 0;
    }
    else if (ac == 4 && !ft_strncmp(av[1], "j", 1))
    {
        fract_setup->set = 2;
        fract_setup->title = "Julia";
        if (ft_atof(av[2]) < -2 || ft_atof(av[3]) < -2)
            return ft_throw_error(2), 2;
        fract_setup->julia_cr = ft_atof(av[2]);
        fract_setup->julia_ci = ft_atof(av[3]);
        return 0;
    }
    return ft_throw_error(1), 1;
}

void ft_throw_error(int err)
{
    if (err == 2)
    {
        write(1, "For julia : <./fractol j num1 num2 > \n\n", 39);
        write(1, "Also! num1 & num2 must be between -2 & 2\n", 41);
        write(1, "only 4 digits after ex: 0.1234\n", 31);
    }
    else
    {
        write(1, "Error : Invalid parameters!\n\n try :\n", 36);
        write(1, "For mandelbrot : <./fractol m > \n", 33);
        write(1, "For Burning Ship : <./fractol b > \n", 35);
        write(1, "For julia : <./fractol j num1 num2 > \n", 38);
    }
}

// void ft_clean_mlx(t_mlx *fract_setup)
// {
//     (void)fract_setup;
// mlx_destroy_image(fract_setup->mlx_ptr, fract_setup->image);
//     // mlx_destroy_window(fract_setup->mlx_ptr, fract_setup->win_ptr);
//     exit(0);
//     // free(fract_setup->mlx_ptr);
// }
