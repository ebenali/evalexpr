# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebenali <ebenali@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/19 10:32:04 by ebenali           #+#    #+#              #
#    Updated: 2019/08/25 17:34:03 by ebenali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGETS=EvalExpr
DEFTGT=$(firstword $(TARGETS))
BUILD_TYPE=REL				# Build types a-la cmake, REL for release

EvalExpr_OUT=eval_expr
EvalExpr_SRCDIR=.
EvalExpr_INCDIR=.
EvalExpr_SRCS=main.c libc_stdio.c libc_string.c libc_vsnprintf.c libc_printf.c\
	  libc_numeric.c libc_ctype.c libc_string2.c lexer.c lexer_lex.c
EvalExpr_LIBS=
EvalExpr_CFLAGS=-DALLOW_MALLOC

# compute CFLAGS
CFLAGS+= $(EvalExpr_CFLAGS)
ifeq ($(firstword $(BUILD_TYPE)),  DBG)
CFLAGS+= -g -ggdb3 -Wall -Wextra -pedantic -fstack-protector-strong \
	 -fsanitize=undefined -fsanitize=address
LDFLAGS+=
endif
ifeq ($(firstword $(BUILD_TYPE)), REL)
CFLAGS+= -Wall -Wextra -pedantic -Werror -O3 -flto -msse4 -mavx
LDFLAGS+= -flto
endif

# target rules
default: $(DEFTGT)

EvalExpr: $(abspath $(EvalExpr_SRCDIR))/EvalExpr_depends.mk $(EvalExpr_OUT)

$(EvalExpr_OUT): $(patsubst %.c,%.o,$(abspath \
	$(patsubst %,$(EvalExpr_SRCDIR)/%,$(EvalExpr_SRCS))))
	$(CC) $(CFLAGS) -I$(abspath $(EvalExpr_INCDIR)) \
		$+ -o $@ $(EvalExpr_LIBS) $(LDFLAGS)

.PHONY: EvalExpr_clean clean fclean re

EvalExpr_clean:
	-$(RM) $(patsubst %.c,%.o,$(EvalExpr_SRCS))
	-$(RM) $(abspath $(EvalExpr_SRCDIR))/EvalExpr_depends.mk

EvalExpr_fclean:
	-$(RM) $(EvalExpr_OUT)

$(abspath $(EvalExpr_SRCDIR))/EvalExpr_depends.mk: $(abspath $(patsubst %,$(EvalExpr_SRCDIR)/%,$(EvalExpr_SRCS)))
	-$(CC) $(CFLAGS) -MM $+ >$@
	-touch $@

clean: $(DEFTGT)_clean

fclean: clean $(DEFTGT)_fclean
	-$(RM) $($(DEFTGT)_OUT)

re: fclean
	@# invoke make sub-process to properly regenerate depends.mk
	exec make $(DEFTGT)

all: $(TARGETS)

norm: EvalExpr_norm

EvalExpr_norm: $(abspath $(EvalExpr_SRCDIR))/EvalExpr_depends.mk
	-norminette $(do_op_SRCS) `awk '( for(i=1; i<NF; ++i) if ($$i ~ /^.*\.h$$/)\
	   	printf("%s ", $$i); )' <EvalExpr_depends.mk`

include $(abspath $($(DEFTGT)_SRCDIR))/$(DEFTGT)_depends.mk
