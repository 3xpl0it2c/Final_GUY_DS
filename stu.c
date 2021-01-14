#include "student.h"
#include <stdio.h>
#include <stdlib.h>
student* newstudent(unsigned long id)
{
    student* newstudent=(student*) malloc(sizeof(student));
    newstudent->id =id ;
    newstudent->coursename = 0;
    newstudent->courses=NULL;
    newstudent->heaPosition=-1;
    
}

