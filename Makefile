NAME = gess_nums
BONUS_NAME = checker
SRC = get_next_line/get_next_line.c \
	  get_next_line/get_next_line_utils.c \
	  main.c \

LIB_DIR = ft_printf
LIB_NAME = libftprintf.a
LIB_PATH = $(LIB_DIR)/$(LIB_NAME)
LIB_LINK = -L$(LIB_DIR) -lftprintf

INCLUDES = -I$(LIB_DIR) -Ift_printf/libft
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

SRC_OBJ = $(SRC:.c=.o)

all: $(LIB_PATH) $(NAME)

$(LIB_PATH):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(SRC_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC_OBJ) $(LIB_LINK)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME) $(SRC_OBJ)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re