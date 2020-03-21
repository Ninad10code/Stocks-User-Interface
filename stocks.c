//The data of stocks is for 3 consecutive days(dates)
//The first date and last date assumed to be same in all questions
//The date is an integer no. with only date to be entered as input no month and year is considered as input
//The input is to be followed as given in the input.txt file
#include<stdio.h>
#include<string.h>
//stocks structure
struct stocks
{
    float open,close,high,low,volm;
};
//Replica of stocks structure for sorting purpose
struct sort
{
    float open,close,high,low,volm,overAll;    
}sort[10];  
//Dates structure 
struct dates
{
    struct stocks S[10];
    struct sort sort[10];
    int first,last;
} D[10][3];

//function to calculate high performance of stocks
int highLowPerformance(struct dates D[][3],char stocks_names[][11],int spin,int epin)
{
    int i,j,posmax,posmin;
    float change,max=0,min=0,x=0;
    min=(((D[0][2].S[0].close)-(D[0][0].S[0].close))/(D[0][0].S[0].close))*100;
    posmin=0;
    for(i=0;i<10;i++)
    {
        change=(((D[i][epin].S[i].close)-(D[i][spin].S[i].close))/(D[i][spin].S[i].close))*100;    
        if(max<change)
        {
            max=change;
            posmax=i;
        }


        if(min>change)
        {
            min=change;
            posmin=i;
        }
    }
    
    printf("\nThe highest performing stock is %s with gain of %f %%\n",stocks_names[posmax],max);
    printf("The lowest performing stock is %s with loss of %f %%\n",stocks_names[posmin],min);
}

//function to calculate price change of stocks 
int price_change(struct dates D[][3],char stocks_names[][11],char name[][11],int spin,int epin)
{
    int i,j,posmax,posmin,found=0;
    float change,max=0,min=0;
    for(i=0;i<10;i++)
    {
        if(strcmp(strupr(name[1]),stocks_names[i])==0)
        {
            change=(((D[i][epin].S[i].close)-(D[i][spin].S[i].close))/(D[i][spin].S[i].close))*100;
            printf("%%change in price of %s stock is %f %%\n",stocks_names[i],change);
            found=1;
        }
    }
    if(found!=1)
    {
        printf("The stock name doesn't exist in the data please check the name of stock\n");
    }
    
}

//function to sort the stocks based on volume and for equal volume based on close price
int sortVolm_close(struct dates D[][3],int sdate,char stocks_names[][11],char text[][11])
{
    int i=0,j=0,sorted=0;
    float temp;
    char word[1][11];
    for(i=0;i<10;i++)
    {
        sort[i].open=D[i][sdate].S[i].open;
        sort[i].close=D[i][sdate].S[i].close;
        sort[i].high=D[i][sdate].S[i].high;
        sort[i].low=D[i][sdate].S[i].low;
        sort[i].volm=D[i][sdate].S[i].volm;
    }

    for(i=0;i<10;i++)
    {
        strcpy(text[i],stocks_names[i]);
    }

    for(j=0;(j<10-1) && (sorted==0);j++)
    {
        sorted=1;
        for(i=1;i<10-j;i++)
        {
            if(sort[i].volm < sort[i-1].volm)
            {
                temp=sort[i].volm;
                sort[i].volm=sort[i-1].volm;
                sort[i-1].volm=temp;

                temp=sort[i].open;
                sort[i].open=sort[i-1].open;
                sort[i-1].open=temp;

                temp=sort[i].close;
                sort[i].close=sort[i-1].close;
                sort[i-1].close=temp;
            
                temp=sort[i].high;
                sort[i].high=sort[i-1].high;
                sort[i-1].high=temp;

                temp=sort[i].low;
                sort[i].low=sort[i-1].low;
                sort[i-1].low=temp;

                strcpy(word[1],text[i]);
                strcpy(text[i],text[i-1]);
                strcpy(text[i-1],word[1]);
                
                sorted=0;
            }
            
        }
    }
    sorted=0;
    for(j=0;(j<10-1) && (sorted==0);j++)
    {
        sorted=1;
        for(i=1;i<10-j;i++)
        {
            if(sort[i].volm == sort[i-1].volm)
            {
                if(sort[i].close < sort[i-1].close)
                {
                    temp=sort[i].volm;
                    sort[i].volm=sort[i-1].volm;
                    sort[i-1].volm=temp;

                    temp=sort[i].open;
                    sort[i].open=sort[i-1].open;
                    sort[i-1].open=temp;

                    temp=sort[i].close;
                    sort[i].close=sort[i-1].close;
                    sort[i-1].close=temp;

                    temp=sort[i].high;
                    sort[i].high=sort[i-1].high;
                    sort[i-1].high=temp;

                    temp=sort[i].low;
                    sort[i].low=sort[i-1].low;
                    sort[i-1].low=temp;

                    strcpy(word[1],text[i]);
                    strcpy(text[i],text[i-1]);
                    strcpy(text[i-1],word[1]);        

                    sorted=0;
                }
            }
            
        }
    }
}

