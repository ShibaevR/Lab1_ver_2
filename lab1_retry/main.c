#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "tests.h"

#include "int-element.h"
#include "float-element.h"


void PrintMenu() {
    printf("\n--------------------------Menu--------------------------\n");
    printf("1. Show all matrices\n");
    printf("2. Show a chosen matrix\n");
    printf("3. Create a matrix\n");
    printf("4. Rename a matrix\n");
    printf("5. Matrix addition\n");
    printf("6. Matrix multiplication\n");
    printf("7. Multiplication of a matrix by a scalar\n");
    printf("8. Add a linear combination of rows to the selected row\n");
    printf("--------------------------------------------------------\n\n");
    printf("Enter 'STOP' to finish\n");
    printf("----------Or----------\n");
    printf("Select an action: ");
}

int main() {

    AllTests();
    printf("\nAll tests completed successfully\n");

    int action;

    MatrixCollection collection;
    collection.matrices = (NamedMatrix*)malloc(sizeof(NamedMatrix));
    collection.size = 0;

    while(1) {
        PrintMenu();

        char user_input[20];
        scanf("%19s", user_input);

        if (strcmp(user_input, "STOP") == 0) {

            for (int g = 0; g < collection.size; g++)
            {
                MatrixFree(&collection.matrices[g].matrix);
                free(collection.matrices[g].name);
            }
            free(collection.matrices);

            exit(0);
        }

        action = atoi(user_input);

        switch(action){
            case 1:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                printf("\nNumber of matrices: %zu\n", collection.size);
                for(int i=0; i < collection.size; i++){
                    printf("\n%d. %s\n", i+1, &collection.matrices[i].name);
                    MatrixPrint(&collection.matrices[i].matrix);
                }

                break;
            }


            case 2:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                int response=0;
                char name[20];
                Matrix m;
                size_t size;

                printf("\nNumber of matrices: %zu\n", collection.size);
                printf("Enter the matrix's name: ");
                scanf("%19s", name);

                MatrixFind(&collection, &m, name, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }

                printf("Matrix %s:\n", name);
                MatrixPrint(&m);

                break;
            }


            case 3:{
                Matrix m;
                char name[20];
                size_t size;
                int response=0;
                int option;
                FieldInfo m_field_info;

                printf("\nEnter the matrix's name: ");
                scanf("%s", name);

                printf("\nWhat type of elements do you want the matrix to have?\n");
                printf("Enter <1> for int or <2> for float: ");
                scanf("%d", &option);

                if(option==1){
                    m_field_info = *GetIntFieldInfo();

                    printf("\nEnter the size of the matrix (max size is 29): ");
                    scanf("%zu", &size);
                    if (size > 29){
                        printf("\nError: The max size is 7!\n");
                        break;
                    }
                }
                else if(option==2){
                    m_field_info = *GetFloatFieldInfo();

                    printf("\nEnter the size of the matrix (max size is 9): ");
                    scanf("%zu", &size);
                    if (size > 9){
                        printf("\nError: The max size is 7!\n");
                        break;
                    }
                }
                else{
                    printf("\nError: This type doesn't exist. Please try again.\n");
                    break;
                }

                void *max_number = malloc(m_field_info.element_size);
                if(max_number == NULL){
                    printf("\nError: Couldn't allocate memory space for multiplier\n");
                    exit(-1);
                }

                printf("\nDo you want to create the matrix automatically or manually?\n");
                printf("Enter <1> for automatic creation or <2> for manual: ");
                scanf("%d", &option);

                if(option==1){
                    printf("\nEnter the max number for random generation: ");
                    if(strcmp( m_field_info.type_name, "int")==0 ){
                        scanf("%d", max_number);
                    }
                    else if(strcmp( m_field_info.type_name, "float")==0 ){
                        scanf("%f", max_number);
                    }
                    MatrixAutoCreate(&collection, &m, name, size, &m_field_info, &response, max_number);
                }
                else if(option==2){
                    MatrixCreate(&collection, &m, name, size, &m_field_info, &response);
                }
                else{
                    printf("\nError: This action doesn't exist. Please try again.\n");
                    break;
                }

                if(collection.size - 1 > 0){
                    if(response > 0){
                        printf("\nError: A matrix with this name already exists\n");
                        break;
                    }
                }

                printf("%zu. %s\n", collection.size, name);
                MatrixPrint(&m);

                break;
            }


            case 4:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                char name_1[20];
                char name_2[20];
                Matrix m;
                int response=0;
                size_t size;

                printf("\nEnter the name of the matrix you want to rename: ");
                scanf("%19s", name_1);


                MatrixFind(&collection, &m, name_1, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }

                printf("\nEnter the new name for the matrix %s: ", name_1);
                scanf("%19s", name_2);

                MatrixRename(&collection, name_1, name_2);

                printf("\nMatrix %s:\n", name_2);
                MatrixPrint(&m);

                break;
            }


            case 5:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }
                else if(collection.size < 2){
                    printf("\nError: There are less then 2 matrices! You need at least 2 matrices for addition\n");
                    break;
                }

                Matrix m_sum, m_1, m_2;
                char name_1[20];
                char name_2[20];
                char name_3[20];
                int response=0;
                size_t size_1;
                size_t size_2;

                printf("\nEnter the first matrix's name: ");
                scanf("%s", name_1);
                MatrixFind(&collection, &m_1, name_1, &response, &size_1);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;

                printf("\nEnter the second matrix's name: ");
                scanf("%s", name_2);
                MatrixFind(&collection, &m_2, name_2, &response, &size_2);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;

                if(size_1 != size_2){
                    printf("\nError: For addition you need matrices to be the same size.\n");
                    break;
                }

                MatrixElementTypeCompare(&m_1, &m_2, &response);
                if(response > 0){
                    printf("\nError: Matrices need to have the same type of elements.\n");
                    break;
                }
                response = 0;

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name_3);
                MatrixFind(&collection, &m_sum, name_3, &response, &size_1);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                response = 0;

                MatrixAdd(&m_sum, &m_1, &m_2, &response, &collection, name_3);

                printf("\nResult - Matrix %s:\n", name_3);
                MatrixPrint(&m_sum);

                break;
            }


            case 6:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }
                else if(collection.size < 2){
                    printf("\nError: There are less then 2 matrices! You need at least 2 matrices for multiplication\n");
                    break;
                }

                Matrix m_mult, m_1, m_2;
                char name_1[20];
                char name_2[20];
                char name_3[20];
                int response=0;
                size_t size_1;
                size_t size_2;

                printf("\nEnter the first matrix's name: ");
                scanf("%s", name_1);
                MatrixFind(&collection, &m_1, name_1, &response, &size_1);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;

                printf("\nEnter the second matrix's name: ");
                scanf("%s", name_2);
                MatrixFind(&collection, &m_2, name_2, &response, &size_2);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;

                if(size_1 != size_2){
                    printf("\nError: For multiplication you need matrices to be the same size.\n");
                    break;
                }

                MatrixElementTypeCompare(&m_1, &m_2, &response);
                if(response > 0){
                    printf("\nError: Matrices need to have the same type of elements.\n");
                    break;
                }
                response = 0;

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name_3);
                MatrixFind(&collection, &m_mult, name_3, &response, &size_1);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                response = 0;

                MatrixMultiply(&m_mult, &m_1, &m_2, &response, &collection, name_3);

                printf("\nResult - Matrix %s:\n", name_3);
                MatrixPrint(&m_mult);

                break;
            }


            case 7:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                Matrix m_mult, m_1;
                char name_1[20];
                char name_2[20];
                int response=0;
                size_t size;

                printf("\nEnter the matrix's name: ");
                scanf("%s", name_1);
                MatrixFind(&collection, &m_1, name_1, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;

                char *type_name = GetElementTypeName(&m_1);

                void *multiplier = malloc(sizeof(m_1.type_info.element_size));
                if(multiplier == NULL){
                    printf("\nError: Couldn't allocate memory space for multiplier\n");
                    exit(-1);
                }

                printf("\nEnter the a %s scalar: ", type_name);
                if (strcmp( type_name, "int")==0 ){
                    scanf("%d", multiplier);
                }
                else if (strcmp( type_name, "float")==0 ){
                    scanf("%f", multiplier);
                }

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name_2);
                MatrixFind(&collection, &m_mult, name_2, &response, &size);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                response = 0;

                MatrixMultiplyByScalar(&m_mult, &m_1, &collection, name_2, multiplier);

                printf("\nResult - Matrix %s:\n", name_2);
                MatrixPrint(&m_mult);

                break;
            }


            case 8:{
                if(collection.size == 0){
                    printf("\nError: No matrices created\n");
                    break;
                }

                Matrix m_res, m_1;
                char name_1[20];
                char name_2[20];
                int response=0;
                size_t size;
                int row_number;

                printf("\nEnter the matrix's name: ");
                scanf("%s", name_1);
                MatrixFind(&collection, &m_1, name_1, &response, &size);
                if(response==0){
                    printf("\nError: A matrix with this name doesn't exist\n");
                    break;
                }
                response = 0;

                printf("\nEnter the number of the row: ");
                scanf("%d", &row_number);
                if(row_number > size || row_number == 0){
                    printf("\nError: This row doesn't exist\n");
                    break;
                }

                printf("\nEnter the new matrix's name: \n");
                scanf("%s", name_2);
                MatrixFind(&collection, &m_res, name_2, &response, &size);
                if(response > 0){
                    printf("\nError: A matrix with this name already exists\n");
                    break;
                }
                response = 0;

                Matrix linear_combination[size];

                char *type_name = GetElementTypeName(&m_1);

                void *max_number;
                if(strcmp( type_name, "int")==0 ){
                    max_number = malloc(sizeof(int));
                    if(max_number == NULL){
                        printf("\nError: Couldn't allocate memory space for multiplier\n");
                        exit(-1);
                    }

                    *(int*)max_number = 10;
                }
                else if(strcmp( type_name, "float")==0 ){
                    max_number = malloc(sizeof(float));
                    if(max_number == NULL){
                        printf("\nError: Couldn't allocate memory space for multiplier\n");
                        exit(-1);
                    }

                    *(float*)max_number = 10.0;
                }

                LinearCombinationInitialize(&linear_combination, &m_1);

                MatrixAddLinearCombination(&m_res, row_number, &m_1, &collection, name_2, &linear_combination, max_number);

                printf("\nResult - Matrix %s:\n", name_2);
                MatrixPrint(&m_res);

                MatrixFree(&linear_combination);

                break;
            }


            default:{
                printf("\nError: This action doesn't exist. Please try again.\n");
                break;
            }
        }
    }

    return 0;
}
