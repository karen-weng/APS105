#include <stdio.h>
#include <math.h>
int main(void) {
    double dailyRate;
    int numDays;
    int freeDays;
    double totalCharge;
    const double HST = 1.13;
    // Get the daily rate
    printf("Enter the daily rate: ");
    scanf("%lf", &dailyRate);
    // Get the number of rental days
    printf("Enter the rental period (in days): ");
    scanf("%d", &numDays);
    // Compute the free days;
    freeDays = floor(numDays / 4);
    printf("\nYour total free day(s) in this rental is: %d", freeDays);
    // Compute the total charge tax inclusive
    totalCharge = (HST) * (numDays - freeDays) * dailyRate;
    printf("\nThe total charge including taxes is: %.2f\n", totalCharge);
    return 0;
}
