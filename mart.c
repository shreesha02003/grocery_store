#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Total=0;

typedef struct stock
{
char name[100];
int price;
struct stock *next;
}stock;
stock *vegetables=NULL,*fruits=NULL,*medicines=NULL,*groceries=NULL;


typedef struct bill
{
	char name[100];
	int ppd;
	int quantity;
	int total_price;
	struct bill *next;
}bill;

bill *first=NULL;

bill* Add_bill(bill *first,char name[],int ppd,int quantity)
{
	bill* temp;
	bill* node=(bill*)malloc(sizeof(bill));
	strcpy(node->name,name);
	node->ppd=ppd;
	node->quantity=quantity;
	Total+=ppd*quantity;
	node->total_price=ppd*quantity;
	if(first==NULL)
		first=node;
	else
	{
	temp = first;
	while(temp->next!=NULL)
	temp = temp->next;
	temp->next = node;
	}
	return(first);
}


stock * ins_last(stock *first,int price,char name[])
{
stock *newnode,*temp;
newnode = (stock*)malloc(sizeof(stock));
strcpy(newnode->name,name);
newnode->price=price;
newnode->next = NULL;
if(first == NULL)
first = newnode;
else
{
temp = first;
while(temp->next!=NULL)
temp = temp->next;
temp->next = newnode;
}
return(first);
}

void Add_stock()
{
	//Vegetables
	vegetables=ins_last(vegetables,30,"Tomatoes");
	vegetables=ins_last(vegetables,40,"Potatoes");
	vegetables=ins_last(vegetables,50,"Onions");
	vegetables=ins_last(vegetables,30,"Carrots");

	//Fruits
	fruits=ins_last(fruits,90,"Apple");
	fruits=ins_last(fruits,40,"Banana");
	fruits=ins_last(fruits,200,"Mango");
	fruits=ins_last(fruits,60,"Pomogrenate");

	//Groceries
	groceries=ins_last(groceries,40,"Soap");
	groceries=ins_last(groceries,150,"Shampoo");
	groceries=ins_last(groceries,50,"Dishwash");
	groceries=ins_last(groceries,30,"Biscuits");
	groceries=ins_last(groceries,120,"Chocolate(DairyMilk)");

	//Medicines
	medicines=ins_last(medicines,40,"Paracetamol");
	medicines=ins_last(medicines,150,"Neosporin");
	medicines=ins_last(medicines,80,"Volini");
	medicines=ins_last(medicines,90,"Dolo650");

}

typedef struct node
{
	char question[50];
	struct node *lptr,*rptr;
}node;

int Question(node *x)
 {
 	char n[5];
	printf("%s",x->question);
	scanf("%s",n);
	if((strcmp(n,"YES")==0)||(strcmp(n,"Yes")==0)||(strcmp(n,"yes")==0))
		return 1;
	return 0;
}

void Display(stock *ptr)
{
	stock *temp;
	temp=ptr;
	int id=1;
	printf("_\n");
	printf("\tITEMID\t|\tNAME\t\t\t|\tPRICE\t|\n");
	printf("_\n");
	while(temp!=NULL)
	{
		printf("\t%d\t|\t%-24s|\t%d\t|\n",id,temp->name,temp->price);
		id++;
		temp=temp->next;
	}
	printf("_\n");
}


void DisplayBill(bill *ptr)
{
	bill *temp;

	temp=ptr;
	int serialno=1;
	printf("\n");
	printf("\tSr.no.\t|\tName\t\t\t|\tPrice\t|\tQuantity\t|\tTotalPrice\t|\n");
	printf("\n");
	while(temp!=NULL)
	{
		printf("\t%d\t|\t%-24s|\t%d\t|\t%d\t\t|\t%-15d\t|\n",serialno,temp->name,temp->ppd,temp->quantity,temp->total_price);
		temp=temp->next;
		serialno+=1;
	}
	printf("\n");
}

