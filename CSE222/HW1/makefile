all: clean compile run

clean:
	@rm -rf bin/*

compile:
	@javac -d bin src/*.java

run:
	@java -cp bin CustomerTrackingSystem

javadoc:
	@rm -rf doc
	@javadoc -d doc src/*.java