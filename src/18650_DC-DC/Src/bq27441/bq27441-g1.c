/*
 * driver_bq27441-g1.c
 *
 *  Created on: 26 ���. 2017 �.
 *      Author: user
 */

#include "bq27441-g1.h"
#include "main.h"

/*!
\brief Parsing of Flag Register result
\param [out] bq27441_g1 Initialized variable of type bq27441_g1_t
\param [in] regval Flag register value
*/

void BQ27441_G1_ParseFlags(bq27441_g1_t *bq27441_g1, uint16_t regval)
{
	//low byte
	bq27441_g1->flags.dsg = (regval & 0x01);
	bq27441_g1->flags.socf = (regval & 0x02) >> 1;
	bq27441_g1->flags.soc1 = (regval & 0x04) >> 2;
	bq27441_g1->flags.bat_det = (regval & 0x08) >> 3;
	bq27441_g1->flags.cfgupmode = (regval & 0x10) >> 4;
	bq27441_g1->flags.itpor = (regval & 0x20) >> 5;
	bq27441_g1->flags.ocvtaken = (regval & 0x80) >> 7;

	//high byte
	bq27441_g1->flags.chg = (regval & 0x100) >> 8;
	bq27441_g1->flags.fc = (regval & 0x200) >> 9;
	bq27441_g1->flags.ut = (regval & 0x4000) >> 14;
	bq27441_g1->flags.ot = (regval & 0x8000) >> 15;
}

/*!
\brief Parsing of Control Status Register result
\param [out] bq27441_g1 Initialized variable of type bq27441_g1_t
\param [in] regval Control Status register value
*/

void BQ27441_G1_ParseControlStatus(bq27441_g1_t *bq27441_g1, uint16_t regval)
{
	//low byte
	bq27441_g1->control_status.vok = (regval & 0x02) >> 1;
	bq27441_g1->control_status.rup_dis = (regval & 0x04) >> 2;
	bq27441_g1->control_status.ldmd = (regval & 0x08) >> 3;
	bq27441_g1->control_status.sleep = (regval & 0x10) >> 4;
	bq27441_g1->control_status.hibernate = (regval & 0x40) >> 6;
	bq27441_g1->control_status.initcomp = (regval & 0x80) >> 7;

	//high byte
	bq27441_g1->control_status.res_up = (regval & 0x100) >> 8;
	bq27441_g1->control_status.qmax_up = (regval & 0x200) >> 9;
	bq27441_g1->control_status.bca = (regval & 0x400) >> 10;
	bq27441_g1->control_status.cca = (regval & 0x800) >> 11;
	bq27441_g1->control_status.calmode = (regval & 0x1000) >> 12;
	bq27441_g1->control_status.ss = (regval & 0x2000) >> 13;
	bq27441_g1->control_status.wdreset = (regval & 0x4000) >> 14;
	bq27441_g1->control_status.shutdownen = (regval & 0x8000) >> 15;
}

/*!
\brief Parsing of Operation Configuration Register result
\param [out] bq27441_g1 Initialized variable of type bq27441_g1_t
\param [in] regval Operation Configuration Register value
*/

void BQ27441_G1_ParseOpConfig(bq27441_g1_t *bq27441_g1, uint16_t regval)
{
	//low byte
	bq27441_g1->op_config.temps = (regval & 0x01);
	bq27441_g1->op_config.batlowen = (regval & 0x04) >> 2;
	bq27441_g1->op_config.rmfcc = (regval & 0x10) >> 4;
	bq27441_g1->op_config.sleep = (regval & 0x20) >> 5;

	//high byte
	bq27441_g1->op_config.gpiopol = (regval & 0x800) >> 11;
	bq27441_g1->op_config.bi_pu_en = (regval & 0x1000) >> 12;
	bq27441_g1->op_config.bie = (regval & 0x2000) >> 13;
}

/* _______________STANDART COMMANDS FUNCTIONS_______________ */

/*!
\brief Getting value of temperature, measured by the fuel gauge 
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of temperature in Celsius
*/

