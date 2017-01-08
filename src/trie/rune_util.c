#include "../dep/libnu/libnu.h"
#include "rune_util.h"

rune *__strToRunes(char *str, size_t *len) {

  ssize_t rlen = nu_strlen(str, nu_utf8_read);
  uint32_t decoded[sizeof(uint32_t) * (rlen + 1)];

  nu_readstr(str, decoded, nu_utf8_read);

  rune *ret = calloc(rlen + 1, sizeof(rune));
  for (int i = 0; i < rlen; i++) {
    ret[i] = (rune)decoded[i] & 0x0000FFFF;
  }
  if (len)
    *len = rlen;

  return ret;
}

char *__runesToStr(rune *in, size_t len, size_t *utflen) {

  uint32_t unicode[len + 1];
  for (int i = 0; i < len; i++) {
    unicode[i] = (uint32_t)in[i] & 0x0000ffff;
  }
  unicode[len] = 0;

  *utflen = nu_bytelen(unicode, nu_utf8_write);

  char *ret = calloc(1, *utflen + 1);

  nu_writestr(unicode, ret, nu_utf8_write);
  return ret;
}
