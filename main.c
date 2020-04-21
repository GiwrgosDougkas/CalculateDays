#include <stdio.h>
#include <stdlib.h>


typedef struct{
  unsigned char Min,Sec,Hour,Day,DOW,Month;
  unsigned short Year;
} TimeDate;

unsigned long RtcConvTimeDateToSec(TimeDate Td){
    TimeDate referenceDate={0,0,0,1,1,1,2000};
    int sec1=referenceDate.Sec,min1=referenceDate.Min,hour1=referenceDate.Hour,day1=referenceDate.Day, mon1=referenceDate.Month, year1=referenceDate.Year;
    int sec2=Td.Sec,min2=Td.Min,hour2=Td.Hour,day2=Td.Day, mon2=Td.Month, year2=Td.Year;
    int days=0, day_diff=0,hour_diff=0,min_diff=0,sec_diff=0;
    int monthDaysReference[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int monthDaysTd[]={31,28,31,30,31,30,31,31,30,31,30,31};
    unsigned long seconds=0;
    int flag=1;
    int i=referenceDate.Month-1;// when the starting date is >1; we want to start count from monthDaysReference[i]

    if (hour2 < hour1)
    {
        hour2 += 24;
        day2 -= 1;
    }
    if (min2 < min1)
    {
        min2 +=60;
        hour2 -= 1;
    }
    if (sec2 < sec1)
    {
        sec2 +=60;
        min2 -= 1;
    }

    if(day2 < day1)
        {
        // borrow days from february
        if (mon2 == 3)
        {   //  check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
            {
                day2 += 29;

            }
            else{
                day2 += 28;

            }
        }

        // borrow days from April or June or September or November
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
        {
           day2 += 30;
        }

        // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
        {
           day2 += 31;
        }

        mon2 -= 1;
    }

    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }

    while(1){
        if ((year1 % 4 == 0 && year1 % 100 != 0) || (year1 % 400 == 0))
        {
                monthDaysReference[1]=29;
        }
        else{
                monthDaysReference[1]=28;
        }
        if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
        {
                monthDaysTd[1]=29;
        }
        else{
                monthDaysTd[1]=28;
        }

        if(year1==referenceDate.Year && year1==year2 &&mon2!=mon1){
             for(int i=mon1-1; i<mon2-1; i++){
                        days+=monthDaysReference[i];
            }
            break;

        }


        if(year1==year2){
                    for(int i=0; i<mon2-1; i++){
                        days+=monthDaysTd[i];
                    }
                    break;

        }

        for(i; i<12; i++){
            days+=monthDaysReference[i];
        }
        i=0;//for next year we want start from monthDaysReference[0];

        year1++;
    }

    seconds=(days+(day2-day1))*86400+(hour2-hour1)*3600+(min2-min1)*60+sec2-sec1;

    printf("Days:%d\n",(days+(day2-day1)));
    printf("Hours:%d\n",(hour2-hour1));
    printf("Min:%d\n",min2-min1);
    printf("Sec:%d\n",sec2-sec1);

    return seconds;
}

