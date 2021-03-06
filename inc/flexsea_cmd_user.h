/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-user' System commands & functions specific to
	user projects
	Copyright (C) 2016 Dephy, Inc. <http://dephy.com/>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************
	[Lead developper] Jean-Francois (JF) Duval, jfduval at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors]
*****************************************************************************
	[This file] flexsea_cmd_user: Interface to the user functions
****************************************************************************/

#ifndef INC_FLEXSEA_CMD_USER_H
#define INC_FLEXSEA_CMD_USER_H

//****************************************************************************
// Include(s)
//****************************************************************************

#include "flexsea_system.h"
#include "flexsea_user_structs.h"

//Include one or more a user project(s):
#include "../MIT_2DoF_Ankle_v1/inc/cmd-MIT_2DoF_Ankle_v1.h"
#include "../RICNU_Knee_v1/inc/cmd-RICNU_Knee_v1.h"
#include "../MotorTestBench/inc/cmd-MotorTestBench.h"

//****************************************************************************
// Prototype(s):
//****************************************************************************

void init_flexsea_payload_ptr_user(void);

//****************************************************************************
// Definition(s):
//****************************************************************************

//Give nickname to function codes here. Always remember that they have to be
//in the 100-127 range!

#define CMD_A2DOF				100
#define CMD_RICNU				101
#define CMD_READ_ALL_RICNU		102
#define CMD_MOTORTB				103

//****************************************************************************
// Structure(s):
//****************************************************************************

//****************************************************************************
// Shared variable(s)
//****************************************************************************


#endif	//INC_FLEXSEA_CMD_USER_H
