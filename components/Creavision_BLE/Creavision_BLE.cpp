
#include "Creavision_BLE.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/version.h"
#include "esphome/core/component.h"
#include "esphome.h"

namespace esphome {
namespace Creavision_BLE {

// // #ifdef ARDUINO_ARCH_ESP32

// // namespace esphome {
// // namespace esp32_ble_server {

// static const char *TAG = "esp32_ble_server";

// static const char *DEVICE_INFORMATION_SERVICE_UUID = "180A";
// static const char *VERSION_UUID = "2A26";
// static const char *MANUFACTURER_UUID = "2A29";


// ESP32BLEServer::ESP32BLEServer() { global_ble_server = this; }

// void ESP32BLEServer::setup() {
//   BLEDevice::init(App.get_name());
//   this->server_ = BLEDevice::createServer();
//   this->server_->setCallbacks(new ESP32BLEServerCallback());

//   BLEService *device_information_service = this->server_->createService(DEVICE_INFORMATION_SERVICE_UUID);
//   BLECharacteristic *version = device_information_service->createCharacteristic(
//                                   VERSION_UUID,
//                                   BLECharacteristic::PROPERTY_READ
//                                 );
//   version->setValue(ESPHOME_VERSION);
//   BLECharacteristic *manufacturer = device_information_service->createCharacteristic(
//                                   MANUFACTURER_UUID,
//                                   BLECharacteristic::PROPERTY_READ
//                                 );
//   manufacturer->setValue("ESPHome");
//   device_information_service->start();

//   BLEAdvertising *advertising = BLEDevice::getAdvertising();
//   advertising->setScanResponse(true);
//   advertising->setMinPreferred(0x06);

//   BLEDevice::startAdvertising();
// }

// void ESP32BLEServer::loop() {

// }

// BLEService* ESP32BLEServer::add_service(const char* uuid) {
//   ESP_LOGD(TAG, "Adding new BLE service");
//   BLEService *service = this->server_->createService(uuid);

//   BLEAdvertising *advertising = BLEDevice::getAdvertising();
//   advertising->addServiceUUID(uuid);

//   return service;
// }

// float ESP32BLEServer::get_setup_priority() const { return setup_priority::HARDWARE; }

// void ESP32BLEServer::dump_config() { ESP_LOGCONFIG(TAG, "ESP32 BLE Server:"); }

// void ESP32BLEServerCallback::onConnect(BLEServer* pServer) {
//   ESP_LOGD(TAG, "BLE Client connected");
// }

// void ESP32BLEServerCallback::onDisconnect(BLEServer* pServer) {
//   ESP_LOGD(TAG, "BLE Client disconnected");
// }

// ESP32BLEServer *global_ble_server = nullptr;

// }  // namespace esp32_ble_server
// }  // namespace esphome


void CreavisionBLEServer::setup() {
  init_ble();
}

void CreavisionBLEServer::loop() {
  // Implement your loop logic here
}

void CreavisionBLEServer::init_ble() {
  esp_ble_gatts_register_callback(std::bind(&CreavisionBLEServer::gatts_event_handler, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
  esp_ble_gatts_app_register(SERVICE_UUID);

  esp_ble_gatts_create_service(ESP_GATT_UUID_LEN_16, &SERVICE_UUID, ESP_GATT_NUM_RESERVE_ATTR_GEN);

  esp_ble_gatts_add_char(ESP_GATT_CHAR_PROP_BIT_NOTIFY, ESP_UUID_LEN_16, &CHAR_UUID_TX, NULL, 0, NULL);
  esp_ble_gatts_add_char(ESP_GATT_CHAR_PROP_BIT_WRITE, ESP_UUID_LEN_16, &CHAR_UUID_RX, NULL, 0, NULL);
}

void CreavisionBLEServer::gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gatts_cb_param_t *param) {
  if (event == ESP_GATTS_CREAT_ATTR_TAB_EVT) {
    if (param->add_attr_tab.status == ESP_GATT_OK) {
      server_handle_ = param->add_attr_tab.svc_handle;
      char_handle_tx_ = param->add_attr_tab.handles[1];
      char_handle_rx_ = param->add_attr_tab.handles[2];
    }
  } else if (event == ESP_GATTS_WRITE_EVT) {
    if (param->write.handle == char_handle_rx_) {
      notify_rx(param->write.value, param->write.len);
    }
  }
}

void CreavisionBLEServer::notify_rx(const uint8_t *data, uint16_t size) {
  // Implement your receive logic here
}

void CreavisionBLEServer::send_data(const uint8_t *data, uint16_t size) {
  esp_ble_gatts_send_indicate(gatts_if, 0, char_handle_tx_, size, data, false);
}

}  // namespace vport
}  // namespace esphome
