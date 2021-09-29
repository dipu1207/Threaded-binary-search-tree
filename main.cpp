#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;
//here we are defining a node structure
class NODE
{public:
   int data;
   	NODE *lchild;
	NODE *rchild;
   	bool lthread,rthread;
   	int rcount;
   	int lcount;
};

//here we are defining a list 
class LIST{
	public:
	int info;
	LIST *next;
};
//here we are creating a class of threaded binary search tree
class BinSearTree{
	private:
	          NODE *root;
	          
	public: 
	        
	         BinSearTree(){ root=nullptr;	}
		      NODE* getRoot(){ return root ;}
		     
		      
			  void deleteKey(int key);
			  void delLeaf(NODE*parent,NODE*current);
			  void delOneChild(NODE*parent,NODE*current);
			  void delTwoChild(NODE*parent,NODE*current);
			  void insert(int key);
		
		       NODE *inorderSuccessor(NODE *ptr);
		        NODE *inorderPredecessor(NODE *ptr);
			   LIST *reverseInorder();
		      void printLIST(LIST *head);
		      NODE* search(int key); 
		      void findKthLargest(int index);
		      void findSuccessor(int key);
		      LIST* elementBetweeenNodes(int first,int second);
			  void printTree();
		      void splitTree();
};//end of class BinSearTree
//delete function for leaf node
void BinSearTree::delLeaf(NODE*parent,NODE*current)
{  
	if(parent==nullptr)//root is only element presenet
	  {
	    root=nullptr;
	     cout<<"element\t"<<current->data<<"\t is deleted"<<endl;
	     return;
		}  
	
	else if(current==parent->lchild)//current id left child of parent
	{  parent->lthread=true;
		parent->lchild=current->lchild;
		
	}
	else
	{  
	    parent->rthread=true;
		parent->rchild=current->rchild;
		
	}
	delete current;
	   
}
//delete function for leaf node
void BinSearTree::delOneChild(NODE*parent,NODE*current)
{ 
  
     NODE*childptr;
	//we will take a reference to the child of node to be deleted it can be either left or right child
	if(current->lthread==false)//means node to be deleted has only left child
	   {
	   	
	   	childptr=current->lchild;
	
	   }
	   
	else {
	        childptr=current->rchild;
      	   }    
	//if the node to be deleted is root node then we will make its child as node
    
	   if(parent==nullptr)
	     {
	       if(current->lchild!=nullptr)
	       //find predecessor of current and put its rchild as null
	       {
	       	NODE*setprede=inorderPredecessor(current);
	       	setprede->rchild=nullptr;
		   }
	       else{
	             NODE*setsucc=inorderSuccessor(current);
	        	setsucc->lchild=nullptr;
		   	
		   }
	     	root=childptr;
	        delete current;
				return;
       
	     }
     //getting inorder predecessor and inorder successor of node to be deleted
	   NODE*inorderPre=inorderPredecessor(current);
        cout<<"predecessor of current is\t"<<inorderPre->data<<endl;
	   NODE*inorderSuc=inorderSuccessor(current);
	   cout<<"successor of current is\t"<<inorderSuc->data<<endl;
	    
    //if node to be deleted is left child of its parent then its parent will point to its child
       if(current==parent->lchild)
          parent->lchild=childptr;
          
          else parent->rchild=childptr;
	    //if node to be deleted has left child.. then node to be deleted  inorder predecessor will have its inorder successsor as the successor of node to be deleted
          if(current->lthread==false)
            {
            	inorderPre->rchild=inorderSuc;
			}
			
			else {
				if(current->rthread==false)
				inorderSuc->lchild=inorderPre;
			}
			         
		
			delete current;
  }

