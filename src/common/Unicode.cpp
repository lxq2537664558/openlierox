/*
	OpenLieroX

	UTF8/Unicode conversions
	
	code under LGPL
	created 01-05-2007
	by Albert Zeyer and Dark Charlie
*/

#ifdef _MSC_VER
#pragma warning(disable: 4786)  // WARNING: identifier XXX was truncated to 255 characters in the debug info
#pragma warning(disable: 4503)  // WARNING: decorated name length exceeded, name was truncated
#endif

#include "Unicode.h"
#include "MathLib.h" // for SIGN


// Table used for removing diacritics and other backward incompatible characters
ConversionItem tConversionTable[] = {
	{ 0xA0, {0xC2, 0xA0, 0x00, 0x00}, ' '},
	{ 0xA1, {0xC2, 0xA1, 0x00, 0x00}, '!'},
	{ 0xA2, {0xC2, 0xA2, 0x00, 0x00}, 'c'},
	{ 0xA3, {0xC2, 0xA3, 0x00, 0x00}, 'L'},
	{ 0xA4, {0xC2, 0xA4, 0x00, 0x00}, 'o'},
	{ 0xA5, {0xC2, 0xA5, 0x00, 0x00}, 'Y'},
	{ 0xA6, {0xC2, 0xA6, 0x00, 0x00}, '|'},
	{ 0xA7, {0xC2, 0xA7, 0x00, 0x00}, '$'},
	{ 0xA8, {0xC2, 0xA8, 0x00, 0x00}, ' '},
	{ 0xA9, {0xC2, 0xA9, 0x00, 0x00}, 'c'},
	{ 0xAA, {0xC2, 0xAA, 0x00, 0x00}, 'a'},
	{ 0xAB, {0xC2, 0xAB, 0x00, 0x00}, '<'},
	{ 0xAC, {0xC2, 0xAC, 0x00, 0x00}, '-'},
	{ 0xAD, {0xC2, 0xAD, 0x00, 0x00}, '-'},
	{ 0xAE, {0xC2, 0xAE, 0x00, 0x00}, 'r'},
	{ 0xAF, {0xC2, 0xAF, 0x00, 0x00}, '-'},
	{ 0xB0, {0xC2, 0xB0, 0x00, 0x00}, '*'},
	{ 0xB1, {0xC2, 0xB1, 0x00, 0x00}, '+'},
	{ 0xB2, {0xC2, 0xB2, 0x00, 0x00}, '2'},
	{ 0xB3, {0xC2, 0xB3, 0x00, 0x00}, '3'},
	{ 0xB4, {0xC2, 0xB4, 0x00, 0x00}, ' '},
	{ 0xB5, {0xC2, 0xB5, 0x00, 0x00}, 'u'},
	{ 0xB6, {0xC2, 0xB6, 0x00, 0x00}, 'P'},
	{ 0xB7, {0xC2, 0xB7, 0x00, 0x00}, '.'},
	{ 0xB8, {0xC2, 0xB8, 0x00, 0x00}, ','},
	{ 0xB9, {0xC2, 0xB9, 0x00, 0x00}, '1'},
	{ 0xBA, {0xC2, 0xBA, 0x00, 0x00}, '0'},
	{ 0xBB, {0xC2, 0xBB, 0x00, 0x00}, '>'},
	{ 0xBC, {0xC2, 0xBC, 0x00, 0x00}, '4'},
	{ 0xBD, {0xC2, 0xBD, 0x00, 0x00}, '2'},
	{ 0xBE, {0xC2, 0xBE, 0x00, 0x00}, '4'},
	{ 0xBF, {0xC2, 0xBF, 0x00, 0x00}, '?'},
	{ 0xC0, {0xC3, 0x80, 0x00, 0x00}, 'A'},
	{ 0xC1, {0xC3, 0x81, 0x00, 0x00}, 'A'},
	{ 0xC2, {0xC3, 0x82, 0x00, 0x00}, 'A'},
	{ 0xC3, {0xC3, 0x83, 0x00, 0x00}, 'A'},
	{ 0xC4, {0xC3, 0x84, 0x00, 0x00}, 'A'},
	{ 0xC5, {0xC3, 0x85, 0x00, 0x00}, 'A'},
	{ 0xC6, {0xC3, 0x86, 0x00, 0x00}, 'A'},
	{ 0xC7, {0xC3, 0x87, 0x00, 0x00}, 'C'},
	{ 0xC8, {0xC3, 0x88, 0x00, 0x00}, 'E'},
	{ 0xC9, {0xC3, 0x89, 0x00, 0x00}, 'E'},
	{ 0xCA, {0xC3, 0x8A, 0x00, 0x00}, 'E'},
	{ 0xCB, {0xC3, 0x8B, 0x00, 0x00}, 'E'},
	{ 0xCC, {0xC3, 0x8C, 0x00, 0x00}, 'I'},
	{ 0xCD, {0xC3, 0x8D, 0x00, 0x00}, 'I'},
	{ 0xCE, {0xC3, 0x8E, 0x00, 0x00}, 'I'},
	{ 0xCF, {0xC3, 0x8F, 0x00, 0x00}, 'I'},
	{ 0xD0, {0xC3, 0x90, 0x00, 0x00}, 'D'},
	{ 0xD1, {0xC3, 0x91, 0x00, 0x00}, 'N'},
	{ 0xD2, {0xC3, 0x92, 0x00, 0x00}, 'O'},
	{ 0xD3, {0xC3, 0x93, 0x00, 0x00}, 'O'},
	{ 0xD4, {0xC3, 0x94, 0x00, 0x00}, 'O'},
	{ 0xD5, {0xC3, 0x95, 0x00, 0x00}, 'O'},
	{ 0xD6, {0xC3, 0x96, 0x00, 0x00}, 'O'},
	{ 0xD7, {0xC3, 0x97, 0x00, 0x00}, 'X'},
	{ 0xD8, {0xC3, 0x98, 0x00, 0x00}, 'O'},
	{ 0xD9, {0xC3, 0x99, 0x00, 0x00}, 'U'},
	{ 0xDA, {0xC3, 0x9A, 0x00, 0x00}, 'U'},
	{ 0xDB, {0xC3, 0x9B, 0x00, 0x00}, 'U'},
	{ 0xDC, {0xC3, 0x9C, 0x00, 0x00}, 'U'},
	{ 0xDD, {0xC3, 0x9D, 0x00, 0x00}, 'Y'},
	{ 0xDE, {0xC3, 0x9E, 0x00, 0x00}, 'b'},
	{ 0xDF, {0xC3, 0x9F, 0x00, 0x00}, 'S'},
	{ 0xE0, {0xC3, 0xA0, 0x00, 0x00}, 'a'},
	{ 0xE1, {0xC3, 0xA1, 0x00, 0x00}, 'a'},
	{ 0xE2, {0xC3, 0xA2, 0x00, 0x00}, 'a'},
	{ 0xE3, {0xC3, 0xA3, 0x00, 0x00}, 'a'},
	{ 0xE4, {0xC3, 0xA4, 0x00, 0x00}, 'a'},
	{ 0xE5, {0xC3, 0xA5, 0x00, 0x00}, 'a'},
	{ 0xE6, {0xC3, 0xA6, 0x00, 0x00}, 'a'},
	{ 0xE7, {0xC3, 0xA7, 0x00, 0x00}, 'c'},
	{ 0xE8, {0xC3, 0xA8, 0x00, 0x00}, 'e'},
	{ 0xE9, {0xC3, 0xA9, 0x00, 0x00}, 'e'},
	{ 0xEA, {0xC3, 0xAA, 0x00, 0x00}, 'e'},
	{ 0xEB, {0xC3, 0xAB, 0x00, 0x00}, 'e'},
	{ 0xEC, {0xC3, 0xAC, 0x00, 0x00}, 'i'},
	{ 0xED, {0xC3, 0xAD, 0x00, 0x00}, 'i'},
	{ 0xEE, {0xC3, 0xAE, 0x00, 0x00}, 'i'},
	{ 0xEF, {0xC3, 0xAF, 0x00, 0x00}, 'i'},
	{ 0xF0, {0xC3, 0xB0, 0x00, 0x00}, 'd'},
	{ 0xF1, {0xC3, 0xB1, 0x00, 0x00}, 'n'},
	{ 0xF2, {0xC3, 0xB2, 0x00, 0x00}, 'o'},
	{ 0xF3, {0xC3, 0xB3, 0x00, 0x00}, 'o'},
	{ 0xF4, {0xC3, 0xB4, 0x00, 0x00}, 'o'},
	{ 0xF5, {0xC3, 0xB5, 0x00, 0x00}, 'o'},
	{ 0xF6, {0xC3, 0xB6, 0x00, 0x00}, 'o'},
	{ 0xF7, {0xC3, 0xB7, 0x00, 0x00}, '/'},
	{ 0xF8, {0xC3, 0xB8, 0x00, 0x00}, 'o'},
	{ 0xF9, {0xC3, 0xB9, 0x00, 0x00}, 'u'},
	{ 0xFA, {0xC3, 0xBA, 0x00, 0x00}, 'u'},
	{ 0xFB, {0xC3, 0xBB, 0x00, 0x00}, 'u'},
	{ 0xFC, {0xC3, 0xBC, 0x00, 0x00}, 'u'},
	{ 0xFD, {0xC3, 0xBD, 0x00, 0x00}, 'y'},
	{ 0xFE, {0xC3, 0xBE, 0x00, 0x00}, 'b'},
	{ 0xFF, {0xC3, 0xBF, 0x00, 0x00}, 'y'},

	{ 0x0100, {0xC4, 0x80, 0x00, 0x00}, 'A'},
	{ 0x0101, {0xC4, 0x81, 0x00, 0x00}, 'a'},
	{ 0x0102, {0xC4, 0x82, 0x00, 0x00}, 'A'},
	{ 0x0103, {0xC4, 0x83, 0x00, 0x00}, 'a'},
	{ 0x0104, {0xC4, 0x84, 0x00, 0x00}, 'A'},
	{ 0x0105, {0xC4, 0x85, 0x00, 0x00}, 'a'},
	{ 0x0106, {0xC4, 0x86, 0x00, 0x00}, 'C'},
	{ 0x0107, {0xC4, 0x87, 0x00, 0x00}, 'c'},
	{ 0x0108, {0xC4, 0x88, 0x00, 0x00}, 'C'},
	{ 0x0109, {0xC4, 0x89, 0x00, 0x00}, 'c'},
	{ 0x010A, {0xC4, 0x8A, 0x00, 0x00}, 'C'},
	{ 0x010B, {0xC4, 0x8B, 0x00, 0x00}, 'c'},
	{ 0x010C, {0xC4, 0x8C, 0x00, 0x00}, 'C'},
	{ 0x010D, {0xC4, 0x8D, 0x00, 0x00}, 'c'},
	{ 0x010E, {0xC4, 0x8E, 0x00, 0x00}, 'D'},
	{ 0x010F, {0xC4, 0x8F, 0x00, 0x00}, 'd'},
	{ 0x0110, {0xC4, 0x90, 0x00, 0x00}, 'D'},
	{ 0x0111, {0xC4, 0x91, 0x00, 0x00}, 'd'},
	{ 0x0112, {0xC4, 0x92, 0x00, 0x00}, 'E'},
	{ 0x0113, {0xC4, 0x93, 0x00, 0x00}, 'e'},
	{ 0x0114, {0xC4, 0x94, 0x00, 0x00}, 'E'},
	{ 0x0115, {0xC4, 0x95, 0x00, 0x00}, 'e'},
	{ 0x0116, {0xC4, 0x96, 0x00, 0x00}, 'E'},
	{ 0x0117, {0xC4, 0x97, 0x00, 0x00}, 'e'},
	{ 0x0118, {0xC4, 0x98, 0x00, 0x00}, 'E'},
	{ 0x0119, {0xC4, 0x99, 0x00, 0x00}, 'e'},
	{ 0x011A, {0xC4, 0x9A, 0x00, 0x00}, 'E'},
	{ 0x011B, {0xC4, 0x9B, 0x00, 0x00}, 'e'},
	{ 0x011C, {0xC4, 0x9C, 0x00, 0x00}, 'G'},
	{ 0x011D, {0xC4, 0x9D, 0x00, 0x00}, 'g'},
	{ 0x011E, {0xC4, 0x9E, 0x00, 0x00}, 'G'},
	{ 0x011F, {0xC4, 0x9F, 0x00, 0x00}, 'g'},
	{ 0x0120, {0xC4, 0xA0, 0x00, 0x00}, 'G'},
	{ 0x0121, {0xC4, 0xA1, 0x00, 0x00}, 'g'},
	{ 0x0122, {0xC4, 0xA2, 0x00, 0x00}, 'G'},
	{ 0x0123, {0xC4, 0xA3, 0x00, 0x00}, 'g'},
	{ 0x0124, {0xC4, 0xA4, 0x00, 0x00}, 'H'},
	{ 0x0125, {0xC4, 0xA5, 0x00, 0x00}, 'h'},
	{ 0x0126, {0xC4, 0xA6, 0x00, 0x00}, 'H'},
	{ 0x0127, {0xC4, 0xA7, 0x00, 0x00}, 'h'},
	{ 0x0128, {0xC4, 0xA8, 0x00, 0x00}, 'I'},
	{ 0x0129, {0xC4, 0xA9, 0x00, 0x00}, 'i'},
	{ 0x012A, {0xC4, 0xAA, 0x00, 0x00}, 'I'},
	{ 0x012B, {0xC4, 0xAB, 0x00, 0x00}, 'i'},
	{ 0x012C, {0xC4, 0xAC, 0x00, 0x00}, 'I'},
	{ 0x012D, {0xC4, 0xAD, 0x00, 0x00}, 'i'},
	{ 0x012E, {0xC4, 0xAE, 0x00, 0x00}, 'I'},
	{ 0x012F, {0xC4, 0xAF, 0x00, 0x00}, 'i'},
	{ 0x0130, {0xC4, 0xB0, 0x00, 0x00}, 'I'},
	{ 0x0131, {0xC4, 0xB1, 0x00, 0x00}, 'i'},
	{ 0x0132, {0xC4, 0xB2, 0x00, 0x00}, 'I'},
	{ 0x0133, {0xC4, 0xB3, 0x00, 0x00}, 'i'},
	{ 0x0134, {0xC4, 0xB4, 0x00, 0x00}, 'J'},
	{ 0x0135, {0xC4, 0xB5, 0x00, 0x00}, 'j'},
	{ 0x0136, {0xC4, 0xB6, 0x00, 0x00}, 'K'},
	{ 0x0137, {0xC4, 0xB7, 0x00, 0x00}, 'k'},
	{ 0x0138, {0xC4, 0xB8, 0x00, 0x00}, 'k'},
	{ 0x0139, {0xC4, 0xB9, 0x00, 0x00}, 'L'},
	{ 0x013A, {0xC4, 0xBA, 0x00, 0x00}, 'l'},
	{ 0x013B, {0xC4, 0xBB, 0x00, 0x00}, 'L'},
	{ 0x013C, {0xC4, 0xBC, 0x00, 0x00}, 'l'},
	{ 0x013D, {0xC4, 0xBD, 0x00, 0x00}, 'L'},
	{ 0x013E, {0xC4, 0xBE, 0x00, 0x00}, 'l'},
	{ 0x013F, {0xC4, 0xBF, 0x00, 0x00}, 'L'},

	{ 0x0140, {0xC5, 0x80, 0x00, 0x00}, 'l'},
	{ 0x0141, {0xC5, 0x81, 0x00, 0x00}, 'L'},
	{ 0x0142, {0xC5, 0x82, 0x00, 0x00}, 'l'},
	{ 0x0143, {0xC5, 0x83, 0x00, 0x00}, 'N'},
	{ 0x0144, {0xC5, 0x84, 0x00, 0x00}, 'n'},
	{ 0x0145, {0xC5, 0x85, 0x00, 0x00}, 'N'},
	{ 0x0146, {0xC5, 0x86, 0x00, 0x00}, 'n'},
	{ 0x0147, {0xC5, 0x87, 0x00, 0x00}, 'N'},
	{ 0x0148, {0xC5, 0x88, 0x00, 0x00}, 'n'},
	{ 0x0149, {0xC5, 0x89, 0x00, 0x00}, 'n'},
	{ 0x014A, {0xC5, 0x8A, 0x00, 0x00}, 'N'},
	{ 0x014B, {0xC5, 0x8B, 0x00, 0x00}, 'n'},
	{ 0x014C, {0xC5, 0x8C, 0x00, 0x00}, 'O'},
	{ 0x014D, {0xC5, 0x8D, 0x00, 0x00}, 'o'},
	{ 0x014E, {0xC5, 0x8E, 0x00, 0x00}, 'O'},
	{ 0x014F, {0xC5, 0x8F, 0x00, 0x00}, 'o'},
	{ 0x0150, {0xC5, 0x90, 0x00, 0x00}, 'O'},
	{ 0x0151, {0xC5, 0x91, 0x00, 0x00}, 'o'},
	{ 0x0152, {0xC5, 0x92, 0x00, 0x00}, 'O'},
	{ 0x0153, {0xC5, 0x93, 0x00, 0x00}, 'o'},
	{ 0x0154, {0xC5, 0x94, 0x00, 0x00}, 'R'},
	{ 0x0155, {0xC5, 0x95, 0x00, 0x00}, 'r'},
	{ 0x0156, {0xC5, 0x96, 0x00, 0x00}, 'R'},
	{ 0x0157, {0xC5, 0x97, 0x00, 0x00}, 'r'},
	{ 0x0158, {0xC5, 0x98, 0x00, 0x00}, 'R'},
	{ 0x0159, {0xC5, 0x99, 0x00, 0x00}, 'r'},
	{ 0x015A, {0xC5, 0x9A, 0x00, 0x00}, 'S'},
	{ 0x015B, {0xC5, 0x9B, 0x00, 0x00}, 's'},
	{ 0x015C, {0xC5, 0x9C, 0x00, 0x00}, 'S'},
	{ 0x015D, {0xC5, 0x9D, 0x00, 0x00}, 's'},
	{ 0x015E, {0xC5, 0x9E, 0x00, 0x00}, 'S'},
	{ 0x015F, {0xC5, 0x9F, 0x00, 0x00}, 's'},
	{ 0x0160, {0xC5, 0xA0, 0x00, 0x00}, 'S'},
	{ 0x0161, {0xC5, 0xA1, 0x00, 0x00}, 's'},
	{ 0x0162, {0xC5, 0xA2, 0x00, 0x00}, 'T'},
	{ 0x0163, {0xC5, 0xA3, 0x00, 0x00}, 't'},
	{ 0x0164, {0xC5, 0xA4, 0x00, 0x00}, 'T'},
	{ 0x0165, {0xC5, 0xA5, 0x00, 0x00}, 't'},
	{ 0x0166, {0xC5, 0xA6, 0x00, 0x00}, 'T'},
	{ 0x0167, {0xC5, 0xA7, 0x00, 0x00}, 't'},
	{ 0x0168, {0xC5, 0xA8, 0x00, 0x00}, 'U'},
	{ 0x0169, {0xC5, 0xA9, 0x00, 0x00}, 'u'},
	{ 0x016A, {0xC5, 0xAA, 0x00, 0x00}, 'U'},
	{ 0x016B, {0xC5, 0xAB, 0x00, 0x00}, 'u'},
	{ 0x016C, {0xC5, 0xAC, 0x00, 0x00}, 'U'},
	{ 0x016D, {0xC5, 0xAD, 0x00, 0x00}, 'u'},
	{ 0x016E, {0xC5, 0xAE, 0x00, 0x00}, 'U'},
	{ 0x016F, {0xC5, 0xAF, 0x00, 0x00}, 'u'},
	{ 0x0170, {0xC5, 0xB0, 0x00, 0x00}, 'U'},
	{ 0x0171, {0xC5, 0xB1, 0x00, 0x00}, 'u'},
	{ 0x0172, {0xC5, 0xB2, 0x00, 0x00}, 'U'},
	{ 0x0173, {0xC5, 0xB3, 0x00, 0x00}, 'u'},
	{ 0x0174, {0xC5, 0xB4, 0x00, 0x00}, 'W'},
	{ 0x0175, {0xC5, 0xB5, 0x00, 0x00}, 'w'},
	{ 0x0176, {0xC5, 0xB6, 0x00, 0x00}, 'Y'},
	{ 0x0177, {0xC5, 0xB7, 0x00, 0x00}, 'y'},
	{ 0x0178, {0xC5, 0xB8, 0x00, 0x00}, 'Y'},
	{ 0x0179, {0xC5, 0xB9, 0x00, 0x00}, 'Z'},
	{ 0x017A, {0xC5, 0xBA, 0x00, 0x00}, 'z'},
	{ 0x017B, {0xC5, 0xBB, 0x00, 0x00}, 'Z'},
	{ 0x017C, {0xC5, 0xBC, 0x00, 0x00}, 'z'},
	{ 0x017D, {0xC5, 0xBD, 0x00, 0x00}, 'Z'},
	{ 0x017E, {0xC5, 0xBE, 0x00, 0x00}, 'z'},
	{ 0x017F, {0xC5, 0xBF, 0x00, 0x00}, 'S'},

	{ 0x018F, {0xC6, 0x8F, 0x00, 0x00}, 'e'},
	{ 0x0192, {0xC6, 0x92, 0x00, 0x00}, 'f'},
	{ 0x01A0, {0xC6, 0xA0, 0x00, 0x00}, 'O'},
	{ 0x01A1, {0xC6, 0xA1, 0x00, 0x00}, 'o'},
	{ 0x01AF, {0xC6, 0xAF, 0x00, 0x00}, 'U'},
	{ 0x01B0, {0xC6, 0xB0, 0x00, 0x00}, 'u'},

	{ 0x01CD, {0xC7, 0x8D, 0x00, 0x00}, 'A'},
	{ 0x01CE, {0xC7, 0x8E, 0x00, 0x00}, 'a'},
	{ 0x01CF, {0xC7, 0x8F, 0x00, 0x00}, 'I'},
	{ 0x01D0, {0xC7, 0x90, 0x00, 0x00}, 'i'},
	{ 0x01D1, {0xC7, 0x91, 0x00, 0x00}, 'O'},
	{ 0x01D2, {0xC7, 0x92, 0x00, 0x00}, 'o'},
	{ 0x01D3, {0xC7, 0x93, 0x00, 0x00}, 'U'},
	{ 0x01D4, {0xC7, 0x94, 0x00, 0x00}, 'u'},
	{ 0x01D5, {0xC7, 0x95, 0x00, 0x00}, 'U'},
	{ 0x01D6, {0xC7, 0x96, 0x00, 0x00}, 'u'},
	{ 0x01D7, {0xC7, 0x97, 0x00, 0x00}, 'U'},
	{ 0x01D8, {0xC7, 0x98, 0x00, 0x00}, 'u'},
	{ 0x01D9, {0xC7, 0x99, 0x00, 0x00}, 'U'},
	{ 0x01DA, {0xC7, 0x9A, 0x00, 0x00}, 'u'},
	{ 0x01DB, {0xC7, 0x9B, 0x00, 0x00}, 'U'},
	{ 0x01DC, {0xC7, 0x9C, 0x00, 0x00}, 'u'},

	{ 0x01FA, {0xC7, 0xBA, 0x00, 0x00}, 'A'},
	{ 0x01FB, {0xC7, 0xBB, 0x00, 0x00}, 'a'},
	{ 0x01FC, {0xC7, 0xBC, 0x00, 0x00}, 'A'},
	{ 0x01FD, {0xC7, 0xBD, 0x00, 0x00}, 'a'},
	{ 0x01FE, {0xC7, 0xBE, 0x00, 0x00}, 'O'},
	{ 0x01FF, {0xC7, 0xBF, 0x00, 0x00}, 'o'},

	{ 0x0259, {0xC9, 0x99, 0x00, 0x00}, 'e'},

	{ 0x02C9, {0xCB, 0x89, 0x00, 0x00}, '-'},
	{ 0x02DA, {0xCB, 0x9A, 0x00, 0x00}, '*'},
	{ 0x02DC, {0xCB, 0x9C, 0x00, 0x00}, '\"'},
	{ 0x02DD, {0xCB, 0x9D, 0x00, 0x00}, '\"'},

	{ 0x0300, {0xCC, 0x80, 0x00, 0x00}, '\''},
	{ 0x0301, {0xCC, 0x81, 0x00, 0x00}, '\''},
	{ 0x0303, {0xCC, 0x83, 0x00, 0x00}, '\"'},
	{ 0x0323, {0xCC, 0xA3, 0x00, 0x00}, '.'},

	{ 0x037E, {0xCD, 0xBE, 0x00, 0x00}, ';'},

	{ 0x0384, {0xCE, 0x84, 0x00, 0x00}, '\''},
	{ 0x0386, {0xCE, 0x86, 0x00, 0x00}, 'A'},
	{ 0x0387, {0xCE, 0x87, 0x00, 0x00}, '.'},
	{ 0x0388, {0xCE, 0x88, 0x00, 0x00}, 'E'},
	{ 0x0389, {0xCE, 0x89, 0x00, 0x00}, 'G'},
	{ 0x038A, {0xCE, 0x8A, 0x00, 0x00}, 'I'},
	{ 0x038C, {0xCE, 0x8C, 0x00, 0x00}, 'O'},
	{ 0x038E, {0xCE, 0x8E, 0x00, 0x00}, 'Y'},
	{ 0x038F, {0xCE, 0x8F, 0x00, 0x00}, 'O'},
	{ 0x0390, {0xCE, 0x90, 0x00, 0x00}, 'i'},

	{ 0x0391, {0xCE, 0x91, 0x00, 0x00}, 'A'},
	{ 0x0392, {0xCE, 0x92, 0x00, 0x00}, 'B'},
	{ 0x0393, {0xCE, 0x93, 0x00, 0x00}, 'G'},
	{ 0x0394, {0xCE, 0x94, 0x00, 0x00}, 'D'},
	{ 0x0395, {0xCE, 0x95, 0x00, 0x00}, 'E'},
	{ 0x0396, {0xCE, 0x96, 0x00, 0x00}, 'Z'},
	{ 0x0397, {0xCE, 0x97, 0x00, 0x00}, 'H'},
	{ 0x0398, {0xCE, 0x98, 0x00, 0x00}, 'T'},
	{ 0x0399, {0xCE, 0x99, 0x00, 0x00}, 'I'},
	{ 0x039A, {0xCE, 0x9A, 0x00, 0x00}, 'K'},
	{ 0x039B, {0xCE, 0x9B, 0x00, 0x00}, 'L'},
	{ 0x039C, {0xCE, 0x9C, 0x00, 0x00}, 'M'},
	{ 0x039D, {0xCE, 0x9D, 0x00, 0x00}, 'N'},
	{ 0x039E, {0xCE, 0x9E, 0x00, 0x00}, 'X'},
	{ 0x039F, {0xCE, 0x9F, 0x00, 0x00}, 'O'},
	{ 0x03A0, {0xCE, 0xA0, 0x00, 0x00}, 'P'},
	{ 0x03A1, {0xCE, 0xA1, 0x00, 0x00}, 'R'},
	{ 0x03A3, {0xCE, 0xA3, 0x00, 0x00}, 'S'},
	{ 0x03A4, {0xCE, 0xA4, 0x00, 0x00}, 'T'},
	{ 0x03A5, {0xCE, 0xA5, 0x00, 0x00}, 'Y'},
	{ 0x03A6, {0xCE, 0xA6, 0x00, 0x00}, 'F'},
	{ 0x03A7, {0xCE, 0xA7, 0x00, 0x00}, 'C'},
	{ 0x03A8, {0xCE, 0xA8, 0x00, 0x00}, 'P'},
	{ 0x03A9, {0xCE, 0xA9, 0x00, 0x00}, 'W'},
	{ 0x03AA, {0xCE, 0xAA, 0x00, 0x00}, 'I'},
	{ 0x03AB, {0xCE, 0xAB, 0x00, 0x00}, 'Y'},
	{ 0x03AC, {0xCE, 0xAC, 0x00, 0x00}, 'a'},
	{ 0x03AD, {0xCE, 0xAD, 0x00, 0x00}, 'e'},
	{ 0x03AE, {0xCE, 0xAE, 0x00, 0x00}, 'h'},
	{ 0x03AF, {0xCE, 0xAF, 0x00, 0x00}, 'i'},
	{ 0x03B0, {0xCE, 0xB0, 0x00, 0x00}, 'y'},
	{ 0x03B1, {0xCE, 0xB1, 0x00, 0x00}, 'I'},
	{ 0x03B2, {0xCE, 0xB2, 0x00, 0x00}, 'a'},
	{ 0x03B3, {0xCE, 0xB3, 0x00, 0x00}, 'b'},
	{ 0x03B4, {0xCE, 0xB4, 0x00, 0x00}, 'g'},
	{ 0x03B5, {0xCE, 0xB5, 0x00, 0x00}, 'd'},
	{ 0x03B6, {0xCE, 0xB6, 0x00, 0x00}, 'e'},
	{ 0x03B7, {0xCE, 0xB7, 0x00, 0x00}, 'z'},
	{ 0x03B8, {0xCE, 0xB8, 0x00, 0x00}, 'h'},
	{ 0x03B9, {0xCE, 0xB9, 0x00, 0x00}, 't'},
	{ 0x03BA, {0xCE, 0xBA, 0x00, 0x00}, 'i'},
	{ 0x03BB, {0xCE, 0xBB, 0x00, 0x00}, 'k'},
	{ 0x03BC, {0xCE, 0xBC, 0x00, 0x00}, 'l'},
	{ 0x03BD, {0xCE, 0xBD, 0x00, 0x00}, 'm'},
	{ 0x03BE, {0xCE, 0xBE, 0x00, 0x00}, 'n'},
	{ 0x03BF, {0xCE, 0xBF, 0x00, 0x00}, 'x'},

	{ 0x03C0, {0xCF, 0x80, 0x00, 0x00}, 'o'},
	{ 0x03C1, {0xCF, 0x81, 0x00, 0x00}, 'p'},
	{ 0x03C2, {0xCF, 0x82, 0x00, 0x00}, 'r'},
	{ 0x03C3, {0xCF, 0x83, 0x00, 0x00}, 's'},
	{ 0x03C4, {0xCF, 0x84, 0x00, 0x00}, 't'},
	{ 0x03C5, {0xCF, 0x85, 0x00, 0x00}, 'y'},
	{ 0x03C6, {0xCF, 0x86, 0x00, 0x00}, 'f'},
	{ 0x03C7, {0xCF, 0x87, 0x00, 0x00}, 'c'},
	{ 0x03C8, {0xCF, 0x88, 0x00, 0x00}, 'p'},
	{ 0x03C9, {0xCF, 0x89, 0x00, 0x00}, 'w'},
	{ 0x03CA, {0xCF, 0x8A, 0x00, 0x00}, 'i'},
	{ 0x03CB, {0xCF, 0x8B, 0x00, 0x00}, 'y'},
	{ 0x03CC, {0xCF, 0x8C, 0x00, 0x00}, 'o'},
	{ 0x03CD, {0xCF, 0x8D, 0x00, 0x00}, 'y'},
	{ 0x03CE, {0xCF, 0x8E, 0x00, 0x00}, 'w'},

	// TODO: finish cyrilic
	{ 0x0401, {0xD0, 0x81, 0x00, 0x00}, 'E'},
	{ 0x0404, {0xD0, 0x84, 0x00, 0x00}, 'E'},
	{ 0x0405, {0xD0, 0x85, 0x00, 0x00}, 'S'},
	{ 0x0406, {0xD0, 0x86, 0x00, 0x00}, 'I'},
	{ 0x0407, {0xD0, 0x87, 0x00, 0x00}, 'I'},
	{ 0x0408, {0xD0, 0x88, 0x00, 0x00}, 'J'},
	{ 0x040C, {0xD0, 0x8C, 0x00, 0x00}, 'K'},
	{ 0x040E, {0xD0, 0x8E, 0x00, 0x00}, 'Y'},
	{ 0x0425, {0xD0, 0xA5, 0x00, 0x00}, 'X'},
	{ 0x042C, {0xD0, 0xAC, 0x00, 0x00}, 'b'},
	{ 0x0430, {0xD0, 0xB0, 0x00, 0x00}, 'a'},
	{ 0x0432, {0xD0, 0xB2, 0x00, 0x00}, 'v'},
	{ 0x0435, {0xD0, 0xB5, 0x00, 0x00}, 'e'},
	{ 0x043A, {0xD0, 0xBA, 0x00, 0x00}, 'k'},
	{ 0x043C, {0xD0, 0xBC, 0x00, 0x00}, 'm'},

	// TODO: hebrew

	{ 0x1E80, {0xE1, 0xBA, 0x80, 0x00}, 'W'},
	{ 0x1E81, {0xE1, 0xBA, 0x81, 0x00}, 'w'},
	{ 0x1E82, {0xE1, 0xBA, 0x82, 0x00}, 'W'},
	{ 0x1E83, {0xE1, 0xBA, 0x83, 0x00}, 'w'},
	{ 0x1E84, {0xE1, 0xBA, 0x84, 0x00}, 'W'},
	{ 0x1E85, {0xE1, 0xBA, 0x85, 0x00}, 'w'},
	{ 0x1EA0, {0xE1, 0xBA, 0xA0, 0x00}, 'A'},
	{ 0x1EA1, {0xE1, 0xBA, 0xA1, 0x00}, 'a'},
	{ 0x1EA2, {0xE1, 0xBA, 0xA2, 0x00}, 'A'},
	{ 0x1EA3, {0xE1, 0xBA, 0xA3, 0x00}, 'a'},
	{ 0x1EA4, {0xE1, 0xBA, 0xA4, 0x00}, 'A'},
	{ 0x1EA5, {0xE1, 0xBA, 0xA5, 0x00}, 'a'},
	{ 0x1EA6, {0xE1, 0xBA, 0xA6, 0x00}, 'A'},
	{ 0x1EA7, {0xE1, 0xBA, 0xA7, 0x00}, 'a'},
	{ 0x1EA8, {0xE1, 0xBA, 0xA8, 0x00}, 'A'},
	{ 0x1EA9, {0xE1, 0xBA, 0xA9, 0x00}, 'a'},
	{ 0x1EAA, {0xE1, 0xBA, 0xAA, 0x00}, 'A'},
	{ 0x1EAB, {0xE1, 0xBA, 0xAB, 0x00}, 'a'},
	{ 0x1EAC, {0xE1, 0xBA, 0xAC, 0x00}, 'A'},
	{ 0x1EAD, {0xE1, 0xBA, 0xAD, 0x00}, 'a'},
	{ 0x1EAE, {0xE1, 0xBA, 0xAE, 0x00}, 'A'},
	{ 0x1EAF, {0xE1, 0xBA, 0xAF, 0x00}, 'a'},
	{ 0x1EB0, {0xE1, 0xBA, 0xB0, 0x00}, 'A'},
	{ 0x1EB1, {0xE1, 0xBA, 0xB1, 0x00}, 'a'},
	{ 0x1EB2, {0xE1, 0xBA, 0xB2, 0x00}, 'A'},
	{ 0x1EB3, {0xE1, 0xBA, 0xB3, 0x00}, 'a'},
	{ 0x1EB4, {0xE1, 0xBA, 0xB4, 0x00}, 'A'},
	{ 0x1EB5, {0xE1, 0xBA, 0xB5, 0x00}, 'a'},
	{ 0x1EB6, {0xE1, 0xBA, 0xB6, 0x00}, 'A'},
	{ 0x1EB7, {0xE1, 0xBA, 0xB7, 0x00}, 'a'},
	{ 0x1EB8, {0xE1, 0xBA, 0xB8, 0x00}, 'E'},
	{ 0x1EB8, {0xE1, 0xBA, 0xB9, 0x00}, 'e'},
	{ 0x1EBA, {0xE1, 0xBA, 0xBA, 0x00}, 'E'},
	{ 0x1EBB, {0xE1, 0xBA, 0xBB, 0x00}, 'e'},
	{ 0x1EBC, {0xE1, 0xBA, 0xBC, 0x00}, 'E'},
	{ 0x1EBD, {0xE1, 0xBA, 0xBD, 0x00}, 'e'},
	{ 0x1EBE, {0xE1, 0xBA, 0xBE, 0x00}, 'E'},
	{ 0x1EBF, {0xE1, 0xBA, 0xBF, 0x00}, 'e'},

	{ 0x1EC0, {0xE1, 0xBB, 0x80, 0x00}, 'E'},
	{ 0x1EC1, {0xE1, 0xBB, 0x81, 0x00}, 'e'},
	{ 0x1EC2, {0xE1, 0xBB, 0x82, 0x00}, 'E'},
	{ 0x1EC3, {0xE1, 0xBB, 0x83, 0x00}, 'e'},
	{ 0x1EC4, {0xE1, 0xBB, 0x84, 0x00}, 'E'},
	{ 0x1EC5, {0xE1, 0xBB, 0x85, 0x00}, 'e'},
	{ 0x1EC6, {0xE1, 0xBB, 0x86, 0x00}, 'E'},
	{ 0x1EC7, {0xE1, 0xBB, 0x87, 0x00}, 'e'},
	{ 0x1EC8, {0xE1, 0xBB, 0x88, 0x00}, 'I'},
	{ 0x1EC9, {0xE1, 0xBB, 0x89, 0x00}, 'i'},
	{ 0x1ECA, {0xE1, 0xBB, 0x8A, 0x00}, 'I'},
	{ 0x1ECB, {0xE1, 0xBB, 0x8B, 0x00}, 'i'},
	{ 0x1ECC, {0xE1, 0xBB, 0x8C, 0x00}, 'O'},
	{ 0x1ECD, {0xE1, 0xBB, 0x8D, 0x00}, 'o'},
	{ 0x1ECE, {0xE1, 0xBB, 0x8E, 0x00}, 'O'},
	{ 0x1ECF, {0xE1, 0xBB, 0x8F, 0x00}, 'o'},
	{ 0x1ED0, {0xE1, 0xBB, 0x90, 0x00}, 'O'},
	{ 0x1ED1, {0xE1, 0xBB, 0x91, 0x00}, 'o'},
	{ 0x1ED2, {0xE1, 0xBB, 0x92, 0x00}, 'O'},
	{ 0x1ED3, {0xE1, 0xBB, 0x93, 0x00}, 'o'},
	{ 0x1ED4, {0xE1, 0xBB, 0x94, 0x00}, 'O'},
	{ 0x1ED5, {0xE1, 0xBB, 0x95, 0x00}, 'o'},
	{ 0x1ED6, {0xE1, 0xBB, 0x96, 0x00}, 'O'},
	{ 0x1ED7, {0xE1, 0xBB, 0x97, 0x00}, 'o'},
	{ 0x1ED8, {0xE1, 0xBB, 0x98, 0x00}, 'O'},
	{ 0x1ED9, {0xE1, 0xBB, 0x99, 0x00}, 'o'},
	{ 0x1EDA, {0xE1, 0xBB, 0x9A, 0x00}, 'O'},
	{ 0x1EDB, {0xE1, 0xBB, 0x9B, 0x00}, 'o'},
	{ 0x1EDC, {0xE1, 0xBB, 0x9C, 0x00}, 'O'},
	{ 0x1EDD, {0xE1, 0xBB, 0x9D, 0x00}, 'o'},
	{ 0x1EDE, {0xE1, 0xBB, 0x9E, 0x00}, 'O'},
	{ 0x1EDF, {0xE1, 0xBB, 0x9F, 0x00}, 'o'},
	{ 0x1EE0, {0xE1, 0xBB, 0xA0, 0x00}, 'O'},
	{ 0x1EE1, {0xE1, 0xBB, 0xA1, 0x00}, 'o'},
	{ 0x1EE2, {0xE1, 0xBB, 0xA2, 0x00}, 'O'},
	{ 0x1EE3, {0xE1, 0xBB, 0xA3, 0x00}, 'o'},
	{ 0x1EE4, {0xE1, 0xBB, 0xA4, 0x00}, 'U'},
	{ 0x1EE5, {0xE1, 0xBB, 0xA5, 0x00}, 'u'},
	{ 0x1EE6, {0xE1, 0xBB, 0xA6, 0x00}, 'U'},
	{ 0x1EE7, {0xE1, 0xBB, 0xA7, 0x00}, 'u'},
	{ 0x1EE8, {0xE1, 0xBB, 0xA8, 0x00}, 'U'},
	{ 0x1EE9, {0xE1, 0xBB, 0xA9, 0x00}, 'u'},
	{ 0x1EEA, {0xE1, 0xBB, 0xAA, 0x00}, 'U'},
	{ 0x1EEB, {0xE1, 0xBB, 0xAB, 0x00}, 'u'},
	{ 0x1EEC, {0xE1, 0xBB, 0xAC, 0x00}, 'U'},
	{ 0x1EED, {0xE1, 0xBB, 0xAD, 0x00}, 'u'},
	{ 0x1EEE, {0xE1, 0xBB, 0xAE, 0x00}, 'U'},
	{ 0x1EEF, {0xE1, 0xBB, 0xAF, 0x00}, 'u'},
	{ 0x1EF0, {0xE1, 0xBB, 0xB0, 0x00}, 'U'},
	{ 0x1EF1, {0xE1, 0xBB, 0xB1, 0x00}, 'u'},
	{ 0x1EF2, {0xE1, 0xBB, 0xB2, 0x00}, 'Y'},
	{ 0x1EF3, {0xE1, 0xBB, 0xB3, 0x00}, 'y'},
	{ 0x1EF4, {0xE1, 0xBB, 0xB4, 0x00}, 'Y'},
	{ 0x1EF5, {0xE1, 0xBB, 0xB5, 0x00}, 'y'},
	{ 0x1EF6, {0xE1, 0xBB, 0xB6, 0x00}, 'Y'},
	{ 0x1EF7, {0xE1, 0xBB, 0xB7, 0x00}, 'y'},
	{ 0x1EF8, {0xE1, 0xBB, 0xB8, 0x00}, 'Y'},
	{ 0x1EF9, {0xE1, 0xBB, 0xB9, 0x00}, 'y'},

	{ 0x2013, {0xE2, 0x80, 0x93, 0x00}, '-'},
	{ 0x2014, {0xE2, 0x80, 0x94, 0x00}, '-'},
	{ 0x2015, {0xE2, 0x80, 0x95, 0x00}, '-'},
	{ 0x2017, {0xE2, 0x80, 0x97, 0x00}, '_'},
	{ 0x2018, {0xE2, 0x80, 0x98, 0x00}, '\''},
	{ 0x2019, {0xE2, 0x80, 0x99, 0x00}, '\''},
	{ 0x201A, {0xE2, 0x80, 0x9A, 0x00}, '\''},
	{ 0x201B, {0xE2, 0x80, 0x9B, 0x00}, '\''},
	{ 0x201C, {0xE2, 0x80, 0x9C, 0x00}, '\"'},
	{ 0x201D, {0xE2, 0x80, 0x9D, 0x00}, '\"'},
	{ 0x201E, {0xE2, 0x80, 0x9E, 0x00}, '\"'},
	{ 0x2020, {0xE2, 0x80, 0xA0, 0x00}, '+'},
	{ 0x2021, {0xE2, 0x80, 0xA1, 0x00}, '+'},
	{ 0x2022, {0xE2, 0x80, 0xA2, 0x00}, '*'}

	// TODO: more :)
};




