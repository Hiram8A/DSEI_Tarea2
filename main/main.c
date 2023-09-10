#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver_t2.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define ESP_INTR_FLAG_DEFAULT 0

static xQueueHandle gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task_example(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY)) {
            printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
        }
    }
}

void app_main(void)
{
	BSP_GPIO_Config io_conf = {};
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	io_conf.gpio_pin = GPIO_NUM_18;
	io_conf.mode = GPIO_MODE_OUTPUT;
	BSP_GPIO_Init(&io_conf);

	io_conf.intr_type = GPIO_INTR_POSEDGE;
	io_conf.gpio_pin = GPIO_NUM_4;
	io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = 1;
    BSP_GPIO_Init(&io_conf);

	//change gpio intrrupt type for one pin
	gpio_set_intr_type(GPIO_NUM_4, GPIO_INTR_ANYEDGE);

	//create a queue to handle gpio event from isr
	gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
	//start gpio task
	xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

	//install gpio isr service
	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	//hook isr handler for specific gpio pin
	gpio_isr_handler_add(GPIO_NUM_4, gpio_isr_handler, (void*) GPIO_NUM_4);

	//remove isr handler for gpio number.
	gpio_isr_handler_remove(GPIO_NUM_4);
	//hook isr handler for specific gpio pin again
	gpio_isr_handler_add(GPIO_NUM_4, gpio_isr_handler, (void*) GPIO_NUM_4);

	printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

	int cnt = 0;
	while(1) {
	   printf("cnt: %d\n", cnt++);
	   vTaskDelay(1000 / portTICK_RATE_MS);
	   gpio_set_level(GPIO_NUM_18, cnt % 2);
	}
}
