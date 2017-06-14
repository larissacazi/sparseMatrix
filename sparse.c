#include <stdion.h>
#include <stdlib.h>

typedef enum {
	FALSE,
	TRUE
} BOOL;

typedef struct Element {
	int row;
	int column;
	int element;
	Element *line;
	Element *col;
} Element;

typedef struct SparseMatrix {
	int row;
	int column;
	Element **line;		//Pointer Vector
	Element **column;	//Pointer Vector
} SparseMatrix;

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
	matrix->column = createVectorElement(column);	

	return matrix;
}

void fillSparseMatrix(SparseMatrix **matrix, int line, int column, int element) {
	Element *e = NULL;
	Element *aux1 = NULL;
	Element *aux2 = NULL;
	BOOL insert = FALSE;

	e = createElement(line, column, element);

	//Insert on line
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
	if((*matrix)->column[column] == NULL) {
		(*matrix)->column[column] = e;
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
			aux1 = aux1->column;
		}

		if(insert == TRUE) {
			aux1 = e;
			e->col = NULL;
		}
		
	}
}

void freeSparseMatrix(SparseMatrix *matrix) {
	
}

Matrix *multiplyMatrices(Matrix *first, Matrix *second) {
}

Matrix *addMatrices(Matrix *first, Matrix *second) {
}



int main() {
	char op;
	int read = 0, i = 0, row = 0, column = 0, element = 0;
	SparseMatrix *first = NULL;
	SparseMatrix *second = NULL; 

	//Get Operation
	scanf("%c", op);
	printf("op [%c]\n", op);

	while() {
		scanf("%d", &read);
		if(read == -1 && i == 0) {
			scanf("%d", &row); row = row - 1;
			scanf("%d", &column); column = column - 1;
			first = createSparseMatrix(row, column);
			i++;
		}
		else if(read == -1 && i == 1) {

		}
	}


	if(op == 'A') {

	}
	else if(op == 'M') {

	}
	
	return 0;
}