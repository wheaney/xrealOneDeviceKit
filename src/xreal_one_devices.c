#include "xreal_one_devices.h"

#include "imu_protocol.h"

#include <string.h>

device_imu_error_type device_imu_open_xreal_one(device_imu_type* device, device_imu_event_callback callback) {
    if (!device) {
        return DEVICE_IMU_ERROR_NO_DEVICE;
    }

    memset(device, 0, sizeof(device_imu_type));

    const imu_hid_info info = {
        .product_id = 0,
        .interface_number = -1,
        .path = NULL,
    };

    if (!imu_protocol_xreal_one.open(device, &info)) {
        return DEVICE_IMU_ERROR_NO_HANDLE;
    }

    device->protocol = &imu_protocol_xreal_one;

    return device_imu_open(device, callback);
}
