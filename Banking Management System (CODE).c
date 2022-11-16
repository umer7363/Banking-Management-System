#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
int acc;
static int arr_size=5;
struct main
{
	char name[20],pin[4];
	float amnt;
	long long int acc_no;
};
union un
{
	struct main m;
};
struct info
{
	union un u;
	
};
int sys_time(void)
{
	time_t t;
	time(&t);
	printf("DATE/TIME : %s",ctime(&t));
}


int pins(char *pin)
{
	
	char ch;
	int i;
	for(i=0;i<=3;)
	{
		ch=getch();
		if(ch>='a'&&ch<='z'||ch=='A'&&ch<='Z')
		{
			continue;    //infinite loop
		}
		else if(ch=='\n')
		{
			if(i==3)
			{
				break;
			}
			else
			{
				continue;
			}
		}
		else if(ch=='\b')    //for deleting a digit in pin
		{
			if(i>0)
			{
				printf("\b \b");
				i--;
				pin--;
			}
		}
		else if(ch>='0'&&ch<='9')   //showing password in *
		{
			*pin=ch;
			ch='*';
			printf("%c",ch);
			i++;
			pin++;
		}
		if(i==4)
		{
			while(ch!='\n')
			{
			
			if(ch=='\b')  //removing digit from pin
			{
			printf("\b \b");
			i--;
			pin--;
			break;	
			}
			ch=getch();
			if(ch=='\r')
			break;
			}
			*pin='\0';
		}
	}
	printf("\n");
	system("cls");
}



int login(FILE *fp)    //In ATM for logging in. Accounts already created in file (My project Record)
{
	int i,a,j,counter=0;
	char c_name[20],c_pin[4];
	struct info arr;
	do
	{
	fflush(stdin);
	printf("USER NAME = ");
	gets(c_name);
	for(j=0;j<arr_size;j++)
	{
	fgets(arr.u.m.name,20,fp);
	fscanf(fp,"%s\n%f\n%lld\n\n",arr.u.m.pin,&arr.u.m.amnt,&arr.u.m.acc_no);
	if(j==0)
	{
		a=strcmp(arr.u.m.name,strcat(c_name,"\n"));
	}
	else
	{
		a=strcmp(arr.u.m.name,c_name);
	}
	if(a==0)
	{
		acc=j;
		break;
	}
	}
	counter++;
	if(!a)
	{
		break;
	}
	else if(a!=0&&counter==3)
	{
	//	PlaySound("C:/Users/ADMIN/Downloads/alarm.wav", NULL, SND_FILENAME);
		exit(0);
	}
	else
	{
		printf("\tNO USER NAME FOUND !\n");
	}
	}while(counter!=3);
	counter=0;
	do
	{
	printf("ENTER PASSWORD = ");
	pins(c_pin);
	counter++;
	a=strcmp(c_pin,arr.u.m.pin);
	if(a==0)
	{
		break;
	}	
	else if(a!=0&&counter==3)
	{
		printf("\tPASSWORD IS INCORRECT !\n");
		exit(0);
	}
	else
	{
		printf("\tPASSWORD IS INCORRECT !\n");
	}
	}while(counter!=3);
	fclose(fp);
}


