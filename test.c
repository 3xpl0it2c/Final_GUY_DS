#include <stdio.h>
#include <assert.h>
#include "hash.c"

void testHashFunc(void) {
	unsigned long testID = 123456789;
	int arraySize = 24;

	int hashFunctionTest = hash(testID, arraySize);

	assert(hashFunctionTest < arraySize && hashFunctionTest >= 0);
}

int main(void) {
	testHashFunc();

	return 0;
}
