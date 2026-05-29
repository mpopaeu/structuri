#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SecListNode {
	unsigned char* pid;
	struct SecListNode* next;
};
struct MainListNode {
	unsigned char id;
	struct MainListNode* next;
	struct SecListNode* head;
};

typedef struct SecListNode SecListNode;
typedef struct MainListNode MainListNode;


MainListNode* insertMainList(MainListNode* head, unsigned char node_id)
{
	MainListNode* new_node = malloc(sizeof(MainListNode));
	new_node->id = node_id;
	new_node->head = NULL; // there is no direct connection yet
	new_node->next = NULL;

	if (head == NULL)
	{
		return new_node;
	}
	else
	{
		MainListNode* temp = head;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new_node;
	}

	return head;
}

// heap memory address will be stored in the secondary list
// to avoid data duplication accross the graph
SecListNode* insertSecList(SecListNode* head, unsigned char *pid)
{
	SecListNode* new_node = malloc(sizeof(SecListNode));
	new_node->pid = pid;
	new_node->next = NULL;

	if (head == NULL)
	{
		return new_node;
	}
	else
	{
		SecListNode* temp = head;
		while (temp->next != NULL)
			temp = temp->next;

		temp->next = new_node;
	}

	return head;
}

int main()
{

	FILE* f = fopen("Graph.txt", "r");

	MainListNode* head_mainlist = NULL;

	unsigned char n_nodes = 0;
	fscanf(f, "%hhu", &n_nodes);

	for (unsigned char i = 0;i < n_nodes; i++)
	{
		head_mainlist = insertMainList(head_mainlist, (unsigned char)(i + 1));
	}


	while (!feof(f))
	{
		unsigned char src, dst;
		fscanf(f, "%hhu,%hhu", &src, &dst);

		MainListNode* temp = head_mainlist;

		// insert the edge (src,dst)
		while (temp != NULL)
		{
			if (temp->id == src)
			{
				MainListNode* temp_dst = head_mainlist;
				unsigned char stop = 0;
				while (temp_dst != NULL && stop == 0)
				{
					if (temp_dst->id == dst)
					{
						stop = 1;
					}
					else
						temp_dst = temp_dst->next;
				}

				temp->head = insertSecList(temp->head, &temp_dst->id);
			}
			temp = temp->next;
		}

		temp = head_mainlist;
		// inserte the edge (dst,src)
		while (temp != NULL)
		{
			if (temp->id == dst)
			{
				MainListNode* temp_dst = head_mainlist;
				unsigned char stop = 0;
				while (temp_dst != NULL && stop == 0)
				{
					if (temp_dst->id == src)
					{
						stop = 1;
					}
					else
						temp_dst = temp_dst->next;
				}

				temp->head = insertSecList(temp->head, &temp_dst->id);
			}
			temp = temp->next;
		}

	}

	printf("Graph stored as list (nodes) of lists (edges):\n");
	MainListNode* temp = head_mainlist;
	while (temp != NULL)
	{
		printf("\nNode %d in the graph having the direct connections -> ", temp->id);
		SecListNode* temp_sec = temp->head;
		while (temp_sec != NULL)
		{
			printf("%d ", *(temp_sec->pid));
			temp_sec = temp_sec->next;
		}

		temp = temp->next;
	}

	return 0;
}
