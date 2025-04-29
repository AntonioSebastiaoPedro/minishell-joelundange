/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llundage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:58:14 by llundage          #+#    #+#             */
/*   Updated: 2024/05/20 19:58:23 by llundage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		return (0);
	}
	new -> content = content;
	new -> next = NULL;
	return (new);
}

/*int	main(void)
{
	char	*str;

	t_list	*elem;
	str = (char *)malloc(6*sizeof(char));
	str = "Hello";
	elem = ft_lstnew((void *)str);
	printf("%s\n", (char *)elem->content);
	free(new->content);
}*/
