# 🎓 Student Record Management System (C)

A dynamic command-line Student Record Management System written in pure C.

This project demonstrates intermediate systems programming concepts including dynamic memory management, sorting algorithms, binary search optimization, statistical computation, and CSV interoperability.

---

## 🚀 Features

* Add students (ID, Name, Grade)
* Delete students by ID
* Binary search (O(log n)) after sorting
* Sort by:

  * Student ID
  * Grade (descending)
* Class statistics:

  * Average GPA
  * Highest grade
  * Lowest grade
* File persistence (custom pipe-delimited format)
* CSV export
* CSV import
* Dynamic memory resizing (vector-style growth)

---

## 🧠 Technical Concepts Demonstrated

### Memory Management

* `malloc`
* `realloc`
* `free`
* Heap-allocated strings
* Automatic capacity doubling strategy

### Algorithms

* Binary Search (O(log n))
* Sorting using `qsort`
* Linear scan for statistics
* Aggregate computations (mean, min, max)

### Data Structures

```c
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
```

---

## 📊 GPA Calculation

The class GPA is calculated as:

```
GPA = (sum of all grades) / number_of_students
```

---

## 📁 File Storage

### Persistent Data File

```
students.txt
```

Format:

```
ID|Name|Grade
```

Example:

```
101|Alice|89.50
102|Bob|76.00
```

---

### CSV Export File

```
students.csv
```

Format:

```
ID,Name,Grade
```

Compatible with:

* Excel
* Google Sheets
* LibreOffice

---

## 🛠 Compilation

### Windows (MinGW)

```bash
gcc -Wall -Wextra -std=c11 -o student_manager.exe student_manager.c
student_manager.exe
```

### Linux / macOS

```bash
gcc -Wall -Wextra -std=c11 -o student_manager student_manager.c
./student_manager
```

---

## 📋 Menu Options

```
1. Add Student
2. Delete Student
3. Search Student (Binary Search)
4. Sort by ID
5. Sort by Grade
6. Show Students
7. Show Statistics (GPA)
8. Export to CSV
9. Import from CSV
10. Exit
```

---

## 🔮 Possible Future Improvements

* Median grade calculation
* Standard deviation
* Input validation & error recovery
* Multi-file modular design (.h/.c separation)
* Hash-table-based indexing
* SQLite database integration
* Networked version (client-server)
* Unit tests

---

## 📜 License

MIT License
---

⭐ If you found this project useful, feel free to star the repository.
