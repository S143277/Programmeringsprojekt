#include "timer.h"


void init_timer(uint16_t priority) {

    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    TIM2->CR1 = 0x0000; // Disable time
    TIM2->ARR = 639999; // Set auto reload value (100e-2*64e6)-1
    TIM2->PSC = 0;
    TIM2->DIER |=0x0001;
    NVIC_SetPriority(TIM2_IRQn, priority);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= 0x0001; // enable time
}

void time(struct interrupt_t *t){
    t->h = 0;
    t->m = 0;
    t->s = 0;
    t->hs = 0;
}

void TIM2_IRQHandler(void){

  //  printf("kris da noda jedi master son of Goku\n");
    TIM2->SR &= ~0x0001; // clear interrupt bit
    t.hs++;
    if (t.hs == 100){
    t.hs=0;
    t.s++;
    }
    if (t.s==60){
    t.s=0;
    t.m++;
    }
    if (t.m==60){
    t.m=0;
    t.h++;
    }
}

void init_stopwatch(){
    gotoxy(1,1);
    window(1, 1, 31, 6, "Stop watch");
    gotoxy(2,3);
    printf("Time since start: ");
    gotoxy(2,4);
    printf("Split time 1:");
    gotoxy(2,5);
    printf("Split time 2:");

}
void stopwatch_joystick(uint8_t *ss, uint8_t *push){


        // Print time since start
        if ((t.s < 10) && (t.m <10 )){
        gotoxy(20,3);
        printf("%d:0%d:0%d.%d",t.h,t.m,t.s,t.hs);
        }
        else if (t.s < 10){
        gotoxy(20,3);
        printf("%d:%d:0%d.%d",t.h,t.m,t.s,t.hs);
        }
        else if (t.m < 10){
        gotoxy(20,3);
        printf("%d:0%d:%d.%d",t.h,t.m,t.s,t.hs);
        }
        else {
        gotoxy(20,3);
        printf("%d:%d:%d.%d",t.h,t.m,t.s,t.hs);
        }


        // Print Split time 1
        uint8_t val = readJoystick();
        if (val == 4){

            if ((t.s < 10) && (t.m <10 )){
            gotoxy(20,4);
            printf("%d:0%d:0%d.%d",t.h,t.m,t.s,t.hs);
            }
            else if (t.s < 10){
            gotoxy(20,4);
            printf("%d:%d:0%d.%d",t.h,t.m,t.s,t.hs);
            }
            else if (t.m < 10){
            gotoxy(20,4);
            printf("%d:0%d:%d.%d",t.h,t.m,t.s,t.hs);
            }
            else {
            gotoxy(20,4);
            printf("%d:%d:%d.%d",t.h,t.m,t.s,t.hs);
            }
        }
        else if (val == 8){
            if ((t.s < 10) && (t.m <10 )){
            gotoxy(20,5);
            printf("%d:0%d:0%d.%d",t.h,t.m,t.s,t.hs);
            }
            else if (t.s < 10){
            gotoxy(20,5);
            printf("%d:%d:0%d.%d",t.h,t.m,t.s,t.hs);
            }
            else if (t.m < 10){
            gotoxy(20,5);
            printf("%d:0%d:%d.%d",t.h,t.m,t.s,t.hs);
            }
            else {
            gotoxy(20,5);
            printf("%d:%d:%d.%d",t.h,t.m,t.s,t.hs);
            }

        }
        else if (val == 16){

            if (*ss==1 && *push ==0){
                __disable_irq();
                *ss=0;
                *push = 1;
            }
            else if (*ss==0 && *push == 0) {
                __enable_irq();
                *ss=1;
                *push = 1;
            }
        }
        else if (val == 0){
           *push = 0;
        }
        else if (val == 2){
            time(&t);
            gotoxy(20,3);
            printf("%d:0%d:0%d.0%d",t.h,t.m,t.s,t.hs);
            *ss=1;
        }
}
