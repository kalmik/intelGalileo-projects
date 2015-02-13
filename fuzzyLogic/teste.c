#include <stdio.h>
#include <string.h>
int main(int argc, char ** argv)
{
   char longString[] = "This is a long string.\nIt has multiple lines of text in it.\nWe want to examine each of these lines separately.\nSo we will do that.";
   const char * curLine = longString;
   while(curLine)
   {
      char * nextLine = strchr(curLine, '\n');
      if (nextLine) *nextLine = '\0';  // temporarily terminate the current line
      printf("curLine=[%s]\n", curLine);
      //if (nextLine) *nextLine = '\n';  // then restore newline-char, just to be tidy    
      curLine = nextLine ? (nextLine+1) : NULL;
   }
   return 0;
}