// ─────────────────────────────────────────────────────────────
// MAIN BLE NUS
// Inicializa la librería BLE NUS.
// Comandos desde nRF Connect:
// E -> enciende LED
// A -> apaga LED
// ─────────────────────────────────────────────────────────────

#include "ble_nus_lib.h"

// ─────────────────────────────────────────────────────────────
// app_main()
// Punto de entrada del programa.
// Toda la lógica BLE está dentro de ble_nus_lib.c.
// ─────────────────────────────────────────────────────────────

void app_main(void)
{
    ble_nus_init();
}