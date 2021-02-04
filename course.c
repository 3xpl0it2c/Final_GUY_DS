#include <stdlib.h>
#include "bool.h"
#include "student.h"

course_t* newCourse(int id, int grade) {
	course_t* c = malloc(sizeof(course_t));
	c->id = id;
	c->grade = grade;

	return c;
}

void addCourse(student_t* s, course_t* c) {
	// Assign a course to a student
	array_course* courses = s->courses;

	if(s->coursesNum < courses->totalSize) {
		int newSize = courses->totalSize * 2;
		courses->data = realloc(courses->data, newSize);
		courses->totalSize = newSize;
	}

	s->coursesNum++;
	courses->data[s->coursesNum] = c;
}

int changeGrade(unsigned long stID, course_t* c) {
	course_t* tmp;
	struct Student* st = getStudent(stID);
	int numOfCourses = st->coursesNum;

	for (int i = 0; i < numOfCourses; i++) {
		tmp = st->courses->data[i];
		if (tmp->id == c->id) {
			tmp->grade = c->grade;
			return true;
		}
	}

	return false;
}
