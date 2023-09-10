#include <stdio.h>
#include "driver_t2.h" // Asegúrate de incluir el archivo de encabezado BSP.h

void BSP_GPIO_Init(BSP_GPIO_Config* config) {
    // Verificar si la configuración es válida (puede agregar más validaciones según sea necesario)
    if (config == 0) {
        // Manejar el error o salir de la función si la configuración no es válida
        return;
    }
    // Configurar el pin GPIO según la configuración proporcionada
    gpio_config_t gpioConfig;
    gpioConfig.pin_bit_mask = (1ULL << config->gpio_pin);
    gpioConfig.mode = config->mode;
    gpioConfig.pull_up_en = config->pull_up_en;
    gpioConfig.pull_down_en = config->pull_down_en;
    gpioConfig.intr_type = config->intr_type;
    gpio_config(&gpioConfig);
}
