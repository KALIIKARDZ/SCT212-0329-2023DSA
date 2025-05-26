//  LAB 2 PART B - LINKED LIST STUDENT LIST 
//Code reimplements the array-based list from Part A using a singly linked list.
// Comments indicate which part of the question is implemented. I choose this instead of multiple files

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
    int gradeFinalized;
} Grade;


// 2. STUDENT STRUCTURE & RELATED SETTERS/GETTERS

typedef struct {
    char name[50];
    char reg_no[20];
    int age;
    Course course;
    Grade grade;
} Student;

char calculate_grade(int mark) {
    if (mark > 69) return 'A';
    else if (mark > 59) return 'B';
    else if (mark > 49) return 'C';
    else if (mark > 39) return 'D';
    else return 'E';
}

void set_marks(Student* s, int mark) {
    if (s->grade.gradeFinalized) {
        printf("Grade already finalized.\n");
        return;
    }
    s->grade.mark = mark;
    s->grade.the_grade = calculate_grade(mark);
    s->grade.gradeFinalized = 1;
}

void set_regNo(Student* s, const char* reg) { strcpy(s->reg_no, reg); }
char* get_regNo(Student s) { return s.reg_no; }

void set_name(Student* s, const char* name) { strcpy(s->name, name); }
char* get_name(Student s) { return s.name; }

void set_age(Student* s, int age) { s->age = age; }
int get_age(Student s) { return s.age; }

void set_course(Student* s, Course c) { s->course = c; }
Course get_course(Student s) { return s.course; }

void set_grade(Student* s, Grade g) { s->grade = g; }
Grade get_grade(Student s) { return s.grade; }


// 3. LINKED LIST IMPLEMENTATION FOR STUDENT LIST


typedef struct Node {
    Student data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} StudentList;

// Constructor: empty list
StudentList create_empty_list() {
    StudentList list;
    list.head = NULL;
    list.size = 0;
    return list;
}

// Constructor: create list with one student
StudentList create_with_student(Student s) {
    StudentList list = create_empty_list();
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->next = NULL;
    list.head = newNode;
    list.size = 1;
    return list;
}

// Constructor: copy from another list
StudentList copy_list(StudentList original) {
    StudentList copy = create_empty_list();
    Node* current = original.head;
    while (current) {
        Student s = current->data;
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = s;
        newNode->next = NULL;

        if (copy.head == NULL) {
            copy.head = newNode;
        } else {
            Node* temp = copy.head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        copy.size++;
        current = current->next;
    }
    return copy;
}

// Add to end
void add_student(StudentList* list, Student s) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }
    list->size++;
}

// Add at specific position
void add_student_at(StudentList* list, Student s, int pos) {
    if (pos < 0 || pos > list->size) {
        printf("Invalid position.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;

    if (pos == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* temp = list->head;
        for (int i = 0; i < pos - 1; i++) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
    list->size++;
}

// Remove by student object (using reg_no match)
void remove_student(StudentList* list, Student s) {
    Node *temp = list->head, *prev = NULL;
    while (temp && strcmp(temp->data.reg_no, s.reg_no) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Student not found.\n");
        return;
    }

    if (!prev) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    list->size--;
}

// Remove by index
void remove_at(StudentList* list, int pos) {
    if (pos < 0 || pos >= list->size) {
        printf("Invalid index.\n");
        return;
    }

    Node *temp = list->head, *prev = NULL;
    for (int i = 0; i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (!prev) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    list->size--;
}

int get_list_size(StudentList* list) {
    return list->size;
}

// Destroy the list
void destroy_list(StudentList* list) {
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}


// 4. DRIVER FUNCTION FOR TESTING


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
    Course c = {"Linked Lists", 202};

    // Add 15 students
    for (int i = 0; i < 15; i++) {
        sprintf(s.name, "Student%d", i + 1);
        sprintf(s.reg_no, "R%d", i + 100);
        s.age = 18 + (i % 4);
        s.course = c;
        s.grade.gradeFinalized = 0;
        add_student(&list, s);
    }

    // Assign marks
    Node* current = list.head;
    int index = 0;
    while (current) {
        int mark = 35 + (index * 4 % 60);
        set_marks(&current->data, mark);
        current = current->next;
        index++;
    }

    // Print all students
    current = list.head;
    while (current) {
        print_student(current->data);
        current = current->next;
    }

    // Clean up
    destroy_list(&list);
    return 0;
}

