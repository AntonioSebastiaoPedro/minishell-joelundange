/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:47:36 by llundage          #+#    #+#             */
/*   Updated: 2024/05/20 19:47:40 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subst;
	size_t	size;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	subst = (char *)malloc(sizeof(char) * (len + 1));
	if (!subst)
		return (NULL);
	ft_strlcpy(subst, s + start, len + 1);
	return (subst);
}

/*int	main()
{
	char	str[] = "Mais um pouco e era Sub-Zero!";
	ft_putendl_fd(ft_substr(str, 20, 30), 1);
}*/
