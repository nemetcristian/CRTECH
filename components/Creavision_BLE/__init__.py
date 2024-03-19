
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.core import coroutine_with_priority, coroutine, Lambda
from esphome.cpp_generator import MockObj


Creavision_BLE_ns = cg.esphome_ns.namespace('Creavision_BLE')
CreavisionBLEServer = Creavision_BLE_ns.class_('CreavisionBLEServer', cg.Component)

CONFIG_SCHEMA = cv.All(
    cv.only_on_esp32, 
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(CreavisionBLEServer),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    cg.add_define('USE_BLE_SERVER')

