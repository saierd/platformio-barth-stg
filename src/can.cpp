#include "can.h"

#include <Arduino.h>

#define Out8_HS_Pin GPIO_PIN_2
#define Out8_HS_GPIO_Port GPIOB
#define CAN_S_Pin GPIO_PIN_6
#define CAN_S_GPIO_Port GPIOB

namespace {

CAN_HandleTypeDef hcan;
can::ReceiveCallback receive_callback = nullptr;

void can_gpio_init()
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB, Out8_HS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(CAN_S_GPIO_Port, CAN_S_Pin, GPIO_PIN_SET);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = Out8_HS_Pin | CAN_S_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void can_init()
{
    hcan.Instance = CAN;
    hcan.Init.Prescaler = 4;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_BS1_11TQ;
    hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
    hcan.Init.TimeTriggeredMode = DISABLE;
    hcan.Init.AutoBusOff = ENABLE;
    hcan.Init.AutoWakeUp = DISABLE;
    hcan.Init.AutoRetransmission = ENABLE;
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_CAN_Start(&hcan) != HAL_OK) {
        Error_Handler();
    }
}

void can_init_filter()
{
    CAN_FilterTypeDef filter_config;
    filter_config.FilterIdHigh = 0;
    filter_config.FilterIdLow = 0;
    filter_config.FilterMaskIdHigh = 0;
    filter_config.FilterMaskIdLow = 0;
    filter_config.FilterFIFOAssignment = 0;
    filter_config.FilterBank = 0;
    filter_config.FilterMode = CAN_FILTERMODE_IDMASK;
    filter_config.FilterScale = CAN_FILTERSCALE_32BIT;
    filter_config.FilterActivation = ENABLE;
    filter_config.SlaveStartFilterBank = 0;
    if (HAL_CAN_ConfigFilter(&hcan, &filter_config) != HAL_OK) {
        Error_Handler();
    }
}

}  // namespace

extern "C" void HAL_CAN_MspInit(CAN_HandleTypeDef* can)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (can->Instance == CAN) {
        /* Peripheral clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();

        /**CAN GPIO Configuration
        PB8     ------> CAN_RX
        PB9     ------> CAN_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF4_CAN;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral interrupt init */
        HAL_NVIC_SetPriority(CEC_CAN_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(CEC_CAN_IRQn);
    }
}

extern "C" void HAL_CAN_MspDeInit(CAN_HandleTypeDef* can)
{
    if (can->Instance == CAN) {
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();

        /**CAN GPIO Configuration
        PB8     ------> CAN_RX
        PB9     ------> CAN_TX
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);

        /* Peripheral interrupt Deinit*/
        HAL_NVIC_DisableIRQ(CEC_CAN_IRQn);
    }
}

extern "C" void CEC_CAN_IRQHandler()
{
    HAL_CAN_IRQHandler(&hcan);
}

extern "C" void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    if (receive_callback == nullptr) {
        return;
    }

    CAN_RxHeaderTypeDef msg;
    uint8_t data[8];
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &msg, data);

    uint32_t id = 0;
    if (msg.IDE == CAN_ID_STD) {
        id = msg.StdId;
    } else {
        id = msg.ExtId;
    }

    receive_callback(id, data, msg.DLC);
}

namespace can {

void init(Baudrate baudrate)
{
    can_gpio_init();
    can_init();
    can_init_filter();

    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        Error_Handler();
    }

    // Change CAN from Silent to Active mode
    HAL_GPIO_WritePin(CAN_S_GPIO_Port, CAN_S_Pin, GPIO_PIN_RESET);

    set_baudrate(baudrate);
}

void set_baudrate(Baudrate baudrate)
{
    hcan.Instance->BTR &= 0xFFFFFC00;
    hcan.Instance->BTR |= static_cast<int>(baudrate);
}

void send(uint32_t id, uint8_t const* data, size_t size)
{
    CAN_TxHeaderTypeDef msg;
    if (id < 2048) {
        msg.IDE = CAN_ID_STD;
        msg.StdId = id;
    } else {
        msg.IDE = CAN_ID_EXT;
        msg.ExtId = id;
    }
    msg.DLC = size;
    msg.RTR = CAN_RTR_DATA;
    msg.TransmitGlobalTime = DISABLE;

    uint32_t mailbox;
    HAL_CAN_AddTxMessage(&hcan, &msg, const_cast<uint8_t*>(data), &mailbox);
}

void on_receive(ReceiveCallback callback)
{
    receive_callback = callback;
}

}  // namespace can
