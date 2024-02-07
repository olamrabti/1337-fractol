/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olamrabt <olamrabt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:25:52 by olamrabt          #+#    #+#             */
/*   Updated: 2024/02/07 14:39:33 by olamrabt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double ft_atoi(const char *str, int *i, int *sign)
{
    unsigned long long num;

    num = 0;
    if (!str)
        return (-3);
    while (str[*i] && (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)))
        (*i)++;
    if (str[*i] && (str[*i] == '-' || str[*i] == '+'))
    {
        if (str[(*i)++] == '-')
            *sign = -1;
    }
    while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
        num = num * 10 + str[(*i)++] - 48;
    return (num);
}

double ft_atof(char *str)
{
    t_atof atof;
    int i;

    i = 0;
    atof.x = 1;
    atof.sign = 1;
    atof.dnum = ft_atoi(str, &i, &atof.sign);
    if (atof.dnum > 2)
        return -4;
    if (!str[i])
        return atof.sign * atof.dnum;
    if (str[i++] != '.' || !(str[i] >= '0' && str[i] <= '9'))
        return -5;
    atof.j = i;
    atof.fnum = ft_atoi(str, &i, &atof.x);
    if (atof.fnum < 0)
        return -6;
    atof.x = 1;
    while (atof.j++ < i)
        atof.x *= 10;
    if (str[i] || (atof.dnum + atof.fnum / atof.x) > 2 || atof.x > 100000)
        return -7;
    return atof.sign * (atof.dnum + atof.fnum / atof.x);
}
