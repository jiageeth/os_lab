chat 1 ///:#include <stdio.h>    // For input-output functions like printf, fgets
#include <stdlib.h>   // For memory allocation, exit, etc.
#include <string.h>   // For string manipulation functions like strlen, strcmp, memset
#include <sys/mman.h> // For memory mapping functions like mmap, munmap
#include <sys/stat.h> // For file status definitions and permissions
#include <unistd.h>   // For POSIX functions like close, usleep
#include <fcntl.h>    // For file control operations like open, fcntl

struct sh 
{
   int turn;
   int exit;
   char msg[128];
};

int main() 
{
   int fd, fret;
   struct sh* s;

   fd = shm_open("/JO", O_CREAT | O_RDWR, 0666);
   if (fd == -1) 
   {
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


   
   if (s->turn != 1 && s->turn != 2) 
   {
      s->turn = 1;
      s->exit = 0;
   }

   while (1) 
   {
      if (s->turn == -1) {
         printf("Chat 1 is exiting...\n");
         break;
      }

      while (s->turn == 2) {
         usleep(1000); //sleep 1
      }

      if (strlen(s->msg) > 0) {
         printf("Chat 2: %s\n", s->msg);
         memset(s->msg, 0, sizeof(s->msg));
      }

      printf("Chat 1: ");
      fgets(s->msg, sizeof(s->msg), stdin);
      s->msg[strcspn(s->msg, "\n")] = '\0';

      if (strcmp(s->msg, "q") == 0) {
         s->turn = -1;
         break;
      }

      s->turn = 2;
   }

   munmap(s, sizeof(struct sh));
   shm_unlink("/JO");
   close(fd);
   return 0;
}