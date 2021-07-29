# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ngerrets <ngerrets@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/15 14:47:03 by ngerrets      #+#    #+#                  #
#    Updated: 2021/07/29 17:40:31 by ngerrets      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# For now this is the default Makefile I use for C projects
# Manually edit:
NAME := so_long
COMPILE_FLAGS ?= -Wall -Wextra -c -g
LINKING_FLAGS ?= -Llib/get_next_line -lgnl
LIBRARIES ?=
SOURCE_DIRECTORY ?= src
HEADER_DIRECTORY ?= include
OBJECTS_DIRECTORY ?= objects
BINARIES_DIRECTORY ?= .

# Don't manually edit:
HEADERS	:= $(shell find $(HEADER_DIRECTORY) -type f -name *.h)
SOURCES := $(shell find $(SOURCE_DIRECTORY) -type f -name *.c)
OBJECTS := $(patsubst $(SOURCE_DIRECTORY)/%,$(OBJECTS_DIRECTORY)/%,$(SOURCES:.c=.o))
INCLUDES := $(patsubst %,-I%,$(dir $(HEADERS)))

# OS specific rules
ifeq ($(shell uname),Darwin)
	MLXLIB := lib/mlx_mac
	LINKING_FLAGS += -Llib/mlx_mac -lmlx -framework OpenGL -framework AppKit
else
	MLXLIB := lib/mlx_linux
	LINKING_FLAGS += -Llib/mlx_linux -lmlx -lXext -lX11 -lm
endif

# Default make-rule. Compile and link files.
all: dependencies $(BINARIES_DIRECTORY)/$(NAME)

dependencies:
	$(MAKE) -C lib/get_next_line
	$(MAKE) -C $(MLXLIB)

# Link files
$(BINARIES_DIRECTORY)/$(NAME): $(BINARIES_DIRECTORY) $(HEADERS) $(OBJECTS)
	@echo "\nLinking files..."
	@$(CC) $(OBJECTS) -o $(BINARIES_DIRECTORY)/$(NAME) $(LINKING_FLAGS) 
	@echo "Done!"

# Create binaries directory
$(BINARIES_DIRECTORY):
	@mkdir -p $(BINARIES_DIRECTORY)

# Compile files
$(OBJECTS_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c $(HEADERS)
	@echo "Compiling: $@"
	@mkdir -p $(@D)
	@$(CC) $(COMPILE_FLAGS) $(INCLUDES) -c -o $@ $<

# Clean objects
clean: cleandeps
	@rm -Rf $(OBJECTS_DIRECTORY)
	@echo "Objects cleaned."

cleandeps:
	$(MAKE) -C lib/get_next_line clean
	$(MAKE) -C $(MLXLIB) clean

# Clean objects and binaries
fclean: clean
	@rm -f $(BINARIES_DIRECTORY)/$(NAME)
	@echo "Binaries cleaned."

# Clean, recompile and relink project
re: fclean all

# Compile, link and run project
run: all
	@echo "Running..."
	@$(BINARIES_DIRECTORY)/$(NAME)

# Prints header and source files
print:
	@echo "---HEADERS: $(HEADERS)" | xargs -n1
	@echo "---SOURCES: $(SOURCES)" | xargs -n1

# In case of bonus
bonus: all

.PHONY: all dependencies clean cleandeps fclean re run print compile bonus