// grabbed from SDL_ttf (also LGPL)
void UNICODE_to_UTF8(unsigned char *utf8, UnicodeChar unicode)
{
    int j=0;

    if (unicode < 0x80)
    {
        utf8[j] = unicode & 0x7F;
    }
    else if (unicode < 0x800)
    {
        utf8[j] = 0xC0 | (unicode >> 6);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x10000)
    {
        utf8[j] = 0xE0 | (unicode >> 12);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x200000)
    {
        utf8[j] = 0xF0 | (unicode >> 18);
        utf8[++j] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x4000000)
    {
        utf8[j] = 0xF8 | (unicode >> 24);
        utf8[++j] = 0x80 | ((unicode >> 18) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else if (unicode < 0x80000000)
    {
        utf8[j] = 0xFC | (unicode >> 30);
        utf8[++j] = 0x80 | ((unicode >> 24) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 18) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 12) & 0x3F);
        utf8[++j] = 0x80 | ((unicode >> 6) & 0x3F);
        utf8[++j] = 0x80 | (unicode & 0x3F);
    }
    else
    	utf8[j] = 0;

    utf8[++j] = 0;
}

/////////////////
// Convert unicode to UTF8
std::string GetUtf8FromUnicode(UnicodeChar ch) {
	if(ch == 0) return std::string("\0", 1);
	static unsigned char utf8[7];
	UNICODE_to_UTF8(utf8, ch);
	return (const char*)utf8;
}


