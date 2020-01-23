#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  TRUE   1
#define  FALSE  0
int DebugMode;

typedef struct mazeStruct
{
	char** arr;  /* allows for a maze of size 30x30 plus outer walls */
	int xsize, ysize;
	int xstart, ystart;
	int xend, yend;
} maze;

//Struct for node
 struct stack
{
	int xcor;
	int ycor;
	struct stack* next;
} ;

//initializes stack to be a NULL and returns
stack* init() {
	 stack* top = NULL;
	 return top;
}

//Pushes top element to front of linked list for fastest access
stack* push(stack* top, int xcor, int ycor) {
    if(DebugMode == TRUE){
        printf("Values being pushed, xcor: %d, ycor: %d\n", xcor, ycor);
    }
	stack* temp =(struct stack *) malloc(sizeof(stack));
	temp->xcor = xcor;
	temp->ycor = ycor;
	temp->next = top;
	return temp;

}

//Deletes node
stack* pop(stack* top) {
	stack* temp = top;
	top = top->next;
    if(DebugMode){
        printf("Values being popped. xcor: %d, ycor: %d\n", temp->xcor, temp->ycor);
    }
	free(temp);
	return top;
}

//returns top
stack* top(stack* top) {
	return top;
}

//clears entire stack
stack* clear(stack* top) {
	stack* temp;
	while (top != NULL) {
		temp = top;
		top = top->next;
		free(temp);
	}
	return top;
}

//returns true if empty false if not empty
bool is_empty(stack* top) {
	if (top == NULL) {
		return true;
	}
	else {
		return false;
	}
}

