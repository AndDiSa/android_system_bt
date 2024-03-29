/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  This file contains the SMP API function external definitions.
 *
 ******************************************************************************/
#ifndef SMP_API_H
#define SMP_API_H

#include "bt_target.h"
#include "smp_api_types.h"

/*****************************************************************************
**  External Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif
/* API of SMP */

/*******************************************************************************
**
** Function         SMP_Init
**
** Description      This function initializes the SMP unit.
**
** Returns          void
**
*******************************************************************************/
extern void SMP_Init(void);

/*******************************************************************************
**
** Function         SMP_SetTraceLevel
**
** Description      This function sets the trace level for SMP.  If called with
**                  a value of 0xFF, it simply returns the current trace level.
**
** Returns          The new or current trace level
**
*******************************************************************************/
extern UINT8 SMP_SetTraceLevel (UINT8 new_level);

/*******************************************************************************
**
** Function         SMP_Register
**
** Description      This function register for the SMP service callback.
**
** Returns          void
**
*******************************************************************************/
extern BOOLEAN SMP_Register (tSMP_CALLBACK *p_cback);

/*******************************************************************************
**
** Function         SMP_Pair
**
** Description      This function is called to start a SMP pairing.
**
** Returns          SMP_STARTED if bond started, else otherwise exception.
**
*******************************************************************************/
extern tSMP_STATUS SMP_Pair (BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         SMP_BR_PairWith
**
** Description      This function is called to start a SMP pairing over BR/EDR.
**
** Returns          SMP_STARTED if pairing started, otherwise reason for failure.
**
*******************************************************************************/
extern tSMP_STATUS SMP_BR_PairWith (BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         SMP_PairCancel
**
** Description      This function is called to cancel a SMP pairing.
**
** Returns          TRUE - pairing cancelled
**
*******************************************************************************/
extern  BOOLEAN SMP_PairCancel (BD_ADDR bd_addr);

/*******************************************************************************
**
** Function         SMP_SecurityGrant
**
** Description      This function is called to grant security process.
**
** Parameters       bd_addr - peer device bd address.
**                  res     - result of the operation SMP_SUCCESS if success.
**                            Otherwise, SMP_REPEATED_ATTEMPTS is too many attempts.
**
** Returns          None
**
*******************************************************************************/
extern void SMP_SecurityGrant(BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
**
** Function         SMP_PasskeyReply
**
** Description      This function is called after Security Manager submitted
**                  Passkey request to the application.
**
** Parameters:      bd_addr      - Address of the device for which PIN was requested
**                  res          - result of the operation SMP_SUCCESS if success
**                  passkey      - numeric value in the range of
**                  BTM_MIN_PASSKEY_VAL(0) - BTM_MAX_PASSKEY_VAL(999999(0xF423F)).
**
*******************************************************************************/
extern void SMP_PasskeyReply (BD_ADDR bd_addr, UINT8 res, UINT32 passkey);

/*******************************************************************************
**
** Function         SMP_ConfirmReply
**
** Description      This function is called after Security Manager submitted
**                  numeric comparison request to the application.
**
** Parameters:      bd_addr      - Address of the device with which numeric
**                                 comparison was requested
**                  res          - comparison result SMP_SUCCESS if success
**
*******************************************************************************/
extern void SMP_ConfirmReply (BD_ADDR bd_addr, UINT8 res);

/*******************************************************************************
**
** Function         SMP_OobDataReply
**
** Description      This function is called to provide the OOB data for
**                  SMP in response to SMP_OOB_REQ_EVT
**
** Parameters:      bd_addr     - Address of the peer device
**                  res         - result of the operation SMP_SUCCESS if success
**                  p_data      - SM Randomizer  C.
**
*******************************************************************************/
extern void SMP_OobDataReply(BD_ADDR bd_addr, tSMP_STATUS res, UINT8 len,
                             UINT8 *p_data);

/*******************************************************************************
**
** Function         SMP_SecureConnectionOobDataReply
**
** Description      This function is called to provide the SC OOB data for
**                  SMP in response to SMP_SC_OOB_REQ_EVT
**
** Parameters:      p_data      - pointer to the data
**
*******************************************************************************/
extern void SMP_SecureConnectionOobDataReply(UINT8 *p_data);

/*******************************************************************************
**
** Function         SMP_Encrypt
**
** Description      This function is called to encrypt the data with the specified
**                  key
**
** Parameters:      key                 - Pointer to key key[0] conatins the MSB
**                  key_len             - key length
**                  plain_text          - Pointer to data to be encrypted
**                                        plain_text[0] conatins the MSB
**                  pt_len              - plain text length
**                  p_out               - pointer to the encrypted outputs
**
**  Returns         Boolean - TRUE: encryption is successful
*******************************************************************************/
extern BOOLEAN SMP_Encrypt (UINT8 *key, UINT8 key_len,
                            UINT8 *plain_text, UINT8 pt_len,
                            tSMP_ENC *p_out);

/*******************************************************************************
**
** Function         SMP_KeypressNotification
**
** Description      This function is called to notify SM about Keypress Notification.
**
** Parameters:      bd_addr      - Address of the device to send keypress
**                                 notification to
**                  value        - keypress notification parameter value
**
*******************************************************************************/
extern void SMP_KeypressNotification (BD_ADDR bd_addr, UINT8 value);

/*******************************************************************************
**
** Function         SMP_CreateLocalSecureConnectionsOobData
**
** Description      This function is called to start creation of local SC OOB
**                  data set (tSMP_LOC_OOB_DATA).
**
** Parameters:      bd_addr      - Address of the device to send OOB data block
**                                 to.
**
**  Returns         Boolean - TRUE: creation of local SC OOB data set started.
*******************************************************************************/
extern BOOLEAN SMP_CreateLocalSecureConnectionsOobData (
                                                                  tBLE_BD_ADDR *addr_to_send_to);

#ifdef __cplusplus
}
#endif
#endif /* SMP_API_H */
