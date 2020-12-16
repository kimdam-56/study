#define _CRT_DECURE_NO_WARNINGS
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UART0.h"

FILE OUTPUT \
= FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
= FDEV_SETUP_STREAM(NULL, UART0_receive, _FDEV_SETUP_READ);

	


int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT;
		
	UART0_init();	
	
    int m, n;
    char boom = '*';
    int count = 0;

	printf("--------지뢰찾기---------\r\n");
	printf("가로, 세로 크기를 입력해주세요.\r\n");
	
    scanf("%d %d", &m, &n);
	
	printf("가로 : %d, 세로 : %d\r\n", m, n);
    
    char **matrix = malloc(sizeof(char *) * m);
    
    for(int i = 0; i < n; i++)
    {
	    matrix[i] = malloc(sizeof(char) * n);
		memset(matrix[i], 0, sizeof(char) * n);
    }
    // 지뢰 입력
    for(int i = 0; i < m; i++)
    {
		scanf("%s ", matrix[i]);
    }
	
    // 지뢰 보여주기
    for(int i = 0; i < m; i++)
    {
		if (i == 0)
		{
			printf("---지뢰찾기---\r\n");
		}
		    printf("%s ", matrix[i]);
	    printf("\r\n");
    }
    //-----------------지뢰찾기 시작---------------------------
	
    for(int i = 0; i < m; i++)
    {
	    for(int j = 0; j < n; j++)
	    {
			if ((i == 0) & (j == 0))
			{
				printf("~~~~~~지뢰찾는중~~~~~~~ \n\r");
			}
			count = 0;
			if (matrix[i][j] != boom) // 지뢰가 아니면 검사
			{
				for (int y = (i - 1); y <= (i + 1); y++)
				{
					for (int x = (j - 1); x <= (j + 1); x++)
					{
							if(y < 0 || x < 0 || y >= m || x >= n)
								continue;
							else if (matrix[y][x] == boom)
							{
								count++;
							}
					}
					matrix[i][j] = count + 48;
				}	
			}
			printf("matrix[%d][%d], count : %d \r\n", i, j, count);
			/*
			if ((i == 0) & (j == 0))
			{
				printf("~~~~~~지뢰찾는중~~~~~~~ \n\r");
			}
		    count = 0;
		    if(matrix[i][j] != boom)
		    {
			    if(matrix[i-1][j-1] == boom)//1
					count++;
			    if(matrix[i-1][j] == boom)//2
					count++;
			    if(matrix[i-1][j+1] == boom)//3
					count++;
			    if(matrix[i][j-1] == boom)//4
					count++;
			    if(matrix[i][j+1] == boom)//5
					count++;
			    if(matrix[i+1][j-1] == boom)//6
					count++;
			    if(matrix[i+1][j] == boom)//7
					count++;
			    if(matrix[i+1][j+1] == boom)//8
					count++;
			    matrix[i][j] = count + 48;
				
				printf("matrix[%d][%d], count : %d \r\n", i, j, count);
		    }
			*/
		    
	    }
    }
    //지뢰찾은거 보여주기
    for(int i = 0; i < m; i++)
    {
		if (i == 0)
		{
			printf("---지뢰위치---\r\n");
		}
		    printf("%s ", matrix[i]);
	    printf("\r\n");
    }
	
	for (int i = 0; i < m; i++)
	{
		free(matrix[i]);
	}
	
	free(matrix);
	
    /* Replace with your application code */
    while (1) 
    {
    }
	
	return 0;
}
