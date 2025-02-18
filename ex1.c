#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_Len 5000
#define MAX_WORDS 500
#define MAX_WORD_LEN 50 

// 定义单词及其出现次数的结构体
typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} Word;

// 比较函数：用于排序，按次数降序，次数相同时按字典序升序
int compare(const void *a, const void *b) {
    Word *word1 = (Word *)a;
    Word *word2 = (Word *)b;
    if (word1->count != word2->count) {
        return word2->count - word1->count; // 按次数降序
    }
    return strcmp(word1->word, word2->word); // 按字典序升序
}

// 转换字符串为小写
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    char text[MAX_LEN];
    Word words[MAX_WORDS];
    int word_count = 0;

    // 初始化单词数组
    for (int i = 0; i < MAX_WORDS; i++) {
        words[i].word[0] = '\0';
        words[i].count = 0;
    }

    // 输入文本
    printf("请输入一段文本：\n");
    fgets(text, MAX_LEN, stdin);

    // 将文本拆分为单词
    char *token = strtok(text, " ,.!?;:\n");
    while (token != NULL) {
        to_lowercase(token); // 将单词转换为小写

        // 查找该单词是否已存在
        int found = 0;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i].word, token) == 0) {
                words[i].count++; // 单词已存在，计数加一
                found = 1;
                break;
            }
        }

        // 如果单词不存在，添加到数组中
        if (!found) {
            strcpy(words[word_count].word, token);
            words[word_count].count = 1;
            word_count++;
        }

        token = strtok(NULL, " ,.!?;:\n"); // 获取下一个单词
    }

    // 排序单词数组
    qsort(words, word_count, sizeof(Word), compare);

    // 输出前10个单词及其出现次数
    for (int i = 0; i < word_count && i < 10; i++) {
        printf("%s:%d\n", words[i].word, words[i].count);
    }

    return 0;
}