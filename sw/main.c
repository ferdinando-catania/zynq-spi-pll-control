#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xgpiops.h"    
#include "xgpio.h"      
#include "xil_printf.h"
#include "sleep.h"

#define PB1_MIO 50 
#define PB2_MIO 51

int main() {
    init_platform();

    XGpioPs ps_instance;
    XGpio pl_instance;
    XGpioPs_Config *ps_config;

    ps_config = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_BASEADDR);
    XGpioPs_CfgInitialize(&ps_instance, ps_config, ps_config->BaseAddr);
    XGpioPs_SetDirectionPin(&ps_instance, PB1_MIO, 0);
    XGpioPs_SetDirectionPin(&ps_instance, PB2_MIO, 0);

    XGpio_Initialize(&pl_instance, XPAR_XGPIO_0_BASEADDR);
    XGpio_SetDataDirection(&pl_instance, 1, 0x00); 

    // Pulisci lo schermo e resetta il cursore nel terminale
    xil_printf("\033[2J\033[H"); 
    xil_printf("--- Sistema di controllo PLL avviato ---\r\n");

    u32 btn1, btn2;
    u32 btn1_prev = 0;
    u32 btn2_prev = 0;

    while(1) {
        btn1 = XGpioPs_ReadPin(&ps_instance, PB1_MIO);
        btn2 = XGpioPs_ReadPin(&ps_instance, PB2_MIO);

        // Gestione Messaggi con "Debounce" e flush
        if (btn1 == 1 && btn1_prev == 0) {
            xil_printf("PLL: Configurazione 1 caricata\r\n");
            usleep(20000); // Pausa per permettere alla UART di svuotare il buffer
        }
        
        if (btn2 == 1 && btn2_prev == 0) {
            xil_printf("PLL: Configurazione 2 caricata\r\n");
            usleep(20000);
        }

        // Logica LED
        u32 led_data = 0;
        if (btn1) led_data |= 0x02; // PB1 -> LD1
        if (btn2) led_data |= 0x01; // PB2 -> LD0
        XGpio_DiscreteWrite(&pl_instance, 1, led_data);

        btn1_prev = btn1;
        btn2_prev = btn2;

        usleep(50000); // Aumentato a 50ms per stabilità totale
    }

    cleanup_platform();
    return 0;
}