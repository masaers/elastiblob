#include "elastiblob.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

int main() {
	struct elastiblob* blob = make_elastiblob(5);
	assert(elastiblob_append_str(blob, "hello") != 0);
	assert(strcmp(elastiblob_str(blob), "hello") == 0);
	assert(elastiblob_append_str(blob, " world") != 0);
	assert(strcmp(elastiblob_str(blob), "hello world") == 0);
	assert(elastiblob_append_chr(blob, '!') != 0);
	assert(strcmp(elastiblob_str(blob), "hello world!") == 0);
	return 0;
}