////////////////////
// Convert UTF8 to unicode (takes iterator pointing to the first UTF8-encoded character)
UnicodeChar GetNextUnicodeFromUtf8(std::string::const_iterator &it, const std::string::const_iterator& last, size_t& num_skipped) {
	num_skipped = 0;
	if(it == last) return 0;
	
	unsigned char ch = *it;
	UnicodeChar res = ch;
	if ( ch >= 0xFC ) {
		res  =  (ch&0x01) << 30; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 24; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 18; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 12; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6; it++;  num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xF8 ) {
		res  =  (ch&0x03) << 24; num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 18; num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 12; num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6;  num_skipped++; it++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xF0 ) {
		res  =  (ch&0x07) << 18; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 12; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6; it++;  num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xE0 ) {
		res  =  (ch&0x0F) << 12; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F) << 6; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	} else
	if ( ch >= 0xC0 ) {
		res  =  (ch&0x1F) << 6; it++; num_skipped++; if(it == last) return 0; ch = *it;
		res |=  (ch&0x3F);
	}

	it++; num_skipped++;
	return res;
}

// Conversion functions

////////////////////////////
// Finds an index for the character in conversion table, returns -1 if not found
int FindTableIndex(UnicodeChar c)
{
	int left, right, middle;

	left = 0;
	right = sizeof(tConversionTable)/sizeof(ConversionItem) - 1;

	// Binary search
	while (left <= right)  {
		middle = (left + right) / 2;
		if (tConversionTable[middle].Unicode == c)
			return middle;

		if (c < tConversionTable[middle].Unicode)
			right = middle - 1;
		else
			left = middle + 1;
	}

	return -1; // No conversion available
}

