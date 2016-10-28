/****************************************************************************
	[Project] FlexSEA: Flexible & Scalable Electronics Architecture
	[Sub-project] 'flexsea-user' User projects
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
	[Lead developper] Luke Mooney, lmooney at dephy dot com.
	[Origin] Based on Jean-Francois Duval's work at the MIT Media Lab 
	Biomechatronics research group <http://biomech.media.mit.edu/>
	[Contributors]
*****************************************************************************
	[This file] user-ex-MIT_2DoF_Ankle_v1: User code running on Execute
*****************************************************************************
	[Change log] (Convention: YYYY-MM-DD | author | comment)
	* 2016-10-28 | jfduval | New release
	*
****************************************************************************/
 
#ifdef BOARD_TYPE_FLEXSEA_EXECUTE

//****************************************************************************
// Include(s)
//****************************************************************************
 
#include "main.h"
#include "../inc/user-ex-MIT_2DoF_Ankle_v1.h"
 
//****************************************************************************
// Variable(s)
//****************************************************************************
 
int state = 0;
int32 ankle_ang = 0, mot_ang = 0, ankle_trans = 0, angle_zero=0, init_angle;
int32 ankle_vel = 0, mot_vel, ankle_torque, last_ankle_torque;
int32 ank_angs[6] = {0,0,0,0,0,0};
int32 mot_angs[6] = {0,0,0,0,0,0};
 
//****************************************************************************
// Private Function Prototype(s):
//****************************************************************************  
 
static void ankle_refresh_values(void);
static int16 get_ankle_trans(double);
static int16 get_ankle_ang(double);
 
//****************************************************************************
// Public Function(s)
//****************************************************************************
 
//Call this function once in main.c, just before the while()
void init_ankle_2dof(void)
{   
    //Controller setup:
    ctrl.active_ctrl = CTRL_OPEN;   //Position controller
    motor_open_speed_1(0);              //0% PWM
	#if(MOTOR_COMMUT == COMMUT_BLOCK)
    Coast_Brake_Write(1);               //Brake (regen)
	#endif
        
    //Position PID gains - initially 0
    ctrl.position.gain.P_KP = 0;
    ctrl.position.gain.P_KI = 0;
    angle_zero = as5047.raw.ang_clks*360/16384+16.4*44*28/12/13;
    init_angle = as5047.raw.ang_clks;   
}
 
//Knee Finite State Machine.
//Call this function in one of the main while time slots.
void ankle_fsm(void)
{
    static int state = -2;
    static int32 state_t = 0;
    state_t++;
     
    ankle_refresh_values();
     
    switch (state)
    {
        case(-2):
            motor_open_speed_1(60);
            if (mot_vel>-10 && state_t>200)
            {
                state_t = 0;
                state = -1;
                angle_zero = as5047.raw.ang_clks*360/16384; 
            }
            break;
        case(-1):
            motor_open_speed_1(-60);
            if (ankle_ang<2000)
            {
                state_t = 0;
                state = 0;
            }
            break;
        case (0):
            ctrl.active_ctrl = CTRL_CURRENT;
            ctrl.current.gain.I_KP = 30;
            ctrl.current.gain.I_KI = 15;
            if (ankle_ang<= 2000)
            {
                set_ankle_torque((ankle_ang-2000)*50);
            }
            else
            {
                set_ankle_torque((ankle_ang-2000)*100);
            }
             
            if (ankle_ang<1500)
            {
                state_t = 0;
                state = 1;
            }
            break;
        case (1):
         
            ankle_torque = (ankle_ang-2000)*50+state_t*state_t/2; //negative value
            if (ankle_torque > last_ankle_torque)
            {
                ankle_torque = last_ankle_torque;
            }
            last_ankle_torque = ankle_torque;
            set_ankle_torque(ankle_torque);
             
            if (ankle_ang>= 2000)
            {
                state_t = 0;
                state = 0;
                last_ankle_torque = 0;
            }
            break;
    }
     
     
}

