#include <stdio.h>
#include "uartCommand.h"

#include "sdkconfig.h"
#include "esp_log.h"

#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define COMMAND_TEST_TXD (CONFIG_COMMAND_UART_TXD)
#define COMMAND_TEST_RXD (CONFIG_COMMAND_UART_RXD)
#define COMMAND_TEST_RTS (UART_PIN_NO_CHANGE)
#define COMMAND_TEST_CTS (UART_PIN_NO_CHANGE)

#define COMMAND_UART_PORT_NUM      (CONFIG_COMMAND_UART_PORT_NUM)
#define COMMAND_UART_BAUD_RATE     (CONFIG_COMMAND_UART_BAUD_RATE)


static const char *TAG_UART2 = "UART TEST";

static char *NAME_UART_COMMAND = "UART";
static char *TYPE_UART_COMMAND  = "2";

unsigned char *s;

unsigned int length = 1024;

static QueueHandle_t queue;
char txBuffer[BUF_SIZE];

void command_uart_task(void *arg){

    
    queue = xQueueCreate(5, sizeof(txBuffer));

    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = COMMAND_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ESP_ERROR_CHECK(uart_driver_install(COMMAND_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(COMMAND_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(COMMAND_UART_PORT_NUM, COMMAND_TEST_TXD, COMMAND_TEST_RXD, COMMAND_TEST_RTS, COMMAND_TEST_CTS));

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    for(;;) {

        // Read data from the UART
        int len = uart_read_bytes(COMMAND_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        // Write data back to the UART
        uart_write_bytes(COMMAND_UART_PORT_NUM, (const char *) data, len);
        if (len) {
            data[len] = '\0';
            //ESP_LOGI(TAG_UART2, "Recv str: %s", (char *) data);
            sprintf(txBuffer, "%s",data);
            xQueueSend(queue, (void*)txBuffer, (TickType_t)0);
        }
        if (queue == 0) {
            ESP_LOGE(TAG_UART2, "Échec de la création de la queue\n");
        }
    }
}

QueueHandle_t getQueueUart2(void){
    return queue;
}