#pragma once

#include <string>

#include "esphome/components/globals/globals_component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text/text.h"
#include "esphome/core/component.h"

namespace esphome {
namespace ha_entity_sensor {

class HaEntitySensor : public sensor::Sensor, public Component {
 public:
  void set_entity_id_text(text::Text *entity_id_text) { this->entity_id_text_ = entity_id_text; }
  void set_entity_id_global(globals::GlobalsComponent<std::string> *entity_id_global) {
    this->entity_id_global_ = entity_id_global;
  }
  void setup() override;
  float get_setup_priority() const override;

 protected:
  text::Text *entity_id_text_{nullptr};
  globals::GlobalsComponent<std::string> *entity_id_global_{nullptr};
  std::string entity_id_storage_;
};

}  // namespace ha_entity_sensor
}  // namespace esphome
