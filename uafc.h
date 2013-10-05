#ifndef _UAFC_H
#define _UAFC_H

struct sensors {
  unsigned int afm;
  double map;
  double iat;
  unsigned int rpm;
  double throttle;
  double afr;
};

struct calculated_values {
  unsigned int afm_out;
  double load;
};

typedef void (*uafc_tick_callback)();


struct sensors * get_sensors();
struct calculated_values * get_calculated_values();

#endif

