#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data stack
typedef struct
{
    char data[100][100];
    int top;
} Stack;

// Fungsi untuk membalik string
// digunakan untuk mengubah infix menjadi prefix
void reverseString(char *str)
{
    int length = strlen(str);
    int start = 0, end = length - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Fungsi untuk menginisialisasi stack
void initStack(Stack *s)
{
    s->top = -1;
}

// Fungsi untuk mengecek apakah stack kosong
int isEmpty(Stack *s)
{
    return s->top == -1;
}

// Fungsi untuk memasukkan elemen ke stack
void push(Stack *s, char *value)
{
    if (s->top < 100 - 1)
        strcpy(s->data[++(s->top)], value);
}

// Fungsi untuk mengeluarkan elemen teratas stack
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

// Fungsi untuk melihat elemen teratas stack
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

// Fungsi untuk mengecek tingkatan prioritas operator
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

// Fungsi untuk mengecek apakah karakter adalah operator
int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Fungsi untuk mengecek apakah karakter adalah operand
int isOperand(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Fungsi untuk mengecek apakah karakter adalah buka kurung
int isOpenParent(char c)
{
    return (c == '(');
}

// Fungsi untuk mengecek apakah karakter adalah tutup kurung
int isCloseParent(char c)
{
    return (c == ')');
}

// fungsi untuk mengubah infix menjadi prefix
void intopost()
{
    printf("==================================================\n");
    printf("=         Konversi Infix ke postfix              =\n");
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
            while (!isEmpty(&s) && !isOpenParent(peek(&s)[0]))
            {
                char *poped = pop(&s);
                char temp[100];
                strcat(temp, poped);
            }
            pop(&s);
        }

        else
        {
            continue;
        }
    }

    while (!isEmpty(&s))
    {
        char *poped = pop(&s);
        char temp[100];
        strcpy(temp, poped);
        strcat(postfix, temp);
    }

    printf("Hasil konversi infix ke postfix: %s\n", postfix);
}

// Fungsi untuk mengubah Postfix menjadi Infix
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

        else if (isOperator(index))
        {
            char op1[100], op2[100], exp[100];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(exp, "(%s%c%s)", op2, index, op1);
            push(&s, exp);
        }

        else
        {
            continue;
        }
    }
    printf("Hasil konversi postfix ke infix: %s\n", pop(&s));
}

// Fungsi untuk mengubah Infix menjaadi Prefix
void intopre()
{
    printf("==================================================\n");
    printf("=         Konversi Infix ke Prefix               =\n");
    printf("==================================================\n");
    printf("Masukkan ekspresi infix: ");
    char infix[100];
    fgets(infix, sizeof(infix), stdin);

    reverseString(infix);

    char prefix[100] = "";
    Stack s;
    initStack(&s);

    for (int i = 0; i < strlen(infix); i++)
    {
        char index = infix[i];

        if (isOperand(index))
        {
            char temp[2] = {index, '\0'};
            strcat(prefix, temp);
        }
        else if (isOperator(index))
        {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) > precedence(index))
            {
                char poped = pop(&s)[0];
                char temp[2] = {poped, '\0'};
                strcat(prefix, temp);
            }
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }
        else if (isCloseParent(index))
        {
            char temp[2] = {index, '\0'};
            push(&s, temp);
        }
        else if (isOpenParent(index))
        {
            while (!isEmpty(&s) && !isCloseParent(peek(&s)[0]))
            {
                char poped = pop(&s)[0];
                char temp[2] = {poped, '\0'};
                strcat(prefix, temp);
            }
            pop(&s);
        }

        else
        {
            continue;
        }
    }

    while (!isEmpty(&s))
    {
        char poped = pop(&s)[0];
        char temp[2] = {poped, '\0'};
        strcat(prefix, temp);
    }

    // Balik hasil prefix agar benar
    reverseString(prefix);

    printf("Hasil konversi infix ke prefix: %s\n", prefix);
}

// Fungsi untuk mengubah Prefix ke Infix
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

        else
        {
            continue;
        }
    }

    printf("Hasil konversi prefix ke infix: %s\n", pop(&s));
}

// Fungsi untuk mengubah Prefix ke Postfix
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

        else
        {
            continue;
        }
    }

    printf("Hasil konversi prefix ke postfix: %s\n", pop(&s));
}

// Fungsi untuk mengubah Postfix ke Prefix
void posttopre()
{
    printf("==================================================\n");
    printf("=         Konversi Postfix ke Prefix             =\n");
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

        else if (isOperator(index))
        {
            char op1[100], op2[100], exp[100];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(exp, "%c%s%s", index, op2, op1);
            push(&s, exp);
        }

        else
        {
            continue;
        }
    }
    printf("Hasil konversi postfix ke prefix: %s\n", pop(&s));
}

int main()
{
    printf("==================================================\n");
    printf("=    KONVERSI ARITMATIKA - PARSING EXPRESSION    =\n");
    printf("==================================================\n");
    printf("=         Tekan ENTER untuk Melanjutkan          =\n");
    printf("==================================================\n");
    getchar();

    while (1)
    {
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
        printf("    0️⃣. Keluar\n");
        printf("==============================================\n");
        printf("👉 Pilih Opsi Anda (0/1/2/3/4/5/6): ");
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
        case 0:
            printf("👋 Program selesai. Terima kasih!\n");
            return 0;
        case 1:
            intopost();
            break;
        case 2:
            posttoin();
            break;
        case 3:
            intopre();
            break;
        case 4:
            pretoin();
            break;
        case 5:
            pretopost();
            break;
        case 6:
            posttopre();
            break;
        default:
            printf("❌ Pilihan Tidak Valid.\n");
        }

        printf("\n==================================================\n");
        printf("=        Tekan ENTER untuk Melanjutkan Lagi      =\n");
        printf("==================================================\n");
        getchar();
    }
    return 0;
}
