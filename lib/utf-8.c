// ---------------- IMPORTATIONS ----------------

//standard
#include <stdio.h>
#include <stdlib.h>

//text manipulation
#include <string.h>

//own header
#include "utf-8.h"








/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ UTF-8 [0.1.0] ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                 UTF-8 by I.A.

        This library is a tool for manipulating text with utf-8 encoding in
    both ways : encoding & decoding. Decoded format is presented under
    unicode arrays (which are basically int arrays).

    27/07/2023 > [0.1.0] :
    - Created utf-8.c/.h.

    BUGS : .
    NOTES : .

    Contact     : i.a.sebsil83@gmail.com
    Youtube     : https://www.youtube.com/user/IAsebsil83
    GitHub repo : https://github.com/iasebsil83

    Let's Code !                                  By I.A.
******************************************************************************************

    LICENSE :

    C_UTF-8
    Copyright (C) 2023 Sebastien SILVANO

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.

    If not, see <https://www.gnu.org/licenses/>.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */








// ---------------- BASICS ----------------

//read unicode array from utf-8 text (returns an array of unicode sets (int) + its length)
int* utf8_read(char* text, size_t* result_length){

	//error cases
	if(text == NULL || result_length == NULL){
		printf("RUNTIME ERROR > utf-8.c : utf8_read() : Text or result length is NULL.\n");
		return NULL;
	}

	//empty text => empty array (NULL)
	size_t text_len = strlen(text);
	if(text_len == 0){
		result_length[0] = 0;
		return NULL;
	}

	//prepare result (maximum amount allocated, will shrink at the end)
	int* result = malloc(text_len * sizeof(int));
	if(result == NULL){
		printf("FATAL ERROR > utf-8.c : utf8_read() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}
	result_length[0] = 0;

	//for each character in utf-8 text
	char   mode = UTF8__READY;
	size_t t    = 0;
	while(t < text_len){

		//case 1 : multiple-byte grapheme
		if(text[t] & 0b10000000){

			//case 1.1 : header byte
			if(text[t] & 0b01000000){

				//
				if(text[t] & 0b00100000){
					if(text[t] & 0b00010000){
						if(text[t] & 0b00001000){
							printf("RUNTIME ERROR > utf-8.c : utf8_read() : Invalid header byte (0x%02x).\n", text[t]);
							mode = UTF8__READY;
						}

						//case 1.2.3 : 4-bytes grapheme
						else{
							mode = UTF8__3RD_TRAILING_BYTE;
							result[result_length[0]] |= (text[t] & 0b00000111) << 18;
						}
					}

					//case 1.2.2 : 3-bytes grapheme
					else{
						mode = UTF8__2ND_TRAILING_BYTE;
						result[result_length[0]] |= (text[t] & 0b00001111) << 12;
					}
				}

				//case 1.2.1 : 2-bytes grapheme
				else{
					mode = UTF8__1ST_TRAILING_BYTE;
					result[result_length[0]] |= (text[t] & 0b00011111) << 6;
				}
			}

			//case 1.2 : trailing byte (if no header have been found just before, ignore it)
			else{
				switch(mode){
					case UTF8__1ST_TRAILING_BYTE:
						mode = UTF8__READY;
						result[result_length[0]++] |= text[t] & 0b00111111;
					break;
					case UTF8__2ND_TRAILING_BYTE:
						mode = UTF8__1ST_TRAILING_BYTE;
						result[result_length[0]] |= (text[t] & 0b00111111) << 6;
					break;
					case UTF8__3RD_TRAILING_BYTE:
						mode = UTF8__2ND_TRAILING_BYTE;
						result[result_length[0]] |= (text[t] & 0b00111111) << 12;
					break;
				}
			}
		}

		//case 2 : ASCII grapheme
		else{
			if(mode != UTF8__READY){ //not expecting an ASCII but rather a trailing byte
				printf("RUNTIME ERROR > utf-8.c : utf8_read() : Text or result length is NULL.\n");
			}

			//regular case (write full byte : U+000XX)
			else{
				result[result_length[0]++] = text[t];
			}

			//in all cases => reset state
			mode = UTF8__READY;
		}

		t++;
	}

	//shrink result if needed
	if(result_length[0] != text_len){
		size_t new_size   = result_length[0] * sizeof(int);
		int*   new_result = malloc(new_size);
		if(new_result == NULL){
			printf("FATAL ERROR > utf-8.c : utf8_read() : Computer refuses to give more memory.\n");
			exit(EXIT_FAILURE);
		}

		//copy content into new buffer
		memcpy(new_result, result, new_size);
		free(result);

		return new_result;
	}

	return result;
}

//write utf-8 text from unicode array
char* utf8_write(int* unicode_arr, unsigned int length){

	//error cases
	if(unicode_arr == NULL || length == 0){
		printf("RUNTIME ERROR > utf-8.c : utf8_write() : Unicode array is NULL or empty.\n");
		return NULL;
	}

	//prepare result (maximum amount allocated, will shrink at the end)
	char* result = malloc(4*length+1);
	if(result == NULL){
		printf("FATAL ERROR > utf-8.c : utf8_write() : Computer refuses to give more memory.\n");
		exit(EXIT_FAILURE);
	}
	size_t result_length = 0;

	//for each character in unicode array
	for(unsigned int ua=0; ua < length; ua++){

		//case 1 : 4-bytes grapheme
		if(unicode_arr[ua] > UTF8__MAX_3BYTES){
			//                          HHHHH--- +                       ---------aaa------------------ => HHHHHaaa (header + 3 data)
			result[result_length++] = 0b11110000 | ((unicode_arr[ua] & 0b000000000111000000000000000000) >> 18);
			result[result_length++] = 0b10000000 | ((unicode_arr[ua] & 0b000000000000111111000000000000) >> 12);
			result[result_length++] = 0b10000000 | ((unicode_arr[ua] & 0b000000000000000000111111000000) >>  6);
			result[result_length++] = 0b10000000 |  (unicode_arr[ua] & 0b000000000000000000000000111111);
			//                          TT------ +                       ------------bbbbbb------------ => TTbbbbbb (trailing + 6 data)
			//                          TT------ +                       ------------------cccccc------ => TTcccccc (trailing + 6 data)
		}	//                          TT------ +                       ------------------------dddddd => TTdddddd (trailing + 6 data)

		//case 2 : 3-bytes grapheme
		else if(unicode_arr[ua] > UTF8__MAX_2BYTES){
			//                          HHHH---- +                       --------aaaa------------ => HHHHaaaa (header + 4 data)
			result[result_length++] = 0b11100000 | ((unicode_arr[ua] & 0b000000001111000000000000) >> 12);
			result[result_length++] = 0b10000000 | ((unicode_arr[ua] & 0b000000000000111111000000) >>  6);
			result[result_length++] = 0b10000000 |  (unicode_arr[ua] & 0b000000000000000000111111);
			//                          TT------ +                       ------------bbbbbb------ => TTbbbbbb (trailing + 6 data)
		}	//                          TT------ +                       ------------------cccccc => TTcccccc (trailing + 6 data)

		//case 3 : 2-bytes grapheme
		else if(unicode_arr[ua] > UTF8__MAX_1BYTE){
			//                          HHH----- +                       -----aaaaa------ => HHHaaaaa (header + 5 data)
			result[result_length++] = 0b11000000 | ((unicode_arr[ua] & 0b0000011111000000) >> 6);
			result[result_length++] = 0b10000000 |  (unicode_arr[ua] & 0b0000000000111111);
		}	//                          TT------ +                       ----------bbbbbb => TTbbbbbb (trailing + 6 data)

		//case 4 : ASCII grapheme
		else{
			result[result_length++] = unicode_arr[ua]; //keep raw byte
		}
	}

	//set end character
	result[result_length] = '\0';

	//shrink result if needed
	if(result_length != length){
		size_t new_size   = result_length+1;
		char*  new_result = malloc(new_size);
		if(new_result == NULL){
			printf("FATAL ERROR > utf-8.c : utf8_write() : Computer refuses to give more memory.\n");
			exit(EXIT_FAILURE);
		}

		//copy content into new buffer
		memcpy(new_result, result, new_size);
		free(result);

		return new_result;
	}

	return result;
}
