#ifndef driver_t2_h
#define driver_t2_h

#include "driver/gpio.h"
#include "driver/adc.h"
#include "driver/i2c.h"

// Estructura para la configuración de GPIO
typedef struct {
    gpio_pullup_t pull_up_en;       /*!< GPIO pull-up                                         */
    gpio_pulldown_t pull_down_en;   /*!< GPIO pull-down                                       */
    gpio_int_type_t intr_type;      /*!< GPIO interrupt type                                  */
    gpio_num_t gpio_pin;
    gpio_mode_t mode;
} BSP_GPIO_Config;

// Estructura para la configuración de ADC
typedef struct {
    adc1_channel_t channel;
    adc_atten_t atten;
} BSP_ADC_Config;

// Estructura para la configuración de I2C
typedef struct {
    i2c_port_t i2c_port;
    i2c_config_t i2c_config;
} BSP_I2C_Config;

// Funciones de inicialización y configuración
void BSP_Init(void);
void BSP_GPIO_Init(BSP_GPIO_Config* config);
void BSP_ADC_Init(BSP_ADC_Config* config);
void BSP_I2C_Init(BSP_I2C_Config* config);

// Otras funciones BSP según sea necesario

#endif // BSP_H
