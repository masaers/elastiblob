#ifndef ELASTIBLOB_H
#define ELASTIBLOB_H
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
#include<string>
extern "C" {
#endif

/**
  An elastic &ldquo;data blob&rdquo; that is allowed to grow dynamically.
 */
struct elastiblob {
  char* buffer;
  size_t size;
  size_t max_size;
};

/**
  Initializes a pointer to an elastic blob. If the pointer points
  to an existing elastic blob, that blob is freed.
 */
int elastiblob_init(struct elastiblob* blob, size_t reserved_size);

/**
	Creates an elastic blob on the heap. It is up to the caller
  to free the retuned blob.
 */
struct elastiblob* make_elastiblob(size_t reserved_size);

/**
  Clones an existing elastiblob into another existing elastiblob.
 */
int elastiblob_clone(struct elastiblob* to, const struct elastiblob* from);

/**
  Swaps the content of two elastiblob pointers. Passing null pointers lead
  to undefined behaviour.
 */
void elastiblob_swap(struct elastiblob* a, struct elastiblob* b);

/**
  Frees the data held by an elastic blob.
 */
void elastiblob_free(struct elastiblob* blob);

/**
	Returns non-null if blob is in a valid state.
 */
inline int elastiblob_valid(const struct elastiblob* blob) {
  return blob->buffer == NULL ? 0 : 1;
}

/**
	Clears the content of the blob.
	Does not actually free any allocated memory.
 */
inline void elastiblob_clear(struct elastiblob* blob) {
  blob->size = 0;
}

/**
  Returns a string representation of the content of the blob.
  If any null characters have been added to the content, the string
  is terminated at the first such character, otherwise the string
  will contain the entire content of the blob. Non-printable
  characters in the content do pose a problem.

  This function represents plenty of rope to shoot yourself in
  the foot with, caution is adviced.
 */
inline const char* elastiblob_str(struct elastiblob* blob) {
  blob->buffer[blob->size] = '\0';
  return (const char*)blob->buffer;
}

/**
  Appends data to an existing elastic blob.
 */
int elastiblob_append(struct elastiblob* blob, const void* content, size_t content_size);

/**
	Appends a string to an existing elastic blob.
 */
inline int elastiblob_append_str(struct elastiblob* blob, const char* str) {
  return elastiblob_append(blob, (const void*)str, strlen(str));
}

/**
  Append a character to an existing elastic blob.
 */
int elastiblob_append_chr(struct elastiblob* blob, const char chr);

/**
	Ensures that an elastic blob can hold at least size bytes.
 */
int elastiblob_reserve(struct elastiblob* blob, size_t size);

/**
  Returns the number of bytes that can be safely written to
  the elastic blob before it has to resize.
 */
inline int elastiblob_available(const struct elastiblob* blob) {
  return blob->max_size - blob->size;
}

/**
  Returns the blob as a charcter buffer that can be written to.
  Writing mor ethan elastiblob_available bytes to the buffer
  results in undefined behavior.
 */
inline char* elastiblob_append_buffer(struct elastiblob* blob) {
  return blob->buffer + blob->size;
}


/**
  Updates the elastic blob following writes to the buffer returned
  by elastiblob_append_buffer.
 */
inline void elastiblob_appended(struct elastiblob* blob, int bytes) {
  blob->size += bytes;
}

inline char elastiblob_endswith(const struct elastiblob* blob) {
  return blob->buffer[blob->size - 1];
}

inline void elastiblob_rewind(struct elastiblob* blob, int bytes) {
  blob->size -= bytes;
}


#ifdef __cplusplus
} // extern C
namespace com { namespace masaers { namespace elastiblob {
/**
	If we have c++, we get to overload function names!
 */
inline int elastiblob_append(struct elastiblob* blob, const std::string& str) {
	return elastiblob_append(blob, str.c_str(), str.size());
}
inline int elastiblob_append(struct elastiblob* blob, const char* str) {
	return elastiblob_append(blob, (void*)str, strlen(str));
}
/**
	With c++, we can use elastic blobs to store arbitrary values!
 */
template<typename T>
inline int elastiblob_append(struct elastiblob* blob, const T& value) {
	return elastiblob_append(blob, &value, sizeof(T));
}
} } } // namespace
#endif

#endif
