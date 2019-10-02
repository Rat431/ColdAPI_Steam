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

#ifndef ECURRENCYCODE_H
#define ECURRENCYCODE_H
#ifdef _WIN32
#pragma once
#endif


typedef enum ECurrencyCode
{
	k_ECurrencyCodeInvalid = 0,
	k_ECurrencyCodeUSD = 1,
	k_ECurrencyCodeGBP = 2,
	k_ECurrencyCodeEUR = 3,
	k_ECurrencyCodeCHF = 4,
	k_ECurrencyCodeRUB = 5,
	k_ECurrencyCodePLN = 6,
	k_ECurrencyCodeBRL = 7,
	//k_ECurrencyCodeMax = 8,
	k_ECurrencyCodeNOK = 9
} ECurrencyCode;

#endif // ECURRENCYCODE_H
