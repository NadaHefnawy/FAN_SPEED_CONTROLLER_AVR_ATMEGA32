/******************************************************************************
 *
 * Module: Fan Controller APP
 *
 * File Name: fan_controller.c
 *
 * Description: source file for the Fan Controller APP
 *
 * Author: Nada Hefnawy
 *
 *******************************************************************************/

#include "adc.h"
#include "DcMotor.h"
#include "lcd.h"
#include "std_types.h"
#include "lm35_sensor.h"
#include "pwm.h"
#define NMH return 0;
int main(void) {

	LCD_init();

	ADC_ConfigType ADC_Config_Ptr = { INTERNAL, F_CPU_8 };

	ADC_init(&ADC_Config_Ptr);

	DcMotor_Init();

	uint8 temperature;

	while (1) {
		/* Read the temperature and control the DC motor depending on it */
		temperature = LM35_getTemperature();
		if (temperature < 30) {
			DcMotor_Rotate(STOP, 0);
			LCD_displayStringRowColumn(0, 3, "Fan is OFF");
		} else if (temperature >= 120) {
			DcMotor_Rotate(CLOCKWISE, 100);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		} else if (temperature >= 90) {
			DcMotor_Rotate(CLOCKWISE, 75);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		} else if (temperature >= 60) {
			DcMotor_Rotate(CLOCKWISE, 50);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		} else if (temperature >= 30) {
			DcMotor_Rotate(CLOCKWISE, 25);
			LCD_displayStringRowColumn(0, 3, "Fan is ON ");
		}
		/* Print the temperature on the LCD */
		LCD_displayStringRowColumn(1, 3, "Temp = ");
		LCD_intgerToString(temperature);
		if (temperature < 100) {
			LCD_displayCharacter(' ');
		}
		LCD_displayString("C");
	}
	NMH
}
