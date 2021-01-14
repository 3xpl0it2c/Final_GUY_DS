#include <stdlib.h>
#include "student.h"


student_type* newStudent(unsigned long studentID) {
	// Ask the computer to give us memory for a student.
	student_type* student = malloc(sizeof(struct Student));

	student->id = studentID;
	student->courses = NULL;
}