//delete function for leaf node
void BinSearTree::delTwoChild(NODE*parent,NODE*current)
{
	//here we are deleting node with two children
	//first we will find the inorder successor of the node to be deleted and also parent of its inorder successor
	 NODE* inorderSucc=current->rchild;
	 NODE*parentInorderSucc=current;
	 while(inorderSucc->lthread==false)
	     {
	     	parentInorderSucc=inorderSucc;
	     	inorderSucc=inorderSucc->lchild;
		 }
		  //copy value of successor ot current
		  current->data=inorderSucc->data;
		 
		 //now we will call two delete fuctions based on the conditions of the successor of current node
		 if(inorderSucc->lthread==true&&inorderSucc->rthread==true)
		   delLeaf(parentInorderSucc,inorderSucc);
		 else delOneChild(parentInorderSucc,inorderSucc);
          
		

}


//print tree 
void BinSearTree::printTree()
{
}

//split tree 
void BinSearTree::splitTree()
{
	
}
// print elements between given two nodes
 LIST* BinSearTree::elementBetweeenNodes(int first,int second)
 {   LIST*headOfList=nullptr;
      LIST*lastOfList=nullptr;
     //we will first find reference of the first node and second node
	NODE* start=search(first);
 	NODE* stop=search(second);
 	if(start==nullptr||stop==nullptr)
 	  {
 	  	cout<<"enter correct input "<<endl<<endl;
 	  	return nullptr;
	   }
	 //now we will start putting value in link list 
	 while(start!=stop)
	 {
	 	LIST*temp=new LIST;
	    temp->info=start->data;
	    temp->next=nullptr;
	    
		if(headOfList==nullptr)
	       {
	       	headOfList=temp;
	       	lastOfList=headOfList;
		     lastOfList->next=nullptr;
			 
		   }
	        
	    else{
	    	
	    	lastOfList->next=temp;
	    	lastOfList=temp;
	    	
		   }
		//start will now point to its successor
		start=inorderSuccessor(start);
	 }
	 //inserting last node
	 	LIST*temp=new LIST;
	    temp->info=start->data;
	    temp->next=nullptr;
	    lastOfList->next=temp;
	    	lastOfList=temp;
	    	
	 return headOfList;
 }
 
//find successor
void BinSearTree::findSuccessor(int key)
{   
    //first check if element is present or not
     NODE*nodeptr=search(key);
	 
	 if(nodeptr==nullptr||nodeptr->rchild==nullptr)//largest element has no successor
        {
        	cout<<"successor is not present"<<endl;
        	return;
		}
     
	    //now nodeptr points to location of node whose data value equals to key and whose successor we want to find
       if(nodeptr->rthread==true)
       //means it is leaf and it points to its inorder successor
       cout<<"the successor of \t"<<key<<"\t is: \t"<<nodeptr->rchild->data<<endl<<endl<<endl;
       
	   else
	   {
       	//means it is a parent and its successor will be found in its right subtree
       	  nodeptr=nodeptr->rchild;
       	  while(nodeptr->lthread==false)
       	     nodeptr=nodeptr->lchild;
          cout<<"the successor of \t"<<key<<"\t is: \t"<<nodeptr->data<<endl<<endl<<endl;
    }
     
}//end of findSuccessor

