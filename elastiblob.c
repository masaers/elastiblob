#include "elastiblob.h"
#include <string.h>
#include <stdlib.h>

extern inline int elastiblob_valid(const struct elastiblob* blob);

void elastiblob_init(struct elastiblob* blob, size_t reserved_size) {
  blob->size = 0;
  blob->max_size = reserved_size;
  blob->buffer = (char*)malloc(reserved_size);
}

struct elastiblob* make_elastiblob(size_t reserved_size) {
  struct elastiblob* result = (struct elastiblob*)malloc(sizeof(struct elastiblob));
  if (result != NULL) {
    elastiblob_init(result, reserved_size);
  }
  return result;
}

void elastiblob_free(struct elastiblob* blob) {
  if (elastiblob_valid(blob)) {
    blob->size = 0;
    blob->max_size = 0;
    free(blob->buffer);
  }
}

int elastiblob_valid(const struct elastiblob* blob) {
  return blob->buffer == NULL ? 0 : 1;
}

void elastiblob_clear(struct elastiblob* blob) {
  blob->size = 0;
}

const char* elastiblob_str(struct elastiblob* blob) {
  ((char*)blob->buffer)[blob->size] = '\0';
  return (const char*)blob->buffer;
}

int elastiblob_append(struct elastiblob* blob, const void* content, size_t content_size) {
  int result = elastiblob_reserve(blob, content_size + 1);
  if (result) {
    memcpy((char*)blob->buffer + blob->size, content, content_size);
    blob->size = blob->size + content_size;
  }
  return result;
}

int elastiblob_append_str(struct elastiblob* blob, const char* str) {
  return elastiblob_append(blob, (void*)str, strlen(str));
}

int elastiblob_append_chr(struct elastiblob* blob, const char chr) {
  int result = elastiblob_reserve(blob, blob->size + 1);
  if (result) {
    ((char*)blob->buffer)[blob->size++] = chr;
  }
  return result;
}

int elastiblob_reserve(struct elastiblob* blob, size_t size) {
  const size_t min_size = blob->size + size;
  if (elastiblob_valid(blob) && blob->max_size < min_size) {
    blob->max_size = min_size + min_size;
    blob->buffer = (char*)realloc((void*)blob->buffer, blob->max_size);
    if (blob->buffer == NULL) {
      // Reallocation failed.
      blob->max_size = 0;
      blob->size = 0;
    }
  }
  return elastiblob_valid(blob);
}

