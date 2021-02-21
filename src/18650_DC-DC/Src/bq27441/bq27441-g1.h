/*
 * bq27441-g1.h
 *
 *  Created on: 24 ���. 2017 �.
 *      Author: user
 */
#include <stdint.h>

#ifndef INC_BQ27441_G1_H_
#define INC_BQ27441_G1_H_

/* ______________________DEFINE Section______________________ */

/*Device address*/
#define BQ27441_G1_ADDR									0x55

/* _________________________________________________________ */


/* ____________________STANDART COMMANDS____________________ */

#define BQ27441_G1_CONTROL_CMD							0x00
#define BQ27441_G1_TEMPERATURE_CMD						0x02
#define BQ27441_G1_VOLTAGE_CMD							0x04
#define BQ27441_G1_FLAGS_CMD							0x06
#define BQ27441_G1_NOMINAL_AVALIABLE_CAPACITY_CMD		0x08
#define BQ27441_G1_FULL_AVALIABLE_CAPACITY_CMD			0x0A
#define BQ27441_G1_REMAINING_CAPACITY_CMD				0x0C
#define BQ27441_G1_FULL_CHARGE_CAPACITY_CMD				0x0E
#define BQ27441_G1_AVERAGE_CURRENT_CMD					0x10
#define BQ27441_G1_STANDBY_CURRENT_CMD					0x12
#define BQ27441_G1_MAX_LOAD_CURRENT_CMD					0x14
#define BQ27441_G1_AVERAGE_POWER_CMD					0x18
#define BQ27441_G1_STATE_OF_CHARGE_CMD					0x1C
#define BQ27441_G1_INTERNAL_TEMPERATURE_CMD				0x1E
#define BQ27441_G1_STATE_OF_HEALTH_CMD					0x20
#define BQ27441_G1_REMAINING_CAPACITY_UNFILTERED_CMD	0x28
#define BQ27441_G1_REMAINING_CAPACITY_FILTERED_CMD		0x2A
#define BQ27441_G1_FULL_CHARGE_CAPACITY_UNFILTERED_CMD	0x2C
#define BQ27441_G1_FULL_CHARGE_CAPACITY_FILTERED_CMD	0x2E
#define BQ27441_G1_STATE_OF_CHARGE_UNFILTERED_CMD		0x30

/* ____________BQ27441-G1_CONTROL_CMD SUBCOMMANDS____________ */

#define BQ27441_G1_CONTROL_STATUS_SUBCMD				0x0000
#define BQ27441_G1_DEVICE_TYPE_SUBCMD					0x0001
#define BQ27441_G1_FW_VERSION_SUBCMD					0x0002
#define BQ27441_G1_DM_CODE_SUBCMD						0x0004
#define BQ27441_G1_PREV_MACWRITE_SUBCMD					0x0007
#define BQ27441_G1_CHEM_ID_SUBCMD						0x0008
#define BQ27441_G1_BAT_INSERT_SUBCMD					0x000C
#define BQ27441_G1_BAT_REMOVE_SUBCMD					0x000D
#define BQ27441_G1_SET_HIBERNATE_SUBCMD					0x0011
#define BQ27441_G1_CLEAR_HIBERNATE_SUBCMD				0x0012
#define BQ27441_G1_SET_CFGUPDATE_SUBCMD					0x0013
#define BQ27441_G1_SHUTDOWN_ENABLE_SUBCMD				0x001B
#define BQ27441_G1_SHUTDOWN_SUBCMD						0x001C
#define BQ27441_G1_SEALED_SUBCMD						0x0020
#define BQ27441_G1_TOGGLE_GPOUT_SUBCMD					0x0023
#define BQ27441_G1_RESET_SUBCMD							0x0041
#define BQ27441_G1_SOFT_RESET_SUBCMD					0x0042
#define BQ27441_G1_EXIT_CFGUPDATE_SUBCMD				0x0043
#define BQ27441_G1_EXIT_RESIM_SUBCMD					0x0044

/* _________________________________________________________ */

/* ____________________EXTENDED COMMANDS____________________ */

