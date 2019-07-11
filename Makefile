CC=gcc
CFLAGS=-Wall -Wextra -Werror
FRAMEWORKS=-framework OpenGL -framework AppKit
RM=rm -rf
OBJS=main.o input.o input_handlers.o input_handle_loop.o transform.o colors.o
NAME=fractol
LIBFT=libft
LIBMLX=minilibx_macos
LIBRENDERING=rendering

vpath libft.a $(LIBFT)
vpath libmlx.a $(LIBMLX)
vpath librendering.a $(LIBRENDERING)

$(NAME): $(OBJS) -lft -lrendering -lmlx
	$(CC) $(OBJS) -L $(LIBMLX) -lmlx -L $(LIBFT) -lft -L $(LIBRENDERING) -lrendering $(FRAMEWORKS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT) clean
	make -C $(LIBRENDERING) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean
	make -C $(LIBMLX) clean
	make -C $(LIBRENDERING) fclean

re: fclean all

$(LIBMLX)/libmlx.a:
	make -C $(LIBMLX)

$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(LIBRENDERING)/librendering.a:
	make -C $(LIBRENDERING)

input.o: input.h input_handlers.h -lmlx
input_handle_loop.o: input.h
main.o: input.h complex.h -lmlx
transform.o: complex.h -lft
