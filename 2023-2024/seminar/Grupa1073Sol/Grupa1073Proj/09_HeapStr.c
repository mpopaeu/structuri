#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define DIM 20

void insert_key_heap(int* heap_struct, int* heap_struct_size, int key)
{
	*heap_struct_size += 1;
	int offs_key = *heap_struct_size - 1;
	heap_struct[offs_key] = key;

	int offs_parent = (offs_key - 1) / 2;

	while (heap_struct[offs_key] > heap_struct[offs_parent])
	{
		int aux = heap_struct[offs_key];
		heap_struct[offs_key] = heap_struct[offs_parent];
		heap_struct[offs_parent] = aux;

		offs_key = offs_parent;

		offs_parent = (offs_key - 1) / 2;
	}
}


int delete_key_heap(int* heap_struct, int* heap_struct_size)
{
	int key;
	int offs_key = 0;
	int max = 0;

	int last_item = heap_struct[*heap_struct_size - 1];
	key = heap_struct[0];
	heap_struct[0] = last_item;

	*heap_struct_size -= 1;

	int left_child = 2 * offs_key + 1;
	int right_child = 2 * offs_key + 2;

	if ((left_child < *heap_struct_size) && (right_child < *heap_struct_size))
	{
		if (heap_struct[left_child] > heap_struct[right_child])
		{
			max = left_child;
		}
		else
		{
			max = right_child;
		}
	}
	else
	{
		if (left_child < *heap_struct_size)
		{
			max = left_child;
		}
	}

	while ((*heap_struct_size > 0) && (heap_struct[max] > last_item))
	{
		int aux = heap_struct[offs_key];
		heap_struct[offs_key] = heap_struct[max];
		heap_struct[max] = aux;

		offs_key = max;

		left_child = 2 * offs_key + 1;
		right_child = 2 * offs_key + 2;
		if ((left_child < *heap_struct_size) && (right_child < *heap_struct_size))
		{
			if (heap_struct[left_child] > heap_struct[right_child])
			{
				max = left_child;
			}
			else
			{
				max = right_child;
			}
		}
		else
		{
			if (left_child < *heap_struct_size)
			{
				max = left_child;
			}
		}
	}

	return key;
}



int main()
{
	int* heap_struct = NULL;

	heap_struct = (int*)malloc(DIM * sizeof(int));
	int max_storage = DIM;

	int no_keys = 0, insert_key;

	FILE* f;
	f = fopen("HeapKeys.txt", "r");

	fscanf(f, "%d", &insert_key);
	while (!feof(f))
	{
		if (no_keys == max_storage)
		{
			max_storage += DIM;
			int* new_heap_struct = (int*)malloc(max_storage * sizeof(DIM));
			for (int i = 0; i < no_keys; i++)
				new_heap_struct[i] = heap_struct[i];

			free(heap_struct);
			heap_struct = new_heap_struct;
		}

		insert_key_heap(heap_struct, &no_keys, insert_key);

		fscanf(f, "%d", &insert_key);
	}

	printf("\n Heap structure right after creation: ");
	for (int i = 0; i < no_keys; i++)
		printf(" %d ", heap_struct[i]);

	insert_key_heap(heap_struct, &no_keys, 26); // a new key 26 is inserted into Heap structure

	printf("\n\n Heap structure after insertion of the key 26: ");
	for (int i = 0; i < no_keys; i++)
		printf(" %d ", heap_struct[i]);
	printf("\n");

	insert_key = delete_key_heap(heap_struct, &no_keys);
	printf("\n\n Heap structure after deletion (key from the root node): ");
	for (int i = 0; i < no_keys; i++)
		printf(" %d ", heap_struct[i]);
	printf("\n");

	printf("Deletion of all keys in the Heap structure: ");
	while (no_keys > 0)
	{
		printf(" %d ", delete_key_heap(heap_struct, &no_keys));
	}
	printf("\n\n");

	free(heap_struct);

	fclose(f);
	return 0;
}