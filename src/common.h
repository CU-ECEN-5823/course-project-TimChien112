/*
 * common.h
 *
 *  Created on: Apr 14, 2019
 *
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include "native_gecko.h"
#include "mesh_generic_model_capi_types.h"
#include "gpio.h"
#include "mesh_lib.h"

// soft timer flags
#define DISPLAY_REFRESH 0x05
#define LOG_REFRESH 0x06
#define TIMER_ID_FACTORY_RESET 0x07
#define TIMER_ID_RESTART 0x08
#define TIMER_ID_FRIEND_FIND 0x09

// external event flag
#define PUSHBUTTON_FLAG 0x13
#define BP1_PIN_INDEX 	128
#define BP0_PIN_INDEX 	64
#define PRESENCE_PIN_INDEX 8
#define PRESENCE_FLAG 	1<<3
#define BP0_FLAG 1<<0
#define BP1_FLAG 1<<1
#define SM_FLAG  1<<2
#define BR_FLAG  1<<3


/// number of active Bluetooth connections
/// as shown in Silicon Labs switch example
static uint8 num_connections = 0;

uint32_t tickCount;
uint8_t trid;

//function declarations
void set_device_name(bd_addr *pAddr);
static void init_models(void);
static void pb_request(uint16_t model_id,
                          uint16_t element_index,
                          uint16_t client_addr,
                          uint16_t server_addr,
                          uint16_t appkey_index,
                          const struct mesh_generic_request *request,
                          uint32_t transition_ms,
                          uint16_t delay_ms,
						  uint8_t request_flags);

static void pb_change(uint16_t model_id,
                         uint16_t element_index,
                         const struct mesh_generic_state *current,
                         const struct mesh_generic_state *target,
						 uint32_t remaining_ms);


static void BR_request(uint16_t model_id,
                          uint16_t element_index,
                          uint16_t client_addr,
                          uint16_t server_addr,
                          uint16_t appkey_index,
                          const struct mesh_generic_request *request,
                          uint32_t transition_ms,
                          uint16_t delay_ms,
                          uint8_t request_flags);
static void BR_change(uint16_t model_id,
                         uint16_t element_index,
                         const struct mesh_generic_state *current,
                         const struct mesh_generic_state *target,
                         uint32_t remaining_ms);

static void SM_request(uint16_t model_id,
                          uint16_t element_index,
                          uint16_t client_addr,
                          uint16_t server_addr,
                          uint16_t appkey_index,
                          const struct mesh_generic_request *request,
                          uint32_t transition_ms,
                          uint16_t delay_ms,
                          uint8_t request_flags);
static void SM_change(uint16_t model_id,
                         uint16_t element_index,
                         const struct mesh_generic_state *current,
                         const struct mesh_generic_state *target,
                         uint32_t remaining_ms);

#endif /* SRC_COMMON_H_ */
