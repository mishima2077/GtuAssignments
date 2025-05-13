all: clean compile run

compile: hw01.c util.c util.h
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o test hw01.c util.c

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
