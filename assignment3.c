#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
//Haziq Ahmed
//Adeel 
// Arham
//Tayab
// state counter (THis specifies the index where new state should be added)
int state_counter = 0;
char state_list[100][100][100] = {{'\0'}}; // This variable is used to store chronicles of a grammer. The index value specifies the states
char non_terminals[100] = {'\0'};          // an array of non-terminals
int non_terminals_index = 0;               // index for non-terminals
char terminals[100] = {'\0'};              // an array of terminals
int terminals_index = 0;                   // index for terminals
char production[100][100][100] = {{'\0'}}; // productions are stored here

// Testing stuff here
char new_states[100][100] = {{'\0'}};

int total_productions;
/*           DEFINING STACK HERE           */
int MAXSIZE = 20;
int stack[20];
int top = -1;

int isempty()
{

    if (top == -1)
        return 1;
    else
        return 0;
}

int isfull()
{

    if (top == MAXSIZE)
        return 1;
    else
        return 0;
}

int peek()
{
    return stack[top];
}

int pop()
{
    int data;

    if (!isempty())
    {
        data = stack[top];
        top = top - 1;
        return data;
    }
    else
    {
        printf("Could not retrieve data, Stack is empty.\n");
        return -1;
    }
}

int push(int data)
{

    if (!isfull())
    {
        top = top + 1;
        stack[top] = data;
    }
    else
    {
        printf("Could not insert data, Stack is full.\n");
        return -1;
    }
}

/*              END OF STACK               */
// swap function to swap two characters:
int swap_dot(char string[], int index)
{
    char temp = string[index];
    char temp2 = string[index + 1];
    string[index] = temp2;
    string[index + 1] = temp;
    return 0;
}

// function to break apart a grammer into left side terminal and its productions
int find_dot(char string[])
{
    for (int i = 0; i < 20; i++)
    {
        if (string[i] == '\0')
        {
            break;
        }
        if (string[i] == '.')
        {
            return i;
        }
    }
    return -1;
}

// Find if we need to add a new state for the current non terminal
int is_NT(int index, char production[], char non_terminal)
{

    if (non_terminal == production[index + 1])
    {
        return 1;
    }

    return 0;
}

