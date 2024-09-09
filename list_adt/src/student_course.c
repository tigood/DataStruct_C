#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100

// 课程节点结构
typedef struct CourseNode {
    int courseID;               // 课程ID
    char courseName[MAX_NAME_LEN]; // 课程名称
    struct CourseNode* next;    // 指向下一个课程的指针
    struct StudentNode* students; // 指向注册该课程的学生链表的指针
} CourseNode;

// 学生节点结构
typedef struct StudentNode {
    int studentID;              // 学生ID
    char studentName[MAX_NAME_LEN]; // 学生姓名
    CourseNode* courses;        // 指向该学生所选课程的链表
    struct StudentNode* next;   // 指向下一个学生的指针
} StudentNode;

// 创建新的课程节点
CourseNode* createCourse(int courseID, const char* courseName) {
    CourseNode* newCourse = (CourseNode*)malloc(sizeof(CourseNode));
    newCourse->courseID = courseID;
    strncpy(newCourse->courseName, courseName, MAX_NAME_LEN);
    newCourse->courseName[MAX_NAME_LEN - 1] = '\0';
    newCourse->next = NULL;
    newCourse->students = NULL;
    return newCourse;
}

// 创建新的学生节点
StudentNode* createStudent(int studentID, const char* studentName) {
    StudentNode* newStudent = (StudentNode*)malloc(sizeof(StudentNode));
    newStudent->studentID = studentID;
    strncpy(newStudent->studentName, studentName, MAX_NAME_LEN);
    newStudent->studentName[MAX_NAME_LEN - 1] = '\0';
    newStudent->courses = NULL;
    newStudent->next = NULL;
    return newStudent;
}

// 向学生的课程链表中添加课程
void addCourseToStudent(StudentNode* student, CourseNode* course) {
    CourseNode* current = student->courses;
    if (current == NULL) {
        student->courses = course;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = course;
    }
}

// 向课程的学生链表中添加学生
void addStudentToCourse(CourseNode* course, StudentNode* student) {
    StudentNode* current = course->students;
    if (current == NULL) {
        course->students = student;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = student;
    }
}

// 打印学生及其所选课程的信息
void printStudent(StudentNode* student) {
    printf("Student ID: %d\n", student->studentID);
    printf("Student Name: %s\n", student->studentName);
    printf("Courses:\n");

    CourseNode* course = student->courses;
    while (course != NULL) {
        printf("    Course ID: %d, Course Name: %s\n", course->courseID, course->courseName);
        course = course->next;
    }
    printf("\n");
}

// 打印课程及其注册者的信息
void printCourse(CourseNode* course) {
    printf("Course ID: %d\n", course->courseID);
    printf("Course Name: %s\n", course->courseName);
    printf("Students Registered:\n");

    StudentNode* student = course->students;
    while (student != NULL) {
        printf("    Student ID: %d, Student Name: %s\n", student->studentID, student->studentName);
        student = student->next;
    }
    printf("\n");
}

int main() {
    // 创建学生
    StudentNode* student1 = createStudent(1, "Alice");
    StudentNode* student2 = createStudent(2, "Bob");

    // 创建课程
    CourseNode* course1 = createCourse(101, "Mathematics");
    CourseNode* course2 = createCourse(102, "Physics");
    CourseNode* course3 = createCourse(103, "Chemistry");

    // 将课程添加到学生节点
    addCourseToStudent(student1, course1);
    addCourseToStudent(student1, course2);
    addCourseToStudent(student2, course2);
    addCourseToStudent(student2, course3);

    // 将学生添加到课程节点
    addStudentToCourse(course1, student1);
    addStudentToCourse(course2, student1);
    addStudentToCourse(course2, student2);
    addStudentToCourse(course3, student2);

    // 打印学生和课程信息
    printf("Students and their Courses:\n");
    printStudent(student1);
    printStudent(student2);

    printf("Courses and their Registered Students:\n");
    printCourse(course1);
    printCourse(course2);
    printCourse(course3);

    // 释放内存（省略）
    free(student1);
    free(student2);
    free(course1);
    free(course2);
    free(course3);

    return 0;
}