bill* Modify(bill *ptr)
{
    int choice;
    bill *temp;
    bill *prev;
    prev=NULL;
    bill* ptemp=prev;
    //bill* qtemp=ptr;
    int new_q;
    char name[40];
    while(1)
    {
        temp=ptr;
        prev=ptemp;
        printf("Enter the name of the item or Enter return if no modification:\n");
        scanf("%s",name);
        if(strcmp(name,"return")==0)
            return ptr;
        while(strcmp(temp->name,name)!=0)
        {
         prev=temp;
         temp=temp->next;
        }

        printf("\n1:Delete the item\n2:Modify the quantity\n3:No changes\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            Total-=temp->total_price;
            if(temp->next!=NULL && prev==NULL)
            {
                prev=temp;
                temp=temp->next;
                free(prev);
                ptr=ptr->next;

            }
            else if(temp->next==NULL && prev==NULL)
            {
                ptr=ptr->next;
            }
            else if(temp->next==NULL)
            {
                prev->next=NULL;
                free(temp);
            }
            else
            {

                prev->next=temp->next;
                free(temp);
            }
            break;
        case 2:
            Total-=temp->total_price;
            printf("Enter the new quantity:\n");
            scanf("%d",&new_q);
            temp->quantity=new_q;
            temp->total_price=temp->ppd*new_q;
            Total+=temp->total_price;
            printf("Quantity updated successfully\n");
            break;
        }
    }

}



void Buy(stock *item)
{
    char change_item[40];
	int choice;
	stock *temp;
	int x;
	int quantity;
	printf("\nThe following items are available:\n\n");
	Display(item);
	printf("\nWhat would you like to buy??\n");
	while(1)
	{
			temp=item;
			printf("\nPlease enter -1 if you don't want to buy anything\nEnter -2 to view and edit the cart:\n");
			scanf("%d",&choice);
			x=choice;
			if(x!=-1 && x!=-2)
			{
			while(x!=1)
				{
				temp=temp->next;
				x--;
				}
			printf("\nBuying %s :-\n",temp->name);
			printf("Enter quantity:");
			scanf("%d",&quantity);
			printf("\nAdded to cart Successfully\n\n");
			first=Add_bill(first,temp->name,temp->price,quantity);
			printf("\nWould you like to buy anything else??\n");
			Display(item);
			}
			else if(x==-2)
            {
                DisplayBill(first);
                printf("Would you like to make changes to the cart ?\nIf yes,please enter YES , else enter NO:\n");
                scanf("%s",change_item);
                if(strcmp(change_item,"NO")==0)
                    return;
                else
                {
                  first=Modify(first);
                  return;
                }

            }
			else
			{
				return;
			}
	}
}

void traversal(node *root)
{

 int flag;
 node *temp;
 temp=root;
 int count=0;
 while(1)
 {
 	count+=1;
 	if(temp==NULL)
 	{
 		return;
	}
 	flag=Question(temp);
 	if(flag)
 	{
  		int choice,pr,tot;
        char data[100];
        switch(count)
        {
        	case 1:
        		Buy(groceries);
        		temp=temp->rptr;
        		break;
        	case 2:
        		Buy(vegetables);
        		temp=temp->rptr;
        		break;
        	case 3:
        		Buy(fruits);
        		temp=temp->rptr;
        		break;
        	case 4:
        		Buy(medicines);
				temp=temp->rptr;
				break;
			default:
				return;
   		}
    }
	else if(flag==0)
	{
		temp=temp->rptr;
	}
}
}

node* build(node* root)
{
	node * temp=root;
	node * right1=(node*)malloc(sizeof(node));
	node * right2=(node*)malloc(sizeof(node));
	node * right3=(node*)malloc(sizeof(node));
	strcpy(right1->question,"\nDo you want to enter the Vegetables Aile??\n");
	strcpy(right2->question,"\nDo you want to enter the Fruits Aile??\n");
	strcpy(right3->question,"\nDo you want to enter the Medicines Aile??\n");
	temp->rptr=right1;
	right1->rptr=right2;
	right2->rptr=right3;
	right3->rptr=NULL;
	right1->lptr=NULL;
	right2->lptr=NULL;
	right3->lptr=NULL;
	return root;
}

int main()
{
	int a=3;
	node * root = (node*)malloc(sizeof(node));
	root->lptr=NULL;
	while(a!=0)
	{
	root=build(root);
	a--;
	}
	strcpy(root->question,"Do you want to enter the Groceries Aile??\n");
	printf("WELCOME TO THE GROCERY STORE\n");
	char choice[5];
	Add_stock();
	while(1)
	{
		printf("\nWe have the following sections:\n1:Groceries\n2:Vegetables\n3:Fruits\n4:Medicines\n\n");
		traversal(root);
		printf("\nContinue Shopping??\n");
		scanf("%s",choice);
		if((strcmp(choice,"YES")==0)||(strcmp(choice,"Yes")==0)||(strcmp(choice,"yes")==0))
			continue;
		else
			{
		    break;
			}
	}
	printf("\nYour Bill:\n");
	DisplayBill(first);
	printf("\nYour Total is: %d Rupees\n\n",Total);
	printf("Thank You for Shopping with Us\n\nDo visit again!!!\n\n");
	return 0;
}
