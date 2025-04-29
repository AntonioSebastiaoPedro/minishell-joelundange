/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:54:49 by llundage          #+#    #+#             */
/*   Updated: 2024/05/20 19:55:10 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*int	main()
{
	ft_putnbr_fd(ft_isprint(45), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isprint(19), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isprint(127), 1);
	ft_putchar_fd('\n', 1);
}*/