float BQ27441_G1_GetTemperature(bq27441_g1_t *bq27441_g1)
{
	float result = 0;

	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_TEMPERATURE_CMD);

	//Kelvin to Celsius
	result = ((float)buffer * 0.1) - 273;

	return result;
}

/*!
\brief Getting value of the measured cell-pack voltage with a range of 0 to 6000 mV 
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of voltage in mV
*/

uint16_t BQ27441_G1_GetVoltage(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_VOLTAGE_CMD);
	return buffer;
}

/*!
\brief Getting the contents of the fuel gauging status register, depicting the current operating status
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of Flag Register
*/

uint16_t BQ27441_G1_GetFlags(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_FLAGS_CMD);
	BQ27441_G1_ParseFlags(bq27441_g1, buffer);
	return buffer;
}

/*!
\brief Getting value of  uncompensated (less than C/20 load) battery capacity remaining
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetNominalAvailableCapacity(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_NOMINAL_AVALIABLE_CAPACITY_CMD);
	return buffer;
}

/*!
\brief Getting value of  uncompensated (less than C/20 load) capacity of the battery when fully charged
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetFullAvailiableCApacity(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_FULL_AVALIABLE_CAPACITY_CMD);
	return buffer;
}

/*!
\brief Getting value of remaining battery capacity compensated for load and temperature
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetRemainingCapacity(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_REMAINING_CAPACITY_CMD);
	return buffer;
}

/*!
\brief Getting value of compensated capacity of the battery when fully charged
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetFullChargeCapacity(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_FULL_CHARGE_CAPACITY_CMD);
	return buffer;
}

/*!
\brief Getting value  that is the average current flow through the sense resistor
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of current in mA
*/

int16_t BQ27441_G1_GetAverageCurrent(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_AVERAGE_CURRENT_CMD);
	return buffer;
}

/*!
\brief Getting value of the measured standby current through the sense resistor
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of current in mA
*/

int16_t BQ27441_G1_GetStandbyCurrent(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_STANDBY_CURRENT_CMD);

	return buffer;
}

/*!
\brief Getting value of the maximum load conditions
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of current in mA
*/

int16_t BQ27441_G1_GetMaxLoadCurrent(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_MAX_LOAD_CURRENT_CMD);
	return buffer;
}

/*!
\brief Getting value  of the average power during charging and discharging of the battery.  It is negative during discharge and positive during charge. A value of 0
indicates that the battery is not being discharged
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of power in mW
*/

int16_t BQ27441_G1_GetAveragePower(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_AVERAGE_POWER_CMD);
	return buffer;
}

/*!
\brief Getting value of the predicted remaining battery capacity expressed as a percentage of FullChargeCapacity() with a range of 0 to 100%
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of predicted remaining battery capacity in %
*/

uint16_t BQ27441_G1_GetStateOfCharge(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_STATE_OF_CHARGE_CMD);
	return buffer;
}

/*!
\brief Getting value of the internal temperature sensor
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of temperature in Celsius
*/

uint16_t BQ27441_G1_GetInternalTemperature(bq27441_g1_t *bq27441_g1)
{
	float result = 0;
	uint16_t buffer;

	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_INTERNAL_TEMPERATURE_CMD);

	//Kelvin to Celsius
	result = ((float)buffer * 0.1) - 273;

	return result;
}

/*!
\brief Getting value, expressed as a percentage of the ratio of predicted FCC(25°C, SOH LoadI) over the DesignCapacity
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of SOH in %
*/

uint16_t BQ27441_G1_GetStateOfHealth(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_STATE_OF_HEALTH_CMD);
	return buffer;
}

/*!
\brief Getting value of the true battery capacity remaining
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetRemainingCapacityUnfiltered(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_REMAINING_CAPACITY_UNFILTERED_CMD);
	return buffer;
}

/*!
\brief Getting value of the filtered battery capacity remaining
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetRemainingCapacityFiltered(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_REMAINING_CAPACITY_FILTERED_CMD);
	return buffer;
}

/*!
\brief Getting value of the compensated capacity of the battery when fully charged
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetFullChargeCapacityUnfiltered(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_FULL_CHARGE_CAPACITY_UNFILTERED_CMD);
	return buffer;
}

/*!
\brief Getting value of the filtered compensated capacity of the battery when fully charged
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of capacity in mAh
*/

