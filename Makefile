SRCS1 =	RunServer.cpp Server.cpp Helper.cpp DataCenter.cpp

SRCS2 =	Client.cpp Helper.cpp

OBJS1 = ${SRCS1:.cpp=.o}
OBJS2 = ${SRCS2:.cpp=.o}

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
		${RM} ${OBJS} *~ #*#

fclean:		clean
		${RM} ${NAME}

re:		fclean all
