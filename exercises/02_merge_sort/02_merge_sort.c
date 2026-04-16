#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(Student stu[], int L, int mid, int R) {
    int i = L, j = mid + 1;
    printf("i = %d, j = %d \n", i, j);
    int index_t = 0;
    // 降序，哪个大先放入temp
    while (i <= mid && j <= R) {
        if (stu[i].score >= stu[j].score) {
            temp[index_t] = stu[i];
            index_t++;
            i++;
        } else {
            temp[index_t] = stu[j];
            index_t++;
            j++;
        }
    }

    // 处理剩余的元素
    while (i <= mid) {
        temp[index_t] = stu[i];
        index_t++;
        i++;
    }
    while (j <= R) {
        temp[index_t] = stu[j];
        index_t++;
        j++;
    }

    // 拷贝回数组
    for (int k = 0; k < R - L + 1; k++) {
        stu[L + k] = temp[k];
    }
}

void merge_sort(int left, int right) {
    // TODO: 在这里添加你的代码
    if (left >= right) return;
    int mid = (left + right) / 2;
    printf("left = %d, right = %d, mid = %d, in merge_sort()\n", left, right, mid);
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(students, left, mid, right);
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}