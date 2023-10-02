// -*- coding: utf-8 -*-
/* 
	Legal:
		Version: MPL 1.1
		
		The contents of this file are subject to the Mozilla Public License Version 
		1.1 the "License"; you may not use this file except in compliance with 
		the License. You may obtain a copy of the License at 
		http://www.mozilla.org/MPL/
		
		Software distributed under the License is distributed on an "AS IS" basis,
		WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
		for the specific language governing rights and limitations under the
		License.

		The Original Code is the SA-MP Mobile Checker Include.
		
		The Initial Developer of the Original Code is Adib "adib_yg".
		Portions created by the Initial Developer are Copyright (c) 2023
		the Initial Developer. All Rights Reserved.

	Contributor(s):
		-

	Special Thanks to:
		-

	-----------------------------------------------------------------------------
	
	Author:
		Adib

	Contact:
		Telegram:
			@adib_yg
		
		Discord:
			@adib_yg

	Created:
		2 October 2023

	Updated:
		2 October 2023

	Version:
		1.0

	Github Repository:
		https://github.com/adib-yg/SAMP-Mobile-Checker

	-----------------------------------------------------------------------------

	Description:

		This includes detects players who are connected to the server with the SA-MP Mobile client
		https://play.google.com/store/apps/details?id=ru.unisamp_mobile.launcher
	
	-----------------------------------------------------------------------------

	Functions:

		native bool: IsPlayerUsingSampMobile(playerid);

	Callbacks:

		native OnPlayerConnectViaSampMobile(playerid);

	-----------------------------------------------------------------------------

	Use:

		#include <samp_mobile_checker>

		public OnPlayerSpawn(playerid) 
		{
			if(IsPlayerUsingSampMobile(playerid)) 
			{
				SendClientMessage(playerid, -1, "You are using SA-MP Mobile client!");
			}
		}

		public OnPlayerConnectViaSampMobile(playerid) 
		{
			SendClientMessage(playerid, -1, "You are using SA-MP Mobile client!");
		}

	-----------------------------------------------------------------------------
*/

// -----------------------------------------------------------------------------

#if defined _samp_mobile_checker_included
	#endinput
#endif

#define _samp_mobile_checker_included
#define _samp_mobile_checker_version 10 // 1.0

#if !defined _INC_open_mp
	#if !defined gpci
	    native gpci(playerid, serial[], len);
	#endif
#endif

// -----------------------------------------------------------------------------

// https://play.google.com/store/apps/details?id=ru.unisamp_mobile.launcher
#define SAMP_MOBILE_CI_SERIAL 			"ED40ED0E8089CC44C08EE9580F4C8C44EE8EE990"

#define IsPlayerUsingSampMobile(%0) 	s_SampMobilePlayer[%0]

// -----------------------------------------------------------------------------

forward OnPlayerConnectViaSampMobile(playerid);

// -----------------------------------------------------------------------------

new 
	bool: s_SampMobilePlayer[MAX_PLAYERS];

// -----------------------------------------------------------------------------

/*stock bool: IsPlayerUsingSampMobile(playerid) {
	return (s_SampMobilePlayer[playerid]);
}*/

// -----------------------------------------------------------------------------

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid) {
	new
        ciSerial[41];

	#if !defined _INC_open_mp
    	gpci(playerid, ciSerial, sizeof(ciSerial));
    #else
    	GPCI(playerid, ciSerial, sizeof(ciSerial));
    #endif

    if(!strcmp(SAMP_MOBILE_CI_SERIAL, ciSerial, true)) 
    {
        s_SampMobilePlayer[playerid] = true; // Android SA-MP Mobile
        CallLocalFunction("OnPlayerConnectViaSampMobile", "i", playerid);
    }
    else 
    {
        s_SampMobilePlayer[playerid] = false; // PC or other clients
    }

	#if defined _SMC_OnPlayerConnect
		return _SMC_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect _SMC_OnPlayerConnect
#if defined _SMC_OnPlayerConnect
	forward _SMC_OnPlayerConnect(playerid);
#endif

// -----------------------------------------------------------------------------

#undef SAMP_MOBILE_CI_SERIAL