all: clean compile run

clean:
	rm -rf bin/*

compile:
	javac -d bin src/GtuContainer/*.java

run:
	java -cp bin GtuContainer.ContainerTestClass

javadoc:
	rm -r doc
	javadoc -d doc src/GtuContainer/*.java
