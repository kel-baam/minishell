/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:57:07 by kel-baam          #+#    #+#             */
/*   Updated: 2023/06/04 18:55:40 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	prompt(int sig)
{
	// g_data.status_code = 1;
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
<<<<<<< HEAD
=======
	// g_data.status_code = 1;
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
>>>>>>> cc7ce58ed5b723f6b4cf49d4ec06c0386dd55df0
}

void	signals_for_parent(void)
{
<<<<<<< HEAD
	// tcgetattr(STDIN_FILENO, &(g_data.newTerm));
	// g_data.oldTerm = g_data.newTerm;
	// g_data.newTerm.c_lflag &= ~ECHOCTL;
	// // ctl C 2
	// signal(SIGINT, prompt);
	// // ctl / 3
	// signal(SIGQUIT, SIG_IGN);
=======
	tcgetattr(STDIN_FILENO, &(g_data.new_term));
	g_data.old_term = g_data.new_term;
	g_data.new_term.c_lflag &= ~ECHOCTL;
	signal(SIGINT, prompt);
	signal(SIGQUIT, SIG_IGN);
>>>>>>> cc7ce58ed5b723f6b4cf49d4ec06c0386dd55df0
}

void	signals_for_child(void)
{
<<<<<<< HEAD
	// g_data.newTerm.c_lflag |= ECHOCTL;
	// tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.newTerm));
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
=======
	g_data.new_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(g_data.new_term));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
>>>>>>> cc7ce58ed5b723f6b4cf49d4ec06c0386dd55df0
}
