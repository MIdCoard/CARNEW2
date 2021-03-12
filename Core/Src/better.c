#include "better.h"

UART_HandleTypeDef* obj;

uint8_t packet[100];

uint8_t isStart = 0;
uint8_t isWaitingType = 0;
uint8_t type = 0;
uint8_t counts = 0;
uint8_t pos = 0;

uint8_t isLaunch = 0;

uint8_t data[6];

float roll,pitch,yaw;

float getPitch() {
	return pitch;
}

float getRoll() {
	return roll ;
	//offset
}

float getYaw() {
	return yaw;
}

void dealData() {
	if (type == 0xAE) {
		int16_t temp;
		temp = (data[0] << 8) | data[1];
		pitch = temp * 0.01f;
		temp = (data[2] << 8) | data[3];
		roll = temp * 0.01f;
		temp = (data[4] << 8) | data[5];
		yaw = temp * 0.01f;
	}
}

//void handleType() {
//	counts++;
//	if (type == 0xAE) {
//		println("????");
//		data[counts - 1] = packet[0];
//		if (counts == 6) {
//			isWaitingExit = 1;
//			dealData();
//		}
//	} else {
//		printIntln(type);
//	}
////	switch (type) {
////		case 0xA0: {
////			if (counts == 6)
////				isWaitingExit = 1;
////			println("A0");
////			break;
////		}
////		case 0xAA: {
////			if (counts == 6)
////				isWaitingExit = 1;
////			println("AA");
////			break;
////		}
////		case 0xAB: {
////			if (counts == 6)
////				isWaitingExit = 1;
////			println("AB");
////			break;
////		}
////		case 0xAE: {
////			data[counts - 1] = packet;
////			if (counts == 6) {
////				isWaitingExit = 1;
////				dealData();
////			}
////			break;
////		}
////		case 0xAC: {
////			if (counts == 4)
////				isWaitingExit = 1;
////			println("AC");
////			break;
////		}
////		case 0xAD: {
////			if (counts == 4)
////				isWaitingExit = 1;
////			println("AD");
////			break;
////		}
////		case 0xAF: {
////			if (counts == 4)
////				isWaitingExit = 1;
////			println("AF");
////			break;
////		}
////		default: {
////			print("ERROR:");
////			printIntln(type);
////			isStart = 0;
////		}
////	}
//}

void handleBetter() {
	if ((!isLaunch && packet[0] == 0xBA) || isLaunch) {
		isLaunch = 1;
		if (!isStart) {
			if (packet[0] == 0xBA) {
				isStart = 1;
				isWaitingType = 1;
			}
		} else {
			if (isWaitingType) {
				pos = 0;
				isWaitingType = 0;
				type = packet[0];
				if (type == 0xA0 || type == 0xAE || type == 0xAB || type == 0xAA) {
					counts = 7;
				} else if (type == 0xAC || type == 0xAD || type == 0xAF) {
					counts = 5;
				} else
					isLaunch = 0;
			} else {
				data[pos++] = packet[0];
				if (pos == counts) {
					dealData();
					isStart = 0;
				}
			}
		}
	}
	receive();
}

void receive() {
	HAL_UART_Receive_IT(obj,packet,1);
}

void initBetter(UART_HandleTypeDef*handle) {
	addUsartHandler(*handle,handleBetter);
	obj = handle;
	receive();
}
