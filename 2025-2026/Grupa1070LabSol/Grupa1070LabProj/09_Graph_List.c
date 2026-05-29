#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct NodeSecList {
	unsigned char edge_node;
	struct NodeSecList* next;
};

struct NodeMainList
{
	unsigned char node_id;
	struct NodeMainList* next;
	struct NodeSecList* head_sec_list;
};

typedef struct NodeSecList NodeSecList;
typedef struct NodeMainList NodeMainList;

NodeMainList* insertNodeMainList(NodeMainList* list, unsigned char id)
{
	NodeMainList* new_node = malloc(sizeof(NodeMainList));

	new_node->node_id = id;
	new_node->head_sec_list = NULL; //initially, the secondary (edges) list si empty
	new_node->next = NULL;

	if (list == NULL) return new_node;

	NodeMainList* temp = list;
	while (temp->next != NULL) temp = temp->next;

	temp->next = new_node;
	return list;

}

NodeSecList* insertNodeSecList(NodeSecList* list, unsigned char id)
{
	NodeSecList* new_node = malloc(sizeof(NodeSecList));

	new_node->edge_node = id;
	new_node->next = list;

	return new_node;
}

int main()
{
	FILE* f = fopen("Graph.txt", "r");

	unsigned char no_nodes;
	fscanf(f, "%hhu", &no_nodes);

	NodeMainList* graph_list = NULL;

	for (unsigned char i = 1; i <= no_nodes; i++)
		graph_list = insertNodeMainList(graph_list, i);

	while (!feof(f))
	{
		unsigned char src, dst;
		fscanf(f, "%hhu,%hhu", &src, &dst);

		// insert the edge [src,dst]
		NodeMainList* temp = graph_list;
		unsigned char insert_flag = 0;
		while (temp != NULL && insert_flag == 0)
		{
			if (temp->node_id == src)
			{
				temp->head_sec_list = insertNodeSecList(temp->head_sec_list, dst);
				insert_flag = 1;
			}
			else
				temp = temp->next;
		}

		// insert the edge [dst,src] -> graph is not oriented
		temp = graph_list;
		insert_flag = 0;
		while (temp != NULL && insert_flag == 0)
		{
			if (temp->node_id == dst)
			{
				temp->head_sec_list = insertNodeSecList(temp->head_sec_list, src);
				insert_flag = 1;
			}
			else
				temp = temp->next;
		}
	}

	fclose(f);

	printf("List-of-list structure to store the graph\n");
	NodeMainList* temp = graph_list;
	while (temp != NULL)
	{
		printf("\nThe edges for the node %d: ", temp->node_id);
		NodeSecList* temp_sec = temp->head_sec_list;
		while (temp_sec != NULL)
		{
			printf(" %d ", temp_sec->edge_node);
			temp_sec = temp_sec->next;
		}


		temp = temp->next;
	}

	// traversal operations over the graph (see 1071 implementation)

	// deallocate the list-of-lists

	return 0;
}