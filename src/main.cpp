#include <Arduino.h>

#include "stm32f0xx_hal.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

#define Out8_HS_Pin GPIO_PIN_2
#define Out8_HS_GPIO_Port GPIOB
#define CAN_S_Pin GPIO_PIN_6
#define CAN_S_GPIO_Port GPIOB

#define CAN_1M 1
#define CAN_500K 2
#define CAN_250K 4
#define CAN_125K 8
#define CAN_100K 10
#define CAN_50K 20

CanTxMsgTypeDef CAN_TX_Msg;
CanRxMsgTypeDef CAN_RX_Msg;
uint8_t u8Data[16];

CAN_HandleTypeDef hcan;

extern "C" void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan)
{
    digitalToggle(LED_BUILTIN);

    if (hcan->pRxMsg->IDE == CAN_ID_STD) {
        switch (hcan->pRxMsg->StdId) {
            case 0x100:
                break;
        }
    } else {
        switch (hcan->pRxMsg->ExtId) {
        }
    }

    __HAL_CAN_ENABLE_IT(hcan, CAN_IT_FMP0);
}

void MainInit()
{
    CAN_FilterConfTypeDef sFilterConfig;

    /* MCU Configuration----------------------------------------------------------*/

    // Instance CAN RX and TX
    // Replace CAN_250K in MX_CAN_Init to change the baudrate
    hcan.pTxMsg = &CAN_TX_Msg;
    hcan.pRxMsg = &CAN_RX_Msg;
    // create open filter
    sFilterConfig.FilterIdHigh = 0;
    sFilterConfig.FilterIdLow = 0;
    sFilterConfig.FilterMaskIdHigh = 0;
    sFilterConfig.FilterMaskIdLow = 0;
    sFilterConfig.FilterFIFOAssignment = 0;
    sFilterConfig.FilterNumber = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.BankNumber = 0;
    HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
    // Interrupt config
    HAL_CAN_Receive_IT(&hcan, 0);
    // Change CAN from Silent to Active mode
    HAL_GPIO_WritePin(CAN_S_GPIO_Port, CAN_S_Pin, GPIO_PIN_RESET);
}

void MX_GPIO_Init()
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

void MX_CAN_Init()
{
    hcan.Instance = CAN;
    hcan.Init.Prescaler = 4;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SJW = CAN_SJW_1TQ;
    hcan.Init.BS1 = CAN_BS1_11TQ;
    hcan.Init.BS2 = CAN_BS2_4TQ;
    hcan.Init.TTCM = DISABLE;
    hcan.Init.ABOM = ENABLE;
    hcan.Init.AWUM = DISABLE;
    hcan.Init.NART = DISABLE;
    hcan.Init.RFLM = DISABLE;
    hcan.Init.TXFP = DISABLE;
    if (HAL_CAN_Init(&hcan) != HAL_OK) {
        Error_Handler();
    }
}

extern "C" void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if (canHandle->Instance == CAN) {
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

extern "C" void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{
    if (canHandle->Instance == CAN) {
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

void loop()
{
    MX_GPIO_Init();
    MX_CAN_Init();
    MainInit();

    hcan.Instance->BTR &= 0xFFFFFC00;
    hcan.Instance->BTR |= CAN_250K;

    int counter = 0;

    while (1) {
        // Send it by CAN
        hcan.pTxMsg->IDE = CAN_ID_STD;
        hcan.pTxMsg->StdId = 0x234;
        hcan.pTxMsg->DLC = 1;
        hcan.pTxMsg->Data[0] = counter;
        HAL_CAN_Transmit(&hcan, 10);

        delay(1000);

        counter++;
    }
}
