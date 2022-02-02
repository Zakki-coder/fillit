NAME = test_ft_bonuses.c

SRC =	./../../*.c						\
		./../../libft.h

CFLAG = -g -Wall -Wextra -Werror -I./../Unity -I./../../

UNITY = ./../Unity/unity.c			\
		./../Unity/unity.h			\
		./../Unity/unity_internals.h	

all: 
	@gcc $(NAME) $(SRC) $(UNITY) $(CFLAG)
	@./a.out
clean:
	@rm a.out 

re: clean all