uint16_t BQ27441_G1_GetFullChargeCapacityFiltered(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_FULL_CHARGE_CAPACITY_FILTERED_CMD);
	return buffer;
}

/*!
\brief Getting value of the true state-of-charge
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of SOC in %
*/

uint16_t BQ27441_G1_GetStateOfChargeUnfiltered(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_STATE_OF_CHARGE_UNFILTERED_CMD);
	return buffer;
}

/* _________________________________________________________ */

/* _______________CONTROL SUBCOMANDS FUNCTIONS______________ */

/*!
\brief Reports the status of device.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of Conrol Status Register 
*/

void BQ27441_G1_GetControlStatus(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_CONTROL_STATUS_SUBCMD);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD);
	BQ27441_G1_ParseControlStatus(bq27441_g1, buffer);
}

/*!
\brief Reports the device type
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of device type (0x0421)
*/

uint16_t BQ27441_G1_GetDeviceType(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_DEVICE_TYPE_SUBCMD);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD);
	return buffer;
}

/*!
\brief Reports the firmware version of the device
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of the firmware version
*/

uint16_t BQ27441_G1_GetFwVersion(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_FW_VERSION_SUBCMD);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD);
	return buffer;
}

/*!
\brief Reports the configuration code stored in Data Memory
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of the DM code
*/

uint16_t BQ27441_G1_GetDmCode(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_DM_CODE_SUBCMD);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD);
	return buffer;
}

/*!
\brief Getting previous MAC command code
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Previous command code
*/

uint16_t BQ27441_G1_GetPrevMacwrite(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_PREV_MACWRITE_SUBCMD);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD);
	return buffer;
}

/*!
\brief Reports the chemical identifier of the battery profile used by the fuel gauge
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Expected value for bq27441-G1A - 0x0128, for bq27441-G1B - 0x0312.
*/

uint16_t BQ27441_G1_GetChemId(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_CHEM_ID_SUBCMD);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD);
	return buffer;
}

/*!
\brief Forces the Flags() [BAT_DET] bit to set when the battery insertion detection is disabled via OpConfig [BIE] = 0. 
In this case, the gauge does not detect battery insertion from the BIN pin logic state, but relies
on the BAT_INSERT host subcommand to indicate battery presence in the system.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_BatInsert(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_BAT_INSERT_SUBCMD);
}

/*!
\brief Forces the Flags() [BAT_DET] bit to clear when the battery insertion detection is disabled via OpConfig
[BIE] = 0. In this case, the gauge does not detect battery removal from the BIN pin logic state, but relies
on the BAT_REMOVE host subcommand to indicate battery removal from the system.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_BatRemove(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_BAT_REMOVE_SUBCMD);
}

/*!
\brief Instructs the fuel gauge to force the CONTROL_STATUS [HIBERNATE] bit to 1. If the necessary conditions are met, 
this enables the gauge to enter the HIBERNATE power mode after the transition to SLEEP power state is detected.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_SetHibernate(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_SET_HIBERNATE_SUBCMD);
}

/*!
\brief Instructs the fuel gauge to force the CONTROL_STATUS [HIBERNATE] bit to 0. This prevents the gauge
from entering the HIBERNATE power mode after the transition to SLEEP power state is detected.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_ClearHibernate(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_CLEAR_HIBERNATE_SUBCMD);
}

/*!
\brief Instructs the fuel gauge to enter CONFIG UPDATE mode
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_SetCfgUpdate(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_SET_CFGUPDATE_SUBCMD);
}

/*!
\brief Instructs the fuel gauge to enable SHUTDOWN mode
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_SetShutdownEnable(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_SHUTDOWN_ENABLE_SUBCMD);
}

/*!
\brief Instructs the fuel gauge to immediately enter SHUTDOWN mode
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_SetShutdown(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_SHUTDOWN_SUBCMD);
}

/*!
\brief Instructs the fuel gauge to  transition from UNSEALED state to SEALED state
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_SetSealed(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_SEALED_SUBCMD);
}

/*!
\brief Commands the device to toggle the GPOUT pin for 1 ms
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_ToggleGpout(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_TOGGLE_GPOUT_SUBCMD);
}

/*!
\brief Performs a full device reset
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_Reset(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_RESET_SUBCMD);
}

/*!
\brief Performs a partial (soft) reset from any mode with an OCV (open-circuit voltage) measurement
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_SoftReset(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_SOFT_RESET_SUBCMD);
}

/*!
\brief Exits CONFIG UPDATE mode without an OCV (open-circuit voltage) measurement and without resimulating to update StateOfCharge()
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_ExitCfgUpdate(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_EXIT_CFGUPDATE_SUBCMD);
}

/*!
\brief Exits CONFIG UPDATE mode without an OCV measurement and resimulates with the updated configuration data to update StateOfCharge()
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_ExitResim(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, BQ27441_G1_EXIT_RESIM_SUBCMD);
}

// MAT: Bad implementation.  LA funcion de Write solo espera un valor de 8 bits. Si le pasas un uint16_t lo hace mal
void BQ27441_G1_SetUnsealed(bq27441_g1_t *bq27441_g1)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_CONTROL_CMD, 0x8000);
}

/* _________________________________________________________ */

