#ifndef LAB1_RETRY_INT_ELEMENT_H
#define LAB1_RETRY_INT_ELEMENT_H

#include "fieldinfo.h"


void IntAdd(void *sum, void* a, void* b);
void IntMultiply(void *product, void* a, void* b);
void IntPrint(void *element);
void IntScan(void *element);
void IntRandom(void *element, void *max_int_number);

FieldInfo *GetIntFieldInfo();


#endif //LAB1_RETRY_INT_ELEMENT_H
