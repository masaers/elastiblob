
test : elastiblob_test
	@(./elastiblob_test && echo "TEST PASSED!") || echo "TEST FAILED!"

elastiblob_test : elastiblob_test.c elastiblob.o
	$(CC) $^ -o $@

elastiblob.o : elastiblob.c elastiblob.h
	$(CC) -c -O3 $< -o $@

clean :
	$(RM) elastiblob.o elastiblob_test
