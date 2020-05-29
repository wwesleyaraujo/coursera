#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct Lista no;
struct Lista{
	int key;
	no *lado;
};
typedef struct myset MyHashSet;
struct myset{
    int head; 
    MyHashSet *abaixo;
    no *lado; 
};



/** Initialize your data structure here. */
MyHashSet* searchHead(MyHashSet* obj,int key){
	if(obj->abaixo == NULL){
		return NULL;
	}else{
		MyHashSet* s = obj->abaixo;
		if(s->head == key%5){
			return s;
		}else{
			return searchHead(s,key);
		}
	}
}

MyHashSet* myHashSetCreate() {
     MyHashSet *new = malloc(sizeof(MyHashSet));
     new->abaixo = NULL;
     new->lado  = NULL;
     return new;
}

void myHashSetAdd(MyHashSet* obj, int key) {
   no *newNo = malloc(sizeof(no));
   newNo->key = key;
   MyHashSet* entry = searchHead(obj,key);
	  	if(entry != NULL){                       // header in hashSet 
	  		printf("Head there is\n");          
	  		newNo->lado = entry->lado;
	  		entry->lado = newNo;
	  		
	  	}else{
	  		MyHashSet *new = myHashSetCreate();
		  	new->head = key % 5;
	  	    newNo->lado = new->lado;
	  	    new->lado = newNo; 
		  	new->abaixo = obj->abaixo;
		  	obj->abaixo = new;  	 	
	   }
}

void printNo(no *n){
	if(n!= NULL){	
			printf("%d*", n->key);
			printNo(n->lado);
		}else{
			return;
		}
}
void printSet(MyHashSet* obj)
{
	if(obj != NULL){	
		printf("%d |", obj->head);
		printNo(obj->lado);
		printf("\n");
		printSet(obj->abaixo);
	}else{
		//printf("vazio");
		return;
	}
}
void printHashSet(MyHashSet* obj)
{
	printf("headers \n");
	 printSet(obj);
}
void myHashSetRemove(MyHashSet* obj, int key) {
  	  MyHashSet* entry = searchHead(obj,key);
  	  if (entry != NULL){
  	  	//	printNo(entry->lado);
  	  	no *anterior = entry->lado;
  	  	if(anterior->key == key){
  	  		entry->lado = anterior->lado;
  	  		free(anterior);
  	  		 printf("Deletando %d\n", key);
  	  	}
  	  	no *n = anterior->lado;
  	  	int flag = 0;
  	  	while( n != NULL && flag==0)
  	  	{
  	  	   if(n->key == key){
  	  	       flag =1;
  	  	       anterior->lado = n->lado;
  	  	       free(n);
  	  	       printf("Deletando %d\n", key);
  	  	       return; 
  	  	   }
  	  	   anterior = n;
  	  	   n = n->lado;
  	  	}
  	  	printf(" \n");
  	  }
}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key) {
  MyHashSet* entry = searchHead(obj,key);
  	  if (entry != NULL){
  	  	//	printNo(entry->lado);
  	  	no *anterior = entry->lado;
  	  	if(anterior->key == key){
  	  		 printf("Encontrado %d\n", key);
  	  		 return true;
  	  	}
  	  	no *n = anterior->lado;
  	  	int flag = 0;
  	  	while( n != NULL && flag==0)
  	  	{
  	  	   if(n->key == key){
  	  	       flag =1;
  	  
  	  	       printf("Encontrado %d\n", key);
  	  	       return true; 
  	  	   }
  	  	   anterior = n;
  	  	   n = n->lado;
  	  	}
  	  	printf(" \n");
  	  }else{
  	  	return false;
  	  }
}
void noFree(no *n){
 
	if(n!= NULL){	
			noFree(n->lado);
			free(n);
		}else{
			return;
		}
}
void myHashSetFree(MyHashSet* obj) {
    
	if(obj != NULL){	
		noFree(obj->lado);
		myHashSetFree(obj->abaixo);
	}else{
		//printf("vazio");
		return;
	}
}

int main(){
	MyHashSet* obj = myHashSetCreate();
	myHashSetAdd(obj, 12);
	myHashSetAdd(obj, 10);
	myHashSetAdd(obj, 6);
	myHashSetAdd(obj, 16);
	myHashSetAdd(obj, 14);
	bool a = myHashSetContains(obj,10);
	myHashSetAdd(obj, 206);
	myHashSetAdd(obj, 7);
	myHashSetAdd(obj, 127);
	MyHashSet* obj2;
	obj2 = obj->abaixo;
	printSet(obj2);
	myHashSetRemove(obj,12);
	printSet(obj2);
	myHashSetFree(obj2);
	free(obj);
	
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 
 * myHashSetRemove(obj, key);
 
 * bool param_3 = myHashSetContains(obj, key);
 
 * myHashSetFree(obj);
*/
