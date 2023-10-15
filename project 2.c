#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
typedef struct
{
    char *name;
    float CET_percentile;
    int Category;
    int first_priority;
    int second_priority;
} Student;

// Structure to represent the priority queue
typedef struct
{
    Student **students;
    int capacity;
    int size;
} PriorityQueue;

typedef struct branch
{
    Student **students;
    int total_seats;
    int size;
    int open;
    int obc;
    int st;
    int nt;
    int sc;
} branch;

branch *createBranch(int total_seats)
{
    branch *br = (branch *)malloc(sizeof(branch));
    br->students = (Student **)malloc(sizeof(Student *) * total_seats);
    br->total_seats = total_seats;
    br->size = 0;
    int t = total_seats / 10;
    br->open = t * 5;
    br->st = t;
    br->nt = t;
    br->sc = t;
    br->obc = total_seats - t * 8;

    return br;
}

// Function to create a new priority queue
PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

    // Array created.
    pq->students = (Student **)malloc(capacity * sizeof(Student *));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

// Function to swap two students
void swapStudents(Student **a, Student **b)
{
    Student *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the heap property of the priority queue
void heapifyDown(PriorityQueue *pq, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->students[left]->CET_percentile > pq->students[largest]->CET_percentile)
        largest = left;

    if (right < pq->size && pq->students[right]->CET_percentile > pq->students[largest]->CET_percentile)
        largest = right;

    if (largest != i)
    {
        swapStudents(&pq->students[i], &pq->students[largest]);
        heapifyDown(pq, largest);
    }
}

// Function to maintain the heap property of the priority queue
void heapifyUp(PriorityQueue *pq, int i)
{
    int childIndex = i;

    while (childIndex > 0)
    {
        int parentIndex = (childIndex - 1) / 2;

        if (pq->students[childIndex]->CET_percentile > pq->students[parentIndex]->CET_percentile)
        {
            swapStudents(&pq->students[childIndex], &pq->students[parentIndex]);
        }
        else
        {
            break;
        }
        childIndex = parentIndex;
    }
}

// Function to insert a student into the priority queue
void insertStudent(PriorityQueue *pq, Student *s1)
{
    if (pq->size == pq->capacity)
    {
        printf("Priority queue is full. Cannot insert student.\n");
        return;
    }

    pq->students[pq->size] = s1;
    pq->size++;

    heapifyUp(pq, pq->size - 1);
}

// Function to remove the student with the highest priority from the queue
Student *removeStudent(PriorityQueue *pq)
{
    if (pq->size == 0)
    {
        printf("Priority queue is empty. Cannot remove student.\n");
        return NULL;
    }

    Student *highestPriorityStudent = pq->students[0];
    pq->students[0] = pq->students[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);

    // printf("%s\n",highestPriorityStudent->name);
    return highestPriorityStudent;
}

// Function to display the contents of the priority queue
void displayPriorityQueue(PriorityQueue *pq)
{
    printf("Priority Queue Contents:\n");
    for (int i = 0; i < pq->size; i++)
    {
        printf("Name: %s, Priority: %.2f\n", pq->students[i]->name, pq->students[i]->CET_percentile);
    }
}

void admission_form(PriorityQueue *pq)
{
    Student *s1 = (Student *)malloc(sizeof(Student));

    s1->name = (char *)malloc(sizeof(char) * 100);

    printf("Enter name: ");
    // char name[100];
    // fgets(name, sizeof(name), stdin);
    // name[strcspn(name, "\n")] = '\0';
    // strcpy(s1->name,name);
    scanf("%s", s1->name);

    printf("Enter CET Percentile: ");
    scanf("%f", &(s1->CET_percentile));

   
    printf("Enter Your Category:\n");
    printf("1. Open\n");
    printf("2. OBC\n");
    printf("3. NT\n");
    printf("4. SC\n");
    printf("5. ST\nEnter here : ");
    scanf("%d", &(s1->Category));
    printf("\n");

    printf("Enter Your Priorities for Branches:\n");
    printf("1. Computer Engi.\n");
    printf("2. Electrical Engi.\n");
    printf("3. ENTC\n");
    printf("4. Instrumentation\n");
    printf("First priority: ");
    scanf("%d", &(s1->first_priority));
    printf("\n");
    printf("Second priority: ");
    scanf("%d", &(s1->second_priority));

    // Inserting students into the priority queue
    insertStudent(pq, s1);
}

