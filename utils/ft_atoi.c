/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:55:42 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/05/06 14:52:57 by kjarmoum         ###   ########.fr       */
=======
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:47:32 by kel-baam          #+#    #+#             */
/*   Updated: 2022/10/24 17:09:09 by kel-baam         ###   ########.fr       */
>>>>>>> b72f58e7d321bb09cb02f23b2a6133404fb18d90
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int				i;
<<<<<<< HEAD
	unsigned long	result;
	int				sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
=======
	int				sign;
	unsigned long	result;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
>>>>>>> b72f58e7d321bb09cb02f23b2a6133404fb18d90
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
<<<<<<< HEAD
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = str[i++] + result * 10 - '0';
		if (result >= 9223372036854775807 && sign == 1)
			return (-1);
		if (result > 9223372036854775807 && sign == -1)
			return (0);
=======
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
>>>>>>> b72f58e7d321bb09cb02f23b2a6133404fb18d90
	}
	return (result * sign);
}