/////////////////////////
// Converts given unicode character to ascii, according to conversion table
// If impossible to convert, returns 0xFF
char UnicodeCharToAsciiChar(UnicodeChar c)
{
	// Regular ascii, just continue
	if (c <= 0x80)
		return (char) c;


	// Unicode, try to convert
	int index = FindTableIndex(c);
	if (index == -1)  // Cannot convert
		return (char)0xFF;
	else
		return tConversionTable[index].Ascii;

}

////////////////////////
// Like tolower() but for all international characters
UnicodeChar	UnicodeToLower(UnicodeChar c)
{
	// ASCII
	if (c < 0xC0)
		return (UnicodeChar)tolower(c);

	// Who the hell invented so crazzy mappings? :S

	// European characters
	if (c >= 0xC0 && c <= 0xD6)
		return c + 0x20;

	if (c >= 0xD8 && c <= 0xDE)
		return c + 0x20;

	if (c >= 0x100 && c <= 0x177 && !(c & 1))
		return c + 1;

	if (c == 0x178)
		return 0xFF;

	if (c >= 0x179 && c <= 0x17E && (c & 1))
		return c + 1;

	if (c == 0x18F)
		return 0x259;

	if (c >= 0x1A0 && c <= 0x1FF && !(c & 1))
		return c + 1;

	// Greece alphabet
	if (c == 0x386)
		return 0x3AC;

	if (c >= 0x388 && c <= 0x38A)
		return c + 0x25;

	if (c >= 0x38C && c <= 0x38F)
		return c + 0x40;

	if (c >= 0x391 && c <= 0x3AB)
		return c + 0x1B;

	// Cyrilic
	if (c >= 0x401 && c <= 0x40F)
		return c + 0x50;

	if (c >= 0x410 && c <= 0x42F)
		return c + 0x20;

	if (c >= 0x490 && c <= 0x4E9 && !(c & 1))
		return c + 1;

	// More European characters
	if (c >= 0x1E80 && c <= 0x1EF9 && !(c & 1))
		return c + 1;

	// This character doesn't have lowercase
	return c;
}