//finding kth largest value
void BinSearTree::findKthLargest(int index){
    int k=index;
	NODE*rootptr=getRoot();
   	if((rootptr->rcount+rootptr->lcount+1)<index||index<1)
		   {
		   	cout<<"kth largest index is invalid"<<endl;
		   	 return;
		   }
    while(rootptr!=nullptr)
	{
             if((rootptr->rcount+1)<index)
			   {
			   	rootptr=rootptr->lchild;
			   	index=index-(rootptr->rcount+1);
			   	}
				else if(rootptr->rcount>=index)
				    rootptr=rootptr->rchild;
			  else
			   {
			      cout<<"value at index no :"<< k<<"\tis\t"<<rootptr->data<<endl;	
		             break;
			     } 
    }
			
}
//search the key value
NODE* BinSearTree::search(int key)
{
     NODE*searchptr=root;
     while(searchptr!=nullptr)
     {
     	if(key<searchptr->data)
     	  {
     	  	if(searchptr->lthread==false)
     	  	    searchptr=searchptr->lchild;
     	  	else 
     	  	   break;
		   }
	    else if(key>searchptr->data)
		      {
		      	if(searchptr->rthread==false)
		      	   searchptr=searchptr->rchild;
		      	else 
		      	    break;
			  }
		else{
			
		    	return searchptr;
		} 
		   
	 }
	
     return nullptr;
     
}
//insert function
void BinSearTree::insert(int key) {
 //creating new node
    NODE *temp=new NODE;
    
    temp->data=key;
    temp->lchild=nullptr;
    temp->rchild=nullptr;
    temp->lthread=true;
    temp->rthread=true;
    temp->rcount=0;
    temp->lcount=0;
    // root is empty
    if (root == nullptr){
       root=temp;
    
        return;
    }
    
NODE *curr=root;

NODE*parent=nullptr;
    while(curr!= nullptr)
   {
        
        if (key < curr->data)
		{
		   parent=curr;
		   if(curr->lthread==false)
		     {
		     	 curr->lcount++;
			     curr=curr->lchild;
			 }
		   else break;
		 }
        else
         if (key > curr->data)
		{  
		 
		   parent=curr;
		   
		   if(curr->rthread==false)
		   {
		        curr->rcount++;
		          curr=curr->rchild;
		   }
		   
		   
		   else break;
		 }
        else
        {
        	
           throw "duplicate found. insert unsuccessful";
			return;
		}
    }//end while
 
    // Now parent points at  insert location
    if (key < parent->data)
	{     parent->lcount++;
		parent->lthread=false;
		temp->lchild=parent->lchild;
        temp->rchild=parent;
        parent->lchild=temp;
    } 
	else
	 { 
	    parent->rcount++;
        parent->rthread=false;
		temp->rchild=parent->rchild;
        temp->lchild=parent;
        parent->rchild=temp;
       }
 
}

//inorder successor 
NODE * BinSearTree::inorderSuccessor(NODE*ptr)
{    
      
	if(ptr->rthread==true)
	  return ptr->rchild;
	else{
		ptr=ptr->rchild;
		while(ptr->lthread==false)
		  ptr=ptr->lchild;
		return ptr;
	}
}//end of inorderSuccessor

//inorder predecessor 
NODE * BinSearTree::inorderPredecessor(NODE*ptr)
{
	if(ptr->lthread==true)
	  return ptr->lchild;
	else{
		ptr=ptr->lchild;
		while(ptr->rthread==false)
		  ptr=ptr->rchild;
		return ptr;
	}
}//end of inorderSuccessor


//function of returning head of link list containing reverseInorder of tree
LIST* BinSearTree::reverseInorder()
{   
        LIST*headOfRevInorder=nullptr;
	//here we will use inorder traveral and at the time of insertion in linked list we will insert from beginning
      if(root==nullptr)
      {  cout<<"tree is empty"<<endl;
            return headOfRevInorder; 
			}

	  else{
	  	    
	  	         NODE*rootptr=root;
	        //we will get the smallest element 
			while(rootptr->lchild!=nullptr)
               rootptr=rootptr->lchild;
	      //now we will start inserting in linked list
		  while(rootptr!=nullptr)
		  {     
		        LIST *temp=new LIST;
	  	        
	  	       temp->info=rootptr->data;
		      
			    if(headOfRevInorder==nullptr)
		         {  temp->next=nullptr;
		         	headOfRevInorder=temp;
				  } 
		       else {
		         	  temp->next=headOfRevInorder;
		       	       headOfRevInorder=temp;
			      }  
		        
				rootptr=inorderSuccessor(rootptr);
		  }//end of while	 
	   }//end os else
		return headOfRevInorder;
	  
}//end of reverseInorder

  //delete key
  void BinSearTree::deleteKey(int key)
  {
  	//we will make current pointer points to node to be deleter and parent pointer points to parent of node to be deleted
  	  NODE*current=getRoot();
  	  NODE*parent=nullptr;
  	//throw exception if root is null
	  if(current==nullptr)
	     {
		 cout<< "tree is empty"<<endl;
		 return;  
	     }
	
	 while(current!=nullptr)
  	  {
  	  	if(key==current->data)
  	  	{ 
  	  	   cout<<"NODE to be deleted is:\t"<<current->data<<endl;
  	  		break;
			}
		else
		{
		   parent =current;
		
		   if(key<current->data)
			  { 
			     if(current->lthread==false)
			  	{
			  		current->lcount--;
			  		current=current->lchild;
				  }
				else
					throw "key not found to be deleted";
					
			   }  
		
		     
			  else
			  { 
			     if(current->rthread==false)
			  	{
			  		current->rcount--;
			  		current=current->rchild;
				  }
				  else   
				        throw "key not found to be deleted";
					
		     }
		 }
		}//end while

     //if we want to delete leaf
      if(current->lthread==true&&current->rthread==true)
          delLeaf(parent,current);
    //delete node with two children      
      else if(current->lthread==false&&current->rthread==false)
          delTwoChild(parent,current);
    //node with one child either left or right
        else delOneChild(parent,current);
        cout<<"delete success"<<endl;
	}  
