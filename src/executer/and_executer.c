/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_executer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahlyel <aahlyel@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:06:06 by aahlyel           #+#    #+#             */
/*   Updated: 2023/05/11 01:21:30 by aahlyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	and_executer(t_cmd *cmd, int infile, int outfile)
{
	int	ret;
	
	ret = and_part_executer(((t_and *)cmd)->left, infile, outfile);
	if (ret)
		ret = and_part_executer(((t_and *)cmd)->right, infile, outfile);
	return (ret);
}

int	and_part_executer(t_cmd *cmd, int infile, int outfile)
{
	int	ret;

	if (cmd->type == REDIR)
		ret = redirect_executer(cmd, infile, outfile);
	else if (cmd->type == EXEC)
		ret = cmd_executer(cmd, infile, outfile);
	else if (cmd->type == BUILTIN)
		ret = builtin_executer(cmd, infile, outfile);
	else if (cmd->type == AND)
		ret = and_executer(cmd, infile, outfile);
	else if (cmd->type == OR)
		ret = or_executer(cmd, infile, outfile);
	else if (cmd->type == PIPE)
		ret = pipe_executer(cmd, infile, outfile);
	return (ret);
}