int main(int argc, char** argv)
{
	  DebugMode = FALSE; 
	    int i;
	    for ( i = 0 ; i < argc ; i++ ){
	      if ( strcmp (argv[i], "-d") == 0 ){
	         DebugMode = TRUE;   
	      }
	    }

	  maze m1;
	  int xpos, ypos;
	  int j;
	  FILE *src;

	  /* verify the proper number of command line arguments were given */
	  if(argc < 2) {
	     printf("Usage: %s <input file name>\n", argv[0]);
	     exit(-1);
	  }
	   /* Try to open the input file. */

	  for ( i = 1 ; i < argc ; i++ ) {
	    if ( strcmp (argv[i], "-d") != 0 ){
	       if ( ( src = fopen( argv[i], "r" )) == NULL ){
	             fprintf ( stderr, "Can't open input file: %s", argv[i] );
	             exit(-1);
	           }
	      }
	  }

	  /* read in the size, starting and ending positions in the maze */
	  if(fscanf (src, "%d %d", &m1.xsize, &m1.ysize) == EOF){
          fprintf(stderr," ");
          exit(-1);
      }
      while(m1.xsize == 0 || m1.ysize == 0){
          fprintf(stderr, "Size can not be 0\n");
          if(fscanf (src, "%d %d", &m1.xsize, &m1.ysize) == EOF){
          fprintf(stderr,"Not enough coordinates");
          exit(-1);
          }
      }
    
	  if(fscanf (src, "%d %d", &m1.xstart, &m1.ystart) == EOF){
          fprintf(stderr,"Not enough coordinates ");
          exit(-1);
      }
      while(m1.xstart > m1.xsize || m1.ystart > m1.ysize){
          fprintf(stderr, "Start out of range\n");
          if(fscanf (src, "%d %d", &m1.xstart, &m1.ystart) == EOF){
          fprintf(stderr,"Not enough coordinates ");
          exit(-1);
          }
      }
      //Set maze End
	  if(fscanf (src, "%d %d", &m1.xend, &m1.yend) == EOF){
          fprintf(stderr,"Not enough coordinates ");
          exit(-1);
      }
      while((m1.xend > m1.xsize || m1.yend > m1.ysize) || (m1.xend == m1.xstart && m1.yend == m1.ystart)){
          fprintf(stderr, "End out of range or blocking start\n");
          if(fscanf (src, "%d %d", &m1.xend, &m1.yend) == EOF){
          fprintf(stderr,"Not enough coordinates ");
          exit(-1);
          }
      }
	  /* print them out to verify the input */
	  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
	  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
	  printf ("end: %d, %d\n", m1.xend, m1.yend);

	  // allocate array  
	  m1.arr = (char **)malloc((m1.xsize+2) * sizeof(char*));
	  for(i = 0; i < m1.xsize+2; i++){
	      m1.arr[i] = (char *)malloc((m1.ysize+2) * sizeof(char));
	  }

	  /* initialize the maze to empty */
	  for (i = 0; i < m1.xsize+2; i++)
	     for (j = 0; j < m1.ysize+2; j++)
	       m1.arr[i][j] = '.';

	  /* mark the borders of the maze with *'s */
	  for (i=0; i < m1.xsize+2; i++)
	    {
	     m1.arr[i][0] = '*';
	     m1.arr[i][m1.ysize+1] = '*';
	    }
	  for (i=0; i < m1.ysize+2; i++)
	    {
	     m1.arr[0][i] = '*';
	     m1.arr[m1.xsize+1][i] = '*';
	    }

	  /* mark the starting and ending positions in the maze */
	  m1.arr[m1.xstart][m1.ystart] = 's';
	  m1.arr[m1.xend][m1.yend] = 'e';

	  /* mark the blocked positions in the maze with *'s */
	  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
	    {
          //checks various requirements outputs messages if debug is on
          if(xpos == m1.xstart && ypos == m1.ystart){
              fprintf(stderr, "blocking start\n");
              continue;
          }
          if(xpos == m1.xend && ypos == m1.yend){
              fprintf(stderr, "blocking end\n");
              continue;
          }
          if(xpos > m1.xsize || ypos > m1.ysize){
              fprintf(stderr, "out of range\n");
              continue;
          }
	     m1.arr[xpos][ypos] = '*';
	    }

	  /* print out the initial maze */
	  for (i = 0; i < m1.xsize+2; i++)
	    {
	     for (j = 0; j < m1.ysize+2; j++)
	       printf ("%c", m1.arr[i][j]);
	     printf("\n");
	    }
    
        char copyArr[m1.xsize+2][m1.ysize+2];
        //Copies for debugging purposes
        if(DebugMode == TRUE){
            for(i = 0; i < m1.xsize + 2; ++i){
                for(j = 0; j < m1.ysize + 2; ++j){
                    copyArr[i][j] = m1.arr[i][j];
                }
            }
        }

    
    //Begin searching for end
    stack* coordList = init();
    coordList = push(coordList, m1.xstart, m1.ystart); //pushes in start
    m1.arr[m1.xstart][m1.ystart] = 'v'; //set start to visited
    m1.arr[m1.xend][m1.yend] = '.'; //sets end to unvisited
    while(!is_empty(coordList)){
        //prints out maze progress if debug mode is true
        if(DebugMode == TRUE){
          for (i = 0; i < m1.xsize+2; i++)
	      {
	       for (j = 0; j < m1.ysize+2; j++)
	         printf ("%c", m1.arr[i][j]);
	       printf("\n");
	      }
        }
        int x = top(coordList)->xcor;
        int y = top(coordList)->ycor;
        //breaks out of while loop if end is found
        if(x == m1.xend && y == m1.yend){
            break;
        }
        //checks different neightbors
        else{
            if(m1.arr[x+1][y] == '.'){
                coordList = push(coordList, x+1, y);
                m1.arr[x+1][y] = 'v';
                continue;
            }
            if(m1.arr[x-1][y] == '.'){
                coordList = push(coordList, x-1, y);
                m1.arr[x-1][y] = 'v';
                continue;
            }
            if(m1.arr[x][y-1] == '.'){
                coordList = push(coordList, x, y-1);
                m1.arr[x][y-1] = 'v';
                continue;
            }
            if(m1.arr[x][y+1] == '.'){
                coordList = push(coordList, x, y+1);
                m1.arr[x][y+1] = 'v';
                continue;
            }
            //pops top if no neightbors are unvisited
            coordList = pop(coordList);
        }
    }
    //if stack is empty, there is no solution
    if(is_empty(coordList)){
        printf("No solution\n");
    }else{
        //add to new stack to reverse coordinates
        stack* reverseStack = init();
        while(!is_empty(coordList)){
            reverseStack = push(reverseStack, top(coordList)->xcor, top(coordList)->ycor);
            coordList = pop(coordList);
        }
        while(!is_empty(reverseStack)){
            //prints out and pops top element
            printf("xcor: %d, ycor: %d\n", top(reverseStack)->xcor, top(reverseStack)->ycor);
            //Prints out path if debug mode is on
            if(DebugMode == TRUE){
                copyArr[top(reverseStack)->xcor][top(reverseStack)->ycor] = 'v';
                for (i = 0; i < m1.xsize+2; i++)
	            {
	             for (j = 0; j < m1.ysize+2; j++)
	               printf ("%c", copyArr[i][j]);
	             printf("\n");
	            }
            }
            reverseStack = pop(reverseStack);
        }
        //Frees all mallocs and closes file
        clear(reverseStack);
        clear(coordList);
    }
    //Frees all mallocs and closes file
    for(i = 0; i < m1.xsize + 2; ++i){
        free(m1.arr[i]);
    }
    free(m1.arr);
    fclose(src);
} 