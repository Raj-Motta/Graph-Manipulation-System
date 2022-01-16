#include <iostream.h>  	//Stream IO file
#include <stdlib.h>    	//Standard Library file
#include <conio.h>     	//Console IO file
#include <math.h>      	//Math functions file
#include <time.h>      	//Time functions file

const int INFINITE=9999;	//Creating a constant value infinite to be returned when a null value is needed to be sent
const int MAX = 3;			//Creating a constant value MAX to set the size of arrays

class Graph 	//Class graph to encapsulate and bind all the graph related functions
{
private:	//Mainly variable declaration
	int vertexCount,edgeCount;		//2 integers to store the total number of vertexes and edges present in the graph
	int vertexProb,edgeProb;		//2 integers to hold the probability of a new node/edge being created in the graph
	
	int node[MAX*MAX];				//Integer array to store the node numbers that are being used in the array				
	
	int graph[MAX][MAX];			//2-dimensional integer array to store the graph					
	int cost[MAX*MAX][MAX*MAX];		//2-dimensional integer array to store the cost of travelling from one point to another for all the points in the graph

public:
	//Constructor for the class graph... used to create the graph, and the cost array
	Graph()//Non parameterized
	{
		int i,j,k,l;	//For iteration through loops
		int x,y;		//For node calculation in cost array

		vertexCount=0;	//Setting the number of vertices in the graph as zero
		edgeCount=0;	//setting the number of edges in the graph as zero

		//Set of statements to create a randomization effect
		cout << "Press any key to start the program: ";
		getch();
		srand(clock());
		srand(clock());

		vertexProb = rand()%100 + 1;	//Randomizing the probability of a node being created
		edgeProb = rand()%100 + 1;		//Randomizing the probability of an edge being created

		//Set of statements to randomly create/make a graph
		for(i=0;i<MAX;i++)	//for loop from 0 to max (exclusive)
		{
			for(j=0;j<MAX;j++)	//for loop from 0 to max (exclusive)
			{
				if(rand()%100 < vertexProb)		//using probability to check whether a new node will be made or not
				{
					graph[i][j] = rand()%100;
					node[vertexCount++]= (i*MAX + j);
				}
				else
				{	graph[i][j] = -1;	}
			}
		}

		//Set of statements to set all the values in array cost as -1
		for(i=0;i<MAX*MAX;i++)	//for loop from 0 to max (exclusive)
		{
			for(j=0;j<MAX*MAX;j++)	//for loop from 0 to max (exclusive)
			{	cost[i][j] = -1;	}
		}

		for(i=0;i<MAX;i++)	//for loop from 0 to max (exclusive)
		{
		  	for(j=0;j<MAX;j++)	//for loop from 0 to max (exclusive)
		  	{
				if(graph[i][j] != -1)	//To check whether there is a value in the node or not
				{
			  		for(k=0;k<MAX;k++)	//for loop from 0 to max (exclusive)
			  		{
						for(l=0;l<MAX;l++)	//for loop from 0 to max (exclusive)
						{
				  			x=(i*MAX +j);
				  			y=(k*MAX +l);
				  			if(graph[k][l] != -1)					//To check whether there is a value in the node or not
				  			{
								if(cost[y][x] != -1)				//checking whether the node is already connected to the destination node to set the cost accordingly
								{	cost[x][y] = cost[y][x];	edgeCount++;	}
								else if(x == y)						//checking whether the node is a diagonal node, or whether the starting node and the destination node are the same node
								{	cost[x][y] = 0;	   edgeCount++;	   }
								else if((rand()%100+1) < edgeProb)	//using probability to check whether a new edge will be made or not
								{	cost[x][y] =  rand()%10 +1;	   edgeCount++;   }
								else
								{	cost[x][y] = -1;	}

								if(x!=y && cost[x][y] == 0)			//debug/double checking the diagonal nodes
								{ 	cost[x][y] = rand()%10 +1;	  }
				  			}
						}
			  		}
				}
		  	}
		}
	}

	//Function to return the number of nodes/vertexes
	inline int getVertex()		//non parameterized
	{	return vertexCount;   }

	//Function to return the number of edges
	inline int getEdge()		//non parameterized
	{	return edgeCount;	  }

	//Function to return the probability of a new vertex being made
	inline int getVertprob()	//Non parameterized
	{	return vertexProb;	  }

	//Function to return the probability of a new edge being made
	inline int getEdgeprob()	//Non parameterized
	{	return edgeProb;	  }

