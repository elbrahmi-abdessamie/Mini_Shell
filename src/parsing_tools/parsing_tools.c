/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:20:43 by aahlyel           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/06 19:40:52 by aelbrahm         ###   ########.fr       */
=======
/*   Updated: 2023/05/06 19:36:49 by aahlyel          ###   ########.fr       */
>>>>>>> 4a2f53b42a5b4ef4ba82793c0184b512c7d858e9
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

int	ft_chrpos(char *line,  char c)
{
	int	i = 0;
	
	if (!line)
		return (-1);
	while (line[i] && line[i] != c)
		i++;
	if (line[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	return (free(s1), free(s2), str);
}