//function to calculate profit and loss of stocks

int  profit_loss(struct dates D[][3],int bd,int sd,char stocks_names[][11])
{
    int i;
    for(i=0;i<10;i++)
    {
        if(((D[i][sd].S[i].close)-(D[i][bd].S[i].open))>0)
        {
            printf("%s stock had a profit of %f\n",stocks_names[i],((D[i][sd].S[i].close)-(D[i][bd].S[i].open)));
        }
        else if(((D[i][sd].S[i].close)-(D[i][bd].S[i].open))<0)
        {
            printf("%s stock had a loss of %f\n",stocks_names[i],((D[i][sd].S[i].close)-(D[i][bd].S[i].open)));
        }
        else
        {
            printf("%s stock had neither profit nor loss\n",stocks_names[i]);
        }
    }
}

//function to calculate overall performance of stocks
int overallPerformance(struct dates D[][3],char stocks_names[][11],char text[][11],int spin,int epin)
{
    int i,j,sorted=0;
    float perchng=0,sum=0,tally,temp,m,n;
    char word[1][11];

    if(spin==0)
    {
        for(i=0;i<10;i++)
        {
            for(j=1;j<epin;j++)
            {
                tally=((((D[i][j].S[i].close)-(D[i][j-1].S[i].close))/(D[i][j-1].S[i].close))-perchng)*D[i][j].S[i].volm;
                perchng=((D[i][j].S[i].close)-(D[i][j-1].S[i].close))/(D[i][j-1].S[i].close);
                sum=sum+tally;          
            }
            sort[i].overAll=sum;
            perchng=0;
            sum=0;
        }
    }
    else
    {
        for(i=0;i<10;i++)
        {
            for(j=spin;j<epin;j++)
            {
                tally=((((D[i][j].S[i].close)-(D[i][j-1].S[i].close))/(D[i][j-1].S[i].close))-perchng)*D[i][j].S[i].volm;
                perchng=((D[i][j].S[i].close)-(D[i][j-1].S[i].close))/(D[i][j-1].S[i].close);
                sum=sum+tally;          
            }
            sort[i].overAll=sum;
            perchng=0;
            sum=0;
        }
    }
    

    for(i=0;i<10;i++)
    {
        strcpy(text[i],stocks_names[i]);
    }

    for(i=0;(i<10-1) && (sorted==0);i++)
    {
        sorted=1;
        for(j=0;j<10-1-i;j++)
        {
            if(sort[j].overAll>sort[j+1].overAll)
            {
                temp=sort[j].overAll;
                sort[j].overAll=sort[j+1].overAll;
                sort[j+1].overAll=temp;

                strcpy(word[1],text[j]);
                strcpy(text[j],text[j+1]);
                strcpy(text[j+1],word[1]); 

                sorted=0;
            }
        }
    }
}
//function to calculate average of average values of stocks price
int averageValue(struct dates D[][3],int spin,int epin)
{
    int i,j;
    float avg,avg_avg,tally,sum=0,v_sum=0,total=0;
    if(spin==0)
    {
        for(i=0;i<10;i++)
        {
            for(j=1;j<epin;j++)
            {
                tally=((((D[i][j].S[i].close)-(D[i][j-1].S[i].close))/(D[i][j-1].S[i].close)))*D[i][j].S[i].volm;
                sum=sum+tally;
                v_sum=v_sum+D[i][j].S[i].volm;
            }
            avg=sum/v_sum;
            total=total+avg;
            sum=0;
            v_sum=0;
        }
        avg_avg=total/10;
        printf("\nThe average of average values of stocks from start date to end date is %f\n",avg_avg);
    }
    else
    {
        for(i=0;i<10;i++)
        {
            for(j=spin;j<epin;j++)
            {
                tally=((((D[i][j].S[i].close)-(D[i][j-1].S[i].close))/(D[i][j-1].S[i].close)))*D[i][j].S[i].volm;
                sum=sum+tally;
                v_sum=v_sum+D[i][j].S[i].volm;
            }
            avg=sum/v_sum;
            total=total+avg;
            sum=0;
            v_sum=0;
        }
        avg_avg=total/10;
        printf("\nThe average of average values of stocks from start date to end date is %f\n",avg_avg);
    }
    
     
}