	//Function to return the list of nodes that have been made
	inline int* getNodeList()	//Non parameterized
	{	return node;		  }

	//Function to return the value stored in the nodes
	int getNodeVal(int x)		//Takes in the node number
	{
		int i = x/MAX;		//Calculating the row number in the graph
		int j = x%MAX;		//Calculating the column number in the graph

		if(graph[i][j] != -1)	//Checking whether the node exists.
		{	return graph[i][j];	}
		else
		{
			return INFINITE;
		}
	}

	//Function to return the cost to move between two given nodes
	int getEdgeVal(int x, int y)//Takes in the starting node point and destination node point
	{
		int i = x/MAX;		//Calculating the row number in the graph for node X
		int j = x%MAX;		//Calculating the column number in the graph for node X
		int k = y/MAX;		//Calculating the row number in the graph for node Y
		int l = y%MAX;		//Calculating the column number in the graph for node Y

		if(cost[x][y] != -1)	//checking whether there is an edge between the two nodes
		{
			//cout << "\nReturning "<< cost[x][y];
			return cost[x][y];	}
		else
		{
			//cout << "\nThe edge does not exist...";
			return INFINITE;
		}
	}

	//function to return the smallest vertex in the graph
	int getSmallestNode()//Takes no arguments as input
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

	//Function to change/set the values stored in nodes
	void setNode(int x, int num)//Takes a node and the number to be updated to
	{
		int i = x/MAX;		//Calculating the row number in the graph
		int j = x%MAX;		//Calculating the column number in the graph
		int k,l;      		//Used to iterate loops
		int y;		  		//Used to store the destination node

		if(graph[i][j] == -1)	//Checking whether there is node at the node X
		{
			for(k=0;k<MAX;k++)	//for from 0 to MAX
			{
				for(l=0;l<MAX;l++)	//for from 0 to MAX
				{
					y=(k*MAX +l);		//Calulation of destination node
					if(graph[k][l] != -1)	//Checking where there is a node at Y
					{
						if(cost[y][x] != -1)				//checking whether the node is already connected to the destination node to set the cost accordingly
						{	cost[x][y] = cost[y][x];	}
						else if(x == y)						//checking whether the node is a diagonal node, or whether the starting node and the destination node are the same node
						{	cost[x][y] = 0;	   }
						else if((rand()%100+1) < edgeProb)	//using probability to check whether a new edge will be made or not
						{	cost[x][y] =  rand()%10 +1;   }
						else
						{	cost[x][y] = -1;	}

						if(x!=y && cost[x][y] == 0)			//Debug
						{ 	cost[x][y] = rand()%10 +1;	  }
					}
				}
			}
			node[vertexCount++] = x; //storing the new node number into the list
		}

		graph[i][j] = num;	//storing the new number as the node
	}

	//Function to update/create new edges
	void setEdge(int x, int y, int num)		//Takes in the starting node point and destination node point, and the number to be updated to
	{
		int i = x/MAX;		//Calculating the row number in the graph for node X
		int j = x%MAX;		//Calculating the column number in the graph for node X
		int k = y/MAX;		//Calculating the row number in the graph for node Y
		int l = y%MAX;		//Calculating the column number in the graph for node Y

		if(graph[i][j] == -1 || graph[k][l] == -1)		//To check whether both nodes are real or not
		{	return;   }
		else if(x == y)									//checking whether the node is a diagonal node, or whether the starting node and the destination node are the same node
		{	cost[y][x]=num;	  }

		cost[x][y]=num;
		edgeCount++;
	}

	void isNode(int x)
	{
		int i = x/MAX;
		int j = x%MAX;

		if(graph[i][j] != -1)
		{	cout << "\na vertex on point "<<x<<" exists!";	}
		else
		{	cout << "\na vertex on point "<<x<<" does not exist...";	}
	}

	//Function to check whether there is a edge between 2 nodes
	void isAdjacent(int x, int y)	//Takes in the starting node point and destination node point
	{
		int i = x/MAX;		//Calculating the row number in the graph for node X
		int j = x%MAX;		//Calculating the column number in the graph for node X
		int k = y/MAX;		//Calculating the row number in the graph for node Y
		int l = y%MAX;		//Calculating the column number in the graph for node Y

		if(graph[i][j] != -1 && graph[k][l] != -1 && cost[x][y] != -1)	//checking whether the x and y node exists, AND that there is edge between them or not
		{	cout << "\n"<<graph[i][j]<<" and "<<graph[k][l]<<" are adjacent...";	}
		else if(graph[i][j] == -1)										//checking whether if node X exists or not
		{	cout << "\nThere is no node such as "<<x;	}
		else if(graph[k][l] == -1)										//checking whether if node Y exists or not
		{	cout << "\nThere is no node such as "<<y;	}
		else
		{	cout << "\n"<<graph[i][j]<<" and "<<graph[k][l]<<" are not adjacent...";	   }
	}

