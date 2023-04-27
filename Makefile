
READLINE_DIR    = /Users/aahlyel/homebrew/opt/readline

SRC = src/minishell.c src/read_line.c src/getters_setters.c src/complete_line.c src/constructors.c  src/echo.c src/parsing/parse_line.c src/parsing/translater.c src/parsing/spliter.c src/parsing/tokenizer.c src/parsing/heredoc_controll.c src/parsing/spliter_handlers.c src/parsing/not_complete_line_checker.c src/parsing_tools/parsing_tools.c src/parsing_tools/parsing_tools2.c src/parsing_tools/ft_split_char.c src/tokenizer/builtins_token.c src/tokenizer/cmds_token.c src/tokenizer/operators_token.c src/tokenizer/orders_token.c src/tokenizer/pipes_token.c src/tokenizer/redirections_token.c src/tokenizer/variables_token.c src/tokenizer/tokenizer_tools.c 

OBJ =  ${SRC:.c=.o}


OBJ_DIR = obj/
BIN_DIR = bin/
CFLAGS		= -Wall -Wextra -Werror -fsanitize=address
LIBRARIES	= -L ${READLINE_DIR}/lib -lreadline -I includes -I ${READLINE_DIR}/include
INCLUDES	= -I${READLINE_DIR}/include
NAME = minishell

all : ${NAME}

${NAME} : ${OBJ_DIR} ${OBJ}
	make -C lib/libft
	cc ${CFLAGS} ${LIBRARIES} ${OBJ} lib/libft/bin/libft.a -o ${NAME}

${OBJ_DIR} : 
	mkdir -p ${OBJ_DIR} ${BIN_DIR}

obj/%.o : ${SRC} include/minishell.h
	cc ${CFLAGS} ${INCLUDES} -c ${SRC} -o ${OBJ}

clean : 
	make clean -C lib/libft
	rm -rf ${OBJ} ${OBJ_DIR}

fclean : clean
	make fclean -C lib/libft
	rm -rf ${NAME} ${BIN_DIR}

re : fclean all