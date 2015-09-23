#ifndef HASHNODE_H
#define HASHNODE_H

class HashNode
{
 public:
  int Value, Count;
  int HeapVal;
  HashNode *Next;

 HashNode(int Val): Value(Val), Count(1), Next(NULL){};
  ~HashNode(){};
};

#endif
