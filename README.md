
# Adsum Networks SDK

Our goal is to allow SoC developers to focus on what they do best,
i.e. their applications, while we provide them the required toolset that abstract the complexity of the SoCs
networking and allow the performance predictability needed for their industrial-grade applications.

Adsum SDK offers multiple components to applications developers, you can include the components you need to monitor your application performance.
Our SDK is designed to be lightweight , so it has a minimal impact on your application and SoC performance.

Please visit our [public documentation page](https://adsumnetworks.io/adsum-getting-started) for more details about Adsum APM Platform, how it works and detailed integration guides.

# Getting Started: 

We provide you step by step guides on how to add the SDK to your application, and how to publish data to your tenant on Adsum cloud-based
APM.

To understand how to integrate our SDK in your project using nRF Connect SDK, check the next section and our [nRFP Connect SDK Integration guide](httsp://adsumnetworks.io/nRF-Connect-SDK-Integration-Guide).

To start sending your performance data to our APM Cloud, [create Adsum APM cloud account](https://apm.adumnetworks.io/signup).

# nRF Connect SDK Integration Guide

This guide provides a walkthrough of the required steps to integrate Adsum SDK lib files into your project using nRF Connect SDK. This integration has been validated against nRF Connect SDK releases ranging
from vXXX to vYYY

##*Note:*

*This guide assumes that you are using a qualified nRF SoC, check the list of [qualified nRF SoCs](https://adsumnetworks/docs/qualified_SoCs_and_SDK).*


## Include Adsum SDK module in the build: 

First, you will need to add Adsum SDK modules to your Zephyr projects manifest, this is located at zephyr/west.yml, which is part of Zephyr SDK main folder. The definition below needs to be added to west.yml file.

```yml
### New definition start
    - name: adsum-module-sdk
      url: https://github.com/adsumnetworks/adsum-module-sdk
      path: zephyr/modules/adsum-module-sdk
      revision: main
### END 

  self:
    path: zephyr
    west-commands: scripts/west-commands.yml

```

Next step, you will need to run the command `west update` to clone the adsum-module-sdk. 

```
$ west update
...
=== updating adsum-module-sdk (zephyr/modules/adsum-module-sdk):
--- adsum-module-sdk: initializing
Initialized empty Git repository in C:/zephyrproject/zephyr/modules/adsum-module-sdk/.git/
--- adsum-module-sdk: fetching, need revision main
...
```


## Update your Project Code

### Define Adsum Models Header

Define Adsum Models Header into the main.c file of your project :

```c
#include "adsum_models.h"
```

### Update your Mesh Elements definition:

Update your Mesh Elements definition in the main.c to include Adsum_models, as you will notice, we are using element id 77, so make sure this id is unique to Adsum in your code.

```c

static struct bt_mesh_elem elements[] = {
	BT_MESH_ELEM(0, models, BT_MESH_MODEL_NONE),
	BT_MESH_ELEM(77, BT_MESH_MODEL_NONE, Adsum_models), // Adsum Model Definition

};
```

### Add the adsum_model_init function
Add the adsum_model_init functionto the main.c file, it serves for Adsum Model initiationalization. This function needs to be added after mesh initialization is complete. You can place it either in the main.c or in the function responsible to initialize your mesh network.

```c
adsum_model_init(&comp); // initial adsum model
```


## Update your project CMakeLists.txt 
CMakeLists.txt file should include the below instructions and targets required for Adsum SDK integration.

```python



set(ZEPHYR_EXTRA_MODULES $ENV{ZEPHYR_BASE}/modules/adsum-module-sdk) #add this line before find_package funtion.


find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# add Adsum SDK Lib defintions

set(adsum_lib_dir ${CMAKE_CURRENT_SOURCE_DIR}/adsum_sdk_lib)

set(ADSUMLIB_LIB_DIR ${adsum_lib_dir}/lib)

add_library(adsum_lib STATIC IMPORTED GLOBAL)

set_target_properties(adsum_lib PROPERTIES IMPORTED_LOCATION ${ADSUMLIB_LIB_DIR}/adsum_lib.a)

target_link_libraries(app PUBLIC adsum_lib)
```
##  Update your project Kernel Configuration

Update your project Kernel Configuration file “prj.conf” to include the appropriate Adsum recommended parameters below.

We do recommend fine-tuning these values based on the scale of your network. Please visit the [Adsum Mesh Models config guide] (<Include a link) where all the parameters are explained along with recommended values based on the scale of your network.

If you are new to Bluetooth Mesh, we encourage you to read our [Bluetooth Mesh primer] (Add link to Adsum Bluetooth Primer) to understand the BLE mesh technology and check our [Adsum terminology page](<Add link to Adsum Terminology>).


```python
#ADSUM MODELS CONFIG

CONFIG_BT_MESH_CRPL=128

ONFIG_BT_MESH_MSG_CACHE_SIZE=128

CONFIG_BT_MESH_ADV_BUF_COUNT=128

CONFIG_BT_MESH_SEG_BUFS=256

CONFIG_BT_MESH_RX_SEG_MAX=10

CONFIG_BT_MESH_TX_SEG_MAX=10

CONFIG_BT_MESH_RX_SEG_MSG_COUNT=10

CONFIG_BT_MESH_TX_SEG_MSG_COUNT=10

CONFIG_BT_MESH_LOOPBACK_BUFS=32

CONFIG_BT_MESH_FRIEND=n

CONFIG_BT_MESH_LOW_POWER=n

CONFIG_BT_MESH_MODEL_EXTENSIONS=n

#Use this parameter to enable UART logging if needed

CONFIG_UART_NRFX=y
```
