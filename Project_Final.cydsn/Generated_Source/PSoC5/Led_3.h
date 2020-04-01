/*******************************************************************************
* File Name: Led_3.h  
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

#if !defined(CY_PINS_Led_3_H) /* Pins Led_3_H */
#define CY_PINS_Led_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Led_3_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Led_3__PORT == 15 && ((Led_3__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Led_3_Write(uint8 value);
void    Led_3_SetDriveMode(uint8 mode);
uint8   Led_3_ReadDataReg(void);
uint8   Led_3_Read(void);
void    Led_3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Led_3_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Led_3_SetDriveMode() function.
     *  @{
     */
        #define Led_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Led_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Led_3_DM_RES_UP          PIN_DM_RES_UP
        #define Led_3_DM_RES_DWN         PIN_DM_RES_DWN
        #define Led_3_DM_OD_LO           PIN_DM_OD_LO
        #define Led_3_DM_OD_HI           PIN_DM_OD_HI
        #define Led_3_DM_STRONG          PIN_DM_STRONG
        #define Led_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Led_3_MASK               Led_3__MASK
#define Led_3_SHIFT              Led_3__SHIFT
#define Led_3_WIDTH              1u

/* Interrupt constants */
#if defined(Led_3__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Led_3_SetInterruptMode() function.
     *  @{
     */
        #define Led_3_INTR_NONE      (uint16)(0x0000u)
        #define Led_3_INTR_RISING    (uint16)(0x0001u)
        #define Led_3_INTR_FALLING   (uint16)(0x0002u)
        #define Led_3_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Led_3_INTR_MASK      (0x01u) 
#endif /* (Led_3__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Led_3_PS                     (* (reg8 *) Led_3__PS)
/* Data Register */
#define Led_3_DR                     (* (reg8 *) Led_3__DR)
/* Port Number */
#define Led_3_PRT_NUM                (* (reg8 *) Led_3__PRT) 
/* Connect to Analog Globals */                                                  
#define Led_3_AG                     (* (reg8 *) Led_3__AG)                       
/* Analog MUX bux enable */
#define Led_3_AMUX                   (* (reg8 *) Led_3__AMUX) 
/* Bidirectional Enable */                                                        
#define Led_3_BIE                    (* (reg8 *) Led_3__BIE)
/* Bit-mask for Aliased Register Access */
#define Led_3_BIT_MASK               (* (reg8 *) Led_3__BIT_MASK)
/* Bypass Enable */
#define Led_3_BYP                    (* (reg8 *) Led_3__BYP)
/* Port wide control signals */                                                   
#define Led_3_CTL                    (* (reg8 *) Led_3__CTL)
/* Drive Modes */
#define Led_3_DM0                    (* (reg8 *) Led_3__DM0) 
#define Led_3_DM1                    (* (reg8 *) Led_3__DM1)
#define Led_3_DM2                    (* (reg8 *) Led_3__DM2) 
/* Input Buffer Disable Override */
#define Led_3_INP_DIS                (* (reg8 *) Led_3__INP_DIS)
/* LCD Common or Segment Drive */
#define Led_3_LCD_COM_SEG            (* (reg8 *) Led_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Led_3_LCD_EN                 (* (reg8 *) Led_3__LCD_EN)
/* Slew Rate Control */
#define Led_3_SLW                    (* (reg8 *) Led_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Led_3_PRTDSI__CAPS_SEL       (* (reg8 *) Led_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Led_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Led_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Led_3_PRTDSI__OE_SEL0        (* (reg8 *) Led_3__PRTDSI__OE_SEL0) 
#define Led_3_PRTDSI__OE_SEL1        (* (reg8 *) Led_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Led_3_PRTDSI__OUT_SEL0       (* (reg8 *) Led_3__PRTDSI__OUT_SEL0) 
#define Led_3_PRTDSI__OUT_SEL1       (* (reg8 *) Led_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Led_3_PRTDSI__SYNC_OUT       (* (reg8 *) Led_3__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Led_3__SIO_CFG)
    #define Led_3_SIO_HYST_EN        (* (reg8 *) Led_3__SIO_HYST_EN)
    #define Led_3_SIO_REG_HIFREQ     (* (reg8 *) Led_3__SIO_REG_HIFREQ)
    #define Led_3_SIO_CFG            (* (reg8 *) Led_3__SIO_CFG)
    #define Led_3_SIO_DIFF           (* (reg8 *) Led_3__SIO_DIFF)
#endif /* (Led_3__SIO_CFG) */

/* Interrupt Registers */
#if defined(Led_3__INTSTAT)
    #define Led_3_INTSTAT            (* (reg8 *) Led_3__INTSTAT)
    #define Led_3_SNAP               (* (reg8 *) Led_3__SNAP)
    
	#define Led_3_0_INTTYPE_REG 		(* (reg8 *) Led_3__0__INTTYPE)
#endif /* (Led_3__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Led_3_H */


/* [] END OF FILE */
