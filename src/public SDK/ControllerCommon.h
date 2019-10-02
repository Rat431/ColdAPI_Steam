//==========================  Open Steamworks  ================================
//
// This file is part of the Open Steamworks project. All individuals associated
// with this project do not claim ownership of the contents
// 
// The code, comments, and all related files, projects, resources,
// redistributables included with this project are Copyright Valve Corporation.
// Additionally, Valve, the Valve logo, Half-Life, the Half-Life logo, the
// Lambda logo, Steam, the Steam logo, Team Fortress, the Team Fortress logo,
// Opposing Force, Day of Defeat, the Day of Defeat logo, Counter-Strike, the
// Counter-Strike logo, Source, the Source logo, and Counter-Strike Condition
// Zero are trademarks and or registered trademarks of Valve Corporation.
// All other trademarks are property of their respective owners.
//
//=============================================================================

#ifndef CONTROLLERCOMMON_H
#define CONTROLLERCOMMON_H
#ifdef _WIN32
#pragma once
#endif


#define STEAMCONTROLLER_INTERFACE_VERSION "STEAMCONTROLLER_INTERFACE_VERSION"
#define STEAMCONTROLLER_INTERFACE_VERSION002 "SteamController002"
#define STEAMCONTROLLER_INTERFACE_VERSION003 "SteamController003"
#define STEAMCONTROLLER_INTERFACE_VERSION004 "SteamController004"
#define STEAMCONTROLLER_INTERFACE_VERSION005 "SteamController005"
#define STEAMCONTROLLER_INTERFACE_VERSION006 "SteamController006"
#define STEAMCONTROLLER_INTERFACE_VERSION007 "SteamController007"

#define STEAM_CONTROLLER_MAX_COUNT 16

#define STEAM_CONTROLLER_MAX_ANALOG_ACTIONS 16

#define STEAM_CONTROLLER_MAX_DIGITAL_ACTIONS 32

#define STEAM_CONTROLLER_MAX_ORIGINS 8

// When sending an option to a specific controller handle, you can send to all controllers via this command
#define STEAM_CONTROLLER_HANDLE_ALL_CONTROLLERS UINT64_MAX

#define STEAM_CONTROLLER_MIN_ANALOG_ACTION_DATA -1.0f
#define STEAM_CONTROLLER_MAX_ANALOG_ACTION_DATA 1.0f

enum ESteamControllerPad
{
	k_ESteamControllerPad_Left,
	k_ESteamControllerPad_Right
};

enum EControllerSource
{
	k_EControllerSource_None,
	k_EControllerSource_LeftTrackpad,
	k_EControllerSource_RightTrackpad,
	k_EControllerSource_Joystick,
	k_EControllerSource_ABXY,
	k_EControllerSource_Switch,
	k_EControllerSource_LeftTrigger,
	k_EControllerSource_RightTrigger,
	k_EControllerSource_Gyro
};

enum EControllerSourceMode
{
	k_EControllerSourceMode_None,
	k_EControllerSourceMode_Dpad,
	k_EControllerSourceMode_Buttons,
	k_EControllerSourceMode_FourButtons,
	k_EControllerSourceMode_AbsoluteMouse,
	k_EControllerSourceMode_RelativeMouse,
	k_EControllerSourceMode_JoystickMove,
	k_EControllerSourceMode_JoystickCamera,
	k_EControllerSourceMode_ScrollWheel,
	k_EControllerSourceMode_Trigger,
	k_EControllerSourceMode_TouchMenu
};

