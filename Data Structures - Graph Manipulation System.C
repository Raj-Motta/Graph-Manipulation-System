#include <stdlib.h>    	//Standard Library file
#include <stdio.h> 		//Standard input output file
#include <conio.h>     	//Console IO file
#include <math.h>      	//Math functions file
#include <time.h>      	//Time functions file

#define INFINITE 9999				//Creating a constant value infinite to be returned when a null value is needed to be sent
#define MAX  3			     		//Creating a constant value MAX for array traversal

int vertexCount,edgeCount;			//2 integers to store the total number of vertexes and edges present in the graph
int vertexProb,edgeProb;			//2 integers to hold the probability of a new vertex/edge being created in the graph

int node[MAX*MAX];					//Integer array to store the vertex numbers that are being used in the array

int graph[MAX][MAX];				//2-dimensional integer array to store the graph
int edge[MAX*MAX][MAX*MAX];		    //2-dimensional integer array to store the edge of travelling from one point to another for all the points in the graph

//Function to create a new graph and edge table
void createGraph()//Non parameterized
{
	int i,j,k,l;	//For iteration through loops
	int x,y;		//For vertex calculation in edge array

	vertexCount=0;	//Setting the number of vertices in the graph as zero
	edgeCount=0;	//setting the number of edges in the graph as zero

	//Set of statements to create a randomization effect
	printf("\nClick on Any button to start the program: ");
	getch();
	srand(clock());
	srand(clock());

	vertexProb = rand()%100 + 1;	//Randomizing the probability of a vertex being created
	edgeProb = rand()%100 + 1;		//Randomizing the probability of an edge being created

	//Set of statements to randomly create/make a graph
	for(i=0;i<MAX;i++)	//for loop from 0 to max (exclusive)
	{
		for(j=0;j<MAX;j++)	//for loop from 0 to max (exclusive)
		{
			if(rand()%100 < vertexProb)		//using probability to check whether a new vertex will be made or not
			{
				graph[i][j] = rand()%100;
				node[vertexCount++]= (i*MAX + j);
			}
			else
			{	graph[i][j] = -1;	}
		}
	}

	//Set of statements to set all the values in array edge as -1
	for(i=0;i<(MAX*MAX);i++)	//for loop from 0 to max (exclusive)
	{
		for(j=0;j<MAX*MAX;j++)	//for loop from 0 to max (exclusive)
		{	edge[i][j] = -1;	}
	}

	for(i=0;i<MAX;i++)	//for loop from 0 to max (exclusive)
	{
		for(j=0;j<MAX;j++)	//for loop from 0 to max (exclusive)
		{
			if(graph[i][j] != -1)	//To check whether there is a value in the vertex or not
			{
				for(k=0;k<MAX;k++)	//for loop from 0 to max (exclusive)
				{
					for(l=0;l<MAX;l++)	//for loop from 0 to max (exclusive)
					{
						x=(i*MAX +j);
						y=(k*MAX +l);
						if(graph[k][l] != -1)					//To check whether there is a value in the vertex or not
						{
							if(edge[y][x] != -1)				//checking whether the vertex is already connected to the destination vertex to set the edge accordingly
							{	edge[x][y] = edge[y][x];	edgeCount++;	}
							else if(x == y)						//checking whether the vertex is a diagonal vertex, or whether the starting vertex and the destination vertex are the same vertex
							{	edge[x][y] = 0;	   edgeCount++;	   }
							else if((rand()%100+1) < edgeProb)	//using probability to check whether a new edge will be made or not
							{	edge[x][y] =  rand()%10 +1;	   edgeCount++;   }
							else
							{	edge[x][y] = -1;	}

							if(x!=y && edge[x][y] == 0)			//debug/double checking the diagonal nodes
							{ 	edge[x][y] = rand()%10 +1;	  }
						}
					}
				}
			}
		}
	}
}

//Function to return the number of nodes/vertexes
int getVertex()		//non parameterized
{	return vertexCount;   }

//Function to return the number of edges
int getEdge()		//non parameterized
{	return edgeCount;	  }

//Function to return the probability of a new vertex being made
int getVertprob()	//Non parameterized
{	return vertexProb;	  }

//Function to return the probability of a new edge being made
int getEdgeprob()	//Non parameterized
{	return edgeProb;	  }

//Function to return the list of vertexes that have been made
int* getVertexList()	//Non parameterized
{	return node;		  }

