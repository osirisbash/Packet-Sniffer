CC:=gcc
BUILD_DIR:= build

GTK_FLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS  := $(shell pkg-config --libs gtk+-3.0)

SRCFILES     := $(shell find -type f -name "*.c" -printf '%P\n')
SRCFILES_OBJ := $(patsubst %.c,%.o,$(SRCFILES))
OBJFILES     := $(addprefix $(BUILD_DIR)/, $(SRCFILES_OBJ))
DEPFILES     := $(patsubst %.o,%.d,$(OBJFILES))

INCLUDE_DIRS := ./

WARNINGS := -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum  -Wunreachable-code
            
CFLAGS := -g3 $(WARNINGS)


$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIRS) -MMD -MP -c $<  -o $@


.PHONY: all clean

all: $(BUILD_DIR) main

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPFILES)

main: $(OBJFILES)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 
	
$(BUILD_DIR):
	mkdir $(BUILD_DIR)



