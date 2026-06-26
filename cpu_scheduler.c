#include <stdio.h>
#include <stdlib.h>
#include <math.h>



 typedef struct Binomial {
	int ID;
	double PLevel;
	 double etime;
	double etimeleft;
	double atime;
	double atimenew;
	int firsttime;
	struct Binomial *parent;
	struct Binomial *sibling;
	struct Binomial *child;
	int degree;
	
}Binomial; 

typedef Binomial* Binomialptr;

Binomialptr Create_Node(int ID, double etime, double atime ){
	
	Binomialptr x;
	x = (Binomialptr)malloc(sizeof(Binomial));
	
	x->ID=ID;
	x->etime=etime;
	x->atime=atime;
	x->etimeleft=etime;
	x->atimenew=atime;
	x->firsttime=1;
	x->degree=0;
	x->child=NULL;
	x->parent=NULL;
	x->sibling=NULL;
	
	
	return x;
	
}


Binomialptr MargeRoots( Binomialptr q , Binomialptr p ){
	
	
	Binomialptr head ;
	
	Binomialptr *ite ;
	ite = &head;
	
	Binomialptr x= q ;
	Binomialptr y= p ;
	
	
	
	while( x != NULL && y != NULL   ){
		
		if(  x->degree >= y->degree ){
			*ite=y;
			y = y->sibling;
		}else{
			*ite= x;
			x = x->sibling;
		}
		
		ite = &( (*ite)->sibling  );
		   
	}
	if(x==NULL)
	*ite = y;
	else
	*ite= x;
	return head;
	
}


void attach_bt(Binomialptr p, Binomialptr c  ){
	
	c->parent = p;
	
	c->sibling = p->child;
	p->child = c;
	p->degree++;
	
	
	
	
	
}

Binomialptr Insert_Node( Binomialptr tree , Binomialptr ne ){
	
	Binomialptr head ;
	head = MargeRoots(  tree, ne);
	
	if (head == NULL) return head;
	
	Binomialptr prev =NULL;
	Binomialptr x = head;
	Binomialptr r= x->sibling;
	
	while (r != NULL){
		
		if ( ( r->degree != x->degree) || ( r->sibling !=NULL && x->degree == r->sibling->degree )  ){
			
			prev = x;
			x=r;
		}else if ( r->PLevel >= x->PLevel   ){
			x->sibling = r->sibling;
			attach_bt(x,r);
		}else{
			
			if (prev == NULL){
				head=r;
			}else{
				prev->sibling=r;
			}
			attach_bt(r,x);
			x=r;
			
		}
	
	r=x->sibling;
		
		
	}
		
		
		
	return head;
	
	
	
}

Binomialptr findMin(Binomialptr head , Binomialptr *prevmin){
	
	Binomialptr x = head;
	Binomialptr y = NULL;
	
	Binomialptr prev = NULL;
	double min = 999999999;
	
	while (x != NULL){
		
		if (x->PLevel < min ){
			min = x->PLevel;
			y = x;
			*prevmin = prev; 
		}
		prev = x ;
		x= x->sibling;
	}
	
	return y;
	
}


Binomialptr reverselist(Binomialptr node){
	
	Binomialptr prev = NULL;
	Binomialptr curr = node;
	Binomialptr next = NULL;
	
	while(curr != NULL){
		next = curr->sibling;
		curr->sibling=prev;
		curr->parent=NULL;
		prev = curr;
		curr = next;
	}
	return prev;
}


Binomialptr DeleteMin(Binomialptr head ){
	
	if (head == NULL)
	return NULL;
	
	Binomialptr prevmin = NULL;
	Binomialptr minNode = findMin(head,&prevmin);
	
	if (prevmin==NULL)
	head=minNode->sibling;
	else
	prevmin->sibling=minNode->sibling;
	
	Binomialptr children = reverselist(minNode->child );
	head = Insert_Node(head , children);
	 return head;
	
}


int CalculateEmax(int *w){
	
	
	int max=0;
	int i=1;
	while ( w[i] != -99){
		
		if (w[i] >= max  )
		max=w[i];
		i+=4;
	}
	return max;
	
	
}

