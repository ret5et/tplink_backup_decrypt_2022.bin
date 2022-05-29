#include <openssl/aes.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h>

static const int HDRSZ = 0x80;


void* loadfile(const char* fileName, size_t* size) {

  struct stat st = {};
  int rs = stat(fileName, &st);
  if (rs != 0)
    return NULL;

  *size = st.st_size;

  void* data = malloc(st.st_size);
  if (data == NULL)
    return NULL;

  FILE* stream = fopen(fileName, "rb");
  if (stream == NULL)
    return NULL;

  fread(data, 1, st.st_size, stream);
  fclose(stream);

  return data;
}

int main(int argc, char* argv[]) {

  if (argc != 3) {
    printf("%s <config.bin> <output.tar>\n", argv[0]);
    return 0;
  }

  AES_KEY key;
  char iv[] = "1234567890abcdef";
  char* password = "0123456789abcdef";

  const char *fileName = argv[1];
  const char* outName = argv[2];
  size_t size = 0;
  void* data = loadfile(fileName, &size);

  if (data == NULL) {
    printf("error\n");
    exit (EXIT_FAILURE);
  }

  AES_set_decrypt_key(password, 128, &key);

  data += HDRSZ; //skip header
  size -= HDRSZ;

  void* out = malloc(size);

  AES_cbc_encrypt(data, out, size, &key, iv, 0);

  FILE *outstream = fopen(outName, "wb");
  fwrite(out, 1, size, outstream);
  fclose(outstream);

  return 1;
}
