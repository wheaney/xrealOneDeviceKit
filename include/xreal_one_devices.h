#pragma once

#include "device_imu.h"

#ifdef __cplusplus
extern "C" {
#endif

device_imu_error_type device_imu_open_xreal_one(device_imu_type* device, device_imu_event_callback callback);

#ifdef __cplusplus
} // extern "C"
#endif
