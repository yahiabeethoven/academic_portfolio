 //============================================================================
// Name         : lab12.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-11-2020
// Date Modified: 25-11-2020 
// Description  : AVL Tree
// Copyright © 2020 Khalid Mengal. All rights reserved.
//============================================================================
#include<iostream>
#include<cstdlib>
#include<iomanip>

using namespace std;

class Node
{
	private:
		int key;
		Node* left;
		Node* right;
	public:
		Node(int key);
		~Node();
		int getKey() { return this->key;}
		friend class AVL;
};

Node::Node(int key)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
}
Node::~Node()
{
	cout<<"deleted.."<<this->key<<endl;
	cout<<"----------------------------------"<<endl;
}
//=============================================================================
class AVL
{
	private:
		Node *root;
	public:
		AVL();									//constructor
		~AVL();									//destructor
		Node* getRoot();						//returns the root of the Tree
		Node* insert(Node* ptr,int key);		//Insert key into tree/subtree with root ptr
		void printInorder(Node* ptr);			//Traverse (inroder) and print the key of a tree/subtree with root ptr
		int height(Node *ptr);				    //Find the height(MaxDepth) of a tree/subtree with root ptr
		Node* findMin(Node *ptr);				//Find and return the Node with minimum key value from a tree/subtree with root ptr
		Node* findMax(Node *ptr);				//Find and return the Node with Max key value from a tree/subtree with root ptr		
		Node* findKey(Node *ptr,int key);		//Find and returns the node with key
		Node* remove(Node *ptr,int key);		//Remove a node with key from the tree/subtree with root
		Node* rotateLeft(Node *z);
		Node* rotateRight(Node *z);
		void printTree();						//Print 2D Tree
	public:	//helper methods
		void insert_helper(int key);			//Helper method for insert method
		void remove_helper(int key);			//Helper method for remove method
	private:
		void printTreeHelper(int *A,bool *B, Node *ptr, int n); //Helper method for PrintTree()
		int balanceFactor(Node *ptr);
		Node* rebalance(Node *ptr);    			// rebalance a node
};

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"display            :Display the AVL Tree"<<endl
		<<"insert <key>       :Insert a new node in AVL"<<endl
		<<"remove <key>       :Remove the node from AVL "<<endl
		<<"height             :Find the hieght of the Tree"<<endl
		<<"min                :Find the node with minimum key in AVL"<<endl
		<<"max                :Find the node with maximum key in AVL"<<endl
		<<"find <key>         :Find a node with a given key value in AVL"<<endl
		<<"inorder            :Print the AVL in Inorder"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( AVL &myAVL)
{
	myAVL.insert_helper(10);
	myAVL.insert_helper(5);
	myAVL.insert_helper(4);
	myAVL.insert_helper(7);
	myAVL.insert_helper(13);
	myAVL.insert_helper(15);
	myAVL.insert_helper(12);
	myAVL.insert_helper(14);
	myAVL.printTree();
}
//================================================================
bool check(string key) {								//function I added to ensure the input can be added to tree to prevent the program from crashing
	for (int i = 0; i < key.length(); i++) {
		if (isdigit(key[i]) == false)
      		return false;
	}      
	return true;
}
//==========================================================
int main(void)
{
	AVL myAVL;
	listCommands();
	string user_input;
	string command;
	string key;

	while(true)
	{
		cout<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		key = user_input.substr(user_input.find(" ")+1);
		
		Node* root = myAVL.getRoot();	//get the root of the tree
		cout<<"----------------------------------"<<endl;
		if( user_input =="display")	myAVL.printTree();
		else if( command =="insert" or command=="i")	
			{ 
				if (check(key)) {
					myAVL.insert_helper(stoi(key)); myAVL.printTree();
				}
				else {
					cout<< "Please type a valid input..."<<endl;
				}
				
			} 
		else if( command =="remove" or command=="r")	
			{ 
				if (check(key)) {
					myAVL.remove_helper(stoi(key)); myAVL.printTree();
				}
				else {
					cout<< "Please type a valid input..."<<endl;
				}		
			}
		else if( command =="height")	cout<<"Height = "<<myAVL.height(root)<<endl;
		else if( command =="min")	
		{
			Node* min = myAVL.findMin(root);
			cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
		}
		else if( command =="max")	
		{
			Node* max = myAVL.findMax(root);
			cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
		}
		else if( command =="find")	
		{
			if (check(key)) {
				cout<<key<<(myAVL.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
			}
			else {
				cout<< "Please type a valid input..."<<endl;
			}		
		}
		else if( command =="inorder")	{myAVL.printInorder(root); cout<<endl;}
		else if( command =="exit") break;
		else if( command == "demo") demo(myAVL); 
		else if( command == "help") listCommands();
		else if( command == "exit") break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}
//=====================================================================
AVL::AVL()
{
	this->root=nullptr;
}
AVL::~AVL()
{
	//Keep removing the Node with Min (or Max) value util entire tree becomes empty
	while(root)
		root=remove(root,findMin(root)->key);
}
// Return the root of the tree
Node* AVL::getRoot()
{
	return root;
}

//Print recursively the tree/subtree rooted at ptr Inorder fromat
void AVL::printInorder(Node *ptr)
{
	if(ptr!=nullptr)
	{
		printInorder(ptr->left);
		cout<<ptr->key<<" ";
		printInorder(ptr->right);
	}
}
//Find the Height (MaxDepth) of the tree/subtree rooted at ptr
int AVL::height(Node* ptr)
{
	if(ptr==nullptr) return -1;
	return max(height(ptr->left),height(ptr->right))+1;
}
// Find recursively (or iteratively ) the key with minimum in the tree/subtree rooted at ptr
Node* AVL::findMin(Node *ptr)
{

	if(ptr==nullptr) 		return nullptr; //if Tree is empty
	else if(ptr->left)		//recursive approach to find the node with minimum key in the tree
		return findMin(ptr->left);
	else								//if reached to the left most node
		return ptr;
}
// Find recursively (or iteratively ) the key with Maximum in the tree/subtree rooted at ptr
Node* AVL::findMax(Node *ptr)
{

	if(ptr==nullptr) 		return nullptr; //if Tree is empty
	else if(ptr->right)		//recursive approach to find the node with Maximum key in the tree
		return findMax(ptr->right);
	else								//if reached to the right most node
		return ptr;
}
// Find recursively the node with key value in the tree/subtree rooted at ptr
Node* AVL::findKey(Node *ptr,int key)
{
	if(ptr==nullptr) 			return nullptr;
	else if(key == ptr->key) 	return ptr;
	else if(key < ptr->key) 	return findKey(ptr->left,key);
	else						return findKey(ptr->right,key);
}
// Calculate and returns the Balance Factor of a Node
int AVL::balanceFactor(Node *ptr)
{
	if (ptr == nullptr) {	
		return 0;
	}
	int leftHeight = height(ptr->left);
	int rightHeight = height(ptr->right);

	return (leftHeight - rightHeight);				//difference between the heights of the left and right trees, the load factor

}
//Helper method for insert method
void AVL::insert_helper(int key)
{	
	root=insert(root,key);
}
//Insert recursively the key in the tree/subtree rooted at ptr
Node* AVL::insert(Node *ptr, int key)
{
	if (ptr ==nullptr) return (new Node(key)); 		//if tree is empty or if we found the right place for new node 

	if(key < ptr->key)								// if the key is smaller
			ptr->left = insert(ptr->left,key);   	// recursively insert new node in left subtree
	else if(key >ptr->key)							// if the key is greater
			ptr->right = insert(ptr->right,key);	// recursively insert new node into right subtree
	else	//if key already present
	{
		cerr<<"Duplicate Values not allowed"<<endl;
		return ptr;   
	}
	ptr = rebalance(ptr);
	return ptr;
}
//==========================================
// Rotate a node to its right
Node* AVL::rotateRight(Node *z)
{  
	Node *y = z->left;					
	Node *T2 = y->right;					//useful if y actually has right child

	y->right = z;							//the rotation step of z
	z->left = T2;							//if y originally didn't have right child, z->left will equal nullptr


	return y;
}  
//==========================================
// Rotate a node to its left  
Node* AVL::rotateLeft(Node *z)
{  
	Node *y = z->right;
	Node *T1 = y->left;						//useful if y has left child

	y->left = z;							//rotation step of z
	z->right = T1;							//if y originally didn't have left child, z->right will equal nullptr
	
	return y;
}
//============================================
// Rebalane a node (ptr)
Node* AVL::rebalance(Node *ptr)
{
	int diff1 = balanceFactor(ptr);								//load factor of orignal node (root of subtree)
	int diff2 = balanceFactor(ptr->left);						//load factor of left subtree of root
	int diff3 = balanceFactor(ptr->right);						//load factor of right subtree of root
	// case 0: Already balanced
	if (diff1 == 0 || diff1 == -1 || diff1 == 1) {		
		return ptr;
	}
	// case 1: right right heavy 
	else if (diff1 > 1 && (diff2 > -1)) {						//rotate right once
		return rotateRight(ptr);
	}
	// case 2: left left heavy
	else if (diff1 < -1 && (diff3 < 1) ) {					//rotate left once
		return rotateLeft(ptr);
	} 
	// case 3: right left heavy 
	else if (diff1 < -1 && (diff3 >= 1) ) {					//rotate right at right child then rotate left at root
		ptr->right = rotateRight(ptr->right);				//update value of right child
		return rotateLeft(ptr);
	}
	// case 4: left right heavy
	else if (diff1 > 1 &&  (diff2 <= -1)){						//rotate left at left child then rotate right at root
		ptr->left = rotateLeft(ptr->left);						//update value of left child
		return rotateRight(ptr);
	}
	return ptr;
}
//=================================================
//Helper method for remove 
void AVL::remove_helper(int key)
{
	if(findKey(root,key)==nullptr)
		cout<<"Key not found..."<<endl;
	else	
		root = remove(root, key);
}
//Remove recursively the node with key value from the tree/subtree rooted at ptr
Node* AVL::remove(Node *ptr,int key)
{
	if(key<ptr->key) 						//if key is smaller than the key at root of the tree/subtree
		ptr->left = remove(ptr->left, key);		//then search in left subtree
	else if(key>ptr->key)
		ptr->right = remove(ptr->right, key);	//else search in right subtree
	else		//The node to be deleted has been found		
	{
		if(ptr->left == nullptr && ptr->right == nullptr)		//if the node to be deleted is a Leaf node then remove it
		{
			delete ptr;
			ptr=nullptr;
			return ptr;
		}
		else if(ptr->right == nullptr)		//if the node to be deleted has no right child 
		{
			Node* tmp = ptr;				//then remove it and connect its left child/subtree to its parent
			ptr = ptr->left;
			delete tmp;
		}
		else if(ptr->left == nullptr)		//if the node to be deleted has no left child
		{
			Node* tmp = ptr;				//then remove it and connect its right child/subtree to its parent
			ptr = ptr->right;
			delete tmp;
		}
		else										//if the node to be deleted has both left and right children
		{
			Node *min = findMin(ptr->right);		//find the node with minimum key in its right subtree 
			swap(ptr->key,min->key);				//and replace it with the minimum node found in right subtree, 
													//We swaped instead of copying so the correct deleted message will be printed
			ptr->right = remove(ptr->right, min->key);	//recursivly remove the minimum node from right subtree
		}
	}
	ptr=rebalance(ptr);
	return ptr;
}
//==================================================================
//  This method prints a Binary Tree in 2D format
//  Created by Saurabh Ray 
//  Copyright © 2020 Saurabh Ray. All rights reserved.

void AVL::printTree(){
   cout<<"Tree :"<<endl;
   char *space = "  ";
   int d = height(this->getRoot());
   int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

   int *A = new int[n];
   bool *B = new bool[n];
   for(int i=0; i<n; ++i) B[i]=false;

   printTreeHelper(A,B,root,n);


   //cout<<"\nTree:"<<endl;
   for(int t=(n+1)/2; t>0; t=t/2){
        for(int j=0; j<n; j++){
            if( ((j+1)%t == 0) && B[j]){
                cout<<setw(3)<<A[j];
                B[j] = false;
            }
            else{
                cout<<space;
            }
        }
        cout<<endl;
   }
   cout<<endl;
   delete [] A;
   delete [] B;
}

void AVL::printTreeHelper(int *A, bool *B, Node *ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}