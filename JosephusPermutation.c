#include <stdio.h>
#include <stdlib.h>

int LinkedListSize;

struct node {
	int data;
	struct node *next;
	struct node *previous;
};

typedef struct node soldier;

soldier* create_soldier (int sequence);
soldier* create_reverse_circle(int n);
soldier* rearrange_circle(soldier* head);
void display(soldier* head);
int kill(soldier* head, int n, int k);

int main () {
	soldier *root;
	int n = 0, k = 0;

	while (1) {
		printf("Enter number of people, and how often to remove a node: ");
		scanf("%d %d", &n, &k);
		if(n >= 2 && k > 0)
			break;
		printf("GENNERIC ERROR NUMBER PANIC SETS IN... Improper input: (n >= 2) (k > 0)\n");
	}

	LinkedListSize = n;

	root = create_reverse_circle(n);
	printf("List:");
	display(root);

	root = rearrange_circle(root);
	printf("\nAfter ordering:");
	display(root);

	printf("\nSurvived: %d\n", kill(root, n, k));

	return 0;
}

soldier* create_soldier (int sequence) {
	soldier *newSoldier = malloc(sizeof(soldier));
	newSoldier -> data = sequence;
	newSoldier -> next = NULL;
	newSoldier -> previous = NULL;
	return newSoldier;
}

soldier* create_reverse_circle(int n) {
	soldier *retRoot, *back, *tempSoldier;

	// sets up head and subtracts 1 from n for including n in head/root
	retRoot = create_soldier(n);
	n--;

	// rear pointer for linking rest of the nodes.
	back = retRoot;

	// creates and linkes rest of the nodes
	while (n > 0) {
		tempSoldier = create_soldier(n);
		tempSoldier -> previous = back;
		back -> next = tempSoldier;

		back = back -> next;
		n--;
	}

	// Creates the "circularly" links
	retRoot -> previous = back;
	back -> next = retRoot;

	return retRoot;
}

soldier* rearrange_circle(soldier* head) {
	// tempSoldierNext just holds the next value so it doesnt get missed
	// up when switching next n previous
	soldier *tempSoldierNext;

	for (int i = LinkedListSize; i > 0; i--) {
		tempSoldierNext = head -> next;
		head -> next = head -> previous;
		head -> previous = tempSoldierNext;
		head = tempSoldierNext;
	}

	// returns head -> next as head is currently pointing to the "end"
	// of the list, however becuase the circular link, next points to true head.
	return head -> next;
}

void display(soldier* head) {
	for (int i = LinkedListSize; i > 0; i--) {
		printf(" %d", head -> data);
		head = head -> next;
	}
}

int kill(soldier* head, int n, int k) {
	// killCounter just adds up and resets to figure out when to "kill" a node
	int retData, killCounter = 1;
	soldier *tempSoldier;

	while (head ->  next != head) {
		if (killCounter == k) {
			// stitches nodes behind and ahead together
			head -> previous -> next = head -> next;
			head -> next -> previous = head -> previous;

			// holds the "kill" node to move head and frees the "killed" node
			tempSoldier = head;
			head = head ->  next;
			free(tempSoldier);
			killCounter = 1;
		} else {
			head = head ->  next;
			killCounter ++;
		}
	}

	retData = head -> data;
	free(head);
	return retData;
}