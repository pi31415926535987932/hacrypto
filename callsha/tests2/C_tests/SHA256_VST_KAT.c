#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Ccommon_test.h"
#include "../../callsha.h"

//  abc vector from that place....
SHA256_VST_KAT_0(){
	unsigned char input[3] = "abc";
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA, 
	0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23, 
	0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C, 
	0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD

	};

	SHA256_VST(input, result, 3);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_0");

} 

//  abc represented in hex
SHA256_VST_KAT_1(){
	unsigned char input[3] = { 97 ,98 ,99 };
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA, 
	0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23, 
	0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C, 
	0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD

	};

	SHA256_VST(input, result, 3);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_1");

} 

SHA256_VST_KAT_2(){
	unsigned char input[56] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0x24, 0x8D, 0x6A, 0x61, 0xD2, 0x06, 0x38, 0xB8, 
	0xE5, 0xC0, 0x26, 0x93, 0x0C, 0x3E, 0x60, 0x39, 
	0xA3, 0x3C, 0xE4, 0x59, 0x64, 0xFF, 0x21, 0x67, 
	0xF6, 0xEC, 0xED, 0xD4, 0x19, 0xDB, 0x06, 0xC1

	};

	SHA256_VST(input, result, 56);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_2");

} 

SHA256_VST_KAT_3(){
    unsigned char *input = malloc(sizeof(char) * 1000000);
	char to_repeat[] = "a";

	int i;
	for(i=0; i<1000000; i++){
		memcpy(input + i*1, to_repeat, 1);
	}

	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xCD, 0xC7, 0x6E, 0x5C, 0x99, 0x14, 0xFB, 0x92, 
	0x81, 0xA1, 0xC7, 0xE2, 0x84, 0xD7, 0x3E, 0x67, 
	0xF1, 0x80, 0x9A, 0x48, 0xA4, 0x97, 0x20, 0x0E, 
	0x04, 0x6D, 0x39, 0xCC, 0xC7, 0x11, 0x2C, 0xD0

	};

	SHA256_VST(input, result, 1000000);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_3");

} 

SHA256_VST_KAT_4(){
	unsigned char input[112] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xcf, 0x5b, 0x16, 0xa7, 0x78, 0xaf, 0x83, 0x80, 
	0x03, 0x6c, 0xe5, 0x9e, 0x7b, 0x04, 0x92, 0x37, 
	0x0b, 0x24, 0x9b, 0x11, 0xe8, 0xf0, 0x7a, 0x51, 
	0xaf, 0xac, 0x45, 0x03, 0x7a, 0xfe, 0xe9, 0xd1

	};

	SHA256_VST(input, result, 112);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_4");

} 

SHA256_VST_KAT_5(){
	unsigned char input[0] = {};
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 
	0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24, 
	0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c, 
	0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55

	};

	SHA256_VST(input, result, 0);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_5");

} 

SHA256_VST_KAT_6(){
	unsigned char input[43] = "The quick brown fox jumps over the lazy dog";
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xd7, 0xa8, 0xfb, 0xb3, 0x07, 0xd7, 0x80, 0x94, 
	0x69, 0xca, 0x9a, 0xbc, 0xb0, 0x08, 0x2e, 0x4f, 
	0x8d, 0x56, 0x51, 0xe4, 0x6d, 0x3c, 0xdb, 0x76, 
	0x2d, 0x02, 0xd0, 0xbf, 0x37, 0xc9, 0xe5, 0x92

	};

	SHA256_VST(input, result, 43);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_6");

} 

SHA256_VST_KAT_7(){
	unsigned char input[3] = { 97 ,98 ,99 };
	unsigned char result[32];
	unsigned char expected_result[32] = {
	0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA, 
	0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23, 
	0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C, 
	0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD

	};

	SHA256_VST(input, result, 3);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_7");

} 

SHA256_VST_KAT_8(){
    unsigned char *input = malloc(sizeof(char) * 1073741824);
	char to_repeat[] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno";

	int i;
	for(i=0; i<16777216; i++){
		memcpy(input + i*64, to_repeat, 64);
	}

	unsigned char result[32];
	unsigned char expected_result[32] = {
	0x50, 0xe7, 0x2a, 0x0e, 0x26, 0x44, 0x2f, 0xe2, 
	0x55, 0x2d, 0xc3, 0x93, 0x8a, 0xc5, 0x86, 0x58, 
	0x22, 0x8c, 0x0c, 0xbf, 0xb1, 0xd2, 0xca, 0x87, 
	0x2a, 0xe4, 0x35, 0x26, 0x6f, 0xcd, 0x05, 0x5e

	};

	SHA256_VST(input, result, 1073741824);
	check_KAT(result, expected_result, 32, "SHA256_VST_KAT_8");

} 
