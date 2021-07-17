NAME = minishell

option = -Iincludes

cc = gcc  #-Wall -Werror -Wextra

files = src/*.c

src = $(wildcard src/*.c)

mkdir = mkdir -p

OBJDIR = obj

obj = $(addprefix $(OBJDIR)/,$(addsuffix .o, $(basename $(notdir $(src)))))

all: $(NAME)

$(NAME): $(obj)
	@$(cc) -o $(NAME) $(option) $^ libft/libft.a -lreadline

$(OBJDIR)/%.o:  src/%.c
	@mkdir -p $(OBJDIR)
	$(cc) $(option) -O3 -c $< -o $@ -lreadline

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make all
