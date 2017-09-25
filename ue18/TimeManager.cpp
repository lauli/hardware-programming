#include <stdio.h>
#include <temperature.h>
#include "hal.h"
#include "FlashConfigService.h"

static float temperature;
static int   temperatureOffset;

FlashConfigService flashConfigService;

Temperature::Temperature() {}

Temperature::~Temperature() {}

void Temperature::init() {
  SMF::subscribe(TEMP_MEASUREMENT_READY, this);
  SMF::subscribe(CALIBRATION_RECEIVED,   this);
  flashConfigService = FlashConfigService();

  Config *config = flashConfigService.readConfig();
  temperatureOffset = config->temperatureOffset;
}

int Temperature::getTemperature() {
  return temperature;
}

void Temperature::handleEvent(Event event) {
  switch (event.id) {
  case TEMP_MEASUREMENT_READY:
    calculateTemperature(event.value);
    break;

  case CALIBRATION_RECEIVED:
    calibrateSensor(event.value);
    break;

  default:
    break;
  }
}

void Temperature::calculateTemperature(uint32_t data) {
  int adcRefTempCal_1_2v_30 = TLV->ADC14_REF1P2V_TS30C;
  int adcRefTempCal_1_2v_85 = TLV->ADC14_REF1P2V_TS85C;

  temperature = (((float)data - adcRefTempCal_1_2v_30) * (85 - 30)) /
                (adcRefTempCal_1_2v_85 - adcRefTempCal_1_2v_30) + 30.0f;

  temperature -= temperatureOffset;

  printf("Temperature: %f \n", temperature);
}

void Temperature::calibrateSensor(uint32_t data) {
  // calculate offset
  temperatureOffset = temperature - data;

  // save offset in flash
  Config config = { temperatureOffset };

  flashConfigService.writeConfig(&config);
}
