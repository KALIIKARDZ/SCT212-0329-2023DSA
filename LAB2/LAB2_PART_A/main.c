// LAB 2 PART A - ARRAY-BASED STUDENT LIST 
//Code extends Lab 1 with an array-based list using dynamic memory (malloc)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. DEFINITIONS FOR COURSE AND GRADE STRUCTS - ADTs


typedef struct {
    char courseName[30];
    int courseCode;
} Course;

typedef struct {
    int mark;
    char the_grade;
    int gradeFinalized; // Flag to prevent re-calculation
} Grade;

// 2. STUDENT STRUCTURE & RELATED SETTERS/GETTERS


typedef struct {
    char name[50];
    char reg_no[20];
    int age;
    Course course;
    Grade grade;
} Student;

// Utility function to calculate grade based on marks
char calculate_grade(int mark) {
    if (mark > 69) return 'A';
    else if (mark > 59) return 'B';
    else if (mark > 49) return 'C';
    else if (mark > 39) return 'D';
    else return 'E';
}

// Set and Get methods
void set_marks(Student* s, int mark) {
    if (s->grade.gradeFinalized) {
        printf("Grade already finalized.\n");
        return;
    }
    s->grade.mark = mark;
    s->grade.the_grade = calculate_grade(mark);
    s->grade.gradeFinalized = 1;
}

int get_marks(Student s) {
    return s.grade.mark;
}

void set_regNo(Student* s, const char* reg) {
    strcpy(s->reg_no, reg);
}

char* get_regNo(Student s) {
    return s.reg_no;
}

void set_name(Student* s, const char* name) {
    strcpy(s->name, name);
}

char* get_name(Student s) {
    return s.name;
}

void set_age(Student* s, int age) {
    s->age = age;
}

int get_age(Student s) {
    return s.age;
}

void set_course(Student* s, Course c) {
    s->course = c;
}

Course get_course(Student s) {
    return s.course;
}

void set_grade(Student* s, Grade g) {
    s->grade = g;
}

Grade get_grade(Student s) {
    return s.grade;
}


// 3. LIST STRUCTURE FOR ARRAY-BASED STUDENT LIST WITH DYNAMIC RESIZING


typedef struct {
    int size;
    int capacity;
    Student* students;
} StudentList;

// Constructor to create an empty list
StudentList create_empty_list() {
    StudentList list;
    list.size = 0;
    list.capacity = 5;
    list.students = (Student*)malloc(list.capacity * sizeof(Student));
    return list;
}

// Constructor to create a list with an initial student
StudentList create_with_student(Student s) {
    StudentList list = create_empty_list();
    list.students[0] = s;
    list.size = 1;
    return list;
}

// Constructor to create a copy of another list
StudentList copy_list(StudentList original) {
    StudentList newList;
    newList.size = original.size;
    newList.capacity = original.capacity;
    newList.students = (Student*)malloc(newList.capacity * sizeof(Student));
    for (int i = 0; i < original.size; i++) {
        newList.students[i] = original.students[i];
    }
    return newList;
}

// Internal function to resize when full
void resize_if_needed(StudentList* list) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->students = (Student*)realloc(list->students, list->capacity * sizeof(Student));
    }
}

// Add student at end
void add_student(StudentList* list, Student s) {
    resize_if_needed(list);
    list->students[list->size++] = s;
}

// Add student at specific position
void add_student_at(StudentList* list, Student s, int pos) {
    if (pos < 0 || pos > list->size) {
        printf("Invalid position.\n");
        return;
    }
    resize_if_needed(list);
    for (int i = list->size; i > pos; i--) {
        list->students[i] = list->students[i - 1];
    }
    list->students[pos] = s;
    list->size++;
}

// Remove student by object (match reg no)
void remove_student(StudentList* list, Student s) {
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->students[i].reg_no, s.reg_no) == 0) {
            for (int j = i; j < list->size - 1; j++) {
                list->students[j] = list->students[j + 1];
            }
            list->size--;
            return;
        }
    }
    printf("Student not found.\n");
}

// Remove student by index
void remove_at(StudentList* list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Invalid index.\n");
        return;
    }
    for (int i = pos; i < list->size - 1; i++) {
        list->students[i] = list->students[i + 1];
    }
    list->size--;
}

// Return current size of list
int get_list_size(StudentList* list) {
    return list->size;
}

// Destroy the list
void destroy_list(StudentList* list) {
    free(list->students);
    list->students = NULL;
    list->size = 0;
    list->capacity = 0;
}

// 4. DRIVER CODE TO TEST FUNCTIONALITY


void print_student(Student s) {
    printf("Name: %s\n", s.name);
    printf("Reg No: %s\n", s.reg_no);
    printf("Age: %d\n", s.age);
    printf("Course: %s (%d)\n", s.course.courseName, s.course.courseCode);
    if (s.grade.gradeFinalized)
        printf("Mark: %d, Grade: %c\n", s.grade.mark, s.grade.the_grade);
    else
        printf("Grade not yet entered.\n");
    printf("-----------------------\n");
}

int main() {
    StudentList list = create_empty_list();
    Student s;
    Course c = {"Data Structures", 101};

    // Add 15 students
    for (int i = 0; i < 15; i++) {
        sprintf(s.name, "Student%d", i + 1);
        sprintf(s.reg_no, "S%d", i + 100);
        s.age = 20 + (i % 5);
        s.course = c;
        s.grade.gradeFinalized = 0;
        add_student(&list, s);
    }

    // Assign marks
    for (int i = 0; i < get_list_size(&list); i++) {
        int mark = 40 + (i * 3 % 60); // random pattern
        set_marks(&list.students[i], mark);
    }

    // Print all students
    for (int i = 0; i < get_list_size(&list); i++) {
        print_student(list.students[i]);
    }

    // Clean up
    destroy_list(&list);
    return 0;
}
