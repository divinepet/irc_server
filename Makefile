SRCS =	RunServer.cpp Server.cpp
HEADERS = Server.hpp
OBJS = ${SRCS:.cpp=.o}
NAME = server
CFLAGS = -I. -g3 -Wall -Werror

all:		${NAME}

${NAME}:	${OBJS} ${HEADERS}
	clang++ -o ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:		clean
	rm -f ${NAME}

re: fclean all