/* ________________EXTENDED COMMANDS FUNCTION_______________ */

/*!
\brief Getting value of the  Operation Configuration Register (which is most useful for system level debug to quickly determine device configuration)
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of the Operation Configuration Register
*/

uint16_t BQ27441_G1_GetOpConfig(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_OP_CONFIG_CMD);
	BQ27441_G1_ParseOpConfig(bq27441_g1, buffer);
	return buffer;
}

/*!
\brief Getting Design Capacity Data Memory value (which is most useful for system level debug to quickly determine device configuration)
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of the capacity in mAh
*/

uint16_t BQ27441_G1_GetDesignCapacity(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_DESIGN_CAPACITY_CMD);
	return buffer;
}

void BQ27441_G1_WriteDataClass(bq27441_g1_t *bq27441_g1, uint8_t value)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_DATA_CLASS_CMD, value);
}

/*!
\brief Setting the data block to be accessed. When 0x00 is written to BlockDataControl(), DataBlock() holds the block number of the data to be read or written.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\param [in] value value = 0x00 to access data located at offset 0 to 31, value = 0x01 to access data located at offset 32 to 41.
\return Value of the data block
*/

uint16_t BQ27441_G1_GetDataBlock(bq27441_g1_t *bq27441_g1, uint8_t value)
{
	uint16_t buffer;
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_DATA_BLOCK_CMD, value);
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_DATA_BLOCK_CMD);
	return buffer;
}

/*uint16_t BQ27441_G1_BlockData (bq27441_g1_t * bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_BLOCK_DATA_CMD);
	return buffer;
}*/

/*!
\brief Getting value of checksum on the 32 bytes of block data
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
\return Value of checksum
*/

uint16_t BQ27441_G1_GetChecksum(bq27441_g1_t *bq27441_g1)
{
	uint16_t buffer;
	buffer = bq27441_g1->Read(BQ27441_G1_ADDR, BQ27441_G1_BLOCK_DATA_CHECKSUM_CMD);
	return buffer;
}

void BQ27441_G1_WriteChecksum(bq27441_g1_t *bq27441_g1, uint16_t value)
{
	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_BLOCK_DATA_CHECKSUM_CMD, value);
}

/*!
\brief Used to control the data access mode. Writing 0x00 to this command enables BlockData() to access to RAM.
\param [in] bq27441_g1 Initialized variable of type bq27441_g1_t
*/

void BQ27441_G1_BlockDataControl(bq27441_g1_t *bq27441_g1)
{

	bq27441_g1->Write(BQ27441_G1_ADDR, BQ27441_G1_BLOCK_DATA_CONTROL_CMD, 0x00);
}

