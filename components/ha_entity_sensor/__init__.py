import esphome.codegen as cg

CODEOWNERS = ["@local"]

# 必须导出 sensor 子模块，ESPHome 才能注册 platform: ha_entity_sensor
from . import sensor  # noqa: F401