//Function to return the value stored in the nodes
int getVertexValue(int x)		//Takes in the vertex location
{
	int i = x/MAX;		//Calculating the row number in the graph
	int j = x%MAX;		//Calculating the column number in the graph

	if(graph[i][j] != -1)	//Checking whether the vertex exists.
	{	return graph[i][j];	}
	else
	{
		return INFINITE;
	}
}
	
//Function to return the edge to move between two given nodes
int getEdgeVal(int x, int y)//Takes in the starting vertex point and destination vertex point
{
	if(edge[x][y] != -1)	//checking whether there is an edge between the two nodes
	{
		return edge[x][y];	}
	else
	{
		return INFINITE;
	}
}

//function to return the smallest vertex in the graph
int getSmallestVertex()//Takes no arguments as input
{
	int i;
	int smallest;

	smallest = graph[node[0]/MAX][node[0]%MAX];//to initialize the value of smallest for further calculation

	//set of statements to find the smallest value throughout the graph
	for(i=1;i<vertexCount;i++)//for loop starting from 1 till vertex count
	{
		if(smallest > graph[node[i]/MAX][node[i]%MAX])
		{	smallest = graph[node[i]/MAX][node[i]%MAX];	  }
	}

	return smallest;
}

//Function to change/set the values stored in a certain vertex
void setVertex(int x, int num)//Takes a vertex and the number to be updated to
{
	int i = x/MAX;		//Calculating the row number in the graph
	int j = x%MAX;		//Calculating the column number in the graph
	int k,l;      		//Used to iterate loops
	int y;		  		//Used to store the destination vertex

	if(graph[i][j] == -1)	//Checking whether there is vertex at the vertex point X
	{
		for(k=0;k<MAX;k++)	//for from 0 to MAX
		{
			for(l=0;l<MAX;l++)	//for from 0 to MAX
			{
				y=(k*MAX +l);		//Calulation of destination vertex vertex
				if(graph[k][l] != -1)	//Checking where there is a vertex at Y
				{
					if(edge[y][x] != -1)				//checking whether the vertex is already connected to the destination vertex to set the edge accordingly
					{	edge[x][y] = edge[y][x];	}
					else if(x == y)						//checking whether the vertex is a diagonal vertex, or whether the starting vertex and the destination vertex are the same vertex
					{	edge[x][y] = 0;	   }
					else if((rand()%100+1) < edgeProb)	//using probability to check whether a new edge will be made or not
					{	edge[x][y] =  rand()%10 +1;   }
					else
					{	edge[x][y] = -1;	}

					if(x!=y && edge[x][y] == 0)			//Debug
					{ 	edge[x][y] = rand()%10 +1;	  }
				}
			}
		}
		node[vertexCount++] = x; //storing the new vertex number into the list
	}

	graph[i][j] = num;	//storing the new number as the vertex
}

//Function to update/create new edges
void setEdge(int x, int y, int num)		//Takes in the starting vertex point and destination vertex point, and the number to be updated to
{
	int i = x/MAX;		//Calculating the row number in the graph for vertex X
	int j = x%MAX;		//Calculating the column number in the graph for vertex X
	int k = y/MAX;		//Calculating the row number in the graph for vertex Y
	int l = y%MAX;		//Calculating the column number in the graph for vertex Y

	if(graph[i][j] == -1 || graph[k][l] == -1)		//To check whether both vertices are real or not
	{	return;   }
	else if(x == y)									//checking whether the vertex is a diagonal vertex, or whether the starting vertex and the destination vertex are the same vertex
	{	edge[y][x]=0;	  }

	edge[x][y]=num;
	edgeCount++;
}

//Function to check whether a vertex exists at a certain point in the graph or not
void isVertex(int x)
{
	int i = x/MAX;
	int j = x%MAX;

	if(graph[i][j] != -1)
	{	printf("\na vertex on point %d exists!", x);	}
	else
	{	printf("\na vertex on point %d does not exist!", x);	}
}

