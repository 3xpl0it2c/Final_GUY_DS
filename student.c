#include <stdlib.h>
#include "binTree.h"
#include "student.h"
#include "hash.h"

extern const int STUDENT_MAP_SIZE;
extern bnode_t* students[STUDENT_MAP_SIZE];

student_t* newStudent(unsigned long studentID) {
	// Allocate memory for a new student.
	student_t* student = malloc(sizeof(struct Student));

	student->id = studentID;
	student->courses = NULL;
	student->heapPosition = -1;
	student->coursesNum = 0;
	
	return student;
}

student_t* getStudent(unsigned long id) {
	int studentPos = hash(id, STUDENT_MAP_SIZE);
	bnode_t* student = students[studentPos];

	if(!student) return NULL;

	return student->key;
}

double getAverage(student_t* st) {
	double gradesSummary = 0;
	int amountOfCourses = st->coursesNum;
	course_t* courses = st->courses->data;

	for(int i = 0; i < amountOfCourses; i++) {
		course_t tmp = courses[i];
		gradesSummary += tmp.grade;
	}

	return gradesSummary / amountOfCourses;
}
