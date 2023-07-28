#ifndef UTF_8_H
#define UTF_8_H






// ---------------- DECLARATIONS ----------------

//utf-8 modes (encoding/decoding use only)
#define UTF8__READY             0
#define UTF8__WAITING_NEXT      1
#define UTF8__1ST_TRAILING_BYTE 2
#define UTF8__2ND_TRAILING_BYTE 3
#define UTF8__3RD_TRAILING_BYTE 4

//utf-8 maxima per mode    AAAAAAAABBBBBBBB
#define UTF8__MAX_1BYTE  0b0000000001111111 //7b             data
#define UTF8__MAX_2BYTES 0b0000011111111111 //11b = 5b+6b    data
#define UTF8__MAX_3BYTES 0b1111111111111111 //16b = 4b+6b+6b data




// ---------------- BASICS ----------------

//read unicode array from utf-8 text (returns an array of unicode sets (int) + its length)
int* utf8_read(char* text, size_t* result_length);

//write utf-8 text from unicode array
char* utf8_write(int* unicode_arr, unsigned int length);






#endif
