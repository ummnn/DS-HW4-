#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); 			   //��� ���� �Լ�
void print_matrix(int** matrix, int row, int col); //��� ��� �Լ�
int free_matrix(int** matrix, int row, int col);   //�޸� �Ҵ� ���� �Լ�
int fill_data(int** matrix, int row, int col); 	   //��Ŀ� ���� �ִ� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);		//����� ���� ���ϴ� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);	//����� ���� ���ϴ� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);		//��ġ����� ���ϴ� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);		//����� ���� ���ϴ� �Լ�

int main()
{
    char command; //��ɾ ��� ����
    printf("[----- [�̵���]  [2019038027] -----]\n");

	int row, col; //��� ��
	srand(time(NULL)); //time�Լ��� �̿��� ������ �� ����

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); //���������� ��� ���� ũ�⸦ �Է¹޴´�
    int** matrix_a = create_matrix(row, col);	//create_matrix �Լ��� matrix_a ����
	int** matrix_b = create_matrix(row, col); 	//create_matrix �Լ��� matrix_b ����
	int** matrix_a_t = create_matrix(col, row); //create_matrix �Լ��� matrix_a_t ����

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} //matrix_a matrix_b�� NULL�� ��� -1��ȯ

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��ɾ �Է¹޴´�

		switch(command) {
		case 'z': case 'Z': //��ɾ z�� Z�� ���
		    printf("Matrix Initialized\n");  
			fill_data(matrix_a, row, col); //fill_data �Լ��� ���a�� ä���
			fill_data(matrix_b, row, col); //fill_data �Լ��� ���b�� ä���
			break;
        case 'p': case 'P': //��ɾ p�� P�� ���
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); //print_matrix�Լ��� matrix_a ���
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); //print_matrix�Լ��� matrix_b ���
			break;
        case 'a': case 'A': //��ɾ a�� A�� ���
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); //addition_matrix �Լ�
			break;
        case 's': case 'S': //��ɾ s�� S�� ���
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //subtraction_matrix �Լ��� matrix_a�� matrix_b�� ���� ���Ѵ�
			break;
        case 't': case 'T': //��ɾ t�� T�� ���
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix�Լ��� matrix_a�� ��ġ�Լ��� matrix_t�� ���Ѵ�
            print_matrix(matrix_a_t, col, row); //print_matrix �Լ��� ��� ���
			break;
        case 'm': case 'M': //��ɾ m�̳� M�� ���
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix�Լ��� matrix_a�� ��ġ�Լ��� matrix_t�� ���Ѵ�
            multiply_matrix(matrix_a, matrix_a_t, row, col);  //multifly_matrix�Լ��� matrix_a�� matrix_a�� ��ġ�Լ��� matrix_t�� ���� ���Ѵ�
			break;
        case 'q': case 'Q': //��ɾ q�� Q�� ���
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //free_matrix�Լ��� matrix_a_t�� �޸� �Ҵ� ����
            free_matrix(matrix_a, row, col);   //free_matrix�Լ��� matrix_a�� �޸� �Ҵ� ����
            free_matrix(matrix_b, row, col);   //free_matrix�Լ��� matrix_b�� �޸� �Ҵ� ����
			break;

		default: //���� ���̽��� �ƴ� �ٸ����� ���´ٸ�
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //concentrarion�޽��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); //��ɾ q�� Q�ϋ����� �ݺ�

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { 					//row�� col�� ������ 0�� ���
		printf("Check the size of row and col!\n"); //�����޽��� ��� ��
		return NULL; 								//NULL ��ȯ
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); //int�� ���� ���������� matrix�� intŸ�Ի����� * row ��ŭ�� �޸� �Ҵ�
	for (int r = 0; r < row; r++) {					  //ũ�Ⱑ row�� �迭 ����
		matrix[r] = (int*)malloc(sizeof(int) * col);  //�����͹迭 matrix[r]�� intŸ�Ի����� * col ��ŭ�� �޸� �Ҵ�
	}

	/* Check post conditions */
	if (matrix == NULL) {						//matrix�� NULL�̶��
		printf("Memory Allocation Failed.\n"); 	//�޸��Ҵ� ���� �޽��� ��� ��
		return NULL; 							//NULL ��ȯ
	}

	return matrix; //matrix ��ȯ
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)  
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row�� col�� ������ 0�ϰ��
		printf("Check the size of row and col!\n"); //�����޽��� ��� �� 
		return;										//NULL ��ȯ
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { //����� ����Ѵ�
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {						//matrix�� NULL�̶��
		printf("Memory Allocation Failed.\n");	//�޸� �Ҵ� ���� �޽��� ��� ��
		return;									//NULL ��ȯ
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row�� col�� ������ 0�̶��
		printf("Check the size of row and col!\n"); //�����޽��� ��� �� 
		return -1;									//-1��ȯ
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //����� col�� �ش��ϴ� �����޸� �Ҵ��� �����Ѵ�
		free(matrix[matrix_row]);
	}

	free(matrix); //matrix ���� �޸� �Ҵ� ����
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //����� ����Ű�� ������ matrix�� row, col�� �޾ƿ´�
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { 					//row �� col������ ������ 0�� �Ѿ���� ��쿡�� 
		printf("Check the size of row and col!\n"); //���� �޽����� ����ϰ�
		return -1; 									// -1�� ��ȯ�Ѵ�
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20; //����� 0~19 ������ ������ ������ ä���
	/* Check post conditions */
    if (matrix == NULL) { 					   //����� NULL�̶��
		printf("Memory Allocation Failed.\n"); //�޸� �Ҵ� ���� �޽����� ����� ��
		return -1;							   //-1 ��ȯ
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col); //create_matrix �Լ��� ����� matrix_sum����� �����
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row�� col�� ������ 0�� ���
		printf("Check the size of row and col!\n"); //���� �޽��� ��� ��
		return -1;									//-1��ȯ
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix_sum�� matrix_a �� matrix_b �� ���Ѱ��� ����
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { //matrix_a, matrix_b, matrix_sum �� �ϳ��� NULL�̶�� 
		printf("Memory Allocation Failed.\n");						  //�޸� �Ҵ� ���� �޽��� ��� ��
		return -1;													  //-1 ��ȯ
	}

	print_matrix(matrix_sum, row, col); //print_matrix�Լ��� �̿��� print_sum ��� ���
	free_matrix(matrix_sum, row, col);	//free_matrix�Լ��� �̿��� matrix_sum�� �Ҵ�� �޸� ����
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); //create_matrix �Լ��� ����� matrix_sub ����� �����
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row�� col�� ������ 0�̶��
		printf("Check the size of row and col!\n");	//�����޽��� ��� ��
		return -1;									//-1��ȯ
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //matrix_a���� matrix_b�� �A �� matrix_sub�� ���� ����
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { //martix_a, matrix_b, matrix_sub �� �ϳ��� NULL�̶��  
		printf("Memory Allocation Failed.\n");						  //�޸� �Ҵ� ���� �޽��� ��� �� 
		return -1;													  //-1 ��ȯ
	}
	print_matrix(matrix_sub, row, col); //print_matrix�Լ��� �̿��� print_sum ��� ���
	free_matrix(matrix_sub, row, col);  //free_matrix �Լ��� �̿��� matrix_sub�� �Ҵ�� �޸� ����

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row�� col�� ������ 0�̶��
		printf("Check the size of row and col!\n"); //�����޽��� ��� ��
		return -1;									//-1��ȯ
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { 
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	 //matrix_t[matrix_row][matrix_col]�� matrix[matrix_col][matrix_row]�� �־� matrix_a�� ��ġ��� matrix_t�� �����
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {   //matrix�� matrix_t�� NULL�� ���
		printf("Memory Allocation Failed.\n"); //�����޽��� ��� ��
		return -1; 							   //-1 ��ȯ
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row); //create_matrix�Լ��� �̿��� matrix_a�� matrix_a�� ��ġ��� matrix_t�� ������ ������ ����� �����
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row�� col�� ������ 0�̶��
		printf("Check the size of row and col!\n");	//�����޽��� ��� ��
		return -1;									//-1��ȯ
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0; 										    					         //�������� �����ϴ� ���� temp �ʱ�ȭ
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; //temp�� matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row] �� ����
			matrix_axt[matrix_a_row][matrix_t_row] = temp; 										 //matrix_axt�� temp�� ����
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {	//matrix_t�� matrix_axt�� NULL�� ���
		printf("Memory Allocation Failed.\n");		//�޸� �Ҵ� ���� �޽��� ��� ��
		return -1;									//-1 ��ȯ
	}
	print_matrix(matrix_axt, row, row); //print_matrix �Լ��� �̿��� matrix_axt���
	free_matrix(matrix_axt, row, col); //free_matrix �Լ��� �̿��� matrix_axt�� �Ҵ�� �޸� ����
	return 1;
}

