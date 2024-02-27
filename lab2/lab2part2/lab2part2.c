#include <stdio.h>

int main(void)
{
    int currentTimeHour, arrivalTimeHour;
    double currentTimeMin, arrivalTimeMin, currentTime, tripTime, arrivalTime;

    printf("Enter current time: ");
    scanf("%d %lf", &currentTimeHour, &currentTimeMin);

    printf("Enter trip time: ");
    scanf("%lf", &tripTime);

    currentTime = currentTimeHour + (currentTimeMin / 60);
    arrivalTime = currentTime + tripTime;

    printf("Current time is %d:%.0lf\n", currentTimeHour, currentTimeMin);

    arrivalTimeHour = (int)arrivalTime;
    arrivalTimeMin = (arrivalTime - arrivalTimeHour) * 60;

    if (arrivalTimeHour < 24)
    {
        printf("Arrival Time is same day %02d:%.0lf ", arrivalTimeHour, arrivalTimeMin);
    }

    else
    {
        arrivalTimeHour = arrivalTimeHour - 24;
        printf("Arrival Time is next day %02d:%.0lf ", arrivalTimeHour, arrivalTimeMin);
    }

    return 0;
}