	//Function to display all the edges for that node
	void allAdjacent(int x)	//takes in the node to be worked on
	{
		int i = x/MAX;		//Calculating the row number in the graph for node X
		int j = x%MAX;		//Calculating the column number in the graph for node X
		int k;				//To iterate a row in the cost array

		if(graph[i][j] == -1)	//checking whether the node exists or not
		{	cout << "The vertice does not exist";	}
		else
		{
			for(k=0;k<MAX*MAX;k++)	//loop from 0 to MAX*MAX
			{
				if(cost[x][k] > -1)		//checking whether the edge exists or not
				{
					cout << graph[k/MAX][k%MAX]<<" is adjacent to "<<graph[i][j]<<" with a distance "<<cost[x][k]<<"\n";
				}
			}
		}
	}

	//Function to create a new edge
	void makeAdjacent(int x, int y)		//Taking a starting and ending node
	{
		int i = x/MAX;		//Calculating the row number in the graph for node X
		int j = x%MAX;		//Calculating the column number in the graph for node X
		int k = y/MAX;		//Calculating the row number in the graph for node Y
		int l = y%MAX;		//Calculating the column number in the graph for node Y

		if(graph[i][j] == -1)		//checking if the node X exist or not
		{	cout << "\nThere is no node such as "<<x;	}
		else if(graph[k][l] == -1)	//checking if the node Y exists or not
		{	cout << "\nThere is no node such as "<<y;	}
		else if(cost[x][y] != -1)	//checking if an edge between the two nodes already exists
		{	cout << "\n"<<graph[i][j]<<" and "<<graph[k][l]<<" are already adjacent...";	}
		else if(x == y)				//checking whether the node is a diagonal node, or whether the starting node and the destination node are the same node
		{	cost[x][y] = 0;	  }
		else if(cost[y][x] != -1)	//checking whether there is an edge between the other node and our starting node
		{	cost[x][y] = cost[y][x];	}
		else
		{
			cost[x][y] = rand()%10 +1;
			cout << "\nEdge has been created!\nThe cost to travel from vertice "<<x<<" to vertice "<<y<<"\nIs :"<<cost[x][y]<<"\n";
		}
	}

	//Function to remove an edge
	void destroyAdjacent(int x, int y)	//Taking a starting and ending node
	{
		if(cost[x][y] == -1)		//checking whether a node already exists or not
		{	cout << "\n"<<graph[x/MAX][x%MAX]<<" and "<<graph[y/MAX][y%MAX]<<" are not adjacent anyways...";	   }
		else if(x==y)				//checking whether the node is a diagonal node, or whether the starting node and the destination node are the same node
		{	cout << "\nThis connection can not be removed\n";}
		else
		{
			cost[x][y] = -1;
			cout << "\nEdge has been removed from the graph";
		}
	}

	void displayGraph()
	{
		int i,j;

		cout << "\nDisplaying the graph that was generated: \n";
		for(i=0;i<MAX;i++)
		{
			for(j=0;j<MAX;j++)
			{
				if(graph[i][j] == -1)
				{ cout <<"nil\t";	}
				else
				{	cout<<graph[i][j]<<"\t";	}
			}
			cout<<endl;
		}
		cout << "\n\n";
	}

	void displayCost()
	{
		int i,j;

		cout << "\nDisplaying the cost of travelling from one point to another: \n";
		for(i=0;i<MAX*MAX;i++)
		{
			cout << i<<"| ";
			for(j=0;j<MAX*MAX;j++)
			{
				if(cost[i][j] == -1)
				{	cout << "nil\t";	}
				else
				{	cout<<cost[i][j]<<"\t";	}
			}
			cout<<endl;
		}

		cout << "\n\n";
	}
};

