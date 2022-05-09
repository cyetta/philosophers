NAME	= philo
BNS_N	=

SRC_N 	= philo.c ft_error.c ft_util.c ft_atoi.c ph_init.c ph_fork.c ph_msg.c\
			ph_mtx_init.c ph_getseteat.c ph_getsetstat.c
SRC_B 	=


DIR_SRC	= ./
DIR_BON	= ./
INCPATH	= ${DIR_SRC} ${DIR_BON}

CC = gcc
RM = rm -f
ifdef DESKTOP_SESSION
CFLAGS = -Wall -Wextra -Werror -pthread
else
CFLAGS = -Wall -Wextra -Werror
endif

SRCS_P	= ${addprefix ${DIR_SRC}, ${SRC_N}}
SRCS_B	= ${addprefix ${DIR_BON}, ${SRC_B}}

OBJ_P	= ${SRCS_P:.c=.o}
OBJ_B	= ${SRCS_B:.c=.o}

DPDS	= ${SRCS_P:.c=.d} ${SRCS_B:.c=.d}

all:	${NAME}

%.o : %.c
	${CC} ${CFLAGS} -MMD -c $< -o $@ -I"${INCPATH}"

include ${wildcard ${DPDS}}

${NAME}: ${OBJ_P}
	${CC} ${CFLAGS} -o $@ ${OBJ_P}

debug:
	${MAKE} CFLAGS="${CFLAGS} -g3" ${NAME}

debug_bonus:
	${MAKE} CFLAGS="${CFLAGS} -g3" SRC_N="${SRC_B}" DIR_SRC="${DIR_BON}" ${NAME}

bonus:
	${MAKE} SRC_N="${SRC_B}" DIR_SRC="${DIR_BON}" ${NAME}

clean:
	${RM} ${OBJ_P} ${OBJ_B} ${DPDS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all bonus clean fclean re debug debug_bonus libft libmlx
