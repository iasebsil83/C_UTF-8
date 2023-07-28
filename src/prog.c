// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//text manipulation
#include <string.h>

//utf-8 utility
#include "../lib/utf-8.h"








/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prog [V.V.V] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                        utf-8.c/.h demonstration program

        Blablabla about the subject.

    DD/MM/YYYY > [V.V.V] :
    - Added something.
    - Added something else.

    DD/MM/YYYY > [V.V.V] :
    - Added something that wasn't before.
    - Fixed a bug.
    - Added something else.
    - Added something else again.

    BUGS : Active bugs in last version.
    NOTES : Notes.

    Contact     :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */








// ---------------- EXECUTION ----------------

//main
int main(){
	//presentation
	printf("This is a basic example of \"utf-8.c/.h\" use.\n\n");



	//read a UTF-8 text
	char   my_utf8_text[] = {
		0x24,                  // U+00024 (dollar)
		0xc2, 0xa3,            // U+000A3 (pound)
		0xd0, 0x98,            // U+00418 (cyrilic ize)
		0xe0, 0xa4, 0xb9,      // U+00939 (a devanagari symbol)
		0xe2, 0x82, 0xac,      // U+020AC (euro)
		0xed, 0x95, 0x9c,      // U+0D55C (hangul syllable : modern Korean)
		0xf0, 0x90, 0x8d, 0x88 // U+10348 (hwair)
	};
	size_t read_result_len = 0;
	int*   read_result     = utf8_read(my_utf8_text, &read_result_len);

	//print result
	printf("read result: [");
	for(size_t r=0; r < read_result_len; r++){
		printf("%02x, ", read_result[r]);
	}
	printf("]\n");

	//write back UTF-8 text
	char* write_result = utf8_write(read_result, read_result_len);

	//print result
	printf("write result: [");
	for(size_t r=0; r < strlen(write_result); r++){
		printf("0x%02x, ", write_result[r] & 0xff);
	}
	printf("]\n");



	return EXIT_SUCCESS;
}
