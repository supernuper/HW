#include "linked-list.h"
#include "grades.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


typedef struct course_item_t {
    char* course_name;
    int grade;
}course_item;

typedef struct student_item_t{
    int id;
    char* name;
    struct list *course_list;
}student_item;


struct grades {
  
    struct list *student_list;
};
 

element_clone_t elem_clone_s(void *element, void **output)
{
student_item* student_elem = (student_item*)element;
student_item** student = (student_item**)output;
*student=(struct student_item*)malloc(sizeof(student_item));
if(*student==NULL){
    return 1;
}
(*student)->name=(char*)malloc(sizeof((strlen(student_elem->name))+1));
if((*student)->name==NULL){
    return 1;
}

(*student)->name=student_elem->name;
(*student)->id=student_elem->id;
(*student)->course_list=student_elem->course_list;
return 0;
};

element_clone_t elem_clone_c(void *element, void **output)
{
course_item* course_elem = (course_item*)element;
course_item** course = (course_item**)output;
*course=(course_item*)malloc(sizeof(course_item));
if(*course==NULL){
    return 1;
}
(*course)->course_name=(char*)malloc(sizeof(*(course_elem->course_name)+1));
if((*course)->course_name==NULL){
    return 1;
}
///if(*course_elem==NULL)return;
*course=course_elem; //FIXME
*(*course)->course_name=*course_elem->course_name;
return 0;
};


element_destroy_t elem_destroy_s(void *element){
    student_item* student = (student_item*)element;
    list_destroy(student->course_list);
    free(student->name);
    free(student);
};

element_destroy_t elem_destroy_c(void *element){
    course_item* course = (course_item*)element;
    free(course->course_name);
    free(course);
};

struct grades* grades_init(){
    struct grades* grades_ds;
    struct student_item_t* student_elm;
    struct student_item_t** student;

    struct course_item_t* course_elm;
    struct course_item_t** course;
    //struct grades_item_t **student_clone;
    //struct course_item_t course;
   grades_ds->student_list = list_init(elem_clone_s(student_elm,student),elem_destroy_s(student_elm));
   student_elm->course_list = list_init(elem_clone_c(course_elm,course),elem_destroy_c(course_elm));
   ///create list

   return(grades_ds);
};

void grades_destroy(struct grades *grades)
{
    if(grades == NULL) return;
    struct iterator* next = list_begin(grades->student_list);  
    struct student_item_t *student; 
   // size_t elem_num = list_size(grades->student_list);
   // for(int i = 1 ; i <=elem_num ; i++ ){
    while(next != NULL){
    student = list_get(next);
    list_destroy(student->course_list);
}
    list_destroy(grades->student_list);
};


int grades_add_student(struct grades *grades, const char *name, int id)
{
    if(grades == NULL)return 1;
    struct iterator* next;
    struct student_item_t *student;
    next=list_begin(grades->student_list); 

    //size_t elem_num;
    //elem_num = list_size(grades->grades_list);
    //for(int i = 1 ; i <=elem_num ; i++ )
    
    while (next != NULL)
    {
        student = list_get(next);
        if(student->id == id){
            return 1;
        }
        next = list_next(next);    
    }
//can be orgenized better?

    student -> id = id;
    student -> name = (char*)malloc(strlen(name));
    if(student -> name == NULL) return 1;
    *(student -> name) = *name;

   int return_val = list_push_back(grades->student_list, student);
   free(student->name);
  return(return_val);
};

int grades_add_grade(struct grades *grades, const char *name, 
                     int id, int grade)
{
    if(grades == NULL || grade <0 || grade > 100) return 1;
    struct iterator* next;
    struct student_item_t *student;
    struct course_item_t* course;
    int success = 0;

    next=list_begin(grades->student_list); 
    
    while (next != NULL && !success)
    {
        student = list_get(next);
        if(student->id == id){
              success = 1;  
        }
        next = list_next(next);    
    }
    if(!success) return 1;

    next=list_begin(student->course_list);
    while (next != NULL)
    {
        course = list_get(next);
        if(*(course->course_name) == *name ) return 1;
        next = list_next(next);    
    }
    
    course->course_name = (char*)malloc(strlen(name));
    if(course->course_name==NULL)return 1;
    *(course->course_name) = *name;
    course-> grade = grade;
    int return_val = list_push_back(student->course_list,course);
    free(course->course_name);
    return return_val;
};

float grades_calc_avg(struct grades *grades, int id, char **out)
{

};
int grades_print_student(struct grades *grades, int id)
{
    
};

int grades_print_all(struct grades *grades)
{

};

//---------------------------------------------------------------------------------------------------//

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "*out" to NULL.
 * @note "out" is a pointer to char*. Meaning, your function should
 * allocate memory on the heap and set "*out" to point on that memory.
 * This methodology (of returning values via pointers) is very common in C.
 * An example of C method that returns a value via pointer:
 * void foo(int *out) {
 *   *out = 1;  
 * }
 */
//float grades_calc_avg(struct grades *grades, int id, char **out);

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
//int grades_print_student(struct grades *grades, int id);

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
//int grades_print_all(struct grades *grades);


