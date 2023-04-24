#ifndef VSCP_H
#define VSCP_H

#include "stdafx.h"

class Vscp
{
public:
	static CString FindDirClient();	//Finds the dir of Community Place/SAPARi installed on the system.
	static BOOL GetBumps(LPCTSTR world); //Gets bumps from the virtual world.
	static int SetBumps(LPCTSTR world, BOOL noMore); //Enable/disable bumps to the virtual world
	static int writtenFiles;
};

#endif