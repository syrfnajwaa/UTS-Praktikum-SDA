#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char data[100];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, char value)
{
    if (s->top < 100 - 1)
        s->data[++(s->top)] = value;
}
char pop(Stack *s)
{
    if (isEmpty(s))
    {
        return '\0';
    }
    else
    {
        return s->data[(s->top)--];
    }
}
char peek(Stack *s)
{
    if (isEmpty(s))
    {
        return '\0';
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

// fungsi untuk merubah infix menjadi prefix
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
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(index))
            {
                char poped = pop(&s);
                char temp[2] = {poped, '\0'};
                strcat(postfix, temp);
            }
            push(&s, index);
        }

        else if (isOpenParent(index))
        {
            push(&s, index);
        }

        else if (isCloseParent(index))
        {
            while (!isEmpty(&s) && !isOpenParent(peek(&s)))
            {
                char poped = pop(&s);
                char temp[2] = {poped, '\0'};
                strcat(postfix, temp);
            }
            pop(&s);
        }

        // print postfix and stack
        printf("Postfix: %s\n", postfix);
        printf("Stack: %s\n", s.data);
    }

    while (!isEmpty(&s))
    {
        char poped = pop(&s);
        char temp[2] = {poped, '\0'};
        strcat(postfix, temp);
    }

    printf("Hasil konversi infix ke prefix: %s\n", postfix);
}

// //
// void posttoin();

// //
// void intopre();

// //
// void pretoin();

// //
// void pretopost();

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
    system("cls");

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
    system("cls");

    switch (opsi)
    {
    case 1:
        intopost();
        break;
    // case 2:
    //     posttoin();
    //     break;
    // case 3:
    //     intopre();
    //     break;
    // case 4:
    //     pretoin();
    //     break;
    // case 5:
    //     pretopost();
    //     break;
    // case 6:
    //     posttopre();
    //     break;
    default:
        printf("❌ Pilihan Tidak Valid.\n");
    }
    return 0;
}
