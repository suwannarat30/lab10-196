#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "LED.h"

// กำหนด LED แต่ละดวง
LED ledA(GPIO_NUM_16); 
LED ledB(GPIO_NUM_17); 
LED ledC(GPIO_NUM_5); 
LED ledD(GPIO_NUM_18); 
LED ledE(GPIO_NUM_19); 
LED ledF(GPIO_NUM_21); 
LED ledG(GPIO_NUM_22); 
LED ledH(GPIO_NUM_23); 

LED* ledArray[] = {&ledA, &ledB, &ledC, &ledD, &ledE, &ledF, &ledG, &ledH};
const int LED_COUNT = sizeof(ledArray) / sizeof(ledArray[0]);

// ฟังก์ชันปิด LED ทุกดวง
void turnAllOff() {
    for (int i = 0; i < LED_COUNT; i++) ledArray[i]->OFF();
}

// ฟังก์ชันพิมพ์ pattern ลง Serial Monitor
void showPattern(int idx1, int idx2 = -1) {
    for (int i = 0; i < LED_COUNT; i++) {
        if (i == idx1 || i == idx2) printf("*");
        else printf(".");
    }
    printf("\n");
}

extern "C" void app_main(void)
{
    while (true) {

        // ---------------------------
        // 1) ไฟวิ่งดวงเดียว
        // ---------------------------
        for (int i = 0; i < LED_COUNT; i++) {
            turnAllOff();
            ledArray[i]->ON();
            showPattern(i);
            vTaskDelay(pdMS_TO_TICKS(200));
        }

        // ---------------------------
        // 2) ไฟวิ่งสองดวงสวนกัน
        // ---------------------------
        for (int step = 0; step < LED_COUNT; step++) {
            turnAllOff();
            int leftIdx = step;
            int rightIdx = LED_COUNT - 1 - step;
            ledArray[leftIdx]->ON();
            ledArray[rightIdx]->ON();
            showPattern(leftIdx, rightIdx);
            vTaskDelay(pdMS_TO_TICKS(200));
            if (leftIdx >= rightIdx) break;
        }

        // กลับออก
        for (int step = LED_COUNT / 2 - 1; step >= 0; step--) {
            turnAllOff();
            int leftIdx = step;
            int rightIdx = LED_COUNT - 1 - step;
            ledArray[leftIdx]->ON();
            ledArray[rightIdx]->ON();
            showPattern(leftIdx, rightIdx);
            vTaskDelay(pdMS_TO_TICKS(200));
        }

        // ---------------------------
        // 3) ไฟวิ่งไปกลับ (Knight Rider)
        // ---------------------------
        // ไปขวา
        for (int i = 0; i < LED_COUNT; i++) {
            turnAllOff();
            ledArray[i]->ON();
            showPattern(i);
            vTaskDelay(pdMS_TO_TICKS(150));
        }
        // กลับซ้าย
        for (int i = LED_COUNT - 2; i > 0; i--) {
            turnAllOff();
            ledArray[i]->ON();
            showPattern(i);
            vTaskDelay(pdMS_TO_TICKS(150));
        }
    }
}
