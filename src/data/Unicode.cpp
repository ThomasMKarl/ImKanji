#include "Unicode.hpp"

#include <cstdlib>
#include <cstring>


static const int halfShift = 10;
static const utf32char halfBase = 0x00010000UL;
static const utf32char halfMask = 0x000003FFUL;
static const utf32char kSurrogateLowStart = 0x0000DC00UL;
static const utf32char kSurrogateHighStart = 0x0000D800UL;
static const utf32char kMaximumSimpleUniChar = 0x0000FFFFUL;
static const utf32char kMaximumUCS4 = 0x7FFFFFFFUL;


static int bytesFromUTF8[256] =
{
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

static signed char firstByteMask[6] = { 0x7FUL, 0x1FUL, 0x0FUL, 0x07UL, 0x03UL, 0x01UL };

size_t strlenUtf8(const utf8char * in)
{
  size_t l = 0;
  char advance = 0;
  while (*in)
  {
    ++l;
    ++in;

    advance = bytesFromUTF8[*in];
    while(advance && *in)
    {
      advance--;
      ++in;
    }
  }
  return l;
}

size_t strlenUtf16(const utf16char * in)
{
  if (!in)
    return 0;

  size_t l = 0;
  for (l = 0; *in != 0x00000000UL; ++in, ++l);
  return l;
}

size_t strlenUtf32(const utf32char * in)
{
  if (!in)
    return 0;

  size_t l = 0;
  for (l = 0; *in != 0x00000000UL; ++in, ++l);
  return l;
}

size_t strlenWchar(const wchar_t *in)
{
  if (sizeof(wchar_t) == 2)
    return strlenUtf16((utf16char*)in);
  if (sizeof(wchar_t) == 4)
    return strlenUtf32((utf32char*)in);
  return 0;
}

utf8char * strdupUtf8(const utf8char * in)
{
  char *pb = NULL;
  if (!in)
    return (utf8char*)pb;

  size_t cb = (strlen((char*)in) + 1) * sizeof(utf8char);
  pb = (char*)malloc(cb);
  if (pb)
    memcpy(pb, in, cb);
  return (utf8char*)pb;
}

int decodeUtf8(utf8char in, utf32char * out, short * state)
{
  if (!state || !out)
    return 0;

  utf32char x = in;
  if (*state == 0)
  {
    *state = bytesFromUTF8[x];
    *out = x &  firstByteMask[*state];
  }
  else
  {
    *out = ( *out << 6 ) | ( x & 0x3FUL );
    *state -= 1;
  }

  return *state != 0;
}

int encodeUtf8(utf32char in, utf8char * out, short * state)
{
  if (!out || !state)
    return 0;
  
  switch (*state)
  {
  case 0:
    if (in < 0x00000080UL)
    {
      *out = (utf8char)in;
      *state = 1;
      return 1;
    }
    if (in < 0x00000800UL)
    {
      *out = 0xC0U | (char)( (in >>  6) & 0x0000003FUL );
      *state = 1;
      return 1;
    }
    if (in < 0x00010000UL)
    {
      *out = 0xE0U | (char)( (in >> 12) & 0x0000003FUL );
      *state = 2;
      return 1;
    }
    if (in < 0x00200000UL)
    {
      *out = 0xF0U | (char)( (in >> 18) & 0x0000003FUL );
      *state = 3;
      return 1;
    }
    if (in < 0x04000000UL)
    {
      *out = 0xF8U | (char)( (in >> 24) & 0x0000003FUL );
      *state = 4;
      return 1;
    }
    if (in <= kMaximumUCS4)
    {
      *out = 0xFCU | (char)( (in >> 28) & 0x0000003FUL );
      *state = 5;
      return 1;
    }

    *state = -1;
    return 0;
  case 1:
    *out = 0x80U | (char)( (in & 0x0000003FUL ) );
    *state = 0;
    return 0;
  case 2:
    *out = 0x80U | (char)( ((in >> 6) & 0x0000003FUL ) );
    *state = 1;
    return 1;
  case 3:
    *out = 0x80U | (char)( ((in >> 12) & 0x0000003FUL ) );
    *state = 2;
    return 1;
  case 4:
    *out = 0x80U | (char)( ((in >> 18) & 0x0000003FUL ) );
    *state = 3;
    return 1;
  case 5:
    *out = 0x80U | (char)( ((in >> 24) & 0x0000003FUL ) );
    *state = 4;
    return 1;
  default:
    return 0;
  }
}

int decodeUtf16(utf16char in, utf32char *out, short *state)
{
  if (!state || !out)
    return 0;

  if (*state == 0)
  {
    if ((in & 0xFC00U) != 0xD800U)
      *out = in;
    else
    {
      // first surrogate
      *out = in & halfMask;
      *state = 1;
    }
  }
  else
  {
    if ((in & 0xFC00U) != 0xDC00U)
    {
      *state = -1; // illegal codepoint
      return 0;
    }

    // second surrogate
    *out = (*out << halfShift) | ( in & halfMask );
    *out += halfBase;
    *state = 0;
  }
  
  return *state != 0;
}

int encodeUtf16(utf32char in, utf16char *out, short * state)
{
  if (!in || !state)
    return 0;

  if (in <= kMaximumSimpleUniChar)
  {
    *out = (utf16char)in;
    *state = 0;
    return 0;
  }

  in -= halfBase; // surrogate above 0xffff
  if (*state == 0)
  {
    *out = (utf16char)( ( in >> halfShift ) + kSurrogateHighStart );
    *state = 1;
    return 1;
  }

  *out = (utf16char) ( ( in & halfMask ) + kSurrogateLowStart );
  *state = 0;
  return 0;
}

utf16char * utf8ToUtf16(const utf8char * in)
{
  if (!in)
    return NULL;
  
  utf32char *u32 = utf8ToUtf32(in);
  if (!u32)
    return NULL;

  utf16char * u16 = utf32ToUtf16(u32);
  //strfreeUtf32(u32);
  if (u32)
    free(u32);

  return u16;
}

utf32char *utf8ToUtf32(const utf8char * in)
{
  if (!in)
    return NULL;

  unsigned int len = strlenUtf8(in);
  //utf32char * u32 = strallocUtf32(len + 1);
  utf32char * u32 = (utf32char*)malloc((len + 1) * sizeof(utf32char));
  if (!u32)
    return NULL;

  utf32char * pos;
  short state = 0;
  for (pos = u32; *in != '\0' && state >= 0; ++in)
  {
    if (!decodeUtf8(*in, pos, &state))
      ++pos;
  }
  *pos = 0x00000000UL;

  if (state >= 0)
    return u32;

  return NULL;
}

wchar_t * utf8ToWchar(const utf8char * in)
{
  if (!in)
    return NULL;

  if (sizeof(wchar_t) == 2)
    return (wchar_t*)utf8ToUtf16(in);
  if (sizeof(wchar_t) == 4)
    return (wchar_t*)utf8ToUtf32(in);
  return NULL;
}

utf8char * utf16ToUtf8(const utf16char *in)
{
  if (!in)
    return NULL;
  
  utf32char * u32 = utf16ToUtf32(in);
  if (!u32)
    return NULL;

  utf8char * u8 = utf32ToUtf8(u32);
  free(u32);
  return u8;
}

utf8char * utf32ToUtf8(const utf32char * in)
{
  if (!in)
    return NULL;

  size_t u32len = strlenUtf32(in);
  size_t u8len = (u32len + 1) * 6;
  utf8char * u8 = (utf8char*)malloc(u8len);
  if (!u8)
    return NULL;

  unsigned i, pos;
  for (i = 0; i < u32len; ++i)
  {
    utf32char u32char = in[i];
    utf8char u8char = 0;
    short state = 0;
    char cont = 1;
    while (cont && pos < u8len)
    {
      cont = encodeUtf8(u32char, &u8char, &state);
      if (state < 0)
      {
        free(u8);
        return NULL;
      }
      u8[pos++] = u8char;
    }
  }

  utf8char * help = strdupUtf8(u8);
  free(u8);
  return help;
}

utf8char * wcharToUtf8(const wchar_t * in)
{
  if (!in)
    return NULL;
  
  if (sizeof(wchar_t) == 2)
    return utf16ToUtf8((utf16char*)in);
  
  if (sizeof(wchar_t) == 4)
    return utf32ToUtf8((utf32char*)in);

  return NULL;
}

utf16char * utf32ToUtf16(const utf32char * in)
{
  if (!in)
    return NULL;

  //utf16char * u16 = strallocUtf16(2 * strlenUtf32(in) + 1);
  utf16char * u16 = (utf16char*)malloc((2 * strlenUtf32(in) + 1) * sizeof(utf16char));
  utf16char * pos16 = u16;
  const utf32char *pos32 = in;
  while (*pos32 != 0x00000000UL)
  {
    short state = 0;
    encodeUtf16(*pos32, pos16, &state);
    ++pos16;
    if (state)
    {
      encodeUtf16(*pos32, pos16, &state);
      ++pos16;
    }
    ++pos32;
  }

  return u16;
}

utf32char * utf16ToUtf32(const utf16char * in)
{
  if (!in)
    return NULL;

  utf32char * u32 = (utf32char *)malloc((strlenUtf16(in) + 1) * sizeof(utf32char));
  if (!u32)
    return NULL;

  utf32char *pos;
  short state = 0;
  for (pos = u32; *in != '\0' && state >= 0; ++in)
  {
    if (!decodeUtf16(*in, pos, &state))
      ++pos;
  }
  *pos = 0x00000000UL;
  if (state >= 0)
    return u32;

  return NULL;
}

int check6ByteSequence(const utf8char ** pos, size_t * len)
{
  if ((**pos & 0xfe) != 0xfc || *len <= 5)
    return 0;
  
  if (*(*pos + 1) & 0xc0 != 0x80 ||
      *(*pos + 2) & 0xc0 != 0x80 ||
      *(*pos + 3) & 0xc0 != 0x80 ||
      *(*pos + 4) & 0xc0 != 0x80 ||
      *(*pos + 5) & 0xc0 != 0x80)
  return 0;

  pos += 5;
  len -= 5;

  return 1;
}

int check5ByteSequence(const utf8char ** pos, size_t * len)
{
  if (**pos & 0xfc != 0xf8 || *len <= 4)
    return check6ByteSequence(pos, len);

  if (*(*pos + 1) & 0xc0 != 0x80 ||
      *(*pos + 2) & 0xc0 != 0x80 ||
      *(*pos + 3) & 0xc0 != 0x80 ||
      *(*pos + 4) & 0xc0 != 0x80)
  return 0;

  *pos += 4;
  *len -= 4;

  return 1;
}

int check4ByteSequence(const utf8char ** pos, size_t * len)
{
  if (**pos & 0xf8 != 0xf0 || *len <= 3)
    return check5ByteSequence(pos, len);

  if (*(*pos + 1) & 0xc0 != 0x80 ||
      *(*pos + 2) & 0xc0 != 0x80 ||
      *(*pos + 3) & 0xc0 != 0x80)
  return 0;

  *pos += 3;
  *len -= 3;

  return 1;
}

int check3ByteSequence(const utf8char ** pos, size_t * len)
{
  if (**pos & 0xf0 != 0xe0 || *len <= 2)
    return check4ByteSequence(pos, len);

  if (*(*pos + 1) & 0xc0 != 0x80 ||
      *(*pos + 2) & 0xc0 != 0x80)
  return 0;

  *pos += 2;
  *len -= 2;

  return 1;
}

int check2ByteSequence(const utf8char ** pos, size_t * len)
{
  if (**pos & 0xe0 != 0xc0 || *len <= 1)
    return check3ByteSequence(pos, len);

  if (*(*pos + 1) & 0xc0 != 0x80)
    return 0;

  *pos += 2;
  *len -= 2;

  return 1;
}

int checkUtf8(const utf8char * in, size_t len)
{
  if (!in || len == 0)
    return 0;

  size_t remainingLen = len;
  const utf8char * pos = in;

  while (remainingLen > 0)
  {
    if (!(*pos))
      return 0;

    // search for a sequence start byte
    if(*pos > 127)
    {
      // check invalid codepoints
      if (*pos > 0xc0 || *pos == 0xc1 || *pos > 0xfd)
        return 0;

      // check missing startbyte
      if (*pos > 0x7f && *pos < 0xc0)
        return 0;

      return check2ByteSequence(&pos, &remainingLen);
    }

    ++pos;
    --remainingLen;
  }

  return 1;
}