int addToBranch(PriorityQueue *pq, branch *br, Student *st)
{
    if (br->size == 20)
    {
        // printf("Seats are full\n");
        return 0;
    }
    if (st->Category == 1)
    {
        if (br->open == 0)
        {
            // printf("Seats are full\n");
            return 0;
        }

        br->students[br->size] = st;
        br->size++;
        br->open--;
        return 1;
    }

    if (st->Category == 2)
    {
        if (br->open == 0)
        {
            if (br->obc == 0)
            {
                return 0;
            }
            br->students[br->size] = st;
            br->size++;
            br->obc--;
            return 1;
        }

        br->students[br->size] = st;
        br->size++;
        br->open--;
        return 1;
    }

    if (st->Category == 3)
    {
        if (br->open == 0)
        {
            if (br->nt == 0)
            {
                return 0;
            }
            br->students[br->size] = st;
            br->size++;
            br->nt--;
            return 1;
        }

        br->students[br->size] = st;
        br->size++;
        br->open--;
        return 1;
    }

    if (st->Category == 4)
    {
        if (br->open == 0)
        {
            if (br->sc == 0)
            {
                return 0;
            }
            br->students[br->size] = st;
            br->size++;
            br->sc--;
            return 1;
        }

        br->students[br->size] = st;
        br->size++;
        br->open--;
        return 1;
    }

    if (st->Category == 5)
    {
        if (br->open == 0)
        {
            if (br->st == 0)
            {
                return 0;
            }
            br->students[br->size] = st;
            br->size++;
            br->st--;
            return 1;
        }

        br->students[br->size] = st;
        br->size++;
        br->open--;
        return 1;
    }
}

void allocateBranch(PriorityQueue *pq, Student *st, branch *comp, branch *elec, branch *entc, branch *instru)
{
    int priority_1 = st->first_priority;
    int priority_2 = st->second_priority;

    int alloted_status;

    // comp
    if (priority_1 == 1)
    {
        alloted_status = addToBranch(pq, comp, st);
    }

    // ele
    if (priority_1 == 2)
    {
        alloted_status = addToBranch(pq, elec, st);

        // entc
    }
    if (priority_1 == 3)
    {
        alloted_status = addToBranch(pq, entc, st);

        // instru
    }
    if (priority_1 == 4)
    {
        alloted_status = addToBranch(pq, instru, st);
    }

    // if priority one is alloted then don't look for second priority
    if (alloted_status)
    {
        return;
    }

    if (priority_2 == 1)
    {
        addToBranch(pq, comp, st);
        return;
    }
    if (priority_2 == 2)
    {
        addToBranch(pq, elec, st);
        return;
    }
    if (priority_2 == 3)
    {
        addToBranch(pq, entc, st);
        return;
    }
    if (priority_2 == 4)
    {
        addToBranch(pq, instru, st);
        return;
    }
}

void display_branch_student(branch *br)
{
    for (int i = 0; i < br->size; i++)
    {
        Student *current = br->students[i];
        printf("    %d. Name: %s     Percentile: %0.2f ", i + 1, current->name, current->CET_percentile);
        if (current->Category == 1)
            printf("    Category: Open\n");
        if (current->Category == 2)
            printf("    Category: OBC\n");
        if (current->Category == 3)
            printf("    Category: NT\n");
        if (current->Category == 4)
            printf("    Category: SC\n");
        if (current->Category == 5)
            printf("    Category: ST\n");
    }

    printf("\n\n");
}

void Allocation(PriorityQueue *pq)
{

    branch *comp = createBranch(10);
    branch *elec = createBranch(10);
    branch *entc = createBranch(10);
    branch *instru = createBranch(10);

    // Student* current_student = removeStudent(pq);
    while (pq->size != 0)
    {
        Student *current_student = removeStudent(pq);
        allocateBranch(pq, current_student, comp, elec, entc, instru);
    }

    printf("Selected Computer Students are:\n");
    display_branch_student(comp);

    printf("Selected Electrical Students are:\n");
    display_branch_student(elec);

    printf("Selected ENTC Students are:\n");
    display_branch_student(entc);

    printf("Selected Instrumentation Students are:\n");
    display_branch_student(instru);
}

int main()
{
    printf("Enter no. of forms to be accepted : ");
    int num;
    scanf("%d", &num);
    PriorityQueue *pq = createPriorityQueue(num);

    int n;
    do
    {

        printf("Enter Your Choice:\n");
        printf("1. Admission Form\n");
        printf("2. Allocate Seats\n");
        printf("3. Exit\nEnter here : ");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            admission_form(pq);
            break;

        case 2:
            Allocation(pq);
            break;

        case 3:
            printf("Exiting the program.\n");
            for (int i = 0; i < pq->size; i++)
            {
                free(pq->students[i]);
            }
            free(pq->students);
            free(pq);
            return 0;
            break;

        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (n != 4);

    return 0;
}