int Unique_etime(Binomialptr head , int ID , double target){
	
	if (head == NULL)
	return 1;
	
	if  ( ( head->ID != ID) && (head->PLevel == target) ){
		head->PLevel=head->atimenew;
		return 0;
		
	}
	if (!Unique_etime(head->child , ID , target)){
		head->PLevel=head->atimenew;
		return 0;
		
	}
	
	
	return Unique_etime(head->sibling , ID , target);
	
	
}

double CalculateP(Binomialptr head , Binomialptr node , int emax){
	
	double cei ;
	
	if (node->firsttime){
		cei = node->etimeleft;
	
	}else{
		double x = exp(pow( (2.0 * node->etimeleft) / (3.0 * (double) emax)   ,3));
		cei = node->etimeleft * x ;
	}
	if (Unique_etime(head , node->ID , cei)){
		return cei;
	}else
	return node->atimenew;
	
	
}


int Tasknum(int *x){
	
	int i=0,num=0;
	while ( x[i] != -99){
		if (x[i] == -1)
		num++;
		i++;
	}
	return num;
	
}


void Helper(Binomialptr head , Binomialptr* list){
	if (head == NULL)
	return;
	Helper(head->sibling , list);
	Helper(head->child,list);
	head->parent=NULL;
	head->sibling=*list;
	head->child=NULL;
	head->degree=0;
	*list=head;
}

Binomialptr Refreshtree(Binomialptr head , int emax){
	
	Binomialptr list =NULL;
	Helper(head,&list);
	Binomialptr refhead=NULL;
	Binomialptr current = list;
	while (current != NULL){
		
		Binomialptr next = current->sibling;
		current->sibling=NULL;
		current->PLevel=CalculateP(refhead,current,emax);
		refhead = Insert_Node(refhead,current);
		current = next;
	}
	return refhead;
}


void printnodes(Binomialptr head){
	if (head == NULL)
	return ;
	
	printf("[P%d : %.3f]",head->ID,head->PLevel);
	printnodes(head->child);
	printnodes(head->sibling);
}

void printtree(Binomialptr head){
	puts("{ ");
	if (head == NULL){
		puts("Empty");
	}else{
		printnodes(head);
	}
	puts("}\n");
}