unsigned long RtcConvTimeDateToSec1(TimeDate Td){
    TimeDate referenceDate={0,0,0,1,1,1,2000};
    int day1=referenceDate.Day,mon1=referenceDate.Month,year1=referenceDate.Year;
    int sec2=Td.Sec,min2=Td.Min,hour2=Td.Hour,day2=Td.Day, mon2=Td.Month, year2=Td.Year;
    int days=0;
    int monthDaysReference[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int monthDaysTd[]={31,28,31,30,31,30,31,31,30,31,30,31};
    unsigned long seconds=0;
    int i=referenceDate.Month-1;

    while(1){
        if ((year1 % 4 == 0 && year1 % 100 != 0) || (year1 % 400 == 0))
        {
                monthDaysReference[1]=29;
        }
        else{
                monthDaysReference[1]=28;
        }
        if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
        {
                monthDaysTd[1]=29;
        }
        else{
                monthDaysTd[1]=28;
        }

        if(year1==year2){
            for(int i=0; i<mon2-1; i++)
                {
                    days+=monthDaysTd[i];
                }

            break;
        }

        for(i; i<12; i++){
            days+=monthDaysReference[i];
        }
        i=0;//for next year we want start from monthDaysReference[0];
        year1++;
    }
    seconds=(days+(day2-day1))*86400+hour2*3600+min2*60+sec2;

    printf("Days:%d\n",days+(day2-day1));
    printf("Hours:%d\n",(hour2));
    printf("Min:%d\n",min2);
    printf("Sec:%d\n",sec2);

    return seconds;
}
int RtcConvTimeDateToSecRecursion(TimeDate Td){
    TimeDate referenceDate={0,0,0,1,1,2,2020};
    int monthDaysReference[]={31,29,31,30,31,30,31,31,30,31,30,31};
    int monthDaysTd[]={31,29,31,30,31,30,31,31,30,31,30,31};
    int days=0;
    int sec1=referenceDate.Sec,min1=referenceDate.Min,hour1=referenceDate.Hour,day1=referenceDate.Day,mon1=referenceDate.Month,year1=referenceDate.Year;
    int year2=Td.Year;
    unsigned long sec=0;

    TimeDate td={Td.Min,Td.Sec,Td.Hour,Td.Day,Td.DOW,Td.Month,Td.Year+1};

    if(year1>year2)
    {
        if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
        {
                monthDaysTd[1]=29;
        }
        else{
                monthDaysTd[1]=28;
        }
        for(int i=0; i<12; i++){
            days+=monthDaysTd[i];
        }
        return days+RtcConvTimeDateToSecRecursion(td);
    }

    if(year1==year2)
    {
         for(int i=0; i<mon1-1; i++)
        {
            days+=monthDaysTd[i];
        }
        return days+referenceDate.Day-Td.Day;
    }

    return 0;
}

unsigned int CalculateDaysWithArray(TimeDate Td){
    TimeDate referenceDate={0,0,0,1,1,1,2000};
    int monthDaysReference[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int year=Td.Year, month=Td.Month;
    int Array[12][Td.Year-referenceDate.Year];
    int yearIncrease=referenceDate.Year;
    int days=0;
    for(int i=0; i<Td.Year-referenceDate.Year; i++){

         if ((yearIncrease % 4 == 0 && yearIncrease % 100 != 0) || (yearIncrease % 400 == 0))
        {
                monthDaysReference[1]=29;
        }
        else{
                monthDaysReference[1]=28;
        }
        for(int j=0; j<12;j++){
            Array[i][j]=monthDaysReference[j];

        }
        yearIncrease++;
    }

     if ((Td.Year % 4 == 0 && Td.Year % 100 != 0) || (Td.Year % 400 == 0))
        {
                monthDaysReference[1]=29;
        }
        else{
                monthDaysReference[1]=28;
        }

    for(int i=0; i<Td.Month-1; i++){
        days+=monthDaysReference[i];
    }

    for(int i=0; i<Td.Year-referenceDate.Year; i++){
        for(int j=0; j<12; j++){
            days+=Array[i][j];
        }
    }
    return days;

}

int main()
{
    TimeDate endDate={0,0,0,1,1,3,2003};
    printf("%d",CalculateDaysWithArray(endDate));
    int day,month, year, hours,min,sec,leap;
    int monthDaysReference[]={31,28,31,30,31,30,31,31,30,31,30,31};
   /* printf("Give year:");
    scanf("%d",&year);
    //cehck for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
                monthDaysReference[1]=29;
        }
        else{
                monthDaysReference[1]=28;
        }

    printf("Give month:");
    scanf("%d",&month);
    //check for month overflow;
    if(month<=0 || month>12){
        do{
            printf("Give month:");
            scanf("%d",&month);
        }while(month<=0 || month>12);
    }

    printf("Give day:");
    scanf("%d",&day);
    //Check for day overflow;
    if(day>monthDaysReference[month-1]){
         do{
            printf("%d max days ",monthDaysReference[month-1]);
            scanf("%d",&day);
        }while(day>monthDaysReference[month-1]);
    }

    printf("Give hour(0-24):");
    scanf("%d",&hours);
    //check for hour overflow
    if(hours<0 || hours>23){
         do{
            printf("Give hour(0-23):");
            scanf("%d",&hours);
        }while(hours<0 || hours>23);
    }

    printf("Give min(0-59):");
    scanf("%d",&min);
    //check for min overflow
    if(min<0 || min>59){
         do{
             printf("Give min:");
            scanf("%d",&min);
        }while(min<0 || min>59);
    }

    printf("Give sec(0-59):");
    scanf("%d",&sec);
    //check for sec overflow
    if(sec<0 || sec>59){
         do{
             printf("Give sec:");
            scanf("%d",&sec);
        }while(sec<0 || sec>59);
    }
    TimeDate Td={min,sec,hours,day,1,month,year};
    printf("%d:",RtcConvTimeDateToSec(Td));*/

    /*TimeDate Td={44,0,18,16,1,4,2022};
    TimeDate forRecursion={0,0,0,1,1,1,2000};
    TimeDate endDate={0,0,0,1,1,1 ,2001};
    TimeDate referenceDate={20,0,8,12,1,2,2002};
    printf("Total seconds:%d\n",RtcConvTimeDateToSec(endDate));
    printf("Total seconds:%d\n",RtcConvTimeDateToSec1(endDate));
    printf("Total sconds:%d",RtcConvTimeDateToSecRecursion(forRecursion));*/
    return 0;
}
