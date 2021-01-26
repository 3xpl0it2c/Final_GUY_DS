#include <stdlib.h>
#include "student.h"

student_type* newStudent(unsigned long studentID) {
	// Allocate memory for a new student.
	student_type* student = malloc(sizeof(struct Student));

	student->id = studentID;
	student->courses = NULL;
	student->heapPosition = -1;
	student->coursesNum = 0;
	
	return student;
}
