all: permutation test

headers = lexicographical.h increase.h decrease.h sjt.h
CFLAGS = -std=c++11

permutation: $(headers) permutation.cpp
	g++ permutation.cpp -o permutation $(CFLAGS)
	@echo "[+] Run example:"
	@echo "###########################"
	./permutation 2018 <init.txt

time_test: $(headers) time_test.cpp
	g++ time_test.cpp -o time_test $(CFLAGS)
	@echo "[+] Run time tests:"
	./time_test

test: $(headers) test.cpp
	g++ test.cpp -o test $(CFLAGS)
	./test

clean:
	rm permutation
	rm time_test
	rm test
