#include "ha_entity_sensor.h"

#include "esphome/components/api/api_server.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ha_entity_sensor {

static const char *const TAG = "ha_entity_sensor";

float HaEntitySensor::get_setup_priority() const { return setup_priority::AFTER_CONNECTION; }

void HaEntitySensor::setup() {
  if (this->entity_id_text_ == nullptr) {
    ESP_LOGE(TAG, "entity_id text not configured");
    return;
  }
  this->entity_id_storage_ = this->entity_id_text_->state;
  if (this->entity_id_storage_.empty()) {
    ESP_LOGW(TAG, "entity_id text is empty");
    return;
  }

  api::global_api_server->subscribe_home_assistant_state(
      this->entity_id_storage_, {}, [this](const std::string &state) {
        auto val = parse_number<float>(state);
        if (!val.has_value()) {
          ESP_LOGW(TAG, "'%s': Can't convert '%s' to number!", this->entity_id_storage_.c_str(), state.c_str());
          this->publish_state(NAN);
          return;
        }
        ESP_LOGV(TAG, "'%s': Got state %.2f", this->entity_id_storage_.c_str(), *val);
        this->publish_state(*val);
      });

  ESP_LOGI(TAG, "Subscribed to Home Assistant entity '%s'", this->entity_id_storage_.c_str());
}

}  // namespace ha_entity_sensor
}  // namespace esphome