int pin(FILE *fp)
{
	int i,a,counter=0;
	char m,n,n_pin1[4],n_pin2[4],*p;
	struct info pass;
	p=pass.u.m.pin;
	system("cls");
	printf("ENTER NEW PIN (4-DIGITS) :");
	pins(n_pin1);
	do
	{
	
	printf("CONFIRM NEW PIN :");
	pins(n_pin2);
	a=strcmp(n_pin1,n_pin2);
	if(a==0)
	{
		p=n_pin1;
		break;
	}
	else
	{
		system("cls");
		printf("YOUR PIN IS INCORRECT \n\nA-WANT TO ENTER NEW PIN AGAIN\n\nB-RE-ENTER CONFIRM PIN\n\nWHAT YOU WANT TO SELECT :");
		fflush(stdin);
		scanf("%c",&n);
		if(n=='a'||n=='A')
		{
			pin(fp);
		}
		else
		{
			continue;
		}
	
	}
	}while(a!=0);
	system("cls");
	FILE *fp1;
	fp1=fopen("MY PROJECT RECORD 2.txt","w");
	if(fp1==NULL)
	{
		printf("UNABLE TO OPEN");
		exit(0);
	}
	for(i=0;i<arr_size;i++)
	{
		
		if(i==acc)
		{
			fgets(pass.u.m.name,20,fp);
			fputs(pass.u.m.name,fp1);
			fscanf(fp,"%s\n%f\n%lld\n\n",pass.u.m.pin,&pass.u.m.amnt,&pass.u.m.acc_no);
			fprintf(fp1,"%s\n%f\n%lld\n\n",n_pin1,pass.u.m.amnt,pass.u.m.acc_no);
		}
		else
		{
		fgets(pass.u.m.name,20,fp);
		fputs(pass.u.m.name,fp1);
		fscanf(fp,"%s\n%f\n%lld\n\n",pass.u.m.pin,&pass.u.m.amnt,&pass.u.m.acc_no);
		fprintf(fp1,"%s\n%f\n%lld\n\n",pass.u.m.pin,pass.u.m.amnt,pass.u.m.acc_no);
		}
		
	}
	fclose(fp1);
	fclose(fp);
	remove("MY PROJECT RECORD.txt");
	rename("MY PROJECT RECORD 2.txt","MY PROJECT RECORD.txt");
	printf("YOUR PIN IS CHANGED SUCCESSFULLY");
}


void receipt(FILE *fp)
{
	int i;
	struct info arr;
	system("cls");
	time_t t;
	time(&t);
	sys_time();
	for(i=0;i<arr_size;i++)
	{
		fgets(arr.u.m.name,20,fp);
		fscanf(fp,"%s\n%f\n%lld\n\n",arr.u.m.pin,&arr.u.m.amnt,&arr.u.m.acc_no);
		if(i==acc)
		break;
	}
	printf("\nACCOUNT NO. : %lld",arr.u.m.acc_no);
	printf("\nACCOUNT NAME : %s",arr.u.m.name);
	printf("\nREMAINING AMOUNT : %.2f",arr.u.m.amnt);
}

int cash_with(FILE *fp)
{
	int i;
	char ch;
	float r_amnt;
	struct info am;
	printf("ENTER AMOUNT : ");
	scanf("%f",&r_amnt);
	{
		for(i=0;i<arr_size;i++)
		{
			fgets(am.u.m.name,20,fp);
			fscanf(fp,"%s\n%f\n%lld\n\n",am.u.m.pin,&am.u.m.amnt,&am.u.m.acc_no);
			if(i==acc)
			break;
		}
	}
	if(r_amnt>am.u.m.amnt)
	{
		system("cls");
		printf("YOU DONT HAVE SUFFICIENT AMOUNT IN YOUR ACCOUNT\nTHANK YOU FOR  BANKING");
		exit(0);
	}
	am.u.m.amnt-=r_amnt;
	r_amnt=am.u.m.amnt;
	rewind(fp);
	FILE *fp2;
	fp2=fopen("MY PROJECT RECORD 2.txt","w");
	if(fp2==NULL)
	{
		printf("UNABLE TO OPEN");
		exit(0);
	}
	for(i=0;i<arr_size;i++)
	{
		
		if(i==acc)
		{
			fgets(am.u.m.name,20,fp);
			fputs(am.u.m.name,fp2);
			fscanf(fp,"%s\n%f\n%lld\n\n",am.u.m.pin,&am.u.m.amnt,&am.u.m.acc_no);
			fprintf(fp2,"%s\n%.2f\n%lld\n\n",am.u.m.pin,r_amnt,am.u.m.acc_no);
		}
		else
		{
		fgets(am.u.m.name,20,fp);
		fputs(am.u.m.name,fp2);
		fscanf(fp,"%s\n%f\n%lld\n\n",am.u.m.pin,&am.u.m.amnt,&am.u.m.acc_no);
		fprintf(fp2,"%s\n%.2f\n%lld\n\n",am.u.m.pin,am.u.m.amnt,am.u.m.acc_no);
		}
	}
	fclose(fp);
	fclose(fp2);
	remove("MY PROJECT RECORD.txt");
	rename("MY PROJECT RECORD 2.txt","MY PROJECT RECORD.txt");
		system("cls");
		printf("YOU WANT RECIEPT (Y / N)");
		ch=getch();
		if(ch=='y'||ch=='Y')
		{
			fp=fopen("MY PROJECT RECORD.txt","r");
			if(fp==NULL)
			{
				printf("UNABLE TO OPEN FILE");
				exit(0);
			}
			receipt(fp);
		}
		else
		{
			system("cls");
			printf("\nTHANK YOU FOR BANKING");
		}

}

