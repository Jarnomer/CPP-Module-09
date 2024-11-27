NAME        := PmergeMe
BUILDLOG    := build.log
SOURCEDIR   := sources
BUILDDIR    := build

NUMCOUNT	:= 10

RM          := rm -rf
SCREENCLEAR := printf "\033c"

CC          := c++
CFLAGS      := -Wall -Werror -Wextra
CPPFLAGS    := -c -MMD -MP
MAKEFLAGS   += --no-print-directory -j4

SOURCES := main \
		   PmergeMe

SOURCES := $(addsuffix .cpp, $(SOURCES))
OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.cpp=.o))
INCS := $(addprefix -I, $(SOURCEDIR))
DEPS := $(OBJECTS:.o=.d)

vpath %.cpp $(SOURCEDIR)

all: $(NAME)

re: fclean
	make all

run: all
	$(SCREENCLEAR)
	./$(NAME) $(shell shuf -i 0-2147483647 -n $(NUMCOUNT))

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	printf "$(V)$(B)Binary:$(T)$(Y) $@ $(T)\n"

define build_cmd
$1/%.o: %.cpp | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

clean:
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG))

fclean: clean
	$(call delete_cmd, $(NAME))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

.PHONY: all re run
.PHONY: clean fclean

.SILENT:
