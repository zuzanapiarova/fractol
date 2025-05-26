NAME	:= fractol
CFLAGS	:=  -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX	:= ./MLX42

SRC_DIR := ./src
MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
MLX42_BUILD = ./MLX42/build
HEADERS	:= -I ./include -I $(LIBMLX)/include/MLX42
# LINUX
#LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
# MAC
# LIBS	:= $()/build/libmlx42.a -ldl -lglfw -pthread -lm

ifeq ($(shell uname), Darwin)
LIBS := $(MLX42_BUILD)/libmlx42.a -L/usr/local/opt -lglfw -framework Cocoa -framework OpenGL -framework IOKit
else
LIBS := $(MLX42_BUILD)/libmlx42.a -ldl -lglfw -pthread -lm
endif

SRCS	:=	$(SRC_DIR)/fractol.c \
 			$(SRC_DIR)/math.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/string_utils.c \
			$(SRC_DIR)/hooks.c \
			$(SRC_DIR)/colorways.c

OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

check_mlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "MLX42 not found, cloning from GitHub..."; \
		git clone $(MLX42_REPO) $(LIBMLX); \
	elif [ -z "$(shell ls $(LIBMLX))" ]; then \
		echo "MLX42 directory is empty, cloning from GitHub..."; \
		rm -rf $(LIBMLX); \
		git clone $(MLX42_REPO) $(LIBMLX); \
	else \
		echo "MLX42 exists, pulling latest updates..."; \
		cd $(LIBMLX) && git pull; \
	fi

libmlx: check_mlx
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