//Function to check whether there is a edge between 2 nodes
void isEdge(int x, int y)	//Takes in the starting vertex point and destination vertex point
{
	int i = x/MAX;		//Calculating the row number in the graph for vertex X
	int j = x%MAX;		//Calculating the column number in the graph for vertex X
	int k = y/MAX;		//Calculating the row number in the graph for vertex Y
	int l = y%MAX;		//Calculating the column number in the graph for vertex Y

	if(graph[i][j] != -1 && graph[k][l] != -1 && edge[x][y] != -1)	//checking whether the x and y vertex exists, AND that there is edge between them or not
	{	printf("\n%d and %d are adjacent...",graph[i][j],graph[k][l]);	}
	else if(graph[i][j] == -1)										//checking whether if vertex X exists or not
	{	printf("\nThere is no vertex such as %d",x);	}
	else if(graph[k][l] == -1)										//checking whether if vertex Y exists or not
	{	printf("\nThere is no vertex such as %d",y);	}
	else
	{	printf("\n%d and %d are not adjacent...",graph[i][j],graph[k][l]);	   }
}

//Function to display all the edges for that vertex
void allEdges(int x)	//takes in the vertex to be worked on
{
	int i = x/MAX;		//Calculating the row number in the graph for vertex X
	int j = x%MAX;		//Calculating the column number in the graph for vertex X
	int k;				//To iterate a row in the edge array

	if(graph[i][j] == -1)	//checking whether the vertex exists or not
	{	printf("The vertice does not exist");	}
	else
	{
		for(k=0;k<MAX*MAX;k++)	//loop from 0 to MAX*MAX
		{
			if(edge[x][k] > -1)		//checking whether the edge exists or not
			{
				printf("\n%d is adjacent to %d with a distance of %d",graph[k/MAX][k%MAX],graph[i][j],edge[x][k]);
			}
		}
	}
}

//Function to create a new edge
void MakeEdge(int x, int y)		//Taking a starting and ending vertex
{
	int i = x/MAX;		//Calculating the row number in the graph for vertex X
	int j = x%MAX;		//Calculating the column number in the graph for vertex X
	int k = y/MAX;		//Calculating the row number in the graph for vertex Y
	int l = y%MAX;		//Calculating the column number in the graph for vertex Y

	if(graph[i][j] == -1)		//checking if the vertex X exist or not
	{	printf("\nThere is no vertex such as %d",x);	}
	else if(graph[k][l] == -1)	//checking if the vertex Y exists or not
	{	printf("\nThere is no vertex such as %d",y);	}
	else if(edge[x][y] != -1)	//checking if an edge between the two nodes already exists
	{	printf("\n%d and %d are adjacent...",graph[i][j],graph[k][l]);	}
	else if(x == y)				//checking whether the vertex is a diagonal vertex, or whether the starting vertex and the destination vertex are the same vertex
	{	edge[x][y] = 0;	  }
	else if(edge[y][x] != -1)	//checking whether there is an edge between the other vertex and our starting vertex
	{	edge[x][y] = edge[y][x];	}
	else
	{
		edge[x][y] = rand()%10 +1;
		printf("\nEdge has been created!\nThe edge to travel from vertice %d to vertice %d\nIs :%d",x,y,edge[x][y]);
	}
}

//Function to remove an edge
void destroyEdge(int x, int y)	//Taking a starting and ending vertex
{
	int i = x/MAX;		//Calculating the row number in the graph for vertex X
	int j = x%MAX;		//Calculating the column number in the graph for vertex X
	int k = y/MAX;		//Calculating the row number in the graph for vertex Y
	int l = y%MAX;		//Calculating the column number in the graph for vertex Y

	if(edge[x][y] == -1)		//checking whether a vertex already exists or not
	{	printf("\n%d and %d are not adjacent...",graph[i][j],graph[k][l]);	   }
	else if(x==y)				//checking whether the vertex is a diagonal vertex, or whether the starting vertex and the destination vertex are the same vertex
	{	printf("\nThis connection can not be removed\n");}
	else
	{
		edge[x][y] = -1;
		printf("\nEdge has been removed from the graph");
	}
}

void displayGraph()
{
	int i,j;

	printf("\nDisplaying the graph that was generated: \n");
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(graph[i][j] == -1)
			{ printf("nil\t");	}
			else
			{	printf("%d\t",graph[i][j]);	}
		}
		printf("\n");
	}
	printf("\n\n");
}

void displayCost()
{
	int i,j;

	printf("\nDisplaying the edge of travelling from one point to another: \n");
	for(i=0;i<MAX*MAX;i++)
	{
		for(j=0;j<MAX*MAX;j++)
		{
			if(edge[i][j] == -1)
			{	printf("nil\t");	}
			else
			{	printf("%d\t",edge[i][j]);	}
		}
		printf("\n");
	}

	printf("\n\n");
}

