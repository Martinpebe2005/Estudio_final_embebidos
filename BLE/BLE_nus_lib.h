#ifndef BLE_NUS_LIB_H
#define BLE_NUS_LIB_H

// ─────────────────────────────────────────────────────────────
// ble_nus_init()
// Inicializa BLE NUS, advertising, GATT y el GPIO del LED.
// ─────────────────────────────────────────────────────────────
void ble_nus_init(void);

// ─────────────────────────────────────────────────────────────
// ble_nus_send_response()
// Envía texto por la característica TX usando Notify.
// ─────────────────────────────────────────────────────────────
void ble_nus_send_response(const char *msg);

#endif