//printLIST
void BinSearTree::printLIST(LIST *head)
{  
   cout<<"contents of list are::"<<"\t\t";
  LIST*temp=head;
   while(temp!=nullptr)
    {
    	cout<<temp->info<<"\t";
    	temp=temp->next;
	}	
     cout<<endl;
}
int main(int argc, char** argv) {
	BinSearTree bst;
	NODE*result;
	int x=10,key,  k1,k2;
     LIST*headOfList=nullptr;
	while(1)
	{   cout<<"enter your choice"<<endl;
		cout<<"1.insert into tree"<<endl;
		cout<<"2.search an element"<<endl;
		cout<<"3.delete an element"<<endl;
		cout<<"4.find inorder succcessor of an element"<<endl;
		cout<<"5.reverse inorder of tree"<<endl;
		cout<<"6.find Kth latgest element"<<endl;
		cout<<"7.all element between k1 and k2"<<endl;
		cout<<"8.print tree"<<endl;
		cout<<"9.split tree"<<endl;
		cout<<"10.print list"<<endl;
	     cout<<"11.exit the program"<<endl<<endl;
		cin>>x;
		switch(x){
			case 1:cout<<"enter key value to be inserted"<<"\t\t";
			        
					 cin>>key;
					 bst.insert(key);
					 cout<<endl<<endl;
				break;
				
			case 2:cout<<"enter element to search"<<"\t\t";
			        
					 cin>>key;
					result= bst.search(key);
					 if(result==nullptr)
					 cout<<"search unsuccessful"<<endl;
					 else cout<<"element found"<<endl;
					 cout<<endl;
			      	break;
				
				
			case 3:cout<<"enter element to delete"<<"\t\t";
			         cin>>key;
					 bst.deleteKey(key);
					 cout<<endl;
			     	break;
				
				
			case 4:cout<<"enter the element to get successor"<<"\t\t";
			         cin>>key;
					 bst.findSuccessor(key);
					 cout<<endl;
			     	break;
				
				
			case 5:cout<<"head of list is returned"<<"\t\t";
			         	headOfList=nullptr;
					   headOfList= bst.reverseInorder();
					    cout<<endl;
				     break;
				
				
			case 6:cout<<"find kth largest element"<<"\t\t";
			         cin>>key;
					 bst.findKthLargest(key);
					 cout<<endl;
				     break;
				
				
			case 7:cout<<"enter keys k1 and k2 where k1 is smaller"<<"\t\t";
			       headOfList=nullptr;
					 cin>>k1>>k2;
					headOfList= bst.elementBetweeenNodes(k1,k2);
			      	break;
				
				
			
			case 8:cout<<"print tree"<<"\t\t";
			         
					 bst.printTree();
				break;
				
				
			case 9:cout<<"split Tree"<<"\t\t";
			         
					 bst.splitTree();
					 cout<<endl;
				break;
				
			case 10:cout<<"print LIST"<<endl;;
			         
					 bst.printLIST(headOfList);
					 cout<<endl;
				break;
				
		
			case 11: return 0;
			default: return 0;
		}//end of switch
	}//end while
	return 0;
}
