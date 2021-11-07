SRCS1 =	RunServer.cpp Server.cpp
SRCS2 =	Client.cpp
SRCS = ${SRCS1} + ${SRCS2}

OBJS1 = ${SRCS1:.cpp=.o}
OBJS2 = ${SRCS2:.cpp=.o}
OBJS = ${OBJS1} + ${OBJS2}

NAME1 = server
NAME2 = client

CFLAGS = -I. -g3 -Wall -Werror

CC = g++
RM = rm -f


all:
		make server
		make client

server:		${OBJS1}
		${CC} -o ${NAME1} ${OBJS1}


client:		${OBJS2}
		${CC} -o ${NAME2} ${OBJS2}


clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME1}
		${RM} ${NAME2}

re:		fclean all
