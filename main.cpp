#include <iostream>
#include <string.h>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>
#include "Quash.h"

using namespace std;

int main(int argc, char *argv[])
{
  Quash *myQuash = new Quash();
  char buffer[256];
  int o;

  while(cin.getline(buffer, 256))
    {

      string command(buffer);

      if(command.compare(0,6,"insert") == 0)
	{
	  o = atoi(&(command[7]));
	  myQuash->InsertHashNode(o);
	}
      else if(command.compare("print") == 0)
	myQuash->print();

      else if(command.compare("deleteMin") == 0)
	  myQuash->deleteMin();

      else if(command.compare(0,6,"lookup") == 0){
          o = atoi(&(command[7]));
          myQuash->lookup(o);
	}
      else if(command.compare(0,6,"delete") == 0){
          o = atoi(&(command[7]));
          myQuash->deleteNode(o);
	}
      else
	cout << "Invalid Command" << endl;
    }
}
