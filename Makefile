NAME = minishell

option = -Iincludes

cc = gcc #-Wall -Werror -Wextra

files = src/*.c

src = $(wildcard src/*.c)

mkdir = mkdir -p

OBJDIR = obj

obj = $(addprefix $(OBJDIR)/,$(addsuffix .o, $(basename $(notdir $(src)))))

all = $(NAME)

all: $(obj)
	@$(cc) -o $(NAME) $(option) $^ libft/libft.a 

$(OBJDIR)/%.o:  src/%.c
	@mkdir -p $(OBJDIR)
	$(cc) $(option) -O3 -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean shot
	make fclean -C libft
	rm -rf $(NAME)

re: fclean
	make all
