#include<stdio.h>
#include<stdlib.h>

#define MAX 30000 // ��ư}�C�`�q 
#define DIGITMAX 10 // �Ʀr���Φs���}�C�`�q 
#define RIGHTMAX 200 // �k�I�u�}�C�`�q 
#define LEFTMAX 1000 // ���I�u�禡�`�q 

void findPrime( int a[] ); // ���ƨ禡 
int primeCheck( int ); // ���k�I�u��Ƨ�M�禡 

void primeOut( int a[], int ); // ��X�禡 

void digitSplit( int a[], int digitDis[] ); // �N�U�ӽ�ƶi���Ƥ��Ψ禡 
int truncatablePrimeLeft( int digitDis[], int ); // ���I�u��ƨ禡 
int truncatablePrimeRight( int * , int , int * ); // �k�I�u��ƨ禡 

int left[LEFTMAX], right[RIGHTMAX]; // ���I�u�禡�}�C�B�k�I�u�禡�}�C 

int main(void)
{
	int a[MAX], digitDis[DIGITMAX]; // �`��ư}�C�B��Ƥ��ΰ}�C 
	
	printf("�B�⤤�еy��\n");
	
	printf("30000 �ӽ�Ƥ��M�䥪�k�I�u��ơG\n");
	findPrime(a);
	/*
	primeOut(a, 1);
	*/
	printf("\n");
	putchar('\n');
	
	digitSplit(a, digitDis);
	
	printf("�k�I�u��ơG\n");
	primeOut(right, 2);
	
	printf("\n");
	putchar('\n');
	
	printf("���I�u��ơG\n");
	primeOut(left, 3);
	
	printf("\n");
	puts("�O���Ш|�j��_�U�f��_���g\n");
	
	putchar('\n');
	
	system("pause");
	return 0;
}

int counter = 0; // �p���ƪ��p�ƾ� 

/* ��l��M��ƨ禡 */ 
void findPrime( int a[] )
{
	int flag = 1, j = 2; // flag to check if the number is prime, flag = 1 is prime 
	
	for( int i = 2 ; i <= 1e9 ; i++ ) // i mod j
	{
		for( int j = 2 ; j < i ; j++ )
		{
			flag = 1;
			
			if( i%j == 0 ) // i mod j = 0 means i isn;t a prime, so break
			{
				flag = 0;
				break;
			}
		}
		
		if( flag == 1 )
		{
			a[counter] = i;
			counter++;
		}
		
		if( counter == MAX ) // if counter is over the array index, findprime func stops 
			break;
	}
	
	return;
}

/* ��󥪥k�I�u��Ƥ��P�_�禡 */ 
int primeCheck( int a )
{
	int flag;
	
	for( int i = 2 ; i < a || a == 1 ; i++ )
	{
		flag = 1;
		
		if( a%i == 0 || a == 1 ) // 1 isn't prime
		{
			flag = 0;
			return 0;
		}
	}
	
	if( flag == 1 )
	{
		return a;
	}
}

/* ��ƿ�X */ 
void primeOut( int a[], int ins )
{
	int x;
	
	switch(ins) // check which prime will be output
	{
		case 1:
			x = counter;
				break;
				
		case 2:
			x = RIGHTMAX;
				break;
		
		case 3:
			x = LEFTMAX;
				break;
	}
	
	for( int i = 0 ; i < x ; i++ )
	{
		if( a[i] == 0 ) // if the a[i] = 0, it means there is no number inside the array, break
			break;
		
		printf("%d ", a[i]);
	}
	return;
}

/* �N�Ʀr�i��U�Ӧ�ƪ����Ψ禡 */ 

void digitSplit( int a[], int digitDis[] )
{
	int flag = 1, countDig = 0, origin, leftBool, rightBool; 
	int countRight = 0, countLeft = 0;
	
	for( int i = 0 ;  i < counter ; i++ )
	{
		origin = a[i]; // let the original number gives to origin
		
		do // try to split the number to each digit
		{
			flag = origin/10; // flag stores other digits
			digitDis[countDig] = origin-flag*10; // origin-flag can get one digit
			origin = flag; // origin will refresh to flag
			
			countDig++; // countDig is the counter of digits
			
		}while( flag > 0 ); // flag < 0 means all the digits is splitted 
		
		
		leftBool = truncatablePrimeLeft( digitDis, countDig ); //  �P�_�ثe�Ʀr�O�_�O���I�u��ơAleftBool = 0 �O 
		
		if( leftBool ) // �N���I�u����x�s��}�C 
		{
			left[countLeft] = a[i];
			countLeft++;
		}
		
		rightBool = truncatablePrimeRight( digitDis, countDig, &a[i] ); //  �P�_�ثe�Ʀr�O�_�O�k�I�u��ơArightBool �O 
		
		if( rightBool ) // �N�k�I�u����x�s��}�C  
		{
			right[countRight] = a[i];
			countRight++;
		}
		
		countDig = 0; // let countDig retrieve initiality 
	}
}

/*
���Ϋ᪺�Ʀr�x�s��}�C�|�ۤϹL�� 
��Ʀr�G233
�b�}�C���Ga[0] = 3, a[1] = 3, a[2] = 2
*/ 

/* ���I�u��ƨ禡 */ 
int truncatablePrimeLeft( int digitDis[] , int countDig )
{
	int times = 1, x = 0; // times �Ψӭp���� 1 ���B10��... 
	
	for( int i = 0 ; i < countDig-1 ; i++ ) // �Ψ��ˬd�O�_�����I�u�A�̫�@��Ƥ��έp�� countDig �ݭn -1 
	{
		x = x + digitDis[i]*times; // ���I�u�ѭӦ�ƶ}�l�ˬd�A�̦���Q���... 
		
		if( !primeCheck(x) || !digitDis[i] ) // ����ˬd���q�L�A�åB�Ʀr�� 0�A���O���I�u 
		{
			return 0;
		}
		
		times = times*10; 
	}
	
	return 1;
}

/* �k�I�u��ƨ禡 */ 
int truncatablePrimeRight( int *ptrSplitNum , int countDig, int *ptrOriNum )
{
	int i = 0, fx; // �ŦX f(k) = ( f(k-1)*a[k] )/10�A�Ҧ���ƺ⧹���Ʒ|�� 0 
	
	for( i ; i < countDig ; i++ )
	{
		if( i == 0 ) // ��l�� 
			fx = (*ptrOriNum - *(ptrSplitNum+i))/10;
			
		else if( i > 0 && i < countDig )
			fx = (fx - *(ptrSplitNum+i))/10;
		
		if( i != countDig-1 ) // �̫�@�줣�έp�� countDig �ݭn -1 
			if( !primeCheck(fx) || ! *(ptrSplitNum+i)) // ����ˬd���q�L�A�åB�Ʀr�� 0�A���O�k�I�u 
				return 0;
	}
	
	return 1;
}
