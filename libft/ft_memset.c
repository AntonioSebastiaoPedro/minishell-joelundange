/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:15:31 by llundage          #+#    #+#             */
/*   Updated: 2024/05/20 20:15:34 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*string;

	string = (char *)s;
	i = 0;
	while (i < n)
	{
		string[i] = c;
		i++;
	}
	return (s);
}

/*int main()
{
	char	str[] = "Ola bom dia";
	char	c = 'u';
	ft_putstr_fd(ft_memset(str, c, 12), 1);
	ft_putchar_fd('\n', 1);
}*/
