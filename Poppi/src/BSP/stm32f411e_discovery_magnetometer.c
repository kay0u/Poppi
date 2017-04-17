/**
  ******************************************************************************
  * @file    stm32f411e_discovery_Magnetometer.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    27-January-2017
  * @brief   This file provides a set of functions needed to manage the
  *          MEMS Magnetometer available on STM32F411E-Discovery Kit.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f411e_discovery_magnetometer.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32F411E_DISCOVERY
  * @{
  */ 

/** @defgroup STM32F411E_DISCOVERY_Magnetometer STM32F411E DISCOVERY Magnetometer
  * @{
  */

/** @defgroup STM32F411E_DISCOVERY_Magnetometer_Private_TypesDefinitions STM32F411E DISCOVERY Magnetometer Private TypesDefinitions
  * @{
  */ 
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_Magnetometer_Private_Defines STM32F411E DISCOVERY Magnetometer Private Defines
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_Magnetometer_Private_Macros STM32F411E DISCOVERY Magnetometer Private Macros
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM32F411E_DISCOVERY_Magnetometer_Private_Variables STM32F411E DISCOVERY Magnetometer Private Variables
  * @{
  */ 
static MAGNETO_DrvTypeDef *MagnetometerDrv;
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_Magnetometer_Private_FunctionPrototypes STM32F411E DISCOVERY Magnetometer Private FunctionPrototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_Magnetometer_Private_Functions STM32F411E DISCOVERY Magnetometer Private Functions
  * @{
  */

/**
  * @brief  Set Magnetometer Initialization.
  * @retval MAGNETO_OK if no problem during initialization
  */
uint8_t BSP_MAGNETO_Init(void)
{
  uint8_t ret = MAGNETO_ERROR;
  MAGNETO_InitTypeDef         LSM303DLHC_InitStructure;
  
	if (Lsm303dlhcDrv_magneto.ReadID() == I_AM_LMS303DLHC_MAG)
  {
    /* Initialize the Magnetometer driver structure */
	  MagnetometerDrv = &Lsm303dlhcDrv_magneto;

    /* MEMS configuration ----------------------------------------------------*/
    /* Fill the Magnetometer structure */
	  LSM303DLHC_InitStructure.Temperature = LSM303DLHC_TEMPSENSOR_ENABLE;
	  LSM303DLHC_InitStructure.DataOutputRate = LSM303DLHC_ODR_220_HZ;
	  LSM303DLHC_InitStructure.FullScale = LSM303DLHC_FS_8_1_GA;
	  LSM303DLHC_InitStructure.Mode = LSM303DLHC_CONTINUOS_CONVERSION;
    
    /* Configure the Magnetometer main parameters */
	MagnetometerDrv->Init(LSM303DLHC_InitStructure);
	  
    ret = MAGNETO_OK;
  }
  else
  {
    ret = MAGNETO_ERROR;
  }

  return ret;
}

/**
  * @brief  Reboot memory content of Magnetometer.
  */
uint8_t BSP_MAGNETO_Status(void)
{
  if(MagnetometerDrv->Status != NULL)
  {
	  return MagnetometerDrv->Status();
  }  
}

/**
  * @brief  Get XYZ axes acceleration.
  * @param  pDataXYZ: Pointer to 3 angular acceleration axes.  
  *                   pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  */
void BSP_MAGNETO_GetXYZ(float *pDataXYZ)
{
  if(MagnetometerDrv->GetXYZ!= NULL)
  {
    MagnetometerDrv->GetXYZ(pDataXYZ);
  }
}

float BSP_MAGNETO_GetTemperature(void)
{
	if (MagnetometerDrv->GetXYZ != NULL)
	{
		return MagnetometerDrv->GetTemperature();
	}
	return -1.f;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
  
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/     
