#include <openssl/aes.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h>

#include <arpa/inet.h>

static const int HDRSZ = 0x80;
static const int head_magic = 0xacac;
struct Header {
  unsigned int size;
  unsigned int magic;
};

//loadfile

void* loadfile(const char* fileName, unsigned int *size) {

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
    printf("%s <inpit.tar> <output.bin>\n", argv[0]);
    return 0;
  }

  AES_KEY key;
  char iv[] = "1234567890abcdef";
  char* password = "0123456789abcdef";
  unsigned int size = 0x0;


  AES_set_encrypt_key(password, 128, &key);

  const char *fileName = argv[1];
  const char* outName = argv[2];
  void* data = loadfile(fileName, &size);

  void* out = calloc(1,size+HDRSZ);

  struct Header *hdr = (struct Header *)out;

  hdr->size = htonl(size);
  hdr->magic = htonl(head_magic);

  void *start = out + HDRSZ;

  AES_cbc_encrypt(data, start, size, &key, iv, 1);

  FILE *outstream = fopen(outName, "wb");
  fwrite(out, 1, size, outstream);
  fclose(outstream);

  return 1;
}
