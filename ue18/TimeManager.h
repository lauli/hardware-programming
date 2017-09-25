#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include "smf.h"

class Temperature : public SM {
public:

  Temperature();
  void init();
  int  getTemperature();
  void handleEvent(Event event);
  void calculateTemperature(uint32_t data);
  void calibrateSensor(uint32_t data);
  virtual ~Temperature();
};

#endif /* TEMPERATURE_H_ */