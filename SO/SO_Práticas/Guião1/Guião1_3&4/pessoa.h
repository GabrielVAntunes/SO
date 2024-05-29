#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

typedef struct Person{
    char name[200];
    int age;
}Person;

int add_person(char *name, int age);
int list_people(int N);
int update_age(char *name, int age);
int update_age_by_num(int position, int age);
int add_person_give_position(char *name, int age);