void BQ27441_G1_Setup(bq27441_g1_t *bq27441_g1, uint16_t capacity, uint16_t tVoltage)
{

	BQ27441_G1_GetFlags(bq27441_g1);
	if (!bq27441_g1->flags.itpor) {
		return;
	}

	uint16_t designEnergy = 3.7 * capacity;
	// Taper current of BQ24075 is 1A, so 0.1*1A + 10% or more => 130mA
	// Taper rate = DesignCapacity / (0.1 * Taper current)
	uint16_t taperRate = capacity / 13;

	volatile HAL_StatusTypeDef result;

	// Unseal
	uint8_t unseal_code[2] = {0x00, 0x80};
	result = i2c_write(BQ27441_G1_ADDR, 0x00, unseal_code, 2);
	HAL_Delay(10);
	result = i2c_write(BQ27441_G1_ADDR, 0x00, unseal_code, 2);

	BQ27441_G1_SetCfgUpdate(bq27441_g1);
	HAL_Delay(1500);
	BQ27441_G1_GetFlags(bq27441_g1);

	uint8_t tempval = 0x00;
	result = i2c_write(BQ27441_G1_ADDR, 0x61, &tempval, 1);

	tempval = 0x52;
	result = i2c_write(BQ27441_G1_ADDR, 0x3E, &tempval, 1);

	tempval = 0x00;
	result = i2c_write(BQ27441_G1_ADDR, 0x3F, &tempval, 1);

	volatile uint8_t old_csum[2] = {0};
	i2c_read(BQ27441_G1_ADDR, 0x60, old_csum, 2);
	uint8_t old_designCap[2] = {0};
	i2c_read(BQ27441_G1_ADDR, 0x4A, old_designCap, 2);
	uint8_t old_designEnergy[2] = {0};
	i2c_read(BQ27441_G1_ADDR, 0x4C, old_designEnergy, 2);
	uint8_t old_terminateVolage[2] = {0};
	i2c_read(BQ27441_G1_ADDR, 0x50, old_terminateVolage, 2);
	uint8_t old_taperRate[2] = {0};
	i2c_read(BQ27441_G1_ADDR, 0x5B, old_taperRate, 2);


	uint8_t newCap_mod[2] = {(capacity >> 8) & 0x00FF, capacity & 0x00FF};
	result = i2c_write(BQ27441_G1_ADDR, 0x4A, newCap_mod, 2);

	uint8_t newNrgy_mod[2] = {(designEnergy >> 8) & 0x00FF, designEnergy & 0x00FF};
	result = i2c_write(BQ27441_G1_ADDR, 0x4C, newNrgy_mod, 2);

	uint8_t newTermV_mod[2] = {(tVoltage >> 8) & 0x00FF, tVoltage & 0x00FF};
	result = i2c_write(BQ27441_G1_ADDR, 0x50, newTermV_mod, 2);

	uint8_t newTaper_mod[2] = {(taperRate >> 8) & 0x00FF, taperRate & 0x00FF};
	result = i2c_write(BQ27441_G1_ADDR, 0x5B, newTaper_mod, 2);

	volatile uint8_t chkTemp = (255 - old_csum[0] - old_designCap[0] - old_designCap[1] - old_designEnergy[0] - old_designEnergy[1] - old_terminateVolage[0] - old_terminateVolage[1] - old_taperRate[0] - old_taperRate[1]) % 256;
	volatile uint8_t new_checksum = 255 - ((chkTemp + newCap_mod[0] + newCap_mod[1] + newNrgy_mod[0] + newNrgy_mod[1] + newTermV_mod[0] + newTermV_mod[1] + newTaper_mod[0] + newTaper_mod[1]) % 256);
	result = i2c_write(BQ27441_G1_ADDR, 0x60, &new_checksum, 1);
	BQ27441_G1_SoftReset(bq27441_g1);
	HAL_Delay(1500);
	BQ27441_G1_SetSealed(bq27441_g1);
	HAL_Delay(20);
}

/* _________________________________________________________ */