#define  BQ27441_G1_OP_CONFIG_CMD						0x3A
#define  BQ27441_G1_DESIGN_CAPACITY_CMD					0x3C
#define  BQ27441_G1_DATA_CLASS_CMD						0x3E
#define  BQ27441_G1_DATA_BLOCK_CMD						0x3F
#define  BQ27441_G1_BLOCK_DATA_CMD						0x40
#define  BQ27441_G1_BLOCK_DATA_CHECKSUM_CMD				0x60
#define  BQ27441_G1_BLOCK_DATA_CONTROL_CMD				0x61

/* _________________________________________________________ */

/* ______________________Types  Section_____________________ */

typedef struct {
	//high byte
	uint8_t ot;
	uint8_t ut;
	uint8_t fc;
	uint8_t chg;
	//low byte
	uint8_t ocvtaken;
	uint8_t itpor;
	uint8_t cfgupmode;
	uint8_t bat_det;
	uint8_t soc1;
	uint8_t socf;
	uint8_t dsg;
} flags_t;

typedef struct {
	//high byte
	uint8_t shutdownen;
	uint8_t wdreset;
	uint8_t ss;
	uint8_t calmode;
	uint8_t cca;
	uint8_t bca;
	uint8_t qmax_up;
	uint8_t res_up;
	//low byte
	uint8_t initcomp;
	uint8_t hibernate;
	uint8_t sleep;
	uint8_t ldmd;
	uint8_t rup_dis;
	uint8_t vok;
} control_status_t;

typedef struct {
	//low byte
	uint8_t sleep;
	uint8_t rmfcc;
	uint8_t batlowen;
	uint8_t temps;
	//high byte
	uint8_t bie;
	uint8_t bi_pu_en;
	uint8_t gpiopol;
} op_config_t;

typedef struct {
	void (*Write)(uint16_t addr, uint8_t regOffset, uint8_t data);
	uint16_t (*Read)(uint16_t addr, uint8_t regOffset);
	flags_t flags;
	control_status_t control_status;
	op_config_t op_config;
} bq27441_g1_t;


/* _________________________________________________________ */



/* ____________________Prototypes Section___________________ */


void BQ27441_G1_ParseFlags(bq27441_g1_t * bq27441_g1, uint16_t regval);
void BQ27441_G1_ParseControlStatus(bq27441_g1_t * bq27441_g1, uint16_t regval);
void BQ27441_G1_ParseOpConfig(bq27441_g1_t * bq27441_g1, uint16_t regval);

/* _______________STANDART COMMANDS FUNCTIONS_______________ */