void main()
{
	int i;
	int choice;
	int vertex,vertex1,vertex2,value;	//Variables to be used as arguments during functioncalling
	int *vertexPtr;

	createGraph();
	clrscr();
	do
	{
		printf("Please choose one of the following functions to be performed on the graph: ");

		//Displaying all the get functions that can be called
		printf("\n1. displays the number of nodes/vertices in the graph.");
		printf("\n2. displays the number of edges in the graph.");
		printf("\n3. displays the chance of a new vertex being made.");
		printf("\n4. displays the chance of a new edge being made.");
		printf("\n5. displays the list of the position of vertices in the graph.");
		printf("\n6. will provide the value stored in a certain position in the graph.");
		printf("\n7. will show the value of the edge between 2 vertices.");
		printf("\n8. will return the value of the smallest vertex present in the graph.");

		//Displaying all the search functions that can be called
		printf("\n9. checks if there is a vertex present on a certain point mentioned by you.");
		printf("\n10. checks if there is an edge between two vertices on the graph.");

		//Displaying all the manipulation functions that can be called
		printf("\n11. used to create or update a vertice in the graph.");
		printf("\n12. used to update an edge between two vertices on the graph.");
		printf("\n13. used to create a new edge between two vertices on the graph.");
		printf("\n14. used to destroy an edge between two vertices on the graph.");

		//Displaying all the display functions that can be called
		printf("\n15. used to display all the edges of a singular vertice on the graph.");
		printf("\n16. used to display the whole graph that had been created.");
		printf("\n17. used to display the edges between all the points in the graph.");

		printf("\n18. Exit...");
		printf("\nEnter your choice : ");

		scanf("%d",&choice);
		clrscr();
		switch(choice)
		{
			case 1:
				printf("The number of vertices in the graph is: %d",getVertex());
				break;

			case 2:
				printf("The number of edges in the graph is: %d",getEdge());
				break;

			case 3:
				printf("The probability of a new vertex being created is: %d",getVertprob());
				break;

			case 4:
				printf("The probability of a new edge being created is: %d",getEdgeprob());
				break;

			case 5:
				vertexPtr = getVertexList();

				for(i=0; i<getVertex();i++)
				{	printf("%d ",*vertexPtr++);   }
				break;

			case 6:
				printf("Which vertex do you want to check: ");
				scanf("%d",&vertex);

				if(getVertexValue(vertex) != INFINITE)
				{	printf("The value stored in vertex %d is: %d",vertex,getVertexValue(vertex));	  }
				else
				{	printf("This vertex does not exist...");	 }
				break;

			case 7:
				printf("Enter 2 nodes between which the edge exists: ");
				scanf("%d%d",&vertex1,&vertex2);

				printf("The value of the edge between the two nodes is: %d",getEdgeVal(vertex1, vertex2));
				break;

			case 8:
				printf("The smallest value in a vertex in the graph is: %d",getSmallestVertex());
				break;

			case 9:
				printf("Which vertex do you want to check: ");
				scanf("%d",&vertex);

				isVertex(vertex);
				break;

			case 10:
				printf("Which nodes do you want to check as adjacent: ");
				scanf("%d%d",&vertex1,&vertex2);

				isEdge(vertex1,vertex2);
				break;

			case 11:
				printf("Enter the vertex you want to create/update and enter the new value to be stored in it: ");
				scanf("%d%d",&vertex,&value);

				setVertex(vertex, value);
				break;

			case 12:
				printf("Enter the two nodes you want to update the edge between, and the value of the edge: ");
				scanf("%d%d%d",&vertex1,&vertex2,&value);

				setEdge(vertex1, vertex2, value);
				break;

			case 13:
				printf("Enter the two nodes you want to make the edge between: ");
				scanf("%d%d",&vertex1,&vertex2);

				MakeEdge(vertex1,vertex2);
				break;

			case 14:
				printf("Enter the two nodes you want to destroy the edge between: ");
				scanf("%d%d",&vertex1,&vertex2);

				destroyEdge(vertex1,vertex2);
				break;

			case 15:
				printf("what vertex do you want to check the edges for: ");
				scanf("%d",&vertex);

				allEdges(vertex);
				break;

			case 16:
				displayGraph();
				break;

			case 17:
				displayCost();
				break;

			case 18:
				exit(0);

			default:
				printf("Wrong input has been detected please enter the correct value next time...");

		}

		printf("\nPress a random character to continue: ");
		getch();
		clrscr();

	}while(1);
}