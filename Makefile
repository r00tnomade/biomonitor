CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm

# Project Files - Added src/patient.c here!
SRCS = main.c src/patient.c src/buffer.c src/analytics.c src/file_io.c
OBJS = $(SRCS:.c=.o)
TARGET = biomonitor

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) patient_report.txt patient_data.bin

.PHONY: all clean