void main()
{
	clrscr();
	int choice;
	Graph G1;

	do
	{
		cout << "Please choose one of the following functions to be performed on the graph: ";

		//Displaying all the get functions that can be called
		cout << "\n1. getVertex... this function displays the number of nodes/vertices in the graph.";
		cout << "\n2. getEdge... this function displays the number of edges in the graph.";
		cout << "\n3. getVertprob... this function displays the chance of a new vertex being made.";
		cout << "\n4. getEdgeprob... this function displays the chance of a new edge being made.";
		cout << "\n5. getNodeList... this function displays the list of the position of vertices in the graph.";
		cout << "\n6. getNodeVal... this function will provide the value stored in a certain position in the graph.";
		cout << "\n7. getEdgeVal... this function will show the value of the edge between 2 vertices.";
		cout << "\n8. getSmallestNode... this function will return the value of the smallest vertex present in the graph.";

		//Displaying all the search functions that can be called
		cout << "\n9. isNode... this function checks if there is a node present on a certain point mentioned by you.";
		cout << "\n10. isAdjacent... this function checks if there is an edge between two vertices on the graph.";

		//Displaying all the manipulation functions that can be called
		cout << "11. setNode... this function is used to create or update a vertice in the graph.";
		cout << "12. setAdjacent... this function is used to update an edge between two vertices on the graph.";
		cout << "13. makeAdjacent... this function is used to create a new edge between two vertices on the graph.";
		cout << "14. destroyAdjacent... this function is used to destroy an edge between two vertices on the graph.";

		//Displaying all the display functions that can be called
		cout << "15. allAdjacent... this function is used to display all the edges of a singular vertice on the graph.";
		cout << "16. display graph... this function is used to display the whole graph that had been created.";
		cout << "17. display cost... this function is used to display the edges between all the points in the graph.";

		cout << "18. Exit...";

		cin >> choice;

		switch(choice)
		{
			case 1:
				cout << "The number of vertices in the graph is: "<<G1.getVertex();
				break;

			case 2:
				cout << "The number of edges in the graph is: "<<G1.getEdge();
				break;

			case 3:
				cout << "The probability of a new vertex being created is: "<<G1.getVertprob();
				break;

			case 4:
				cout << "The probability of a new edge being created is: "<<G1.getEdgeprob();
				break;

			case 5:
				int *vertexPtr;
				vertexPtr = G1.getNodeList();

				for(int i=0; i<G1.getVertex();i++)
				{	cout << *vertexPtr++;   }
				break;

			case 6:
				int index;
				cout << "Which node do you want to check: ";
				cin >> index;

				if(G1.getNodeVal(index) != INFINITE)
				{	cout << "The value stored in index "<<index<<" is: "<<G1.getNodeVal(index);	  }
				else
				{	cout << "This node does not exist...";	 }
				break;

			case 7:
				int index1, index2;
				cout << "Enter 2 nodes between which the edge exists: ";
				cin >> index1>>index2;

				cout << "The value of the edge between the two nodes is: "<<G1.getEdgeVal(index1, index2);
				break;

			case 8:
				cout << "The smallest value in a node in the graph is: "<<G1.getSmallestNode();
				break;

			case 9:
				int node;

				cout << "Which node do you want to check: ";
				cin >> node;

				G1.isNode(node);
			 	break;

			case 10:
				int node1, node2;

				cout << "Which nodes do you want to check as adjacent: ";
				cin >> node1>>node2;

				G1.isAdjacent(node1,node2);
				break;

			case 11:
				int vertex, value;

				cout << "Enter the node you want to create/update and enter the new value to be stored in it: ";
				cin >> vertex>>value;

				G1.setNode(vertex, value);
				break;

			case 12:
				int vertex1, vertex2, data;

				cout << "Enter the two nodes you want to update the edge between, and the value of the edge";
				cin >> vertex1>>vertex2>>data;

				G1.setEdge(vertex1, vertex2, data);
				break;

			case 13:
				int point1, point2;

				cout << "Enter the two nodes you want to make the edge between";
				cin >> point1>>point2;

				G1.makeAdjacent(point1, point2);
				break;

			case 14:
				int set1, set2;

				cout << "Enter the two nodes you want to destroy the edge between";
				cin >> set1>>set2;

				G1.makeAdjacent(set1, set2);
				break;

			case 15:
				int point;

				cout << "what node do you want to check the edges for: ";
				cin >> point;

				G1.allAdjacent(point);
				break;

			case 16:
				G1.displayGraph();
				break;

			case 17:
				G1.displayCost();
				break;

			case 18:
				exit(0);

			default:
				cout << "Wrong input has been detected please enter the correct value next time...";

		}

		cout << "Press a random character to continue: ";
		getch();

	}while(1);
}