int check_new_state(char new_state[100][100], int productions, int index, int length, int k)
{
    char temp[100];
    for (int j = 0; j < length; j++)
    {
        char temp[100] = {'\0'};
        temp[0] = non_terminals[k];
        temp[1] = '-';
        temp[2] = '>';
        for (int n = 0; n < strlen(production[k][j]); n++)
        {
            printf("this: %c\n", production[k][j][n]);
            temp[3 + n] = production[k][j][n];
        }
        printf("%s temp\n", temp);
        for (int i = 0; i < 100; i++)
        {
            if (new_state[i][0] == '\0')
            {
                break;
            }
            if (strcmp(new_state[i], temp) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

// returns the index of non terminal in the non-terminals array if non-terminal is found
char find_closure(char new_state[100][100], int productions, int index)
{
    int closure_index = 0;
    int result = 0;
    for (int m = 0; m < productions; m++)
    {
        for (int k = 0; k < strlen(non_terminals); k++)
        {
            closure_index = find_dot(new_state[m]);
            if (is_NT(closure_index, new_state[m], non_terminals[k]) == 1)
            {
                // printf("hea: %c     %s %d\n", non_terminals[k], new_state[m], closure_index);
                // Finds number of productions for the non terminal
                int length = 0;
                for (int i = 0; i < 100; i++)
                {
                    if (production[k][i][0] == '\0')
                    {
                        break;
                    }
                    length++;
                }
                result = check_new_state(new_state, productions, index, length, k);
                printf("result %d\n", result);
                if (result == 1)
                {
                    for (int j = 0; j < length; j++)
                    {
                        new_state[productions][0] = non_terminals[k];
                        new_state[productions][1] = '-';
                        new_state[productions][2] = '>';
                        for (int n = 0; n < strlen(production[k][j]); n++)
                        {
                            new_state[productions][3 + n] = production[k][j][n];
                        }
                        productions++;
                        printf("Closure: %c->%s\n", non_terminals[k], production[k][j]);
                    }
                }
                // for (int i = 0; i < 100; i++)
                // {
                //     printf("YAHH: %c\n", new_state[productions][i]);
                // }
            }
        }
    }
}

int find_index(char terminal_symbol)
{
    for (int i = 0; i < strlen(non_terminals); i++)
    {
        // printf("%c terminals\n",non_terminals[i]);
        if (non_terminals[i] == terminal_symbol)
        {
            return i;
        }
    }
    return -1;
}
int find_production_count(int index)
{
    int i = 0;
    while (i < 100)
    {
        if (production[index][i][0] == '\0')
        {
            return i;
        }
        i = i + 1;
    }
    return -1;
}
char break_prod(char *prod)
{
    // to count number of productions to make an array list
    int count = 0;
    int max = 0;
    int size = 0;
    for (int i = 3; i < strlen(prod); i++)
    {
        if (prod[i] == '|')
        {
            if (max < size)
            {
                max = size;
            }
            size = 0;
            count++;
        }
        size++;
    }
    char ans[count][max];
}

// This function is used to add new states in the state list. This new state will be added in index (value depends upon the state counter) of state list
void add_new_state(int length, char new_state[100][100])
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        count = 0;
        for (int j = 0; j < strlen(new_state[i]); j++)
        {
            state_list[state_counter][i][j] = new_state[i][j];
        }
    }
}

// THis function is used for reading grammer from the file and store it in the state 0 (The index 0 of the state list)
void file_handler()
{
    FILE *ptr;
    ptr = fopen("grammer.txt", "r");
    char temp[80]; // temp array used for copying a single line from a file
    if (ptr == NULL)
    {
        printf("There was an error in opening the file");
    }
    int count = 0;
    int production_index = 0;
    // THese steps are used to store S^bar -> S
    state_list[state_counter][production_index][count] = 'Q';
    count++;
    state_list[state_counter][production_index][count] = '-';
    count++;
    state_list[state_counter][production_index][count] = '>';
    count++;
    state_list[state_counter][production_index][count] = '.';
    count++;
    // Adding start state to non terminals list
    non_terminals[non_terminals_index] = 'Q';
    non_terminals_index++;
    while (fgets(temp, sizeof(temp), ptr) != NULL)
    {
        for (int i = 0; i < strlen(temp); i++)
        {
            if (temp[i] == ' ')
            {
                continue;
            }
            else if (temp[i] != '\n' && temp[i] != '>' && temp[i] != '|' && temp[i] != '-')
            {
                if (production_index == 0)
                {
                    state_list[state_counter][production_index][count] = temp[i];
                    count = 0;
                    production_index++;
                }
                state_list[state_counter][production_index][count] = temp[i];
                count++;
                if (i == strlen(temp) - 1)
                {
                    production_index++;
                }
            }
            else if (temp[i] == '>')
            {
                state_list[state_counter][production_index][count] = temp[i];
                count++;
                state_list[state_counter][production_index][count] = '.';
                count++;
            }
            else if (temp[i] == '-')
            {
                non_terminals[non_terminals_index] = temp[i - 1];
                non_terminals_index++;
                state_list[state_counter][production_index][count] = temp[i];
                count++;
            }
            else if (temp[i] == '|')
            {
                production_index++;
                count = 0;
                while (state_list[state_counter][production_index - 1][count] != '.')
                {
                    state_list[state_counter][production_index][count] = state_list[state_counter][production_index - 1][count];
                    count++;
                }
                state_list[state_counter][production_index][count] = '.';
                count++;
            }
            else
            {
                production_index++;
            }
        }
        count = 0;
        memset(temp, 0, 80);
    }
    state_counter++;
    total_productions = production_index;
    fclose(ptr);
}

// This function is used to check if the new productions created through traversal is already in the store as state or not
// First it will find the total matched productions in a state and compare it with total productions in the new production list
// If its equal that means that the new production state is already in the state list and if not then it will add it in the state list
int check_state(char new_state[100][100], int length)
{
    if (new_state[0][0] == '\0')
    {
        return 0;
    }
    int production_count_new_state; // This variable is used to count the number of productions in the new state
    int x = 0;
    int check_match; // We will count how many strings were matched
    // if the number of strings match is equal to length of the new_state then we will not append that state
    for (int i = 0; i < state_counter; i++)
    {
        production_count_new_state = 0;
        check_match = 0;
        for (int count_new_state_production = 0; count_new_state_production < length; count_new_state_production++) // This will iterate over all the productions made through the traversal
        {
            if (state_list[i][count_new_state_production][0] == '\0') // THis is used to figure out the total number of production in a new state list
            {
                // production_count_new_state--;
                break;
            }
            for (int j = 0; j < strlen(state_list[i][0]); j++)
            {
                if (strcmp(new_state[count_new_state_production], state_list[i][j]) == 0)
                {
                    check_match++; // string matched
                }
            }
            production_count_new_state++;
        }
        printf("%d\t%d\n", production_count_new_state, check_match);
        if (check_match == production_count_new_state)
        {
            break;
        }
    }
    if (check_match != production_count_new_state)
    {
        printf("not Matched\n");
        // This will append the new state in the state list
        add_new_state(length, new_state);
        state_counter++;
        return 1;
    }
    return 0;
}

// This function is simply to display the chronicles
void display_states()
{
    for (int i = 0; i < state_counter; i++)
    {
        printf("state %d\n", i);
        for (int j = 0; j < total_productions; j++)
        {
            if (strcmp(state_list[i][j], "\0") != 0)
            {
                printf("%s\n", state_list[i][j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    // char production[100][100][100] = {{'\0'}};
    file_handler();
    for (int i = 0; i < total_productions; i++)
    {
        printf("%s\n", state_list[0][i]);
    }

    // new_state formate char new_state1[100][100] = {"Q->S.","Q->SLR"}; anthing in 2d array. just store it in tthis kinds of array

    // char new_state1[100][100] = {"Q->.S"};
    // int length1 = sizeof(new_state1) / sizeof(new_state1[0]);
    // char new_state2[100][100] = {"Q->S."};
    // int length2 = sizeof(new_state2) / sizeof(new_state2[0]);
    // printf("result %d\n", check_state(new_state1, length1));
    // display_states();
    // printf("result %d\n", check_state(new_state2, length2));
    // display_states();
    // int length3 = sizeof(new_state2) / sizeof(new_state2[0]);
    // printf("result %d\n", check_state(new_state2, length3));
    // display_states();
    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%s\n", grammer[i]);
    // }
    for (int i = 0; i < strlen(non_terminals); i++)
    {
        printf("Non Terminals: %c\n", non_terminals[i]);
    }

    // to seperate out non terminals
    for (int j = 0; j < total_productions; j++)
    {
        for (int i = 0; i < strlen(state_list[0][j]); i++)
        {
            int flag;
            for (int k = 0; k < strlen(non_terminals); k++)
            {
                if (state_list[0][j][i] != non_terminals[k] && state_list[0][j][i] != '-' && state_list[0][j][i] != '>' && state_list[0][j][i] != '.')
                {
                    flag = 1;
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {

                terminals[terminals_index] = state_list[0][j][i];
                terminals_index++;
            }
        }
    }

    for (int i = 0; i < strlen(terminals); i++)
    {

        printf("Terminals: %c\n", terminals[i]);
    }

    // to separate production
    for (int j = 0; j < total_productions; j++)
    {
        int flag = 0;
        char terminal = state_list[0][j][0];
        int index = find_index(terminal);
        int pro_index = find_production_count(index); // production index
        int count = 0;

        for (int i = 1; i < strlen(state_list[0][j]); i++)
        {
            if (flag == 1)
            {
                production[index][pro_index][count] = state_list[0][j][i];
                count += 1;
            }
            if (state_list[0][j][i] == '>')
            {
                flag = 1;
            }
        }
    }

    printf("productions\n");
    for (int i = 0; i < 100; i++)
    {
        printf("index %d\n", i);
        if (production[i][0][0] == '\0')
        {
            break;
        }
        for (int j = 0; j < 100; j++)
        {
            if (production[i][j][0] == '\0')
            {
                break;
            }
            printf("%d \n", j);
            printf("%s\n", production[i][j]);
        }
    }

    // code for state traversal
    push(0);
    // checking for empty stack
    while (!isempty())
    {
        int current_state = pop();
        int production_number = 0;
        char current_production[100] = {'\0'};
        char current_non_terminal;
        /* THIS PART IS FOR TERMINALS TRAVERSAL*/
        for (int j = 0; j < strlen(non_terminals); j++)
        {
            // printf("stack counter %d\n",state_counter);
            int created_state = 0;
            char new_state[100][100] = {{'\0'}}; // adds new state for each traversal into it
            int moved = 0;                       // boolean to keep track of if the dot moved or not
            int new_state_prod = 0;              // keeps track of how many sproductions have been made for a specific state
            char closure[100];                   // stores the closure
            int closure_index = -1;              // stores the index of the closure
            printf("non terminal %c\n", non_terminals[j]);
            current_non_terminal = non_terminals[j];
            for (int i = 0; i < 100; i++)
            {
                memset(current_production, '\0', 100);

                if (state_list[current_state][i][0] == '\0')
                {
                    break;
                }
                for (int j = 0; j < strlen(state_list[current_state][i]); j++)
                {
                    current_production[j] = state_list[current_state][i][j];
                }
                printf("stack counter %d\n", state_counter);
                printf("AT PRODUCTION: %s\n", current_production);
                int dot = find_dot(current_production);
                if (current_production[dot + 1] != '\0' && is_NT(dot, current_production, non_terminals[j]) == 1)
                {
                    swap_dot(current_production, dot);
                    printf("MOVED: %s\n", current_production);
                    created_state++;
                    for (int m = 0; m < strlen(current_production); m++)
                    {
                        new_state[new_state_prod][m] = current_production[m];
                    }
                    moved = 1;
                }
                if (moved == 1)
                {
                    new_state_prod++;
                    closure_index = find_closure(new_state, new_state_prod, dot + 1);
                    // int length = sizeof(new_state) / sizeof(new_state[0]);
                    // // printf("result %d\n", check_state(new_state, length));
                    // if (check_state(new_state, length) == 1)
                    // {
                    //     push(state_counter - 1);
                    // }
                    moved = 0;
                }

                printf("new_state\n");
                for (int l = 0; l < 100; l++)
                {
                    if (new_state[l][0] == '\0')
                    {
                        break;
                    }
                    printf("%s\n", new_state[l]);
                }
                printf("END\n");
                printf("state: %d\n", current_state);
                printf("CREATED: %d\n", created_state);
            }
            printf("new_state\n");
            for (int l = 0; l < 100; l++)
            {
                if (new_state[l][0] == '\0')
                {
                    break;
                }
                printf("%s\n", new_state[l]);
            }
            printf("CHecking\n");
            int length = sizeof(new_state) / sizeof(new_state[0]);
            // printf("result %d\n", check_state(new_state, length));
            if (check_state(new_state, length) == 1)
            {
                push(state_counter - 1);
            }
            production_number++;
        }
        /* THIS PART IS FOR TERMINALS TRAVERSAL*/
        for (int j = 0; j < strlen(terminals); j++)
        {
            int created_state = 0;
            char new_state[100][100] = {{'\0'}}; // adds new state for each traversal into it
            int moved = 0;                       // boolean to keep track of if the dot moved or not
            int new_state_prod = 0;              // keeps track of how many sproductions have been made for a specific state
            char closure[100];                   // stores the closure
            int closure_index = -1;              // stores the index of the closure
            printf("terminal %c\n", terminals[j]);
            current_non_terminal = terminals[j];
            for (int i = 0; i < 100; i++)
            {
                memset(current_production, '\0', 100);

                if (state_list[current_state][i][0] == '\0')
                {
                    int length = sizeof(new_state) / sizeof(new_state[0]);
                    // printf("result %d\n", check_state(new_state, length));
                    if (check_state(new_state, length) == 1)
                    {
                        push(state_counter - 1);
                    }
                    break;
                }
                for (int j = 0; j < strlen(state_list[current_state][i]); j++)
                {
                    current_production[j] = state_list[current_state][i][j];
                }
                printf("AT PRODUCTION: %s\n", current_production);
                int dot = find_dot(current_production);
                if (current_production[dot + 1] != '\0' && is_NT(dot, current_production, terminals[j]) == 1)
                {
                    swap_dot(current_production, dot);
                    printf("MOVED: %s\n", current_production);
                    created_state++;
                    for (int m = 0; m < strlen(current_production); m++)
                    {
                        new_state[new_state_prod][m] = current_production[m];
                    }
                    moved = 1;
                }
                if (moved == 1)
                {
                    new_state_prod++;
                    closure_index = find_closure(new_state, new_state_prod, dot + 1);
                    printf("new_state\n");
                    for (int l = 0; l < 100; l++)
                    {
                        if (new_state[l][0] == '\0')
                        {
                            break;
                        }
                        printf("%s\n", new_state[l]);
                    }
                    // int length = sizeof(new_state) / sizeof(new_state[0]);
                    // // printf("result %d\n", check_state(new_state, length));
                    // if (check_state(new_state, length) == 1)
                    // {
                    //     push(state_counter - 1);
                    // }
                    moved = 0;
                }

                printf("new_state\n");
                for (int l = 0; l < 100; l++)
                {
                    if (new_state[l][0] == '\0')
                    {
                        break;
                    }
                    printf("%s\n", new_state[l]);
                }
                printf("END\n");
                printf("state: %d\n", current_state);
                printf("CREATED: %d\n", created_state);
            }
            printf("new_state\n");
            for (int l = 0; l < 100; l++)
            {
                if (new_state[l][0] == '\0')
                {
                    break;
                }
                printf("%s\n", new_state[l]);
            }
            printf("CHecking\n");
            int length = sizeof(new_state) / sizeof(new_state[0]);
            // printf("result %d\n", check_state(new_state, length));
            if (check_state(new_state, length) == 1)
            {
                printf("added\n");
                push(state_counter - 1);
            }

            production_number++;
        }
    }
    printf("\n\nhello\n");
    display_states();

    // for x -> non_terminal:
    //     closure[100];
    //     for(int i=0;i=100;i++){
    //         if(state_list[stack[-1]][i][0]=='\0'){
    //             break;
    //         }
    //         2d_list[100] = state_list[stack[-1]][0]
    //         dot = find_dot(2d_list[100])
    //         if(traverse(dot,1d_list,non_terminal[x])==1){
    //             new_state.append(2d_list)
    //             closure.append(2d_list[dot+2])
    //         }
    //     }
    //     2d_list[100][100] = state_list[stack[-1]][0]

    //     def traverse(dot,list,x):
    //     if(dot<strlen(list)-1){
    //         if(1d_list[dot+1]==x){
    //             1d_list[dot],1d_list[dot+1] = 1d_list[dot+1],1d_list[dot]
    //             return 1
    //         }
    //     }
    //     return 0
}