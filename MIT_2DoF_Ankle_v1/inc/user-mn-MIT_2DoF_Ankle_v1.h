/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-manage' Mid-level computing, and networking
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
	[This file] user_ankle_2dof: 2-DoF Ankle Functions
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-09-23 | jfduval | Initial GPL-3.0 release
	*
****************************************************************************/

#include "main.h"

#ifdef BOARD_TYPE_FLEXSEA_MANAGE

#ifndef INC_ANKLE_2DOF_H
#define INC_ANKLE_2DOF_H

//****************************************************************************
// Include(s)
//****************************************************************************

	
//****************************************************************************
// Shared variable(s)
//****************************************************************************

//****************************************************************************
// Public Function Prototype(s):
//****************************************************************************	

void init_ankle_2dof(void);
void ankle_2dof_fsm_1(void);
void ankle_2dof_fsm_2(void);

//****************************************************************************
// Definition(s):
//****************************************************************************	

//****************************************************************************
// Structure(s)
//****************************************************************************	

	
#endif	//INC_ANKLE_2DOF_H

#endif 	//BOARD_TYPE_FLEXSEA_MANAGE