void simulation(int *inputs ,int tasknum, int emax,int delayOn){
		
		double awt[100]={-99};
		double delay=0;
		if (delayOn)
		 delay = 0.1;
		 double wt[100]={-99};
	
	int q;
	for (q=1 ; q <= emax ; q++){
		
		Binomialptr head = NULL;
		double currenttime =0 ;
		int finishedtask =0;
		
		
		int i=2;
		int added=0;
		while ( tasknum > finishedtask  ){
			
			
			
				while (inputs[i] != -99){
					
					if ( inputs[i] <= currenttime ){
					Binomialptr newnode = Create_Node(inputs[i-2],inputs[i-1],inputs[i]);
					newnode->PLevel= CalculateP(head, newnode , emax);
					head =Insert_Node(head,newnode);
					added++;
				}
					
					i+=4;
				}
				
				if (head == NULL){
					currenttime++;
					i=2+4*added;
					continue;
				}
				
				Binomialptr prevmin = NULL;
				Binomialptr currenttask = findMin(head, &prevmin);
				head=DeleteMin(head);
				
				
				
				
				
				if ( currenttask->etimeleft > q) {
				currenttask->atimenew=currenttime;
				currenttime+=q ;
				
				if (head != NULL)
				currenttime+=delay;
				
				
                    currenttask->etimeleft = currenttask->etimeleft -q ;
                    
                    
                    Binomialptr w =Create_Node(currenttask->ID,currenttask->etimeleft,currenttask->atimenew);
                    w->PLevel= CalculateP(head, w , emax);
                    w->etime= currenttask->etime;
                    w->atime=currenttask->atime;
                    w->firsttime=0;
                    head =Insert_Node(head,w);
				
					
				}else{
					currenttime+=currenttask->etimeleft;
					
					wt[currenttask->ID]= currenttime - ( currenttask->atime + currenttask->etime );
					currenttime+=delay;
					
					finishedtask++;
					
					free(currenttask);
					
				}
				if (head != NULL)
				head = Refreshtree(head,emax);
				
				
				
				i=2+4*added;
				}
				
				int j=1;
				double sum=0;
				while ( wt[j] != -99){
					sum += wt[j];
					j++;
				}
				awt[q]= sum/ tasknum;
				
				
			
			
			
			
			
		}
		
		int k=1;
		double min =9999;
		int index =0;
		for ( ; k <= q-1 ; k++){
			
				if (awt[k] < min){
				min = awt[k];
				index = k;
			}
			
		
			
		}
		k=1;
		for ( ; k <= q-1 ; k++){
			if (  fabs(awt[k] - min) < 0.01 )
			printf("The best q is %d \n",k);
		}
		k=1;
		puts("Tasks		Wating Time");
		for ( ; k <= tasknum ; k++ ){
			printf("P%d\t\t%.2f\n",k,(double)wt[k]);
		}
		
		
		printf("And the AWT is : %f",min);
		
		puts("\nTime Trace for best q\n");
		 q= index;
		
			Binomialptr head = NULL;
		double currenttime =0 ;
		int finishedtask =0;
		
		
		int i=2;
		int added=0;
		while ( tasknum+1 > finishedtask  ){
			
			
			
				while (inputs[i] != -99){
					
					if ( inputs[i] <= currenttime ){
					Binomialptr newnode = Create_Node(inputs[i-2],inputs[i-1],inputs[i]);
					newnode->PLevel= CalculateP(head, newnode , emax);
					head =Insert_Node(head,newnode);
					added++;
				}
					
					i+=4;
				}
				
				if (head == NULL){
					printf("Time %.2f: CPU Idle\n",currenttime);
					printtree(head);
					currenttime++;
					i=2+4*added;
					if ( added == tasknum)
					finishedtask++;
					
					continue;
				}
				
				Binomialptr prevmin = NULL;
				Binomialptr currenttask = findMin(head, &prevmin);
				printf("Time %.2f: P%d allocated.\n Heap:",currenttime,currenttask->ID);
				printtree(head);
				head=DeleteMin(head);
				
				
				
				
				if ( currenttask->etimeleft > q) {
				
				currenttime+=q ;
				
				if (head != NULL)
				currenttime+=delay;
				
				
                    currenttask->etimeleft = currenttask->etimeleft -q ;
                    currenttask->atimenew=currenttime;
                    
                    
                    Binomialptr w =Create_Node(currenttask->ID,currenttask->etimeleft,currenttask->atimenew);
                    w->PLevel= CalculateP(head, w , emax);
                    w->etime= currenttask->etime;
                    w->atime=currenttask->atime;
                    w->firsttime=0;
                    head =Insert_Node(head,w);
				
					
				}else{
					currenttime+=currenttask->etimeleft;
					currenttime+=delay;
					wt[currenttask->ID]= currenttime - ( currenttask->atime + currenttask->etime );
					finishedtask++;
					
					free(currenttask);
					
				}
				if (head != NULL)
				head = Refreshtree(head,emax);
				
				
				
				i=2+4*added;
				}
		puts("\nEnd of Trace\n");
		
	}
	
	
	
	
	




void main ( ){
	

	int inputs[100]={0};
	
	
puts("--- Task Input Mode ---\n"
     "Format: [Execution Time] [Arrival Time]\n"
     "Type -1 to stop.");
int i=1;
int j=0;
while (1){
	
	int etime;
	int atime;
	scanf("%d",&etime);
	if (etime == -1)
	break;
	
	printf("Task %d :",i);
	printf("	 %d",etime);
	
	scanf("%d",&atime);
	printf(" 	%d",atime);
	
	inputs[j]=i;
	++j;
	inputs[j]=etime;
	++j;
	inputs[j]=atime;
	++j;
	inputs[j]=-1;
  
	 
	
	
	printf("\n");
	


	i++;
	j++;
}
inputs[j]=-99;
j++;
inputs[j]=-99;
j++;
inputs[j]=-99;



int s = CalculateEmax(inputs);


int num =Tasknum(inputs);

simulation(inputs,num ,s,0);
puts("\nNow with delay the new results is : \n");
simulation(inputs,num ,s,1);






	
}


