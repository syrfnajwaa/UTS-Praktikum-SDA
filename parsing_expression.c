#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char data[100][100];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, char *value)
{
    if (s->top < 100 - 1)
        strcpy(s->data[++(s->top)], value);
}
char *pop(Stack *s)
{
    if (isEmpty(s))
    {
        return "";
    }
    else
    {
        return s->data[(s->top)--];
    }
}
char *peek(Stack *s)
{
    if (isEmpty(s))
    {
        return "";
    }
    else
    {
        return s->data[s->top];
    }
}

int precedence(char op)
{
    switch (op)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int isOperand(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int isOpenParent(char c)
{
    return (c == '(');
}

int isCloseParent(char c)
{
    return (c == ')');
}

// fungsi untuk mengubah infix menjadi prefix
void intopost()
{
    printf("==================================================\n");
    printf("=         Konversi Infix ke Prefix               =\n");
    printf("==================================================\n");
    printf("Masukkan ekspresi infix: ");
    char infix[100];
    fgets(infix, sizeof(infix), stdin);

    char postfix[100] = "";
    Stack s;
    initStack(&s);

    for (int i = 0, j = 0; i < strlen(infix); i++)
    {
        char index = infix[i];
        if (isOperand(index))
        {
            char temp[2] = {index, '\0'};
            strcat(postfix, temp);
        }

        else if (isOperator(index))
        {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(index))
            {
                char poped = pop(&s)[0];
                char temp[2] = {poped, '\0'};
                strcat(postfix, temp);
            }
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }

        else if (isOpenParent(index))
        {
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }

        else if (isCloseParent(index))
        {
            while (!isEmpty(&s) && !isOpenParent(peek(&s) [0]))
            {
                char *poped = pop(&s);
                char temp[100];
                strcat(temp, poped);
            }
            pop(&s);
        }

        // print postfix dan stack
        printf("Postfix: %s\n", postfix);
        printf("Stack Top: %s\n", peek(&s));
    }

    while (!isEmpty(&s))
    {
        char *poped = pop(&s);
        char temp[100];
        strcpy(temp, poped);
        strcat(postfix, temp);
    }

    printf("Hasil konversi infix ke prefix: %s\n", postfix);
}

// // Fungsi untuk mengubah Postfix ke Infix
void posttoin()
{
    printf("==================================================\n");
    printf("=         Konversi Postfix ke Infix              =\n");
    printf("==================================================\n");
    printf("Masukkan ekspresi postfix: ");
    char postfix[100];
    fgets(postfix, sizeof(postfix), stdin);
    postfix[strcspn(postfix, "\n")] = 0; 

    Stack s;
    initStack(&s);

    for (int i = 0; i < strlen(postfix); i++)
    {
        char index = postfix[i];
        if (isOperand(index))
        {
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }
        
        else 
        {
            char op1[100], op2[100], exp[100];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(exp, "(%s%c%s)", op2, index, op1);
            push(&s, exp);
        }

        printf("Stack Top: %s\n", isEmpty(&s) ? "" : s.data[s.top]);
    }
    printf("Hasil konversi postfix ke infix: %s\n", pop(&s));
}


// //
// void intopre();

// // Fungsi untuk mengubah Prefix ke Infix
void pretoin()
{
    printf("==================================================\n");
    printf("=         Konversi Prefix ke Infix               =\n");
    printf("==================================================\n");
    printf("Masukkan ekspresi prefix: ");
    char prefix[100];
    fgets(prefix, sizeof(prefix), stdin);
    prefix[strcspn(prefix, "\n")] = 0; 

    Stack s;
    initStack(&s);
    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) 
    {
        char index = prefix[i];

        if (isOperand(index)) 
        {
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }
        else if (isOperator(index)) 
        {
            char op1[100], op2[100], exp[100];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(exp, "(%s%c%s)", op1, index, op2);
            push(&s, exp);
        }

        printf("Stack Top: %s\n", isEmpty(&s) ? "" : s.data[s.top]); 
    }

    printf("Hasil konversi prefix ke infix: %s\n", pop(&s));
}


// // Fungsi untuk mengubah Prefix ke Postfix
void pretopost()
{
    printf("==================================================\n");
    printf("=         Konversi Prefix ke Postfix             =\n");
    printf("==================================================\n");
    printf("Masukkan ekspresi prefix: ");
    char prefix[100];
    fgets(prefix, sizeof(prefix), stdin);
    prefix[strcspn(prefix, "\n")] = 0; 

    Stack s;
    initStack(&s);
    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) 
    {
        char index = prefix[i];

        if (isOperand(index)) 
        {
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }
        else if (isOperator(index)) 
        {
            char op1[100], op2[100], exp[100];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(exp, "%s%s%c", op1, op2, index);
            push(&s, exp);
        }

        printf("Stack Top: %s\n", isEmpty(&s) ? "" : s.data[s.top]); 
    }

    printf("Hasil konversi prefix ke postfix: %s\n", pop(&s));
}


// //
// void posttopre();

int main()
{
    printf("==================================================\n");
    printf("=    KONVERSI ARITMATIKA - PARSING EXPRESSION    =\n");
    printf("==================================================\n");
    printf("=         Tekan ENTER untuk Melanjutkan          =\n");
    printf("==================================================\n");
    getchar();
    #ifdef _WIN32
       system("cls");
    #else
       system("clear");
    #endif

    printf("==================================================\n");
    printf("=  Silahkan pilih menu konversi yang diinginkan  =\n");
    printf("==================================================\n");
    printf("    1️⃣. Infix ke Postfix\n");
    printf("    2️⃣. Postfix ke Infix\n");
    printf("    3️⃣. Infix ke Prefix\n");
    printf("    4️⃣. Prefix ke Infix\n");
    printf("    5️⃣. Prefix ke Postfix\n");
    printf("    6️⃣. Postfix ke Prefix\n");
    printf("==============================================\n");
    printf("👉 Pilih Opsi Anda (1/2/3/4/5/6): ");
    int opsi;
    scanf("%d", &opsi);
    getchar();
    #ifdef _WIN32
       system("cls");
    #else
       system("clear");
    #endif

    switch (opsi)
    {
    case 1:
        intopost();
        break;
    case 2:
        posttoin();
        break;
    // case 3:
    //     intopre();
    //     break;
    case 4:
        pretoin();
        break;
    case 5:
        pretopost();
        break;
    // case 6:
    //     posttopre();
    //     break;
    default:
        printf("❌ Pilihan Tidak Valid.\n");
    }
    return 0;
}
