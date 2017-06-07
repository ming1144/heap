#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>


typedef int element;
struct max_heap {
	int      capacity; // the capacity of this array
	int      n;  
	element* key;
};

struct max_heap *create_max_heap()
{
	struct max_heap *s;
	s = (struct max_heap*) malloc(sizeof(struct max_heap));
	s->capacity = 0; s->n = 0;   s->key = NULL;
	return s;
}

void release_max_heap(struct  max_heap**s)
{
	if ((*s)->key) 
		free((*s)->key);
	free(*s);  *s = NULL;
}

// Remove the element with the largest key value
void  delete_max_heap(struct max_heap* s)
{
	if (s->n > 0) { // insert your code here 
		element lastEle = s->key[s->n];
		s->n--;
		int now = 1;
		while (now * 2 <= s->n)
		{
			element leftChild = s->key[now * 2];
			element rightChild;
			if (now * 2 == s->n)
				rightChild = 0;
			else
				rightChild = s->key[now * 2 + 1];

			if (leftChild >= rightChild)
			{
				if (leftChild > lastEle)
				{
					s->key[now] = leftChild;
					now *= 2;
				}
				else
				{
					s->key[now] = lastEle;
					break;
				}
			}
			else
			{
				if (rightChild > lastEle)
				{
					s->key[now] = rightChild;
					now *= 2;
					now += 1;
				}
				else
				{
					s->key[now] = lastEle;
					break;
				}
			}
		}
		s->key[now] = lastEle;
		return;
	}
}

// Add a new element into a max heap
void insert_max_heap(struct max_heap* s, element data)
{
	int p;
	if (s->n + 1 >= s->capacity) {
		s->capacity *= 2;   if (s->capacity == 0) s->capacity = 2;
		s->key = (element*)((s->key) ?
			realloc(s->key, s->capacity*sizeof(element)) :
			malloc(s->capacity*sizeof(element)));
	}
	// Add data into the max heap
	// insert your code here	

	if (s->n == 0)
	{
		s->n++;
		s->key[s->n] = data;
		return;
	}

	int now = s->n + 1;
	while (now != 0)
	{
		if (s->key[now / 2] < data)
		{
			s->key[now] = s->key[now / 2];
			now = now / 2;
		}
		else
		{
			s->key[now] = data;
			s->n++;
			break;
		}
	}
	return;
}
	

int main(void)
{
	struct max_heap *maxheap = create_max_heap();
	int  i, n, op, x;
	scanf("%d", &op);
	while (op != -1) {
		if (op == 0) {
			scanf("%d", &x);
			insert_max_heap(maxheap, x); // push       
		}
		else if (op == 1) { // pop
			if (maxheap->n >= 1) {
				printf("top:%d\n", maxheap->key[1]);
				delete_max_heap(maxheap);
			}
			else printf("max heap is empty\n");
		}
		else if (op == 2) {
			for (i = 1; i <= maxheap->n; ++i)
				printf(((i<maxheap->n) ? "%d," : "%d\n"), maxheap->key[i]);
		}
		scanf("%d", &op);
	}
	release_max_heap(&maxheap);  return 0;
}

