all: clean compile run

clean: 
	@rm -rf out/*
	@rm -rf *.txt

compile:
	@javac -d out src/*.java

run:
	@java -cp out -Xint src.Main 

javadoc:
	@rm -rf doc
	@javadoc -d doc src/*.java