float BQ27441_G1_GetTemperature(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetVoltage(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetFlags(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetNominalAvailableCapacity(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetFullAvailiableCApacity(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetRemainingCapacity(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetFullChargeCapacity(bq27441_g1_t * bq27441_g1);
int16_t  BQ27441_G1_GetAverageCurrent(bq27441_g1_t * bq27441_g1);
int16_t  BQ27441_G1_GetStandbyCurrent(bq27441_g1_t * bq27441_g1);
int16_t  BQ27441_G1_GetMaxLoadCurrent(bq27441_g1_t * bq27441_g1);
int16_t  BQ27441_G1_GetAveragePower(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetStateOfCharge(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetInternalTemperature(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetStateOfHealth(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetRemainingCapacityUnfiltered(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetRemainingCapacityFiltered(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetFullChargeCapacityUnfiltered(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetFullChargeCapacityFiltered(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetStateOfChargeUnfiltered(bq27441_g1_t * bq27441_g1);

/* _________________________________________________________ */



/* _______________CONTROL SUBCOMANDS FUNCTIONS______________ */

void BQ27441_G1_GetControlStatus(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetDeviceType(bq27441_g1_t * bq27441_g1);
uint16_t BQ27441_G1_GetFwVersion(bq27441_g1_t * bq27441_g1);	//return the firmware version
uint16_t BQ27441_G1_GetDmCode(bq27441_g1_t * bq27441_g1);		//return the 8-bit DM Code as the least significant byte
uint16_t BQ27441_G1_GetPrevMacwrite(bq27441_g1_t * bq27441_g1);	//return the previous command written to CONTROL
uint16_t BQ27441_G1_GetChemId(bq27441_g1_t * bq27441_g1);		//return the chemical identifier for the Impedance Track� configuration
void BQ27441_G1_BatInsert (bq27441_g1_t * bq27441_g1);			//forces the Flags() [BAT_DET] bit to set when the battery insertion detection is disabled via OpConfig[BIE] = 0.
void BQ27441_G1_BatRemove (bq27441_g1_t * bq27441_g1);			//forces the Flags() [BAT_DET] bit to clear when the battery insertion detection is disabled via OpConfig[BIE] = 0.
void BQ27441_G1_SetHibernate (bq27441_g1_t * bq27441_g1);		//force the CONTROL_STATUS [HIBERNATE] bit to 1.
void BQ27441_G1_ClearHibernate (bq27441_g1_t * bq27441_g1);		//force the CONTROL_STATUS [HIBERNATE] bit to 0.
void BQ27441_G1_SetCfgUpdate (bq27441_g1_t * bq27441_g1);		//set the Flags() [CFGUPMODE] bit to 1 and enter CONFIG UPDATE mode.
void BQ27441_G1_SetShutdownEnable (bq27441_g1_t * bq27441_g1);	//enable SHUTDOWN mode and set the CONTROL_STATUS [SHUTDOWNEN]status bit.
void BQ27441_G1_SetShutdown (bq27441_g1_t * bq27441_g1);		//immediately enter SHUTDOWN mode after receiving this subcommand.
void BQ27441_G1_SetSealed (bq27441_g1_t * bq27441_g1);			//transition from UNSEALED state to SEALED state
void BQ27441_G1_ToggleGpout (bq27441_g1_t * bq27441_g1);		//pulse the GPOUT pin for approximately 1 ms within 1 second of receiving the command
void BQ27441_G1_Reset (bq27441_g1_t * bq27441_g1);				//perform a full device reset
void BQ27441_G1_SoftReset (bq27441_g1_t * bq27441_g1);			//perform a partial (soft) reset from any mode with an OCV measurement
void BQ27441_G1_ExitCfgUpdate (bq27441_g1_t * bq27441_g1);
void BQ27441_G1_ExitResim (bq27441_g1_t * bq27441_g1);


void BQ27441_G1_SetUnsealed (bq27441_g1_t * bq27441_g1);

/* _________________________________________________________ */



/* ________________EXTENDED COMMANDS FUNCTION_______________ */

uint16_t BQ27441_G1_GetOpConfig(bq27441_g1_t * bq27441_g1);						//return OpConfig Data Memory register setting
uint16_t BQ27441_G1_GetDesignCapacity(bq27441_g1_t * bq27441_g1);				//returns the Design Capacity Data Memory value
void BQ27441_G1_WriteDesignCapacity(bq27441_g1_t * bq27441_g1, uint16_t value);
void BQ27441_G1_WriteDataClass (bq27441_g1_t * bq27441_g1, uint8_t value);		//sets the data class to be accessed
uint16_t BQ27441_G1_GetDataBlock (bq27441_g1_t * bq27441_g1, uint8_t value);	//To access data located at offset 0 to 31, value = 0x00. To access data located at offset 32 to 41, value = 0x01.
uint16_t BQ27441_G1_BlockData (bq27441_g1_t * bq27441_g1);						// remainder of the 32-byte data block when accessing general block data
uint16_t BQ27441_G1_GetChecksum (bq27441_g1_t * bq27441_g1);					// contains the checksum on the 32 bytes of block data read or written.
void BQ27441_G1_WriteChecksum (bq27441_g1_t * bq27441_g1, uint16_t value);
void BQ27441_G1_BlockDataControl (bq27441_g1_t * bq27441_g1);					// control the data access mode.

/* _________________________________________________________ */


void BQ27441_G1_Setup(bq27441_g1_t * bq27441_g1, uint16_t capacity, uint16_t tVoltage);

#endif /* INC_BQ27441_G1_H_ */
