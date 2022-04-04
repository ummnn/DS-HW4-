#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); 		   //행렬 생성 함수
void print_matrix(int** matrix, int row, int col); //행렬 출력 함수
int free_matrix(int** matrix, int row, int col);   //메모리 할당 해제 함수
int fill_data(int** matrix, int row, int col); 	   //행렬에 값을 넣는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);		//행렬의 합을 구하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);	//행렬의 차를 구하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);		//전치행렬을 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);		//행렬의 곱을 구하는 함수

int main()
{
    char command; //명령어를 담는 변수
    printf("[----- [이동현]  [2019038027] -----]\n");

	int row, col; //행과 열
	srand(time(NULL)); //time함수를 이용해 랜덤한 수 생성

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); //정수형으로 행과 열의 크기를 입력받는다
    int** matrix_a = create_matrix(row, col);	//create_matrix 함수로 matrix_a 생성
	int** matrix_b = create_matrix(row, col); 	//create_matrix 함수로 matrix_b 생성
	int** matrix_a_t = create_matrix(col, row); //create_matrix 함수로 matrix_a_t 생성

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} //matrix_a matrix_b가 NULL일 경우 -1반환

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
		scanf(" %c", &command); //명령어를 입력받는다

		switch(command) {
		case 'z': case 'Z': //명령어가 z나 Z인 경우
		    printf("Matrix Initialized\n");  
			fill_data(matrix_a, row, col); //fill_data 함수로 행렬a를 채운다
			fill_data(matrix_b, row, col); //fill_data 함수로 행렬b를 채운다
			break;
        case 'p': case 'P': //명령어가 p나 P인 경우
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); //print_matrix함수로 matrix_a 출력
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); //print_matrix함수로 matrix_b 출력
			break;
        case 'a': case 'A': //명령어가 a나 A인 경우
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); //addition_matrix 함수
			break;
        case 's': case 'S': //명령어가 s나 S인 경우
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //subtraction_matrix 함수로 matrix_a와 matrix_b의 차를 구한다
			break;
        case 't': case 'T': //명령어가 t나 T인 경우
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix함수로 matrix_a의 전치함수인 matrix_t를 구한다
            print_matrix(matrix_a_t, col, row); //print_matrix 함수로 결과 출력
			break;
        case 'm': case 'M': //명령어가 m이나 M인 경우
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); //transpose_matrix함수로 matrix_a의 전치함수인 matrix_t를 구한다
            multiply_matrix(matrix_a, matrix_a_t, row, col);  //multifly_matrix함수로 matrix_a와 matrix_a의 전치함수인 matrix_t의 곱을 구한다
			break;
        case 'q': case 'Q': //명령어가 q나 Q인 경우
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //free_matrix함수로 matrix_a_t의 메모리 할당 해제
            free_matrix(matrix_a, row, col);   //free_matrix함수로 matrix_a의 메모리 할당 해제
            free_matrix(matrix_b, row, col);   //free_matrix함수로 matrix_b의 메모리 할당 해제
			break;

		default: //위의 케이스가 아닌 다른값이 들어온다면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //concentrarion메시지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //명령어가 q나 Q일까지 반복

	return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { 					//row와 col이 음수나 0일 경우
		printf("Check the size of row and col!\n"); //오류메시지 출력 후
		return NULL; 								//NULL 반환
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); //int에 대한 이중포인터 matrix에 int타입사이즈 * row 만큼의 메모리 할당
	for (int r = 0; r < row; r++) {					  //크기가 row인 배열 생성
		matrix[r] = (int*)malloc(sizeof(int) * col);  //포인터배열 matrix[r]에 int타입사이즈 * col 만큼의 메모리 할당
	}

	/* Check post conditions */
	if (matrix == NULL) {						//matrix가 NULL이라면
		printf("Memory Allocation Failed.\n"); 	//메모리할당 실패 메시지 출력 후
		return NULL; 							//NULL 반환
	}

	return matrix; //matrix 반환
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)  
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row와 col이 음수나 0일경우
		printf("Check the size of row and col!\n"); //오류메시지 출력 후 
		return;										//NULL 반환
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) { //행렬을 출력한다
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	}
	printf("\n");
	/* Check post conditions */
	 if (matrix == NULL) {						//matrix가 NULL이라면
		printf("Memory Allocation Failed.\n");	//메모리 할당 실패 메시지 출력 후
		return;									//NULL 반환
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row와 col이 음수나 0이라면
		printf("Check the size of row and col!\n"); //오류메시지 출력 후 
		return -1;									//-1반환
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //행렬의 col에 해당하는 동적메모리 할당을 해제한다
		free(matrix[matrix_row]);
	}

	free(matrix); //matrix 동적 메모리 할당 해제
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col) //행렬을 가리키는 포인터 matrix와 row, col을 받아온다
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) { 					//row 와 col값으로 음수나 0이 넘어왔을 경우에는 
		printf("Check the size of row and col!\n"); //오류 메시지를 출력하고
		return -1; 									// -1을 반환한다
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20; //행렬을 0~19 사이의 랜덤한 값으로 채운다
	/* Check post conditions */
    if (matrix == NULL) { 					   //행렬이 NULL이라면
		printf("Memory Allocation Failed.\n"); //메모리 할당 실패 메시지를 출력한 후
		return -1;							   //-1 반환
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col); //create_matrix 함수를 사용해 matrix_sum행렬을 만든다
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row와 col이 음수나 0일 경우
		printf("Check the size of row and col!\n"); //오류 메시지 출력 후
		return -1;									//-1반환
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {  //matrix_sum에 matrix_a 와 matrix_b 를 더한값을 저장
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) { //matrix_a, matrix_b, matrix_sum 중 하나라도 NULL이라면 
		printf("Memory Allocation Failed.\n");						  //메모리 할당 실패 메시지 출력 후
		return -1;													  //-1 반환
	}

	print_matrix(matrix_sum, row, col); //print_matrix함수를 이용해 print_sum 행렬 출력
	free_matrix(matrix_sum, row, col);	//free_matrix함수를 이용해 matrix_sum에 할당된 메모리 해제
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col); //create_matrix 함수를 사용해 matrix_sub 행렬을 만든다
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row나 col이 음수나 0이라면
		printf("Check the size of row and col!\n");	//오류메시지 출력 후
		return -1;									//-1반환
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { //matrix_a에서 matrix_b를 A 후 matrix_sub에 값을 저장
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) { //martix_a, matrix_b, matrix_sub 중 하나라도 NULL이라면  
		printf("Memory Allocation Failed.\n");						  //메모리 할당 실패 메시지 출력 후 
		return -1;													  //-1 반환
	}
	print_matrix(matrix_sub, row, col); //print_matrix함수를 이용해 print_sum 행렬 출력
	free_matrix(matrix_sub, row, col);  //free_matrix 함수를 이용해 matrix_sub에 할당된 메모리 해제

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row나 col이 음수나 0이라면
		printf("Check the size of row and col!\n"); //오류메시지 출력 후
		return -1;									//-1반환
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) { 
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	 //matrix_t[matrix_row][matrix_col]에 matrix[matrix_col][matrix_row]을 넣어 matrix_a의 전치행렬 matrix_t을 만든다
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) {   //matrix나 matrix_t가 NULL일 경우
		printf("Memory Allocation Failed.\n"); //오류메시지 출력 후
		return -1; 							   //-1 반환
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row); //create_matrix함수를 이용해 matrix_a와 matrix_a의 전치행렬 matrix_t의 곱셈을 저장할 행렬을 만든다
	/* Check pre conditions */
	if (row <= 0 || col <= 0) {						//row나 col이 음수나 0이라면
		printf("Check the size of row and col!\n");	//오류메시지 출력 후
		return -1;									//-1반환
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0; 										    					         //곱셈값을 저장하는 변수 temp 초기화
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; //temp에 matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row] 을 저장
			matrix_axt[matrix_a_row][matrix_t_row] = temp; 										 //matrix_axt에 temp값 저장
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {	//matrix_t나 matrix_axt가 NULL일 경우
		printf("Memory Allocation Failed.\n");		//메모리 할당 실패 메시지 출력 후
		return -1;									//-1 반환
	}
	print_matrix(matrix_axt, row, row); //print_matrix 함수를 이용해 matrix_axt출력
	free_matrix(matrix_axt, row, col); //free_matrix 함수를 이용해 matrix_axt에 할당된 메모리 해제
	return 1;
}

