/*******************************************************************************
* File Name: Potentiometer.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Potentiometer_H) /* Pins Potentiometer_H */
#define CY_PINS_Potentiometer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Potentiometer_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Potentiometer__PORT == 15 && ((Potentiometer__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Potentiometer_Write(uint8 value);
void    Potentiometer_SetDriveMode(uint8 mode);
uint8   Potentiometer_ReadDataReg(void);
uint8   Potentiometer_Read(void);
void    Potentiometer_SetInterruptMode(uint16 position, uint16 mode);
uint8   Potentiometer_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Potentiometer_SetDriveMode() function.
     *  @{
     */
        #define Potentiometer_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Potentiometer_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Potentiometer_DM_RES_UP          PIN_DM_RES_UP
        #define Potentiometer_DM_RES_DWN         PIN_DM_RES_DWN
        #define Potentiometer_DM_OD_LO           PIN_DM_OD_LO
        #define Potentiometer_DM_OD_HI           PIN_DM_OD_HI
        #define Potentiometer_DM_STRONG          PIN_DM_STRONG
        #define Potentiometer_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Potentiometer_MASK               Potentiometer__MASK
#define Potentiometer_SHIFT              Potentiometer__SHIFT
#define Potentiometer_WIDTH              1u

/* Interrupt constants */
#if defined(Potentiometer__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Potentiometer_SetInterruptMode() function.
     *  @{
     */
        #define Potentiometer_INTR_NONE      (uint16)(0x0000u)
        #define Potentiometer_INTR_RISING    (uint16)(0x0001u)
        #define Potentiometer_INTR_FALLING   (uint16)(0x0002u)
        #define Potentiometer_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Potentiometer_INTR_MASK      (0x01u) 
#endif /* (Potentiometer__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Potentiometer_PS                     (* (reg8 *) Potentiometer__PS)
/* Data Register */
#define Potentiometer_DR                     (* (reg8 *) Potentiometer__DR)
/* Port Number */
#define Potentiometer_PRT_NUM                (* (reg8 *) Potentiometer__PRT) 
/* Connect to Analog Globals */                                                  
#define Potentiometer_AG                     (* (reg8 *) Potentiometer__AG)                       
/* Analog MUX bux enable */
#define Potentiometer_AMUX                   (* (reg8 *) Potentiometer__AMUX) 
/* Bidirectional Enable */                                                        
#define Potentiometer_BIE                    (* (reg8 *) Potentiometer__BIE)
/* Bit-mask for Aliased Register Access */
#define Potentiometer_BIT_MASK               (* (reg8 *) Potentiometer__BIT_MASK)
/* Bypass Enable */
#define Potentiometer_BYP                    (* (reg8 *) Potentiometer__BYP)
/* Port wide control signals */                                                   
#define Potentiometer_CTL                    (* (reg8 *) Potentiometer__CTL)
/* Drive Modes */
#define Potentiometer_DM0                    (* (reg8 *) Potentiometer__DM0) 
#define Potentiometer_DM1                    (* (reg8 *) Potentiometer__DM1)
#define Potentiometer_DM2                    (* (reg8 *) Potentiometer__DM2) 
/* Input Buffer Disable Override */
#define Potentiometer_INP_DIS                (* (reg8 *) Potentiometer__INP_DIS)
/* LCD Common or Segment Drive */
#define Potentiometer_LCD_COM_SEG            (* (reg8 *) Potentiometer__LCD_COM_SEG)
/* Enable Segment LCD */
#define Potentiometer_LCD_EN                 (* (reg8 *) Potentiometer__LCD_EN)
/* Slew Rate Control */
#define Potentiometer_SLW                    (* (reg8 *) Potentiometer__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Potentiometer_PRTDSI__CAPS_SEL       (* (reg8 *) Potentiometer__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Potentiometer_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Potentiometer__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Potentiometer_PRTDSI__OE_SEL0        (* (reg8 *) Potentiometer__PRTDSI__OE_SEL0) 
#define Potentiometer_PRTDSI__OE_SEL1        (* (reg8 *) Potentiometer__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Potentiometer_PRTDSI__OUT_SEL0       (* (reg8 *) Potentiometer__PRTDSI__OUT_SEL0) 
#define Potentiometer_PRTDSI__OUT_SEL1       (* (reg8 *) Potentiometer__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Potentiometer_PRTDSI__SYNC_OUT       (* (reg8 *) Potentiometer__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Potentiometer__SIO_CFG)
    #define Potentiometer_SIO_HYST_EN        (* (reg8 *) Potentiometer__SIO_HYST_EN)
    #define Potentiometer_SIO_REG_HIFREQ     (* (reg8 *) Potentiometer__SIO_REG_HIFREQ)
    #define Potentiometer_SIO_CFG            (* (reg8 *) Potentiometer__SIO_CFG)
    #define Potentiometer_SIO_DIFF           (* (reg8 *) Potentiometer__SIO_DIFF)
#endif /* (Potentiometer__SIO_CFG) */

/* Interrupt Registers */
#if defined(Potentiometer__INTSTAT)
    #define Potentiometer_INTSTAT            (* (reg8 *) Potentiometer__INTSTAT)
    #define Potentiometer_SNAP               (* (reg8 *) Potentiometer__SNAP)
    
	#define Potentiometer_0_INTTYPE_REG 		(* (reg8 *) Potentiometer__0__INTTYPE)
#endif /* (Potentiometer__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Potentiometer_H */


/* [] END OF FILE */
