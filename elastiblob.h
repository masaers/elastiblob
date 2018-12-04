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
void elastiblob_init(struct elastiblob* blob, size_t reserved_size);

/**
	Creates an elastic blob on the heap. It is up to the caller
  to free the retuned blob.
 */
struct elastiblob* make_elastiblob(size_t reserved_size);

/**
  Frees the data held by an elastic blob.
 */
void elastiblob_free(struct elastiblob* blob);

/**
	Returns non-null if blob is in a valid state.
 */
int elastiblob_valid(const struct elastiblob* blob);

/**
	Clears the content of the blob.
	Does not actually free any allocated memory.
 */
void elastiblob_clear(struct elastiblob* blob);

/**
  Returns a string representation of the content of the blob.
  If any null characters have been added to the content, the string
  is terminated at the first such character, otherwise the string
  will contain the entire content of the blob. Non-printable
  characters in the content do pose a problem.

  This function represents plenty of rope to shoot yourself in
  the foot with, caution is adviced.
 */
const char* elastiblob_str(struct elastiblob* blob);

/**
  Appends data to an existing elastic blob.
 */
int elastiblob_append(struct elastiblob* blob, const void* content, size_t content_size);

/**
	Appends a string to an existing elastic blob.
 */
int elastiblob_append_str(struct elastiblob* blob, const char* str);

/**
  Append a character to an existing elastic blob.
 */
int elastiblob_append_chr(struct elastiblob* blob, const char chr);

/**
	Ensures that an elastic blob can hold at least size bytes.
 */
int elastiblob_reserve(struct elastiblob* blob, size_t size);


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
