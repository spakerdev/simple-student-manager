#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4
#define DATA_FILE "students.txt"
#define CSV_FILE "students.csv"

typedef struct {
    int id;
    char *name;
    float grade;
} Student;

typedef struct {
    Student *students;
    int size;
    int capacity;
} StudentList;

/* ---------- Function Prototypes ---------- */
void initList(StudentList *list);
void resizeList(StudentList *list);
void freeList(StudentList *list);

void addStudent(StudentList *list, int id, const char *name, float grade);
void deleteStudent(StudentList *list, int id);
int binarySearch(StudentList *list, int id);

void sortByID(StudentList *list);
void sortByGrade(StudentList *list);

void printStudents(StudentList *list);
float calculateGPA(StudentList *list);
void printStatistics(StudentList *list);

void saveToFile(StudentList *list);
void loadFromFile(StudentList *list);

void exportToCSV(StudentList *list);
void importFromCSV(StudentList *list);

void menu();

/* ---------- Core List Functions ---------- */

void initList(StudentList *list) {
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->students = malloc(sizeof(Student) * list->capacity);
    if (!list->students) {
        perror("Memory allocation failed");
        exit(1);
    }
}

void resizeList(StudentList *list) {
    list->capacity *= 2;
    Student *temp = realloc(list->students,
                            sizeof(Student) * list->capacity);
    if (!temp) {
        perror("Reallocation failed");
        exit(1);
    }
    list->students = temp;
}

void freeList(StudentList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->students[i].name);
    }
    free(list->students);
}

/* ---------- Student Operations ---------- */

void addStudent(StudentList *list, int id,
                const char *name, float grade) {

    if (list->size >= list->capacity) {
        resizeList(list);
    }

    list->students[list->size].id = id;
    list->students[list->size].grade = grade;

    list->students[list->size].name =
        malloc(strlen(name) + 1);

    if (!list->students[list->size].name) {
        perror("Memory allocation failed");
        exit(1);
    }

    strcpy(list->students[list->size].name, name);
    list->size++;
}

void deleteStudent(StudentList *list, int id) {
    sortByID(list);
    int index = binarySearch(list, id);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    free(list->students[index].name);

    for (int i = index; i < list->size - 1; i++) {
        list->students[i] = list->students[i + 1];
    }

    list->size--;
}

int binarySearch(StudentList *list, int id) {
    int left = 0, right = list->size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (list->students[mid].id == id)
            return mid;
        else if (list->students[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

/* ---------- Sorting ---------- */

int compareByID(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return s1->id - s2->id;
}

int compareByGrade(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;

    if (s2->grade > s1->grade) return 1;
    if (s2->grade < s1->grade) return -1;
    return 0;
}

void sortByID(StudentList *list) {
    qsort(list->students, list->size,
          sizeof(Student), compareByID);
}

void sortByGrade(StudentList *list) {
    qsort(list->students, list->size,
          sizeof(Student), compareByGrade);
}

/* ---------- Statistics ---------- */

float calculateGPA(StudentList *list) {
    if (list->size == 0) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < list->size; i++) {
        sum += list->students[i].grade;
    }

    return sum / list->size;
}

void printStatistics(StudentList *list) {
    if (list->size == 0) {
        printf("No students available.\n");
        return;
    }

    float min = list->students[0].grade;
    float max = list->students[0].grade;

    for (int i = 1; i < list->size; i++) {
        if (list->students[i].grade < min)
            min = list->students[i].grade;
        if (list->students[i].grade > max)
            max = list->students[i].grade;
    }

    printf("\n--- Class Statistics ---\n");
    printf("Total Students: %d\n", list->size);
    printf("Average GPA: %.2f\n", calculateGPA(list));
    printf("Highest Grade: %.2f\n", max);
    printf("Lowest Grade: %.2f\n", min);
}

/* ---------- Display ---------- */

void printStudents(StudentList *list) {
    if (list->size == 0) {
        printf("No students available.\n");
        return;
    }

    for (int i = 0; i < list->size; i++) {
        printf("ID: %d | Name: %s | Grade: %.2f\n",
               list->students[i].id,
               list->students[i].name,
               list->students[i].grade);
    }
}

/* ---------- File Persistence ---------- */

void saveToFile(StudentList *list) {
    FILE *file = fopen(DATA_FILE, "w");
    if (!file) {
        perror("File save failed");
        return;
    }

    for (int i = 0; i < list->size; i++) {
        fprintf(file, "%d|%s|%.2f\n",
                list->students[i].id,
                list->students[i].name,
                list->students[i].grade);
    }

    fclose(file);
}

void loadFromFile(StudentList *list) {
    FILE *file = fopen(DATA_FILE, "r");
    if (!file) return;

    int id;
    float grade;
    char name[256];

    while (fscanf(file, "%d|%255[^|]|%f\n",
                  &id, name, &grade) == 3) {
        addStudent(list, id, name, grade);
    }

    fclose(file);
}

/* ---------- CSV ---------- */

void exportToCSV(StudentList *list) {
    FILE *file = fopen(CSV_FILE, "w");
    if (!file) {
        perror("CSV export failed");
        return;
    }

    fprintf(file, "ID,Name,Grade\n");

    for (int i = 0; i < list->size; i++) {
        fprintf(file, "%d,%s,%.2f\n",
                list->students[i].id,
                list->students[i].name,
                list->students[i].grade);
    }

    fclose(file);
    printf("Exported to %s successfully.\n", CSV_FILE);
}

void importFromCSV(StudentList *list) {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) {
        perror("CSV import failed");
        return;
    }

    char line[512];

    fgets(line, sizeof(line), file); // skip header

    int id;
    char name[256];
    float grade;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d,%255[^,],%f",
                   &id, name, &grade) == 3) {
            addStudent(list, id, name, grade);
        }
    }

    fclose(file);
    printf("Imported from %s successfully.\n", CSV_FILE);
}

/* ---------- Menu ---------- */

void menu() {
    printf("\n--- Student Manager ---\n");
    printf("1. Add Student\n");
    printf("2. Delete Student\n");
    printf("3. Search Student (Binary Search)\n");
    printf("4. Sort by ID\n");
    printf("5. Sort by Grade\n");
    printf("6. Show Students\n");
    printf("7. Show Statistics (GPA)\n");
    printf("8. Export to CSV\n");
    printf("9. Import from CSV\n");
    printf("10. Exit\n");
    printf("Choice: ");
}

/* ---------- Main ---------- */

int main() {
    StudentList list;
    initList(&list);
    loadFromFile(&list);

    int choice, id;
    char name[256];
    float grade;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Grade: ");
                scanf("%f", &grade);
                addStudent(&list, id, name, grade);
                break;

            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteStudent(&list, id);
                break;

            case 3:
                sortByID(&list);
                printf("Enter ID to search: ");
                scanf("%d", &id);
                int index = binarySearch(&list, id);
                if (index != -1) {
                    printf("Found: %s | Grade: %.2f\n",
                           list.students[index].name,
                           list.students[index].grade);
                } else {
                    printf("Student not found.\n");
                }
                break;

            case 4:
                sortByID(&list);
                printf("Sorted by ID.\n");
                break;

            case 5:
                sortByGrade(&list);
                printf("Sorted by Grade.\n");
                break;

            case 6:
                printStudents(&list);
                break;

            case 7:
                printStatistics(&list);
                break;

            case 8:
                exportToCSV(&list);
                break;

            case 9:
                importFromCSV(&list);
                break;

            case 10:
                saveToFile(&list);
                freeList(&list);
                printf("Goodbye.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }
}
