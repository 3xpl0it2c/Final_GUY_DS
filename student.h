struct Course {
	int id;
	int grade;
}

struct Student {
	unsigned long id;
	struct Course *courses;
	int coursesNum;
	int heapPosition;
}
