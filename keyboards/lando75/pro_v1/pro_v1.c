
#include "app_ble_func.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "lando75.h"
// #include "custom_board.h"
#define POWER_PIN GPIO(1,9)


bool has_usb(void) {
  return (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED
    || nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY);
}

// static bool ble_flag = false;

void nrfmicro_power_enable(bool enable) {

  if (has_usb())
      enable = true;

  if (enable) {
    nrf_gpio_pin_set(POWER_PIN);
    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_write(POWER_PIN, 0);
  } else {
    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_clear(POWER_PIN); // works
    //input with pull-up consumes less than without it when pin is open (Hasu)
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLUP); // doesn't seem to work
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_NOPULL); // neither this
    //nrf_gpio_cfg_input(POWER_PIN, NRF_GPIO_PIN_PULLDOWN); // or this
  }
}

// uint8_t nrfmicro_switch_pin(void) {
//   uint8_t value = nrf_gpio_pin_read(SWITCH_PIN);
//   return value;
// }


// void check_ble_switch(bool init) {

//   // uint8_t value = nrfmicro_switch_pin();

//   // if (init || ble_flag != value) {
//   //   ble_flag = value;

//     // mind that it doesn't disable BLE completely, it only disables send
//     set_usb_enabled(!ble_flag);
//     set_ble_enabled(ble_flag);

//     nrf_gpio_pin_clear(LED_PIN);

//     if (ble_flag) {
//       // blink twice on ble enabled
//       for (int i=0; i<2; i++) {
//         nrf_gpio_pin_set(LED_PIN);
//         nrf_delay_ms(100);
//         nrf_gpio_pin_clear(LED_PIN);
//         nrf_delay_ms(100);
//       }
//     }
//   }
// }

void nrfmicro_init(void) {

  // configure pins
  nrf_gpio_cfg_output(POWER_PIN);
  // nrf_gpio_cfg_output(LED_PIN);
  // nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);

  nrfmicro_power_enable(true);
  // check_ble_switch(true);
}

void matrix_init_user() {

// nrfmicro_init();

    nrf_gpio_cfg_output(POWER_PIN);
    nrf_gpio_pin_clear(POWER_PIN);
    // nrf_gpio_pin_write(POWER_PIN, 0);
  set_usb_enabled(true);
  eeconfig_update_rgblight_default();
  rgblight_enable();
}