////////////////////////
// Like toupper() but for all international characters
UnicodeChar	UnicodeToUpper(UnicodeChar c)
{
	// ASCII
	if (c < 0xC0)
		return (UnicodeChar)toupper(c);

	// Who the hell invented so crazzy mappings? :S

	// European characters
	if (c >= 0xE0 && c <= 0xF6)
		return c - 0x20;

	if (c >= 0xF8 && c <= 0xFE)
		return c - 0x20;

	if (c == 0xFF)
		return 0x178;

	if (c >= 0x100 && c <= 0x177 && (c & 1))
		return c - 1;

	if (c >= 0x179 && c <= 0x17E && !(c & 1))
		return c - 1;

	if (c == 0x259)
		return 0x18F;

	if (c >= 0x1A0 && c <= 0x1FF && (c & 1))
		return c - 1;

	// Greece alphabet
	if (c == 0x3AC)
		return 0x386;

	if (c >= 0x3AD && c <= 0x3AF)
		return c - 0x25;

	if (c >= 0x3CC && c <= 0x3CF)
		return c - 0x40;

	if (c >= 0x3B1 && c <= 0x3CB)
		return c - 0x1B;

	// Cyrilic
	if (c >= 0x451 && c <= 0x45F)
		return c - 0x50;

	if (c >= 0x430 && c <= 0x44F)
		return c - 0x20;

	if (c >= 0x490 && c <= 0x4E9 && (c & 1))
		return c - 1;

	// More European characters
	if (c >= 0x1E80 && c <= 0x1EF9 && (c & 1))
		return c - 1;

	// This character doesn't have uppercase
	return c;
}

