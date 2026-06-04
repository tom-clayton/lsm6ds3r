# lsm6ds3tr

Minimal LSM6DS3TR sensor driver for gesture recognition. I2C bus control functions are passed in, allowing it to be used with any native micro-controller code or high level framework.

### Usage

Requires i2c read / write functions to be passed in its initialisation function, wrapped in the i2c_bus_t structure from i2c_wrapper.h.

```C
int lsm6ds_init(const i2c_bus_t *i2c_bus);
```

Detects one type of gesture at a time, selected by the following functions:

```C
void lsm6ds_setup_tap();
void lsm6ds_setup_AWT();
void lsm6ds_setup_6D();
```

Detected gestures will create an interrupt on int1.

### Installation notes

Requires i2c_wrapper.h to be included.

### Todo

Recognise multiple simultaneous gestures.<br>
More gesture types.<br>
Supply accelerometer data.<br>
