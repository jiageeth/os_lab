chat 2:////:#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

struct sh {
   int turn;
   int exit;
   char msg[128];
};

int main() {
   int fd, fret;
   struct sh* s;

   fd = shm_open("/JO", O_CREAT | O_RDWR, 0666);
   if (fd == -1) {
      printf("Error in creating Shared Memory!\n");
      return 1;
   }

   fret = ftruncate(fd, sizeof(struct sh));
   if (fret == -1) {
      printf("Error in truncating the file\n");
      return 1;
   }

   s = (struct sh*) mmap(NULL, sizeof(struct sh), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if (s == MAP_FAILED) {
      printf("Error in mapping shared memory\n");
      return 1;
   }


   
   while (1) {
      if (s->turn == -1) 
      {
         printf("Chat 2 is exiting...\n");
         break;
      }

      while (s->turn == 1) 
      {
         usleep(1000);
      }

      if (strlen(s->msg) > 0) 
      {
         printf("Chat 1: %s\n", s->msg);
         memset(s->msg, 0, sizeof(s->msg));
      }

      printf("Chat 2: ");
      fgets(s->msg, sizeof(s->msg), stdin);
      s->msg[strcspn(s->msg, "\n")] = '\0';

      if (strcmp(s->msg, "q") == 0) 
      {
         s->turn = -1;
         break;
      }

      s->turn = 1;
   }

   munmap(s, sizeof(struct sh));
   shm_unlink("/JO");
   close(fd);
   return 0;
}