/////////////////////////
// Find a substring in a string (case insensitive)
// Handles UTF8 strings correctly
size_t Utf8StringCaseFind(const std::string& text, const std::string& search_for)
{
	// HINT: same as stringcasefind, only using UTF8 functions instead (a bit slower)
	size_t search_for_size = Utf8StringSize(search_for);

	if (text.size() == 0 || search_for_size == 0 || search_for_size > Utf8StringSize(text))
		return std::string::npos;

	std::string::const_iterator it1 = text.begin();
	std::string::const_iterator it2 = search_for.begin();

	size_t number_of_same = 0;
	size_t number_of_same_bytes = 0;
	size_t result = 0;

	// Go through the text
	while (it1 != text.end())  {
		size_t num_skipped = 0;
		UnicodeChar c1 = UnicodeToLower(GetNextUnicodeFromUtf8(it1, text.end(), num_skipped));
		UnicodeChar c2 = UnicodeToLower(GetNextUnicodeFromUtf8(it2, search_for.end()));

		// The two characters are the same
		if (c1 == c2)  {
			number_of_same++;  // If number of same characters equals to the size of the substring, we've found it!
			if (number_of_same == search_for_size)
				return result - number_of_same_bytes;
			number_of_same_bytes += num_skipped;
		} else {
			number_of_same = 0;
			number_of_same_bytes = 0;
			it2 = search_for.begin();
		}

		result += num_skipped;
	}

	return std::string::npos; // Not found
}

