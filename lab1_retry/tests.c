#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tests.h"
#include "matrix.h"
#include "int-element.h"


void TestMatrixCreation(){
    int response = -1;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[1] = "a";
    size_t size_1 = 2;
    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    if(collection.size != 1){
        printf("\nError in MatrixAutomaticCreate: couldn't add a matrix to the collection\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);

        assert(response);
    }
}


void TestExistingMatrixFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[1] = "a";
    size_t size_1 = 2;
    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);
    MatrixFind(&collection, &m_1, name_1, &response, &size_1);

    if(response == 0){
        printf("\nError in MatrixFind: couldn't find the matrix to the collection\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);

        assert(response);
    }
}


void TestNotExistingMatrixFind(){
    int response = -1;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[1] = "a";
    char non_existing_name[1] = "c";
    size_t size_1 = 2;
    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);
    MatrixFind(&collection, &m_1, non_existing_name, &response, &size_1);

    if(response == 0){
        printf("\nError in MatrixFind: found a matrix that doesn't exist\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);

        assert(response);
    }
}


void TestRenamedMatrixFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[1] = "a";
    char new_name[1] = "d";
    size_t size_1 = 2;
    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);
    MatrixRename(&collection, name_1, new_name);
    MatrixFind(&collection, &m_1, new_name, &response, &size_1);

    if(response == 0){
        printf("\nError in MatrixRename: couldn't rename a matrix\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);

        assert(response);
    }
}


void TestReplacedNameMatrixFind(){
    int response = -1;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    Matrix m_1;
    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    char name_1[1] = "a";
    char new_name[1] = "d";
    size_t size_1 = 2;
    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);
    MatrixRename(&collection, name_1, new_name);
    MatrixFind(&collection, &m_1, name_1, &response, &size_1);

    if(response == 0){
        printf("\nError in MatrixRename: found a name that's no longer in use\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);

        assert(response);
    }
}


void TestMatrixAdd(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_2;
    char name_2[1] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, &response, max_number);

    Matrix m_sum;
    size_t size_3 = 2;
    char name_3[3] = "sum";
    MatrixAdd(&m_sum, &m_1, &m_2, &response, &collection, name_3);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_sum.data + i*m_sum.size + j == NULL){
                printf("\nError in MatrixAdd: incorrect sum of elements\n");

                collection.size = 0;
                free(collection.matrices);
                MatrixFree(&m_1);
                MatrixFree(&m_2);
                MatrixFree(&m_sum);

                assert(response);
            }
        }
    }
}


void TestMatrixSumFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_2;
    char name_2[1] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, &response, max_number);

    Matrix m_sum;
    size_t size_3 = 2;
    char name_3[3] = "sum";
    MatrixAdd(&m_sum, &m_1, &m_2, &response, &collection, name_3);

    MatrixFind(&collection, &m_sum, name_3, &response, &size_3);
    if(response == 0){
        printf("\nError in MatrixAdd: couldn't add the matrix sum to the collection\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);
        MatrixFree(&m_2);
        MatrixFree(&m_sum);

        assert(response);
    }
}


void TestMatrixMultiply(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_2;
    char name_2[1] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, &response, max_number);

    Matrix m_product;
    size_t size_3 = 2;
    char name_3[7] = "product";
    MatrixMultiply(&m_product, &m_1, &m_2, &response, &collection, name_3);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_product.data + i*m_product.size + j == NULL){
                printf("\nError in MatrixMultiply: incorrect product of elements\n");

                collection.size = 0;
                free(collection.matrices);
                MatrixFree(&m_1);
                MatrixFree(&m_2);
                MatrixFree(&m_product);

                assert(response);
            }
        }
    }
}


void TestMatrixProductFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_2;
    char name_2[1] = "b";
    size_t size_2 = 2;
    MatrixAutoCreate(&collection, &m_2, name_2, size_2, &m_field_info, &response, max_number);

    Matrix m_product;
    size_t size_3 = 2;
    char name_3[7] = "product";
    MatrixMultiply(&m_product, &m_1, &m_2, &response, &collection, name_3);

    MatrixFind(&collection, &m_product, name_3, &response, &size_3);
    if(response == 0){
        printf("\nError in MatrixMultiply: couldn't add the matrix to the collection\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);
        MatrixFree(&m_2);
        MatrixFree(&m_product);

        assert(response);
    }
}