enum EControllerActionOrigin
{
	k_EControllerActionOrigin_None,
	k_EControllerActionOrigin_A,
	k_EControllerActionOrigin_B,
	k_EControllerActionOrigin_X,
	k_EControllerActionOrigin_Y,
	k_EControllerActionOrigin_LeftBumper,
	k_EControllerActionOrigin_RightBumper,
	k_EControllerActionOrigin_LeftGrip,
	k_EControllerActionOrigin_RightGrip,
	k_EControllerActionOrigin_Start,
	k_EControllerActionOrigin_Back,
	k_EControllerActionOrigin_LeftPad_Touch,
	k_EControllerActionOrigin_LeftPad_Swipe,
	k_EControllerActionOrigin_LeftPad_Click,
	k_EControllerActionOrigin_LeftPad_DPadNorth,
	k_EControllerActionOrigin_LeftPad_DPadSouth,
	k_EControllerActionOrigin_LeftPad_DPadWest,
	k_EControllerActionOrigin_LeftPad_DPadEast,
	k_EControllerActionOrigin_RightPad_Touch,
	k_EControllerActionOrigin_RightPad_Swipe,
	k_EControllerActionOrigin_RightPad_Click,
	k_EControllerActionOrigin_RightPad_DPadNorth,
	k_EControllerActionOrigin_RightPad_DPadSouth,
	k_EControllerActionOrigin_RightPad_DPadWest,
	k_EControllerActionOrigin_RightPad_DPadEast,
	k_EControllerActionOrigin_LeftTrigger_Pull,
	k_EControllerActionOrigin_LeftTrigger_Click,
	k_EControllerActionOrigin_RightTrigger_Pull,
	k_EControllerActionOrigin_RightTrigger_Click,
	k_EControllerActionOrigin_LeftStick_Move,
	k_EControllerActionOrigin_LeftStick_Click,
	k_EControllerActionOrigin_LeftStick_DPadNorth,
	k_EControllerActionOrigin_LeftStick_DPadSouth,
	k_EControllerActionOrigin_LeftStick_DPadWest,
	k_EControllerActionOrigin_LeftStick_DPadEast,
	k_EControllerActionOrigin_Gyro_Move,
	k_EControllerActionOrigin_Gyro_Pitch,
	k_EControllerActionOrigin_Gyro_Yaw,
	k_EControllerActionOrigin_Gyro_Roll,

	k_EControllerActionOrigin_Count
};
enum EXboxOrigin
{
	k_EXboxOrigin_A,
	k_EXboxOrigin_B,
	k_EXboxOrigin_X,
	k_EXboxOrigin_Y,
	k_EXboxOrigin_LeftBumper,
	k_EXboxOrigin_RightBumper,
	k_EXboxOrigin_Menu,  //Start
	k_EXboxOrigin_View,  //Back
	k_EXboxOrigin_LeftTrigger_Pull,
	k_EXboxOrigin_LeftTrigger_Click,
	k_EXboxOrigin_RightTrigger_Pull,
	k_EXboxOrigin_RightTrigger_Click,
	k_EXboxOrigin_LeftStick_Move,
	k_EXboxOrigin_LeftStick_Click,
	k_EXboxOrigin_LeftStick_DPadNorth,
	k_EXboxOrigin_LeftStick_DPadSouth,
	k_EXboxOrigin_LeftStick_DPadWest,
	k_EXboxOrigin_LeftStick_DPadEast,
	k_EXboxOrigin_RightStick_Move,
	k_EXboxOrigin_RightStick_Click,
	k_EXboxOrigin_RightStick_DPadNorth,
	k_EXboxOrigin_RightStick_DPadSouth,
	k_EXboxOrigin_RightStick_DPadWest,
	k_EXboxOrigin_RightStick_DPadEast,
	k_EXboxOrigin_DPad_North,
	k_EXboxOrigin_DPad_South,
	k_EXboxOrigin_DPad_West,
	k_EXboxOrigin_DPad_East,
};
enum ESteamInputType
{
	k_ESteamInputType_Unknown,
	k_ESteamInputType_SteamController,
	k_ESteamInputType_XBox360Controller,
	k_ESteamInputType_XBoxOneController,
	k_ESteamInputType_GenericGamepad,		// DirectInput controllers
	k_ESteamInputType_PS4Controller,
	k_ESteamInputType_AppleMFiController,	// Unused
	k_ESteamInputType_AndroidController,	// Unused
	k_ESteamInputType_SwitchJoyConPair,		// Unused
	k_ESteamInputType_SwitchJoyConSingle,	// Unused
	k_ESteamInputType_SwitchProController,
	k_ESteamInputType_MobileTouch,			// Steam Link App On-screen Virtual Controller
	k_ESteamInputType_PS3Controller,		// Currently uses PS4 Origins
	k_ESteamInputType_Count,
	k_ESteamInputType_MaximumPossibleValue = 255,
};
// ControllerHandle_t is used to refer to a specific controller.
// This handle will consistently identify a controller, even if it is disconnected and re-connected
typedef uint64 ControllerHandle_t;


