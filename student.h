struct Course {
	int id;
	int grade;
};

struct Student {
	unsigned long id;
	struct Course *courses;
	int coursesNum;
	int heapPosition;
};

typedef struct Course course_type;
typedef struct Student student_type;
