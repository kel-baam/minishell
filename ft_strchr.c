/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 23:17:54 by kel-baam          #+#    #+#             */
/*   Updated: 2022/10/24 17:10:56 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "mini.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(&s[i]));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(&s[i]));
	return (NULL);
}
