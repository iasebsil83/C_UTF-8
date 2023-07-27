// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

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
	char         my_utf8_text[] = { 0x24, 0xc2, 0xa3, 0xd0, 0x98, 0xe0, 0xa4, 0xb9, 0xe2, 0x82, 0xac, 0xed, 0x95, 0x9c, 0xf0, 0x90, 0x8d, 0x88 };
	unsigned int res_len        = 0;
	int*         res            = utf8_read(my_utf8_text, &res_len);

	//print result
	printf("res [");
	for(size_t r=0; r < res_len; r++){
		printf("%02x,", res[r]);
	}
	printf("]\n");



	return EXIT_SUCCESS;
}
