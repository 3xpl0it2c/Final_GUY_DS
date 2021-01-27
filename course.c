#include <stdlib.h>
#include "student.h"

void addCourse(student_t* s, course_t* c) {
	// Assign a course to a student 
	array_course* courses = s->courses;

	if(s->coursesNum < courses->totalSize) {
		int newSize = courses->totalSize * 2;
		courses->data = realloc(courses->data, newSize);
		courses->totalSize = newSize;
	}

	s->coursesNum++;
	courses->data[s->coursesNum] = *c;
}