/////////////////////////
// Converts the Utf8 encoded string to format that will display correctly in old LX
std::string OldLxCompatibleString(const std::string &Utf8String)
{
	std::string result = "";
	std::string::const_iterator utf8_it = Utf8String.begin();
	std::string::const_iterator last_it = Utf8String.begin();

	UnicodeChar current;
	int index;
	while (utf8_it != Utf8String.end())  {
		current = GetNextUnicodeFromUtf8(utf8_it, Utf8String.end());
		if (current <= 0x80)  {  // Normal ascii, don't convert in any way
			result += (char)current;
			last_it = utf8_it;
			continue;
		}

		// Unicode character
		index = FindTableIndex(current);
		result += std::string(last_it, utf8_it); // Keep the UTF8, old LX will ignore it
		if (index == -1)
			result += UNKNOWN_CHARACTER; // For characters that cannot be converted
		else
			result += tConversionTable[index].Ascii;

		last_it = utf8_it;
	}

	return result;
}

/////////////////////////
// Converts the string created by function above back to a normal UTF8 string
// WARNING: passing a normal UTF8 string in this function will result in wrong output
std::string Utf8String(const std::string& OldLxString)
{
	std::string result = "";
	std::string::const_iterator utf8_it = OldLxString.begin();
	std::string::const_iterator last_it = OldLxString.begin();

	UnicodeChar current;
	while (utf8_it != OldLxString.end())  {
		current = GetNextUnicodeFromUtf8(utf8_it, OldLxString.end());
		if (current <= 0x80)  {  // Normal ascii, don't convert in any way
			result += (char)current;
			last_it = utf8_it;
			continue;
		}

		// Unicode character

		result += std::string(last_it, utf8_it); // Keep the UTF8
		if(utf8_it == OldLxString.end()) break;
		if ((unsigned char)(*utf8_it) <= 0x80)  { // If after the unicode character comes another one, just continue

			// Ignore if the converted character comes after UTF8 character
			// NOTE: the check if the character is really a valid converted UTF8 is not made because
			// of forward compatibility - in future versions the conversion table can slightly change
			// which would make it incompatible
			utf8_it++;
		}

		last_it = utf8_it;
	}

	return result;
}

