NAME	= philo_bonus
BNS_N	=

SRC_N 	= ft_atoi_bonus.c ft_error_bonus.c ft_util_bonus.c philo_bonus.c init_ph_bonus.c init_smp_bonus.c ph_prc_bonus.c \
			ph_msg_bonus.c ph_getset_bonus.c
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
	${MAKE} CFLAGS="${CFLAGS} -g3 " ${NAME}

debug_bonus:
	${MAKE} CFLAGS="${CFLAGS} -g3" SRC_N="${SRC_B}" DIR_SRC="${DIR_BON}" ${NAME}

bonus:
	${MAKE} SRC_N="${SRC_B}" DIR_SRC="${DIR_BON}" ${NAME}

clean:
	${RM} ${OBJ_P} ${OBJ_B} ${DPDS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all bonus clean fclean re debug debug_bonus
