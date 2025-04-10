all: clean compile run

clean: 
	@rm -rf out/*

compile:
	@javac -d out src/*.java

run:
	@java -cp out InventoryTest

javadoc:
	@rm -rf doc
	@javadoc -d doc src/*.java