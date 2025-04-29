/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:14:47 by llundage          #+#    #+#             */
/*   Updated: 2024/05/20 20:14:50 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_zero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_calloc(size_t count, size_t n)
{
	void	*arm;

	if (count && n && count > (UINT_MAX / n))
		return (NULL);
	arm = malloc(count * n);
	if (!arm)
		return (NULL);
	s_zero(arm, count * n);
	return (arm);
}
