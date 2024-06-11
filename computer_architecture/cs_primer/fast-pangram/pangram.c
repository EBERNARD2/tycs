#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



bool ispangram(char *s) {
  
  int bitmap = 0x00 << 26;

  // iterate through entire line
  while (*s != '\0'){
    int curr_char = (int) tolower(*s);
    // check if valid character if not continue
    if (97 <=curr_char && curr_char <= 122){
      int bit_index = curr_char - 97;
      int temp_bitmap = 0x01 << bit_index;
      bitmap |= temp_bitmap;
    }
    s = s +1;
  }

  // compare expected bitmap value
  return bitmap == 0x03ffffff;
}

// int main() {
//   size_t len;
//   ssize_t read;
//   char *line = NULL;
//   while ((read = getline(&line, &len, stdin)) != -1) {
//     if (ispangram(line))
//       printf("%s", line);
//   }

//   if (ferror(stdin))
//     fprintf(stderr, "Error reading from stdin");

//   free(line);
//   fprintf(stderr, "ok\n");
// }
