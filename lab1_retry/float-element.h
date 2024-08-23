#ifndef LAB1_RETRY_FLOAT_ELEMENT_H
#define LAB1_RETRY_FLOAT_ELEMENT_H

#include "fieldinfo.h"


void FloatAdd(void *sum, void* a, void* b);
void FloatMultiply(void *product, void* a, void* b);
void FloatPrint(void *element);
void FloatScan(void *element);
void FloatRandom(void *element, void *max_float_number);

FieldInfo *GetFloatFieldInfo();

#endif //LAB1_RETRY_FLOAT_ELEMENT_H
