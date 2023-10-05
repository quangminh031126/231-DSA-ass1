Q: Let's say i have a circular doubly linked list, each node have an int value and string id. value can be positive or negative. Print items of the longest sublist that has the smallest sum of value, the sublist must have at least 4 items in the format "id value /n" and items must be printed clock wise. If there multiple sublist with the same smallest sum, print the last found sublist. Write this in C++
A: Here is a C++ code snippet that should do what you're asking for. This code assumes that you have a `Node` structure defined with `int value`, `string id`, and `Node* next`, `Node* prev` pointers.

```cpp
#include <iostream>
#include <string>

using namespace std;

struct Node {
    int value;
    string id;
    Node* next;
    Node* prev;
};

void printSmallestSublist(Node* head) {
    Node *start = head, *end = NULL;
    int minSum = INT_MAX, sum = 0, len = 0;
    Node *ptr = head, *minStart = NULL, *minEnd = NULL;

    do {
        sum += ptr->value;
        len++;

        while (sum > minSum || len < 4) {
            sum -= start->value;
            start = start->next;
            len--;
        }

        if ((sum < minSum || (sum == minSum && len >= 4)) && len >= 4) {
            minSum = sum;
            minStart = start;
            minEnd = ptr;
        }

        ptr = ptr->next;

    } while (ptr != head);

    if (minStart == NULL) {
        cout << "No sublist found with at least 4 items." << endl;
        return;
    }

    ptr = minStart;

    do {
        cout << ptr->id << " " << ptr->value << endl;
        ptr = ptr->next;

    } while (ptr != minEnd->next);
}
```

This function `printSmallestSublist` takes the head of the circular doubly linked list as input and prints the id and value of each node in the longest sublist with the smallest sum of values. The sublist must contain at least 4 nodes. If there are multiple such sublists, it prints the last one found. The nodes are printed in a clockwise order. If no such sublist is found, it prints a message indicating so.

Please note that this code does not handle memory allocation or deallocation for the linked list nodes. You would need to implement that separately. Also, this code does not include any error checking or exception handling, so you might want to add that depending on your needs.