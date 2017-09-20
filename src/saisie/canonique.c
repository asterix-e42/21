/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonique.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 21:59:36 by tdumouli          #+#    #+#             */
/*   Updated: 2017/09/02 17:53:57 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
//#include <term.h>

int		pass_canonique(void)
{
	struct termios term;

	term.c_iflag = ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	term.c_oflag = ~OPOST;
	term.c_lflag = ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	term.c_cflag = ~(CSIZE | PARENB);
	term.c_cflag |= CS8;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}