//main function
int main()
{
    int i,j,start=26,end=28,first,k,sdate,date,buyDate,sellDate,bd,sd,exit=0,action;
    int startdt,enddt,spin,epin;
    char stocks_names[11][11]={"SBIN","TATAMOTORS","PNB","YESBANK","TECHM","INFY","TCS","TITAN","ONGC","IOC"};
    char text[11][11],name[1][11];

    printf("The stocks data is from 26 to 28 October\n");
    first=start;

    //data is taken from the file and stored into the appropriate structure variable
    FILE *fp1;
    fp1=fopen("inputs.txt","r");
    for(i=0;i<10;i++)
    {
        
        for(j=0;j<3;j++)
        {
            D[i][j].first = first;
            fscanf(fp1,"%f",&D[i][j].S[i].open);
            fscanf(fp1,"%f",&D[i][j].S[i].close);
            fscanf(fp1,"%f",&D[i][j].S[i].high);
            fscanf(fp1,"%f",&D[i][j].S[i].low);
            fscanf(fp1,"%f",&D[i][j].S[i].volm);
            first++;
        }
        first=start;    
    }
    fclose(fp1);
    printf("\n");

    //Displays the entries of each stocks
    for(i=0;i<10;i++)
    {
        printf("Here are the entries of %s stock\n",stocks_names[i]);
        printf("Date\t");
        printf("Open_Price\t");
        printf("Close_Price\t");
        printf("High_Price\t");
        printf("Low_Price\t");
        printf("Volume\t");
        printf("\n");
        for(j=0;j<3;j++)
        {
            printf("%d\t",D[i][j].first);
            printf("%f\t",D[i][j].S[i].open);
            printf("%f\t",D[i][j].S[i].close);
            printf("%f\t",D[i][j].S[i].high);
            printf("%f\t",D[i][j].S[i].low);
            printf("%f\t",D[i][j].S[i].volm);
            printf("\n"); 
        }
        printf("\n\n");
    }

    //User interface created
    while(exit!=1)
    {
        printf("\nTHE STOCKS PORTAL\n");
        printf("1 %%change in price of stock\n");
        printf("2 To sort the stocks based on the volume\n");
        printf("3 To find profit or loss of stocks\n");
        printf("4 To find highest performing stock\n");
        printf("5  To list stocks as per increasing overall performance\n");
        printf("6 To find average of average values of all stocks\n");
        printf("7 To exit \n\n");
        printf("Please enter the respective no for following condition you want to check\n");
        scanf("%d",&action);
        switch(action)
        {
            case 1: printf("Enter the name of stock you want to see %% change for and also the start and end date\n");
                    scanf("%s %d %d",name[1],&startdt,&enddt);
                    spin=startdt-start;
                    epin=enddt-start;
                    printf("The %% change in price of stocks from %d to %d date is as followed\n",startdt,enddt);
                    price_change(D,stocks_names,name,spin,epin);
                    break;
            case 2: printf("\nEnter the date you want to see the stock sorted by volumes\n");
                    scanf("%d",&date);
                    sdate=date-start;
                    sortVolm_close(D,sdate,stocks_names,text);
                    printf("The sorted data wrt volume and close price on date %d is as follows\n",date);
                    for(i=0;i<10;i++)
                    {
                        printf("Here are the entries of %s stock\n",text[i]);
                        printf("Date\t");
                        printf("Open_Price\t");
                        printf("Close_Price\t");
                        printf("High_Price\t");
                        printf("Low_Price\t");
                        printf("Volume\t");
                        printf("\n");

                        printf("%d\t",D[i][sdate].first);
                        printf("%f\t",sort[i].open);
                        printf("%f\t",sort[i].close);
                        printf("%f\t",sort[i].high);
                        printf("%f\t",sort[i].low);
                        printf("%f\t",sort[i].volm);
                        printf("\n");
                    }
                    break;
            case 3: printf("\nEnter the buying and selling date of stocks\n");
                    scanf("%d %d",&buyDate,&sellDate);
                    printf("\n");
                    bd=buyDate-start;
                    sd=sellDate-start;
                    profit_loss(D,bd,sd,stocks_names);
                    printf("\n");
                    break;
            case 4: printf("\nEnter the start and end date to find the highest performing stock\n");
                    scanf("%d %d",&startdt,&enddt);
                    spin=startdt-start;
                    epin=enddt-start;
                    highLowPerformance(D,stocks_names,spin,epin);
                    printf("\n");
                    break;
            case 5: printf("\nEnter the start and end date to find the overall performace of stocks\n");
                    scanf("%d %d",&startdt,&enddt);
                    spin=startdt-start;
                    epin=enddt-start;
                    overallPerformance(D,stocks_names,text,spin,epin);
                    printf("The stocks as per overall performance is as follows\n");
                    for(i=0;i<10;i++)
                    {
                        printf("%s\t%f %%\n",text[i],sort[i].overAll);
                    }
                    break;
            case 6: printf("\nEnter the start and end date to find the average of average values of stocks\n");
                    scanf("%d %d",&startdt,&enddt);
                    spin=startdt-start;
                    epin=enddt-start;
                    averageValue(D,spin,epin);
                    break;
            case 7: exit=1;
                    printf("Thank you\n");
                    break;
            default :printf("Please enter a valid no\n");
        }
    }
}