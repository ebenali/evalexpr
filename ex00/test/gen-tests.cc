/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen-tests.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:16:40 by ebenali           #+#    #+#             */
/*   Updated: 2019/08/25 19:17:35 by ebenali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <unistd.h>

std::string gen_expr(unsigned long maxnest, unsigned long cur_nest) {
	do {
		std::string retv{};
		if (cur_nest > 0)
			retv += " (";
		do {

			if (cur_nest < maxnest && rand() % 100 < 30) {
				retv += gen_expr(maxnest, cur_nest+1);
			} else
				retv += std::to_string((rand()%2) ? (rand() % 100) : -(rand() % 100));
			retv += (std::string{" "} + ("+-*/%"[rand() % 5]) + " ");
		} while (rand() % 100 <= 10);

		retv += (std::string{" 2 "} + ("+-*/%"[rand() % 5]) + " 42 ");
		do {
			retv += (std::string{" "} + ("+-*/%"[rand() % 5]) + " ");
			if (cur_nest < maxnest && rand() % 100 < 30) {
				retv += gen_expr(maxnest, cur_nest+1); break;
			} else
				retv += std::to_string((rand()%2) ? (rand() % 100): -(rand()%100));
		} while (rand() % 100 < 10);

		if (cur_nest > 0)
			retv += ") ";
		if (system((std::string{"echo "} + "\"" + retv + "\" | bc >/dev/null 2>&1").c_str()) != 0) {
			std::cerr << "randomly generated expression contains div or modulo by zero. retrying...\n";
			continue ;
		} else
			return (retv);
	} while (true);
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	unsigned long ncases = argc > 1 ? std::strtoul(argv[1], NULL, 0) : 10;
	unsigned long maxnest = argc > 2 ? std::strtoul(argv[2], NULL, 0) : 5;
	while (ncases--)
		std::cout << gen_expr(maxnest, 0) << "\n";
}
