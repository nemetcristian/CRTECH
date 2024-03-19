// #include "esphome/core/component.h"
// #include "esphome/core/helpers.h"
// #include "esphome/core/preferences.h"
// #include "esphome.h"

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>
// #include <BLE2902.h>

// namespace esphome {
// namespace esp32_ble_server {

// class ESP32BLECharacteristicCallback : public BLECharacteristicCallbacks {
//   void onWrite(BLECharacteristic *characteristic);
// };

// class ESP32BLEServerCallback: public BLEServerCallbacks {
//   void onConnect(BLEServer* pServer);
//   void onDisconnect(BLEServer* pServer);
// };

// class ESP32BLEServer : public Component {
//  public:
//   ESP32BLEServer();
//   void setup() override;
//   void loop() override;
//   void dump_config() override;
//   float get_setup_priority() const override;

//   BLEService* add_service(const char *uuid);

//  protected:

//   BLEServer *server_;
// };

// extern ESP32BLEServer *global_ble_server;

// }  // namespace esp32_ble_server
// }  // nameapsce esphome


// #ifndef VPORT_BLE_H
// #define VPORT_BLE_H

#include "esphome/core/component.h"
// #include "esp32_ble.h"

namespace esphome {
namespace Creavision_BLE {

class CreavisionBLEServer : public Component {
 public:
  void setup() override;
  void loop() override;

 private:
  static constexpr uint16_t SERVICE_UUID = 0x1000; // Change this to your service UUID
  static constexpr uint16_t CHAR_UUID_TX = 0x1001; // Change this to your TX characteristic UUID
  static constexpr uint16_t CHAR_UUID_RX = 0x1002; // Change this to your RX characteristic UUID

  uint16_t server_handle_ = 0;
  uint16_t char_handle_tx_ = 0;
  uint16_t char_handle_rx_ = 0;

  void init_ble();
  void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param);
  void notify_rx(const uint8_t *data, uint16_t size);

 public:
  void send_data(const uint8_t *data, uint16_t size);
};

}  // namespace vport
}  // namespace esphome

// #endif
