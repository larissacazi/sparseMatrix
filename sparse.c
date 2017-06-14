#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	FALSE,
	TRUE
} BOOL;

typedef struct Element {
	int row;
	int column;
	int element;
	struct Element *line;
	struct Element *col;
} Element;

typedef struct SparseMatrix {
	int row;
	int column;
	Element **line;		//Pointer Vector
	Element **col;	//Pointer Vector
} SparseMatrix;

char *getSubstring(char *first, int idx, int len) {
	char *subStr = (char*)malloc(sizeof(char) * (len+1));
	
	memcpy(subStr, &first[idx], len);
	subStr[len] = '\0';
	//printf("substr = %s\n", subStr);

	return subStr;
}

void printIntMatrix(int **m, int r, int c) {
	int i, j;

	printf("---- Matrix:\n");
	for(i=0; i<r; i++) {
		for(j=0; j<c; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("---- ---- ----\n");
}

Element *createElement(int line, int column, int element) {
	Element *e = NULL;
	e = (Element *)calloc(1, sizeof(Element));
	e->row = line;
	e->column = column;
	e->element = element;

	return e;
}

Element **createVectorElement(int n) {
		Element **vector = NULL;

		vector = (Element**)calloc(n, sizeof(Element*));

		return vector;
}

SparseMatrix *createSparseMatrix(int row, int column) {
	SparseMatrix *matrix = NULL;
	matrix = (SparseMatrix*)calloc(1, sizeof(SparseMatrix));
	
	matrix->row = row;
	matrix->column = column;
	matrix->line = createVectorElement(row);
	matrix->col = createVectorElement(column);	

	return matrix;
}

void printSparseMatrix(SparseMatrix *matrix) {
	int **m = NULL;
	int i = 0, j = 0;
	Element *aux = NULL;

	m = (int**)calloc(matrix->row, sizeof(int*));

	for(i=0; i<matrix->row; i++) {
		m[i] = (int*)calloc(matrix->column, sizeof(int));
	}

	for(i=0; i<matrix->row; i++) {
		aux = matrix->line[i];

		while(aux != NULL) {
			m[aux->row][aux->column] = aux->element;
			aux = aux->line;
		}
	}

	printf("---- Matrix:\n");
	for(i=0; i<matrix->row; i++) {
		for(j=0; j<matrix->column; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("---- ---- ----\n");

}

int **getIntMatrix(SparseMatrix *matrix) {
	int **m = NULL;
	int i = 0, j = 0;
	Element *aux = NULL;

	m = (int**)calloc(matrix->row, sizeof(int*));

	for(i=0; i<matrix->row; i++) {
		m[i] = (int*)calloc(matrix->column, sizeof(int));
	}

	for(i=0; i<matrix->row; i++) {
		aux = matrix->line[i];

		while(aux != NULL) {
			m[aux->row][aux->column] = aux->element;
			aux = aux->line;
		}
	}

	return m;
}

void fillSparseMatrix(SparseMatrix **matrix, int line, int column, int element) {
	Element *e = NULL;
	Element *aux1 = NULL;
	Element *aux2 = NULL;
	BOOL insert = FALSE;

	e = createElement(line, column, element);
	printf("Matrix->Row [%d] Matrix->Col [%d]\n", (*matrix)->row, (*matrix)->column);
	printf("line [%d] column [%d]\n", line, column);

	if(line > (*matrix)->row || column > (*matrix)->column) return;

	//Insert on line
	printf("fillSparseMatrix:: Insert on line\n");
	if((*matrix)->line[line] == NULL) {
		(*matrix)->line[line] = e;

	}
	else {
		aux1 = (*matrix)->line[line];
		aux2 = (*matrix)->line[line];
		while(aux1 != NULL) {
			if(aux1->row > line) {
				aux2 = e;
				e->line = aux1;
				insert = TRUE;
				break;
			}
			aux2 = aux1;
			aux1 = aux1->line;
		}

		if(insert == TRUE) {
			aux1 = e;
			e->line = NULL;
		}

	}
	insert = FALSE;

	//Insert on column
	printf("fillSparseMatrix:: Insert on column\n");
	if((*matrix)->col[column] == NULL) {
		(*matrix)->col[column] = e;
	}
	else {
		aux1 = (*matrix)->col[column];
		aux2 = (*matrix)->col[column];
		while(aux1 != NULL) {
			if(aux1->column > column) {
				aux2->col = e;
				e->col = aux1;
				insert = TRUE;
				break;
			}
			aux2 = aux1;
			aux1 = aux1->col;
		}

		if(insert == TRUE) {
			aux1 = e;
			e->col = NULL;
		}
		
	}
}

void freeSparseMatrix(SparseMatrix *matrix) {
	
}

SparseMatrix *convertInMatrixToSparseMatrix(int **m, int r, int c) {
	SparseMatrix *matrix = NULL;

	matrix = createSparseMatrix(r, c);

	for(i=0; i<r; i++) {
		for(j=0; j<c; j++) {
			if(m[i][j] != 0) {
				fillSparseMatrix(&matrix, i, j, m[i][j]);
			}
		}
	}

	return matrix;
}


SparseMatrix *multiplyMatrices(SparseMatrix *first, SparseMatrix *second) {
	int **firstM = NULL;
	int **secondM = NULL;
	int **result = NULL;
	SparseMatrix *matrix = NULL;
	int i, j, k;

	result = (int **)malloc(sizeof(int*) * first->row);
	for(i=0; i<first->row; i++) result[i] = (int*)calloc(second->column, sizeof(int));

	if(first->column != second->row) return;

	firstM = getIntMatrix(first);
	secondM = getIntMatrix(second);

	for(i=0; i<first->row; i++) {
		for(j=0; j<second->column; j++) {
			for(k=0; k<first->column; k++) {
				result[i][j] += first[i][k] * second[k][j];
			}
		}

	}

	printIntMatrix(result, first->row, second->column);
	matrix = convertInMatrixToSparseMatrix(result, first->row, second->column);

	return matrix;
}

SparseMatrix *addMatrices(SparseMatrix *first, SparseMatrix *second) {
	int **firstM = NULL;
	int **secondM = NULL;
	int **result = NULL;
	SparseMatrix *matrix = NULL;
	int i, j, k;

	result = (int **)malloc(sizeof(int*) * first->row);
	for(i=0; i<first->row; i++) result[i] = (int*)calloc(first->column, sizeof(int));

	if(first->row != second->row) return;
	if(first->column != second->column) return;

	firstM = getIntMatrix(first);
	secondM = getIntMatrix(second);

	for(i=0; i<first->row; i++) {
		for(j=0; j<second->column; j++) {
			for(k=0; k<first->column; k++) {
				result[i][j] += first[i][j] + second[i][j];
			}
		}

	}

	printIntMatrix(result, first->row, first->column);
	matrix = convertInMatrixToSparseMatrix(result, first->row, first->column);

	return matrix;
}

int main() {
	char op;
	int read = 0, row = 0, column = 0, value = 0;
	SparseMatrix *first = NULL;
	SparseMatrix *second = NULL;
	BOOL ret = TRUE;
	char line[30];



	//Get Operation
	scanf("%c", &op);
	printf("op [%c]\n", op);

	//Reading Data FIRST
	scanf("%d %d %d", &value, &row, &column);
	first = createSparseMatrix(row, column);
	while (scanf("%d %d %d", &row, &column, &value) && row != -1){
		fillSparseMatrix(&first, row, column, value);
	}
	printf("First Matrix:\n");
	printSparseMatrix(first);

	//Reading Data SECOND
	second = createSparseMatrix(column, value);
	//while (scanf("%d %d %d", &row, &column, &value) != EOF && i < 4){
	while (scanf("%d %d %d", &row, &column, &value) && row != -1){
		fillSparseMatrix(&second, row, column, value);
	}
	printf("Second Matrix:\n");
	printSparseMatrix(second);


	if(op == 'A') {

	}
	else if(op == 'M') {

	}
	
	return 0;
}