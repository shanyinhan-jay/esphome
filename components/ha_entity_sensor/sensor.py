import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import globals, sensor, text

CODEOWNERS = ["@local"]
DEPENDENCIES = ["api", "globals", "text"]
AUTO_LOAD = ["api"]

ha_entity_sensor_ns = cg.esphome_ns.namespace("ha_entity_sensor")
# CustomAPIDevice 仅在 C++ 头文件中继承（2025.x Python 侧无 api.CustomAPIDevice）
HaEntitySensor = ha_entity_sensor_ns.class_("HaEntitySensor", sensor.Sensor, cg.Component)

CONF_ENTITY_ID_TEXT_ID = "entity_id_text_id"
CONF_ENTITY_ID_GLOBAL_ID = "entity_id_global_id"

CONFIG_SCHEMA = sensor.sensor_schema(HaEntitySensor, accuracy_decimals=2).extend(
    {
        cv.Optional(CONF_ENTITY_ID_TEXT_ID): cv.use_id(text.Text),
        cv.Optional(CONF_ENTITY_ID_GLOBAL_ID): cv.use_id(globals.GlobalsComponent),
    }
).extend(
    cv.require_at_least_one_key(CONF_ENTITY_ID_TEXT_ID, CONF_ENTITY_ID_GLOBAL_ID)
)

async def to_code(config):
    cg.add_define("USE_API_HOMEASSISTANT_STATES")
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    if CONF_ENTITY_ID_TEXT_ID in config:
        ent = await cg.get_variable(config[CONF_ENTITY_ID_TEXT_ID])
        cg.add(var.set_entity_id_text(ent))
    if CONF_ENTITY_ID_GLOBAL_ID in config:
        glob = await cg.get_variable(config[CONF_ENTITY_ID_GLOBAL_ID])
        cg.add(var.set_entity_id_global(glob))