void fund_trans(FILE *fp)
{
	char f_opt;
	int ft_acc,j,i;
	float t_amnt,tacc_amnt,tj_amnt;
	long long int f_acc;
	struct info fund;
	printf("ENTER THE ACCOUNT NO. TO WHICH YOU WANT TO TRANSFER :");
	scanf("%lld",&f_acc);
	for(j=0;j<arr_size;j++)
	{
		fgets(fund.u.m.name,20,fp);
		fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
		if(fund.u.m.acc_no==f_acc)
		{
			ft_acc=j;
			break;
		}
		else if(fund.u.m.acc_no!=f_acc&&j>=arr_size-1)
		{
			system("cls");
			printf("NO ACCOUNT FOUND ON THIS ACCOUNT NO. :");
			exit(0);
		}
	}
	rewind(fp);
	printf("ENTER THE AMOUNT YOU WANT TO TRANSFER :");
	scanf("%f",&t_amnt);
	for(j=0;j<arr_size;j++)
	{
		fgets(fund.u.m.name,20,fp);
		fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
		if(j==acc)
		{
			break;
		}
	}	
	if(t_amnt>fund.u.m.amnt)
	{
		system("cls");
		printf("YOU DONT HAVE SUFFICIENT AMOUNT IN YOUR ACCOUNT\nTHANK YOU FOR  BANKING");
		exit(0);
	}
	rewind(fp);
	for(j=0;j<arr_size;j++)
	{
		fgets(fund.u.m.name,20,fp);
		fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
		if(j==ft_acc)
		{
			break;
		}
	}	
	printf("ACCOUNT NAME : %s",fund.u.m.name);
	printf("\nACCOUNT NO. : %lld",f_acc);
	printf("\nYOU  WANT TO TRANFER %.2f ON THIS ACCOUNT (Y / N) : ",t_amnt);
	fflush(stdin);
	scanf("%c",&f_opt); 
	if(f_opt=='y'||f_opt=='Y')
	{
		rewind(fp);
		for(j=0;j<arr_size;j++)
		{
			fgets(fund.u.m.name,20,fp);
			fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
			if(j==ft_acc)
			{
				break;
			}
		}
		fund.u.m.amnt+=t_amnt;
		tj_amnt=fund.u.m.amnt;
		rewind(fp);
		for(j=0;j<arr_size;j++)
		{
			fgets(fund.u.m.name,20,fp);
			fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
			if(j==acc)
			{
				break;
			}
		}
		fund.u.m.amnt-=t_amnt;
		tacc_amnt=fund.u.m.amnt;

		printf("YOUR AMOUNT IS SUCCESSFULLY TRANSFER");
		rewind(fp);
		FILE *fp1;
		fp1=fopen("MY PROJECT RECORD 2.txt","w");
		if(fp1==NULL)
		{
			printf("FILE UNABLE TO OPEN");
			exit(0);
		}
		else
		{
			for(i=0;i<arr_size;i++)
			{
				if(i==acc)
				{
					fgets(fund.u.m.name,20,fp);
					fputs(fund.u.m.name,fp1);
					fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
					fprintf(fp1,"%s\n%.2f\n%lld\n\n",fund.u.m.pin,tacc_amnt,fund.u.m.acc_no);
					
				}
				else if(i==ft_acc)
				{
					fgets(fund.u.m.name,20,fp);
					fputs(fund.u.m.name,fp1);
					fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
					fprintf(fp1,"%s\n%.2f\n%lld\n\n",fund.u.m.pin,tj_amnt,fund.u.m.acc_no);
				}
				else
				{
					fgets(fund.u.m.name,20,fp);
					fputs(fund.u.m.name,fp1);
					fscanf(fp,"%s\n%f\n%lld\n\n",fund.u.m.pin,&fund.u.m.amnt,&fund.u.m.acc_no);
					fprintf(fp1,"%s\n%.2f\n%lld\n\n",fund.u.m.pin,fund.u.m.amnt,fund.u.m.acc_no);
				}
				
			}
			fclose(fp);
			fclose(fp1);
			remove("MY PROJECT RECORD.txt");
			rename("MY PROJECT RECORD 2.txt","MY PROJECT RECORD.txt");
		}
	}
	else
	{
		printf("\nTHANK YOU FOR BANKING");
		return ;
	}
}

