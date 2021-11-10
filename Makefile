SRCS =	$(wildcard */*.cpp)
HEADERS = $(wildcard */*.hpp)
OBJS = ${SRCS:.cpp=.o}
NAME = ircserv
CFLAGS = -I. -g3 -Wall -Werror

all:		${NAME}

${NAME}:	${OBJS} ${HEADERS}
	clang++ -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re: fclean all