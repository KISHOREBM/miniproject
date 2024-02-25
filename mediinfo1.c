#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    char name[20],cont[20],disease[20],symp[10][20],s[10],id[20];
    float bill;
    struct node* link;
};
typedef struct node* NODE;
NODE getnode()
{
    NODE x;
    x=(NODE)malloc(sizeof(struct node));
    if(x==NULL)
    {
        printf("memory not allocated\n");
        exit(0);
    }
    return x;
}
NODE intake(FILE *inputFile)
{
    NODE temp = getnode();
    fscanf(inputFile, "%s %s %s %s", temp->id, temp->name, temp->cont, temp->disease);
    for (int i = 0; ; i++)
    {
        fscanf(inputFile, "%s", temp->symp[i]);
        if(strcmp(temp->symp[i], "no") == 0)
        break;
    }
    
    fscanf(inputFile, "%s", temp->s);
    fscanf(inputFile, "%f", &(temp->bill));
    return temp;
}

NODE insert(NODE head, FILE *inputFile)
{
    NODE temp = intake(inputFile);
    temp->link = head->link;
    head->link = temp;
    return head;
}

NODE delete(NODE head,FILE *inputFile)
{
    NODE cur = head->link;
    char num[10];
    fscanf(inputFile,"%s",num);
    NODE prv = head;

    while (cur != NULL)
    {
        if (strcmp(cur->id, num) == 0)
        {
            printf("%s with id deleted\n", num);
            prv->link = cur->link;
            free(cur);
            return head;
        } 

        prv = cur;
        cur = cur->link;
    }

    printf("id not found\n");
    return head;
}
void suc(NODE head,FILE *inputFile)
{
    if (head->link == NULL)
    {
        printf("no information\n");
        return;
    }

    char type[10];
    fscanf(inputFile,"%s",type);
    int totalCases = 0;
    int successCases = 0;

    NODE cur = head->link;
    
    while (cur != NULL)
    {
        if (strcmp(cur->disease, type) == 0)
        {
            totalCases++;

            if (strcmp(cur->s, "success") == 0)
            {
                successCases++;
            }
        }

        cur = cur->link;
    }

    if (totalCases == 0)
    {
        printf("No cases found for the given disease.\n");
        return;
    }

    float successRate = (float)successCases / totalCases * 100;
    printf("Success rate for %s is %.2f%%\n", type, successRate);
}
void display(NODE head)
{
    if (head->link == NULL)
    {
        printf("no nodes\n");
        return;
    }

    NODE cur = head->link;

    while (cur != NULL)
    {
        printf("\nid=%s\nname=%s\ncontact=%s\ndisease=%s\nsucesses=%s\n", cur->id, cur->name, cur->cont, cur->disease, cur->s);

        printf("Symptoms:\n");
        for (int i = 0; strcmp(cur->symp[i], "no") != 0; i++)
        {
            printf("%d.%s\n", i + 1, cur->symp[i]);
        }

        printf("bill=%f\n", cur->bill);
        cur = cur->link;
    }
}

int main()
{
    NODE head = getnode();
    head->link = NULL;
    int ch;
    FILE *inputFile = fopen("data.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    while (1)
    {
        fscanf(inputFile, "%d", &ch);
        switch (ch)
        {
        case 1:
            head = insert(head,inputFile);
            break;
        case 2:
            head = delete(head,inputFile);
            break;
        case 3:
            display(head);
            break;
        case 4:
            suc(head,inputFile);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }
    fclose(inputFile);

    return 0;
}
