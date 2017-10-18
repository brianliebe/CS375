all:	program1 program2 program3

program1:
	g++ program1.cpp -o program1 -std=c++11

program2:
	g++ program2.cpp -o program2 -std=c++11

program3:
	g++ program3.cpp -o program3 -std=c++11

clean:
	rm -f program1
	rm -f program2
	rm -f program3
	rm -f output1.txt
	rm -f output2.txt
	rm -f output3.txt

print:	run
	cat output1.txt
	cat output2.txt
	cat output3.txt

run:	all
	./program1 filex.txt filey.txt output1.txt
	./program2 filex.txt filey.txt output2.txt
	./program3 filex.txt filey.txt output3.txt
