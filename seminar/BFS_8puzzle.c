#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
#define SIZE 9
#define MAX_VISITED 400000

//  -----------  NODE

typedef struct _node* NodePosition;
typedef struct _node {
    int board[N][N];
    int m;
    NodePosition parent;
} Node;

NodePosition CreateNode(int board[N][N], int m, NodePosition parent);
int equals(int a[N][N], int b[N][N]);
int printBoard(NodePosition node);
int printSolution(NodePosition node);

NodePosition CreateNode(int board[N][N], int m, NodePosition parent)
{
    NodePosition newNode = (NodePosition)malloc(sizeof(Node));
    memcpy(newNode->board, board, sizeof(int) * SIZE);
    newNode->m = m;
    newNode->parent = parent;
    return newNode;
}

int equals(int a[N][N], int b[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i][j] != b[i][j]) return 0;
    return 1;
}

int printBoard(NodePosition node)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", node->board[i][j]);
        printf("\n");
    }
    printf("\n");
    return EXIT_SUCCESS;
}

int printSolution(NodePosition node)
{
    if (node == NULL) return EXIT_SUCCESS;
    printSolution(node->parent);
    printBoard(node);
    return EXIT_SUCCESS;
}

//  -----------  QUEUE

typedef struct _queue* QueuePosition;
typedef struct _queue {
    NodePosition element;
    QueuePosition next;
} Queue;
QueuePosition front = NULL;
QueuePosition rear = NULL;

int isQueueEmpty();
int Enqueue(NodePosition node);
NodePosition Dequeue();

int isQueueEmpty() {
    if (front == NULL)
        return 1;
    else
        return 0;
}

int Enqueue(NodePosition node)
{
    QueuePosition newQueue = (QueuePosition)malloc(sizeof(Queue));
    newQueue->element = node;
    newQueue->next = NULL;

    if (rear == NULL)
    {
        front = rear = newQueue;
    }
    else
    {
        rear->next = newQueue;
        rear = newQueue;
    }
    return EXIT_SUCCESS;
}

NodePosition Dequeue()
{
    if (isQueueEmpty())
        return NULL;

    QueuePosition temp = front;
    NodePosition node = temp->element;

    front = front->next;
    if (front == NULL)
        rear = NULL;

    free(temp);
    return node;
}

//  -----------  VISITED

int Visited[MAX_VISITED][SIZE];
int visited_count = 0;

int isVisited(int board[N][N]);
int MarkVisited(int board[N][N]);

int isVisited(int board[N][N])
{
    int i, j;
    for (i = 0; i < visited_count; i++)
    {
        int match = 1;
        for (j = 0; j < SIZE; j++)
        {
            if (Visited[i][j] != board[j / 3][j % 3])
            {
                match = 0;
                break;
            }
        }
        if (match) return 1;
    }
    return 0;
}
int MarkVisited(int board[N][N])
{
    if (visited_count >= MAX_VISITED)
        return EXIT_FAILURE;

    int i;
    for (i = 0; i < SIZE; i++)
    {
        Visited[visited_count][i] = board[i / 3][i % 3];
    }
    visited_count++;
    return EXIT_SUCCESS;
}

// --------- MOVES

int generateMoves(NodePosition current)
{
    int row[4] = { 0, 0, -1, 1 };  //potezi 
    int col[4] = { 1, -1, 0, 0 };  //--||--
    int x0 = 0, y0 = 0; // pozicija za 0

    int i, j;
    for (i = 0; i < N; i++)  //trazenje 0
    {
        for (j = 0; j < N; j++)
        {
            if (current->board[i][j] == 0) 
            {
                x0 = i;
                y0 = j;
            }
        }
    }

    for (int k = 0; k < 4; k++)
    {
        int nx = x0 + row[k];
        int ny = y0 + col[k];
        
        if (nx >= 0 && nx < N && ny >= 0 && ny < N) // k --  0->left  1->right  2->up  3->down
        {
            int newBoard[N][N];
            memcpy(newBoard, current->board, sizeof(int) * SIZE);

            newBoard[x0][y0] = newBoard[nx][ny];
            newBoard[nx][ny] = 0;

            if (!isVisited(newBoard))
            {
                MarkVisited(newBoard);
                NodePosition newNode = CreateNode(newBoard, current->m + 1, current);
                Enqueue(newNode);

            }
        }
    }
    return EXIT_SUCCESS;

}

// -------BFS
int BFS(int start[N][N], int goal[N][N]) {
    NodePosition root = CreateNode(start, 0, NULL);

    MarkVisited(start);
    Enqueue(root);

    while (!isQueueEmpty()) {
        NodePosition current = Dequeue();

        if (equals(current->board, goal)) {
            printf("Rjesenje pronadjeno u %d poteza:\n\n", current->m);
            printSolution(current);
            return EXIT_SUCCESS;
        }

        generateMoves(current);
    }

    printf("Rjesenje nije pronadjeno.\n");
    return EXIT_FAILURE;
}
int isSolvable(int board[N][N])
{
    int arr[SIZE];
    int k = 0;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            arr[k++] = board[i][j];

    int inv = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = i + 1; j < SIZE; j++)
            if (arr[i] && arr[j] && arr[i] > arr[j])
                inv++;

    return (inv % 2 == 0);
}
int main()
{
    int start[3][3] = { 0 };

    printf("upisi polja: \n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("[%d][%d]: ", i, j);
            scanf("%d", &start[i][j]);
        }
    }
    printf("\nSTART:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%d ", start[i][j]);
        printf("\n");
    }

    if (!isSolvable(start)) {
        printf("Puzzle nema rjesenje.\n");
        return 0;
    }
    else
    {
        printf("Puzzle ima rjesenje.\n");
    }
    int goal[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    BFS(start, goal);
    return EXIT_SUCCESS;
}