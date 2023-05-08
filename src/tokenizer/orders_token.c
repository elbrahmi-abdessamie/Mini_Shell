/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orders_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:31:43 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/08 14:12:51 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*get_token_order(char *line)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		has_option;

	i = 0;
	j = 0;
	has_option = 0;
	cmd = NULL;
	if (!*line)
		return (free(line), NULL);
	while (ft_isspace(line[i]))
		i++;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	cmd = get_token_builtins(ft_strdup(line + i), j);
	if (!cmd)
		cmd = get_token_cmd(ft_strdup(line + i), j);
	if (!cmd)
		cmd = invalid_constructor(ft_strdup(line));
		// return (pr_custom_err(ERR_CMD, line, line + i), NULL);
		// cmd = get_token_variable_assignement(ft_strdup(line + i));
	free (line);
	return (cmd);
}