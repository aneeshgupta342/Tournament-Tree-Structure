#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* next;
    struct node* down;
    int skill1;
    int skill2;
} node;

int max(int a, int b) {
    return a > b ? a : b;
}

node* createNode(int skill1, int skill2) {
    node* head = (node*)malloc(sizeof(node));
    head->next = NULL;
    head->down = NULL;
    head->skill1 = skill1;
    head->skill2 = skill2;
    return head;
}

node* create_level(node* head) {
    node* new_head = NULL;
    node* prev = NULL;
    node* temp = head;

    while (temp != NULL) {
        node* temp2 = NULL;

      
        if (temp->next == NULL) {
            temp2 = createNode(max(temp->skill1, temp->skill2), -1e7);  
        } else {
           
            int max1 = max(temp->skill1, temp->skill2);
            int max2 = max(temp->next->skill1, temp->next->skill2);
            temp2 = createNode(max1, max2);
        }

       
        temp->down = temp2;
        if (temp->next) {
            temp->next->down = temp2;
        }

        
        if (prev) {
            prev->next = temp2;
        }

        prev = temp2;

        
        temp = temp->next ? temp->next->next : NULL;

        if (new_head == NULL) {
            new_head = temp2;
        }
    }

    return new_head;
}

node* create_first_level(int n, int skill[]) {
    node* prev = NULL;
    node* head = NULL;

    for (int i = 0; i < n; i += 2) {
        node* temp = NULL;

        if (i == n - 1) {
            
            temp = createNode(skill[i], -1e7);  
        } else {
            temp = createNode(skill[i], skill[i + 1]);
        }

        if (prev) {
            prev->next = temp;
        }

        if (i == 0) {
            head = temp;
        }

        prev = temp;
    }

    return head;
}

void simulate_helper(node* level) {
    if (level == NULL || level->next == NULL) {
        return;
    }

    node* next_level = create_level(level);
    simulate_helper(next_level);
}

int simulate_tournament(int n, int skill[]) {
    node* start = create_first_level(n, skill);
    simulate_helper(start);
    
    node *temp= start;
    while(temp->down != NULL)
    temp = temp->down;
    
    print_tree(start);
    return max(temp->skill1, temp->skill2);
    
}

void print_tree(node * start)
{
  int count =1;
  while(start)
  {
    printf("Round %d:\n", count);
    int count2 = 1;
    node *temp = start;
    while(temp != NULL)
    {
      int d1 = temp->skill1;
      int d2 = temp->skill2;
      printf("M%d = ", count2);
      count2++;
      if(d1 != -1e7)
      printf("%d ", d1);
      if(d2 != -1e7)
      printf("%d ", d2);
      
      temp = temp->next;
    }
    start = start->down;
    count++;
    printf("\n");
    
  }
}




int main() {
    int n;
    scanf("%d", &n);
    int skill[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &skill[i]);
    }

    int winner = simulate_tournament(n, skill);
    printf("Winner(skill level) = %d\n", winner);
    
    

    
    
   
    

    return 0;
}
