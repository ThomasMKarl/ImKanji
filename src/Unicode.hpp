#pragma once
#include <cwchar>


typedef unsigned char utf8char;
typedef unsigned short utf16char;
typedef unsigned int utf32char;

size_t strlenUtf8(const utf8char * in);
size_t strlenUtf16(const utf16char * in);
size_t strlenUtf32(const utf32char * in);
size_t strlenWchar(const wchar_t *in);
utf8char * strdupUtf8(const utf8char * in);
int decodeUtf8(utf8char in, utf32char * out, short * state);
int encodeUtf8(utf32char in, utf8char * out, short * state);
int decodeUtf16(utf16char in, utf32char *out, short *state);
int encodeUtf16(utf32char in, utf16char *out, short * state);
utf16char * utf8ToUtf16(const utf8char * in);
utf32char *utf8ToUtf32(const utf8char * in);
wchar_t * utf8ToWchar(const utf8char * in);
utf8char * utf16ToUtf8(const utf16char *in);
utf8char * utf32ToUtf8(const utf32char * in);
utf8char * wcharToUtf8(const wchar_t * in);
utf16char * utf32ToUtf16(const utf32char * in);
utf32char * utf16ToUtf32(const utf16char * in);
int checkUtf8(const utf8char * in, size_t len);
