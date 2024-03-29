CC = gcc # Compiler to use
OPTIONS = -O0 -g -Wall -pthread #-lrt # -g for debug, -O2 for optimise and -Wall additional messages
INCLUDES = -I . # Directory for header file
OBJS = main.o module.o # List of objects to be build
.PHONY: all clean # To declare all, clean are not files
	 
all: ${OBJS}
	    @echo "Building.." # To print "Building.." message
		    ${CC} ${OPTIONS} ${INCLUDES} ${OBJS} -o pc 
			 
%.o: %.c  # % pattern wildcard matching
	    ${CC} ${OPTIONS} -c $*.c ${INCLUDES}
list:
	    @echo $(shell ls) # To print output of command 'ls'
		 
clean:
	    @echo "Cleaning up.."
		    -rm -rf *.o # - prefix for ignoring errors and continue execution
				-rm log_file # - clean up log files
					-rm human_log_file
					    -rm pc
