/*
Devesh Bhogre
PB47-B3
A* algorithm
*/

#include<iostream>
#include <cstring>
using namespace std;

class Node      //node class is a datastructure that is maintained to store the information about our node
{
	//private variables are assigned so as to follow the oops concept
	private:
		int data[3][3];
		int level;
		int cost;
		int empt_pos1;
		int empt_pos2;
		Node *parent;
		friend class Graph;   //As the variables are private to use this variables in another class friend class is declared
		friend class Priorityqueue;
};
class Priorityqueue //this is maintained to store the node in priority wise manner
{
	private:
		Node *queue[100];
		int index;
	public:
		Priorityqueue()
		{
			index=0;
		}
		void insert(Node* data);
		Node* atTop()
		{
			Node *temp=queue[1];
			return temp;

		}
		void pop();
		Node* atIndex(int index)
		{
			return queue[index];
		}
		int isEmpty()
		{
			if(index==0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}


};
void Priorityqueue::insert(Node* data)
{
	index++;
	int j=index;
	if(j==1)
	{
		queue[index]=data;
	}
	queue[index]=data;
	while(j>1)
	{
		if(queue[j/2]->cost>queue[j]->cost)
		{
			Node *temp=queue[j/2];
			queue[j/2]=queue[j];
			queue[j]=temp;
			j=j/2;
		}
		else
		{
			break;
		}


	}

}
void Priorityqueue::pop()
{
	queue[1]=queue[index];
	index--;
	int j=1;
	while(j<index)
	{
		int minimum=j;
		if(queue[2*j]->cost>queue[2*j+1]->cost)
		{
			minimum=2*j+1;
			if(queue[j]->cost>queue[minimum]->cost)
			{
				Node *temp=queue[j];
				queue[j]=queue[minimum];
				queue[minimum]=temp;

			}
			j=minimum;
		}
		else
		{
			minimum=2*j;
			if(queue[j]->cost>queue[minimum]->cost)
			{
				Node *temp=queue[j];
				queue[j]=queue[minimum];
				queue[minimum]=temp;

			}
			j=minimum;

		}
		if(minimum==j)
		{
			break;
		}
	}

}

class Graph
{
	private:
	 int final[3][3];
	 Node* root;
	public:
	Graph()
	{
		root=new Node();
		root->cost=0;
		root->parent=NULL;
		root->level=1;
		cout<<"Enter the initial matrix:\n";
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				cin>>root->data[i][j];
				if(root->data[i][j]==-1)
				{
					root->empt_pos1=i;
					root->empt_pos2=j;
				}
			}
		}
		cout<<"enter the output required:\n";
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				cin>>final[i][j];
			}
		}
	}
	void evaluate();
	int isAvailable();
	int calculateHCost(Node *data);
	int isSafe(int x,int y);
	void swap(int x,int y,int x1,int y1,Node*data);
	void showSolution(Node *data);



};
void Graph::showSolution(Node* data)
{
	Node *temp;
	temp=data;
	while(temp!=NULL)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				cout<<temp->data[i][j]<<" ";
			}
			cout<<"\n";
		}
		cout<<"\n";
		temp=temp->parent;

	}


}
void Graph::swap(int row ,int column,int new_row,int new_column,Node* data)
{
	int temp=data->data[new_row+row][new_column+column];
	data->data[new_row+row][new_column+column]=data->data[new_row][new_column];
	data->data[new_row][new_column]=temp;



}
int row[]={0,0,-1,+1};
int column[]={-1,+1,0,0};
int Graph::isSafe(int x,int y)
{
	if(x>=0 && x<=2 && y>=0 && y<=2)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}
int Graph::calculateHCost(Node *data)
{
	int count=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(data->data[i][j] != final[i][j])
			{
				count++;
			}

		}
	}
	return count;


}
void Graph::evaluate()
{
	Priorityqueue p1;
	root->cost=calculateHCost(root)+root->level;
	p1.insert(root);
	while(!p1.isEmpty())
	{
		Node * temp=p1.atTop();
		p1.pop();
		if(temp->cost-temp->level==0)
		{
			cout<<"solution found\n";
			showSolution(temp);
			break;
		}
		for(int i=0;i<4;i++)
		{
			if(isSafe(temp->empt_pos1+row[i],temp->empt_pos2+column[i]))
			{
				Node *curr=new Node();
				memcpy(curr->data,temp->data, sizeof curr->data);
				curr->level=temp->level+1;
				swap(row[i],column[i],temp->empt_pos1,temp->empt_pos2,curr);
				curr->empt_pos1=temp->empt_pos1+row[i];
				curr->empt_pos2=temp->empt_pos2+column[i];
				curr->cost=calculateHCost(curr)+curr->level;
				curr->parent=temp;
				p1.insert(curr);

			}
		}
	}



}

int main()
{
	Graph g1;
	g1.evaluate();
}

/*
OUTPUT:
Enter the initial matrix:
1 2 3
5 6 -1
7 8 4
enter the output required:
1 2 3
5 8 6
-1 7 4
solution found
1 2 3 
5 8 6 
-1 7 4 

1 2 3 
5 8 6 
7 -1 4 

1 2 3 
5 -1 6 
7 8 4 

1 2 3 
5 6 -1 
7 8 4 
*/
