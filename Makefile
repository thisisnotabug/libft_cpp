
#

# Executable name
NAME			:= libft.a

# Git submodule to init
SUBMODULES		:=

# Base flags
BASE_FLAGS		= -Wall -Wextra
INCLUDE_FLAGS	=

# Compilation flags (per language)
C_FLAGS			= $(INCLUDE_FLAGS) $(BASE_FLAGS)
CPP_FLAGS		= $(INCLUDE_FLAGS) $(BASE_FLAGS) -std=c++14



LINK_FLAGS		= $(BASE_FLAGS)

DEBUG_MODE		?= 0
ifeq ($(DEBUG_MODE),1)
	# Extra flags used in debug mode
	BASE_FLAGS	+= -g
else
	# Extra flags used when not in debug mode
	BASE_FLAGS	+= -O2
endif
export DEBUG_MODE

UNAME			:= $(shell uname | cut -c1-6)
ifeq ($(UNAME),CYGWIN)
  CC_CPP		= i686-w64-mingw32-g++
  CC_AR			= i686-w64-mingw32-ar
else
  CC_CPP		= clang++
  CC_AR			= ar
endif


# Objects directory
O_DIR			:= _objs

# Jobs
JOBS			:= 4

# Depend file name
DEPEND			:= depend.mk

# tmp
SUBMODULE_RULES	:= $(addsuffix /.git,$(SUBMODULES))
PRINT_OK	= printf '  \033[32m$<\033[0m\n'
PRINT_LINK	= printf '\033[32m$@\033[0m\n'

# Default rule (need to be before any include)
all: $(SUBMODULE_RULES) init
	-make -j$(JOBS) $(NAME)

# Include $(O_FILES) and dependencies
include $(DEPEND)

init: $(LIBS_RULES) $(OBJ_DIR_TREE) $(PUBLIC_LINKS)

# Linking
$(NAME): $(OBJ_DIR_TREE) $(PUBLIC_LINKS) $(LINK_DEPENDS) $(O_FILES)
	$(CC_AR) rcs $@ $(O_FILES) && $(PRINT_LINK)

# Compiling
$(O_DIR)/%.o: %.c
	clang $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(O_DIR)/%.o: %.cpp
	$(CC_CPP) $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(SUBMODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Create include links
$(PUBLIC_LINKS):
	ln -fs $(abspath $<) $@
# Create obj directories
$(OBJ_DIR_TREE):
	mkdir -p $@

# Set debug mode and make
debug: _debug all

# Clean, set debug mode and make
rebug: fclean debug

# Clean obj files
clean:
	-rm -f $(O_FILES) $(PUBLIC_LINKS) 2> /dev/null
	-rm -df $(OBJ_DIR_TREE) 2> /dev/null

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean all

# Set debug flags
_debug:
	$(eval DEBUG_MODE = 1)

.SILENT:
.PHONY: all clean fclean re debug rebug _debug init