void acc_no_gen(struct info acc_gen)
{
	long long int a=0;
	int n,arr_acc[4];
	char id;
	for(n=0;n<=3;n++)
	{
		arr_acc[n]=rand();
	}
	a+=arr_acc[0]*100000;
	a+=arr_acc[1];
	a=a*10000;
	a+=arr_acc[2];
	a=a*100000;
	a+=arr_acc[3];
	acc_gen.u.m.acc_no=a;
}


void create_acc(void)
{
	struct info arr;
	int a;
	char opt,n_name[20],n_pin[4],nacc_pin[4],ncacc_pin[4];
	float nacc_amnt;
	printf("ENTER ACCOUNT NAME :");
	fflush(stdin);
	gets(n_name);
	strcpy(arr.u.m.name,n_name);
	printf("ENTER PIN FOR YOUR ACCOUNT :");
	pins(nacc_pin);
	do
	{
		printf("ENTER CONFIRM PIN :");
		pins(ncacc_pin);
		a=strcmp(nacc_pin,ncacc_pin);
		if(a==0)
		{
			strcpy(arr.u.m.pin,ncacc_pin);
			break;
		}
		else
		{
			printf("YOUR CONFIRM PIN IS  INCORRECT  ENTER AGAIN :\n");
		}
		
	}while(a!=0);
	printf("ENTER AMOUNT TO DEPOSIT IN YOUR ACCOUNT (GREATER THAN 1000): ");
	scanf("%f",&nacc_amnt);
	if(nacc_amnt<1000)
	{
		do
		{
		printf("ENTER AMOUNT GREATER THAN 1000 \n");
		printf("YOU HAVE AMOUNT GREATER THAN 1000 OR NOT ? (Y / N) :");
		fflush(stdin);
		scanf("%c",&opt);
		if(opt=='Y'||opt=='y')
		{
			printf("ENTER AMOUNT : ");
			scanf("%f",&nacc_amnt);
		}
		else
		{
			printf("THANKS FOR BANKING ");
			exit(0);
		}
		}while(nacc_amnt<1000);
		arr.u.m.amnt=nacc_amnt;	
	}
	else
	{
		arr.u.m.amnt=nacc_amnt;
	}
	acc_no_gen(arr);
	FILE *fp;
	fp=fopen("MY PROJECT RECORD.txt","a+");
	if(fp==NULL)
	{
		printf("FILE UNABLE TO OPEN");
		exit(0);
	}
	else
	{
		printf("YOUR ACCOUNT HAS BEEN CREATED\n");
		printf("YOUR ACCOUNT NO. : %lld",arr.u.m.acc_no);
		fputs(arr.u.m.name,fp);
		fprintf(fp,"\n");
		fprintf(fp,"%s",arr.u.m.pin);
		fprintf(fp,"\n");
		fprintf(fp,"%f",arr.u.m.amnt);
		fprintf(fp,"\n");
		fprintf(fp,"%lld",arr.u.m.acc_no);
		fprintf(fp,"\n\n");
		fclose(fp);
		system("cls");
	
	}
}
int main()
{
	int j,a,b,counter=0;
	char opt,b_sys;
	struct info arr;
	printf("\t\tWELCOME TO FAST BANK LIMITED!\n");
	FILE *fptr;
	fptr=fopen("MY PROJECT RECORD.txt","r");
	if(fptr==NULL)
	{
		printf("UNABLE TO OPEN FILE");
		exit(0);
	}
	else
	{
	for(j=0;!feof(fptr);j++)
	{
		fgets(arr.u.m.name,20,fptr);
		fflush(stdin);
		fscanf(fptr,"%s\n%f\n%lld\n\n",arr.u.m.pin,&arr.u.m.amnt,&arr.u.m.acc_no);
		counter++;
	}
	arr_size=counter;
	fclose(fptr);
	printf("B- BANKING SYSTEM\nA- ATM\nE-EXIT\nWHERE YOU WANT TO GO : ");
	fflush(stdin);
	scanf("%c",&b_sys);
	if(b_sys=='A'||b_sys=='a')
	{
		system("cls");
		fptr=fopen("MY PROJECT RECORD.txt","r");
		if(fptr==NULL)
		{
		printf("UNABLE TO OPEN FILE");
		exit(0);
		}
		login(fptr);
		printf("A- CHANGE PIN\nB- RECIEPT\nC- CASH WITHDRAWL\nD- TRANSFER FUND ");
		fflush(stdin);
		printf("\nWHAT YOU WANT TO SELECT : ");
		scanf("\n%c",&opt);
		switch((opt=='a'||opt=='A')?1:(opt=='b'||opt=='B')?2:(opt=='c'||opt=='C')?3:(opt=='d'||opt=='D')?4:5)
		{
			case 1:
			{
				fptr=fopen("MY PROJECT RECORD.txt","r");
				if(fptr==NULL)
				{
				printf("UNABLE TO OPEN FILE");
				exit(0);
				}
				else
				{
				pin(fptr);
				break;
				}
			}
			case 2:
			{
				fptr=fopen("MY PROJECT RECORD.txt","r");
				if(fptr==NULL)
				{
				printf("UNABLE TO OPEN FILE");
				exit(0);
				}
				else
				{
				receipt(fptr);
				fclose(fptr);
				break;	
				}
			}
			case 3:
			{
				system("cls");
				fptr=fopen("MY PROJECT RECORD.txt","r");
				if(fptr==NULL)
				{
				printf("UNABLE TO OPEN FILE");
				exit(0);
				}
				else
				{
				cash_with(fptr);
				break;
				}
			}
			case 4:
			{
				system("cls");
				fptr=fopen("MY PROJECT RECORD.txt","r");
				if(fptr==NULL)
				{
				printf("UNABLE TO OPEN FILE");
				exit(0);
				}
				else
				{
				fund_trans(fptr);
				break;
				}
			}	
		}
	}
		else if(b_sys=='B'||b_sys=='b')
	{
		char b_opt;
		printf("C- CREATE ACCOUNT");
		printf("\nWHAT YOU WANT TO SELECT : ");
		fflush(stdin);
		scanf("%c",&b_opt);
		switch((b_opt=='C'||b_opt=='c')?1:5)
		{
			case 1:
			{
				system("cls");
				create_acc();
				main();
				}
			
			}
		}
		
	}
}
	
