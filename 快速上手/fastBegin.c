/*
 * 根据列标号来读取字符串并输出
 * 4 9 12 20 -1                 其中两两一对，-1代表结束
 * oajsoiio1j23oij12io3j
 * hello
 * aknsdansdjk
 * aksndjnwajkqkdnaksnd
 * asdnkansdjknasjkdn
 * ...
 * ...
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 20
#define MAX_INPUT 1000

int read_column_numbers(int columns[], int max);
void rearrange(char *output, char const *input,
        int n_columns, int const columns[]);

int main(void) {
    int n_columns;          // 进行处理的列标号
    int columns[MAX_COLS];   // 需要处理的列数
    char input[MAX_INPUT];  // 容纳输入行的数组
    char output[MAX_INPUT];  // 容纳输出行的数组

    // 读取该串列标号
    n_columns = read_column_numbers(columns, MAX_COLS);

    //读取，处理和打印剩余的输入行
    while (gets(input) != NULL) {
        printf("Original input: %s\n", input);
        rearrange(output, input, n_columns, columns);
        printf("Rearranged line: %s\n", output);
    }
}

// 读取列标号如果超出不记
int read_column_numbers(int columns[], int max) {
    int num = 0;
    int ch;

    // 取得列标号，小于0则停止
    while (num < max && scanf("%d", &columns[num]) == 1 && columns[num] >= 0) {
        num += 1;
    }

    // 必须为偶数个
    if (num % 2 != 0) {
        puts("列数不成对");
        exit(EXIT_FAILURE);
    }

    while ((ch = getchar()) != EOF && ch != '\n');

    return num;
}

// 处理输入行，将指定列的字符链接在一起，输出行以NUL结尾
void rearrange(char *output, char const *input, int n_columns, int const columns[]) {
    int col;            // columns数组的下标
    int output_col;     // 输出列计数器
    int len;            // 输出行的长度

    len = strlen(input);
    output_col = 0;

    // 处理每对标号
    for (col = 0; col < n_columns; col += 2) {
        int nchars = columns[col + 1] - columns[col] + 1;

        // 如果输入行结束或者输出行已经满了就结束任务
        if (columns[col] >= len || output_col == MAX_INPUT - 1)
            break;

        // 如果输出行数据空间不足，就只复制可以容纳的内容
        if (output_col + nchars > MAX_INPUT - 1)
            nchars = MAX_INPUT - output_col - 1;

        // 复制相关的数据
        strncpy(output + output_col, input + columns[col], nchars);
        output_col += nchars;
        output[output_col] = '\0';
    }
}