
CC = clang
CFLAGS = -Wall -Wextra -std=c11 -Wno-unused-parameter -Wno-unused-variable
LDFLAGS = -lc

BUILD = build
TARGET = $(BUILD)/align

SRC = ./align.c

OBJ = $(SRC:%.c=$(BUILD)/%.o)
DEP = $(OBJ:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD):
	mkdir -p $@


-include $(DEP)

clean:
	rm -rf $(BUILD)

.PHONY: all clean