#if(ACTIVE_PROJECT == PROJECT_ANKLE_2DOF)
int32 get_enc_custom()
{
    int32 mt;
    #if(ACTIVE_SUBPROJECT == SUBPROJECT_A)
		#if(RUNTIME_FSM == ENABLED)
        	mt = (as5047.angle_cont)*360/16384-angle_zero-16.4*44*28/12/13;
		#else
			mt = (as5047.angle_cont)*360/16384;
		#endif
    #else
		#if(RUNTIME_FSM == ENABLED)
        	mt = (-as5047.angle_cont)*360/16384+angle_zero-16.4*44*28/12/13;
		#else
			mt = -(as5047.angle_cont)*360/16384;
		#endif
    #endif
    return mt;
}
#endif
 
//****************************************************************************
// Private Function(s)
//****************************************************************************
 
//Note: 'static' makes them private; they can only called from functions in this
//file. It's safer than making everything global.
 
//Here's an example function:
static void ankle_refresh_values(void)
{
    //Motor angle in degrees
    mot_ang = get_enc_custom();
     
    ankle_ang = get_ankle_ang(mot_ang);
 
    ankle_trans = get_ankle_trans(mot_ang);
     
    ank_angs[5] = ank_angs[4];
    ank_angs[4] = ank_angs[3];
    ank_angs[3] = ank_angs[2];
    ank_angs[2] = ank_angs[1];
    ank_angs[1] = ank_angs[0];
    ank_angs[0] = ankle_ang;
     
    mot_angs[5] = mot_angs[4];
    mot_angs[4] = mot_angs[3];
    mot_angs[3] = mot_angs[2];
    mot_angs[2] = mot_angs[1];
    mot_angs[1] = mot_angs[0];
    #if(ACTIVE_SUBPROJECT == SUBPROJECT_A)
        mot_angs[0] = as5047.raw.ang_clks;
    #else
        mot_angs[0] = -as5047.raw.ang_clks;
    #endif
     
     
    ankle_vel = (ank_angs[0]-ank_angs[5])*1000/5;
    mot_vel = (mot_angs[0]-mot_angs[5]);
     
}
 
 
//returns the ankle angle [deg x 100]
int16 get_ankle_ang(double ma) //mot_ang [deg] where mot_ang = 0 is at maximum dorsiflexion
{
    static double a0 = 202.2+1140, a1 = 1302, b1 = 14.76, a2 = -39.06, b2 = -7.874, w = 0.00223;
    if (ma<0) {ma = 0;}
    return (int16)(a0+a1*cos(ma*w)+b1*sin(ma*w)+a2*cos(ma*w*2)+b2*sin(ma*w*2));
}
 
//returns the current transmission ration [N*10]
int16 get_ankle_trans(double ma) //mot_ang [deg] where mot_ang = 0 is at maximum dorsiflexion
{
    static double a0 = 202.2+1140, a1 = 1302, b1 = 14.76, a2 = -39.06, b2 = -7.874, w = 0.00223;
    double slope;
    if (ma<0) {ma = 0;}
     
    slope = (-w*a1*sin(ma*w)+w*b1*cos(ma*w)-2*w*a2*sin(ma*w*2)+2*w*b2*cos(ma*w*2));
    #if(ACTIVE_SUBPROJECT == SUBPROJECT_A)
        double transmission = ((double)(1000.0/slope));
    #else
        double transmission = ((double)(-1000.0/slope));
    #endif
     
     
    if (transmission >3000){return 3000;}
    else {return (int16)transmission;}
}
 
void set_ankle_torque(int32 des_torque) //des_torque in mNm
{
    int32 motor_torque = des_torque/(ankle_trans/10); //[mNm] at the motor
    int32 des_motor_current = motor_torque*10; //[mA] at the motor 
    ctrl.current.setpoint_val = des_motor_current/12; //[current IU]
}
 
//That function can be called from the FSM.

#endif //BOARD_TYPE_FLEXSEA_EXECUTE