// These handles are used to refer to a specific in-game action or action set
// All action handles should be queried during initialization for performance reasons
typedef uint64 ControllerActionSetHandle_t;
typedef uint64 ControllerDigitalActionHandle_t;
typedef uint64 ControllerAnalogActionHandle_t;


// Safe to add new bitfields at the end of this list for new buttons/actions, 
// but never re-use or re-number an existing flag as old client code will be 
// confused.
#define STEAM_RIGHT_TRIGGER_MASK            0x0000001
#define STEAM_LEFT_TRIGGER_MASK             0x0000002
#define STEAM_RIGHT_BUMPER_MASK             0x0000004
#define STEAM_LEFT_BUMPER_MASK              0x0000008
#define STEAM_BUTTON_0_MASK                 0x0000010
#define STEAM_BUTTON_1_MASK                 0x0000020
#define STEAM_BUTTON_2_MASK                 0x0000040
#define STEAM_BUTTON_3_MASK                 0x0000080
#define STEAM_TOUCH_0_MASK                  0x0000100
#define STEAM_TOUCH_1_MASK                  0x0000200
#define STEAM_TOUCH_2_MASK                  0x0000400
#define STEAM_TOUCH_3_MASK                  0x0000800
#define STEAM_BUTTON_MENU_MASK              0x0001000
#define STEAM_BUTTON_STEAM_MASK             0x0002000
#define STEAM_BUTTON_ESCAPE_MASK            0x0004000
#define STEAM_BUTTON_BACK_LEFT_MASK         0x0008000
#define STEAM_BUTTON_BACK_RIGHT_MASK        0x0010000
#define STEAM_BUTTON_LEFTPAD_CLICKED_MASK   0x0020000
#define STEAM_BUTTON_RIGHTPAD_CLICKED_MASK  0x0040000
#define STEAM_LEFTPAD_FINGERDOWN_MASK       0x0080000
#define STEAM_RIGHTPAD_FINGERDOWN_MASK      0x0100000
#define STEAM_JOYSTICK_BUTTON_MASK			0x0400000


#pragma pack( push, 1 )

struct SteamControllerState001_t
{
	// If packet num matches that on your prior call, then the controller state hasn't been changed since 
	// your last call and there is no need to process it
	uint32 unPacketNum;

	// bit flags for each of the buttons
	uint64 ulButtons;

	// Left pad coordinates
	short sLeftPadX;
	short sLeftPadY;

	// Right pad coordinates
	short sRightPadX;
	short sRightPadY;

};

struct ControllerAnalogActionData003_t
{
	// Type of data coming from this action, this will match what got specified in the action set
	EControllerSourceMode eMode;

	// The current state of this action; will be delta updates for mouse actions
	float x, y;

	// Whether or not this action is currently available to be bound in the active action set
	bool bActive;
};

struct ControllerDigitalActionData003_t
{
	// The current state of this action; will be true if currently pressed
	bool bState;

	// Whether or not this action is currently available to be bound in the active action set
	bool bActive;
};
struct ControllerAnalogActionData_t
{
	// Type of data coming from this action, this will match what got specified in the action set
	EControllerSourceMode eMode;

	// The current state of this action; will be delta updates for mouse actions
	float x, y;

	// Whether or not this action is currently available to be bound in the active action set
	bool bActive;
};
struct ControllerDigitalActionData_t
{
	// The current state of this action; will be true if currently pressed
	bool bState;

	// Whether or not this action is currently available to be bound in the active action set
	bool bActive;
};
struct ControllerMotionData_t
{
	// Sensor-fused absolute rotation; will drift in heading
	float rotQuatX;
	float rotQuatY;
	float rotQuatZ;
	float rotQuatW;

	// Positional acceleration
	float posAccelX;
	float posAccelY;
	float posAccelZ;

	// Angular velocity
	float rotVelX;
	float rotVelY;
	float rotVelZ;
};
#pragma pack( pop )

#define SteamControllerState_t SteamControllerState001_t


#endif // CONTROLLERCOMMON_H
