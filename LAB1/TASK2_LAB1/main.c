#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 40 give gu code

typedef struct {
    char courseName[30];
    int courseCode;
} Course;

typedef struct {
    int mark;
    char the_grade;
    int gradeFinalized; // Flag to prevent grade edits
} Grade;

typedef struct {
    char name[50];
    char reg_no[20];
    int age;
    Course course;
    Grade grade;
} Student;

// Grade calculation
char calculate_grade(int mark) {
    if (mark > 69) return 'A';
    else if (mark > 59) return 'B';
    else if (mark > 49) return 'C';
    else if (mark > 39) return 'D';
    else return 'E';
}

// Add marks and calculate grade
void enter_marks(Student* s) {
    if (s->grade.gradeFinalized) {
        printf("Grade for %s already finalized and cannot be changed.\n", s->name);
        return;
    }

    printf("Enter marks for %s: ", s->name);
    scanf("%d", &s->grade.mark);
    s->grade.the_grade = calculate_grade(s->grade.mark);
    s->grade.gradeFinalized = 1;
    printf("Grade calculated: %c\n", s->grade.the_grade);
}

// Edit student details (except grade)
void edit_student(Student* s) {
    printf("Editing details for %s\n", s->name);
    printf("Enter new name: ");
    scanf(" %[^\n]", s->name); // allow spaces
    printf("Enter new registration number: ");
    scanf("%s", s->reg_no);
    printf("Enter new age: ");
    scanf("%d", &s->age);
    // Course editing (optional)
    printf("Enter new course name: ");
    scanf(" %[^\n]", s->course.courseName);
    printf("Enter new course code: ");
    scanf("%d", &s->course.courseCode);
}

void print_student(Student s) {
    printf("Name: %s\n", s.name);
    printf("Reg No: %s\n", s.reg_no);
    printf("Age: %d\n", s.age);
    printf("Course: %s (%d)\n", s.course.courseName, s.course.courseCode);
    if (s.grade.gradeFinalized)
        printf("Mark: %d, Grade: %c\n", s.grade.mark, s.grade.the_grade);
    else
        printf("Grade not yet entered.\n");
    printf("---------------------------\n");
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice, index;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Edit student\n");
        printf("3. Enter marks & calculate grade\n");
        printf("4. Display all students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (count >= MAX_STUDENTS) {
                    printf("Student limit reached.\n");
                } else {
                    printf("Enter name: ");
                    scanf(" %[^\n]", students[count].name);
                    printf("Enter reg no: ");
                    scanf("%s", students[count].reg_no);
                    printf("Enter age: ");
                    scanf("%d", &students[count].age);
                    printf("Enter course name: ");
                    scanf(" %[^\n]", students[count].course.courseName);
                    printf("Enter course code: ");
                    scanf("%d", &students[count].course.courseCode);
                    students[count].grade.gradeFinalized = 0;
                    count++;
                    printf("Student added successfully.\n");
                }
                break;

            case 2:
                printf("Enter student index (0 to %d): ", count - 1);
                scanf("%d", &index);
                if (index >= 0 && index < count)
                    edit_student(&students[index]);
                else
                    printf("Invalid index.\n");
                break;

            case 3:
                printf("Enter student index (0 to %d): ", count - 1);
                scanf("%d", &index);
                if (index >= 0 && index < count)
                    enter_marks(&students[index]);
                else
                    printf("Invalid index.\n");
                break;

            case 4:
                for (int i = 0; i < count; i++)
                    print_student(students[i]);
                break;

            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
