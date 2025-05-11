// LAB 2 - PART A: ARRAY-BASED STUDENT LIST WITH FULL FUNCTIONALITY
// When run expected output should be 15 students and their details
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//PART A.2: Define Course and Grade as ADTs ---
typedef struct {
    char courseName[30];
    int courseCode;
} Course;

typedef struct {
    int mark;
    char the_grade;
    int finalized;
} Grade;

//PART A.2: Define Student Struct with Grade and Course ---
typedef struct {
    char name[50];
    char reg_no[20];
    int age;
    Course course;
    Grade grade;
} Student;

//PART A.1: Define Array-Based List ---
typedef struct {
    int size;
    int capacity;
    Student* students;
} StudentList;

//Utility Function to Calculate Grade (PART A.3)
char calculate_grade(int mark) {
    if (mark > 69) return 'A';
    else if (mark > 59) return 'B';
    else if (mark > 49) return 'C';
    else if (mark > 39) return 'D';
    else return 'E';
}

// Dynamic Resizing
void resize_list(StudentList* list) {
    list->capacity *= 2;
    list->students = (Student*)realloc(list->students, sizeof(Student) * list->capacity);
}

// PART A.1: Constructors
// Create empty list
StudentList* create_empty_list() {
    StudentList* list = (StudentList*)malloc(sizeof(StudentList));
    list->size = 0;
    list->capacity = 4;
    list->students = (Student*)malloc(sizeof(Student) * list->capacity);
    return list;
}

// Create list with 1 initial student
StudentList* create_with_one_student(Student student) {
    StudentList* list = create_empty_list();
    list->students[0] = student;
    list->size = 1;
    return list;
}

// Copy constructor from existing list
StudentList* copy_list(StudentList* original) {
    StudentList* new_list = (StudentList*)malloc(sizeof(StudentList));
    new_list->size = original->size;
    new_list->capacity = original->capacity;
    new_list->students = (Student*)malloc(sizeof(Student) * new_list->capacity);
    for (int i = 0; i < original->size; i++) {
        new_list->students[i] = original->students[i];
    }
    return new_list;
}

//PART A.1: Add student to end
void add_student(StudentList* list, Student s) {
    if (list->size >= list->capacity) {
        resize_list(list);
    }
    list->students[list->size++] = s;
}

//PART A.1: Add student at specific position
void insert_student_at(StudentList* list, Student s, int pos) {
    if (pos < 0 || pos > list->size) {
        printf("Invalid position.\n");
        return;
    }
    if (list->size >= list->capacity) {
        resize_list(list);
    }
    for (int i = list->size; i > pos; i--) {
        list->students[i] = list->students[i - 1];
    }
    list->students[pos] = s;
    list->size++;
}

//PART A.1: Remove by Student name
void remove_student_by_name(StudentList* list, char* name) {
    int found = -1;
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->students[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Student not found.\n");
        return;
    }
    for (int i = found; i < list->size - 1; i++) {
        list->students[i] = list->students[i + 1];
    }
    list->size--;
}

//PART A.1: Remove by index
void remove_student_at(StudentList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index.\n");
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->students[i] = list->students[i + 1];
    }
    list->size--;
}

//PART A.1: Return list size
int get_list_size(StudentList* list) {
    return list->size;
}

//PART A.1: Destroy list
void destroy_list(StudentList* list) {
    free(list->students);
    free(list);
}

//PART A.2 & A.3: Student functions
void set_marks(Student* s, int marks) {
    if (s->grade.finalized) {
        printf("Grade already finalized.\n");
        return;
    }
    s->grade.mark = marks;
    s->grade.the_grade = calculate_grade(marks);
    s->grade.finalized = 1;
}

void set_name(Student* s, char* name) { strcpy(s->name, name); }
void set_regNo(Student* s, char* reg) { strcpy(s->reg_no, reg); }
void set_age(Student* s, int age) { s->age = age; }
void set_course(Student* s, Course c) { s->course = c; }

char* get_name(Student* s) { return s->name; }
char* get_regNo(Student* s) { return s->reg_no; }
int get_age(Student* s) { return s->age; }
Course get_course(Student* s) { return s->course; }
Grade get_grade(Student* s) { return s->grade; }

//PART A.4: Driver Program to test everything
int main() {
    StudentList* list = create_empty_list();

    for (int i = 0; i < 15; i++) {
        Student s;
        sprintf(s.name, "Student%d", i + 1);
        sprintf(s.reg_no, "REG%d", 1000 + i);
        s.age = 18 + (i % 5);
        strcpy(s.course.courseName, "DSA");
        s.course.courseCode = 200 + i;
        s.grade.finalized = 0;
        set_marks(&s, 40 + i);  // Assign marks and compute grade
        add_student(list, s);
    }

    // Display all students
    printf("\n--- Student List ---\n");
    for (int i = 0; i < get_list_size(list); i++) {
        Student s = list->students[i];
        printf("Name: %s, Reg: %s, Age: %d, Course: %s (%d), Mark: %d, Grade: %c\n",
               s.name, s.reg_no, s.age,
               s.course.courseName, s.course.courseCode,
               s.grade.mark, s.grade.the_grade);
    }

    destroy_list(list);
    return 0;
}