void TestMatrixMultiplyByScalar(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_result;
    size_t size_2 = 2;
    char name_2[7] = "result";

    void *multiplier = malloc(m_field_info.element_size);
    *(int*)multiplier = 5;

    MatrixMultiplyByScalar(&m_result, &m_1, &collection, name_2, multiplier);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_result.data + i*m_result.size + j == NULL || m_result.data + i*m_result.size + j == m_1.data + i*m_1.size + j){
                printf("\nError in MatrixMultiplyByScalar: incorrect product of elements\n");

                collection.size = 0;
                free(collection.matrices);
                MatrixFree(&m_1);
                MatrixFree(&m_result);

                assert(response);
            }
        }
    }
}


void TestMatrixMultiplyByScalarFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_result;
    size_t size_2 = 2;
    char name_2[7] = "result";

    void *multiplier = malloc(m_field_info.element_size);
    *(int*)multiplier = 5;

    MatrixMultiplyByScalar(&m_result, &m_1, &collection, name_2, multiplier);

    MatrixFind(&collection, &m_result, name_2, &response, &size_2);

    if(response == 0){
        printf("\nError in MatrixMultiplyByScalar: couldn't add the matrix to the collection\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);
        MatrixFree(&m_result);

        assert(response);
    }
}


void TestMatrixAddLinearCombination(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_result;
    size_t size_2 = 2;
    char name_2[7] = "result";
    int row_number = 2;

    Matrix linear_combination;
    char name_3[2] = "lc";
    size_t size_3 = 1;

    LinearCombinationInitialize(&linear_combination, &m_1);

    MatrixAddLinearCombination(&m_result, row_number, &m_1, &collection, name_2, &linear_combination, max_number);

    for(int i=0; i < 2; i++){
        for(int j=0; j < 2; j++){
            if(m_result.data + i*m_result.size + j == NULL || m_result.data + i*m_result.size + j == m_1.data + i*m_1.size + j){
                printf("\nError in MatrixAddLinearCombination: incorrect sum of elements\n");

                collection.size = 0;
                free(collection.matrices);
                MatrixFree(&m_1);
                MatrixFree(&m_result);
                MatrixFree(&linear_combination);

                assert(response);
            }
        }
    }
}


void TestMatrixMatrixAddLinearCombinationFind(){
    int response = 0;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    FieldInfo m_field_info;
    m_field_info = *GetIntFieldInfo();

    void *max_number = malloc(m_field_info.element_size);
    *(int*)max_number = 5;

    Matrix m_1;
    char name_1[1] = "a";
    size_t size_1 = 2;
    MatrixAutoCreate(&collection, &m_1, name_1, size_1, &m_field_info, &response, max_number);

    Matrix m_result;
    size_t size_2 = 2;
    char name_2[7] = "result";
    int row_number = 2;

    Matrix linear_combination;
    char name_3[2] = "lc";
    size_t size_3 = 1;

    LinearCombinationInitialize(&linear_combination, &m_1);

    MatrixAddLinearCombination(&m_result, row_number, &m_1, &collection, name_2, &linear_combination, max_number);

    MatrixFind(&collection, &m_result, name_2, &response, &size_3);
    if(response == 0){
        printf("\nnError in MatrixAddOfLinearCombination: couldn't add the matrix to the collection\n");

        collection.size = 0;
        free(collection.matrices);
        MatrixFree(&m_1);
        MatrixFree(&m_result);
        MatrixFree(&linear_combination);

        assert(response);
    }
}


void AllTests(){

    TestMatrixCreation();                       //Проверка добавления 1 матрицы в коллекцию

    TestExistingMatrixFind();                   //Проверка нахождения существующей матрицы в коллекции
    TestNotExistingMatrixFind();                //Проверка нахождения несуществующей матрицы в коллекции

    TestRenamedMatrixFind();                    //Проверка переименовывания матрицы
    TestReplacedNameMatrixFind();               //Проверка нахождения уже заменённого имени

    TestMatrixAdd();                            //Проверка сложения матриц
    TestMatrixSumFind();                        //Проверка добавления суммы матриц в коллекцию

    TestMatrixMultiply();                       //Проверка умножения матриц
    TestMatrixProductFind();                    //Проверка добавления произведения матриц в коллекцию

    TestMatrixMultiplyByScalar();               //Проверка умножения матрицы на число
    TestMatrixMultiplyByScalarFind();           //Проверка добавления новой мтарицы в коллекцию

    TestMatrixAddLinearCombination();           //Проверка добавления к строке матрицы линейной комбинации других строк
    TestMatrixMatrixAddLinearCombinationFind(); //Проверка добавления новой матрицы в коллекцию

}