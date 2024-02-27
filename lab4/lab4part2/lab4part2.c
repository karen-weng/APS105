#include <stdio.h>
#include <stdlib.h>

int countLuckyNumbers() {
    int luckyCount = 0;
    int numInput;
    printf("Input an integer: ");
    scanf("%d", &numInput);
    while ( numInput != 0) {
        int sevenCount = 0;
        int eachNum = abs(numInput);
        while (eachNum > 0) {
            if (eachNum % 10 == 7) {
                sevenCount++;
            }
            eachNum /= 10;
        }
        
        if (sevenCount == 3) {
            luckyCount++;
        }
        printf("Input an integer (0 to stop): ");
        scanf("%d", &numInput);
    }
    return luckyCount;
}

int main(void) {
    int lucky_count = countLuckyNumbers();    
    printf("You entered %d lucky number(s)!\n", lucky_count);
    return 0;
}
