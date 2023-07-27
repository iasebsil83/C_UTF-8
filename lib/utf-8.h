#ifndef UTF_8_H
#define UTF_8_H






// ---------------- DECLARATIONS ----------------

//utf-8 modes (encoding/decoding use only)
#define UTF8__READY             0
#define UTF8__WAITING_NEXT      1
#define UTF8__1ST_TRAILING_BYTE 2
#define UTF8__2ND_TRAILING_BYTE 3
#define UTF8__3RD_TRAILING_BYTE 4




// ---------------- BASICS ----------------

//read unicode array from utf-8 text (returns an array of unicode sets (int) + its length)
int* utf8_read(char* text, unsigned int* result_length);

//write utf-8 text from unicode array
char* utf8_write(int* unicode_arr, unsigned int length);






#endif