/////////////////////////
// Removes special UTF8 characters from the string
std::string RemoveSpecialChars(const std::string &Utf8String)
{
	std::string result = "";
	std::string::const_iterator utf8_it = Utf8String.begin();

	UnicodeChar current;
	int index;
	while (utf8_it != Utf8String.end())  {
		current = GetNextUnicodeFromUtf8(utf8_it, Utf8String.end());
		if (current <= 0x80)  // Normal ascii, keep it
			result += (char)current;
		else  { // Replace the unicode character with an ascii equivalent (if some)
			index = FindTableIndex(current);
			if (index != -1)
				result += tConversionTable[index].Ascii;
		}
	
	}

	return result;
}



/*
 * Functions for UTF conversions taken from enconding.c, created by W3C
 * The license is available at the following address:
 * http://dev.w3.org/cvsweb/~checkout~/XML/Copyright?rev=1.1&content-type=text/plain
 * Original file: http://dev.w3.org/cvsweb/~checkout~/XML/encoding.c
 *
 */

//////////////
// Converts UTF16 to UTF8
std::string Utf16ToUtf8(const Utf16String& str)
{
    Uint32 c, d = 0;
	std::string result;
    int bits, iters;

	for (Utf16String::const_iterator in = str.begin(); in != str.end();)  {
		c = *in;
		in++;
		if ((c & 0xFC00) == 0xD800) { // surrogates
			if ((in != str.end()) && (((d = (unsigned char)*in) & 0xFC00) == 0xDC00)) {
				c &= 0x03FF;
				c <<= 10;
				c |= d & 0x03FF;
				c += 0x10000;
			} else {
				return result;
			}

			in++;
        }

		// assertion: c is a single UTF-4 value

		if (c < 0x80)  {
			result += (char)c;
			bits= 0;
			iters = 0;
		} else if (c < 0x800)  {
			result += (char)((c >>  6) | 0xC0);
			bits=  0;
			iters = 1;
		} else if (c < 0x10000)  {
			result += (char)((c >> 12) | 0xE0);
			bits=  6;
			iters = 2;
		} else {
			result += (char)((c >> 18) | 0xF0);
			bits= 12;
			iters = 3;
		}
 
		for ( ; iters; --iters) {
			result += (char)(((c >> bits) & 0x3F) | 0x80);
		}
	}

	return result;
}

///////////////
// Converts UTF8 to UTF16
Utf16String Utf8ToUtf16(const std::string& str)
{
    Uint32 c, d, trailing;
	Utf16String result;

	for (std::string::const_iterator in = str.begin(); in != str.end();)  {
		d = (unsigned char)*in;
		in++;

		if (d < 0x80)  {
			c = d;
			trailing = 0;
		} else if (d < 0xC0)  {
			return result; // trailing byte in leading position
		} else if (d < 0xE0)  {
			c = d & 0x1F;
			trailing = 1;
		} else if (d < 0xF0)  {
			c = d & 0x0F;
			trailing= 2;
		} else if (d < 0xF8)  { 
			c = d & 0x07;
			trailing= 3;
		} else  {
			return result; // no chance for this in UTF-16
		}

		for ( ; trailing; trailing--) {
			if (in == str.end())
				return result;
			if (((d = (unsigned char)*in++) & 0xC0) != 0x80)
				return result;
			c <<= 6;
			c |= d & 0x3F;
		}

		// assertion: c is a single UTF-4 value
		if (c < 0x10000) {
			result += (Utf16Char) c;
		} else if (c < 0x110000)  {
			c -= 0x10000;
			result += 0xD800 | (c >> 10);
			result += 0xDC00 | (c & 0x03FF);
		} else {
			return result;
		}
    }
    return result;
}


//////////////////
// Convert a Unicode string to UTF8
std::string UnicodeToUtf8(const UnicodeString& str)
{
	std::string result;
	for (UnicodeString::const_iterator i = str.begin(); i != str.end(); i++)  {
		result += GetUtf8FromUnicode(*i);
	}

	return result;
}

//////////////////
// Convert a UTF8 string to Unicode
UnicodeString Utf8ToUnicode(const std::string& str)
{
	UnicodeString result;
	for (std::string::const_iterator it = str.begin(); it != str.end();)
		result += GetNextUnicodeFromUtf8(it, str.end());

	return result;
}

