#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{

   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public virtual Cache
{
    public:

        LRUCache(int capacity);
        virtual void set(int key, int value);
        virtual int get(int key);
};


// ******************************************************************************************************

LRUCache::LRUCache(int capacity)
{
    this->cp = capacity;
}

void
LRUCache::set(int key, int value)
{
  Node* tmp = NULL;

  if (mp.empty())
  {
    tmp = new Node(key, value);
    this->tail = tmp;
    this->head = tmp;
  }
  else
  {
    tmp = new Node(this->tail, this->head->next, key, value);
    this->head = tmp;
  }

  assert(tmp != NULL);
  mp[key] = tmp;
}

int
LRUCache::get(int key)
{
    auto it = mp.find(key);

    if(it == mp.end())
    {
        return -1;
    }
    else // HIT cache
    {
        Node* node = (*it).second;

        if (mp.size() > 1)
        { // move the hit to the first position
          node->prev->next = node->next;
          node->prev = this->tail;
          node->next = this->head->next;
          this->head = node;
        }

        return node->value;
    }
}

// ******************************************************************************************************

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
