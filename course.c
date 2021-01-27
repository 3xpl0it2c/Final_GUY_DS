#include <stdlib.h>
#include "student.h"

void insertToCourseArray(array_course* arr, course_t course) {
	if (arr->index < (arr->totalSize - 1)) {
		int newSize = arr->totalSize * 2;
		arr->data = realloc(arr->data, newSize);
		arr->totalSize = newSize;
	}
	
	arr->index++;
	arr->data[arr->index] = course;
}


void addCourse(student_t* s, course_t* c) {
	return insertToCourseArray(s->courses, *c);
}
