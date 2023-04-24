#include "stdafx.h"
#include "SAPARiNoMoreBumps.h"
#include "Vscp.h"

#include <string>
#include <vector>

int Vscp::writtenFiles = 0;

CString Vscp::FindDirClient()
{
	CString dir;
	HKEY hKey;
	CFileStatus status;
	if(CFile::GetStatus("C:\\Sony\\Community Place Browser\\bin\\cpbrowse.exe", status) != 1)
	{
		if(CFile::GetStatus("C:\\Program Files\\Sony\\Community Place Browser\\bin\\cpbrowse.exe", status) != 1)
		{
			if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Sony\\‚³‚Ï‚è\\Install"), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
			{	
				if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Sony\\Community Place Browser\\Install"), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
				{
					if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Sony Corporation\\Community Place Browser\\Install"), 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS)
					{
						dir.Empty();
					}
					else 
					{
						TCHAR szData[256];
						DWORD dwKeyDataType;
						DWORD dwDataBufSize = 256;
						if (RegQueryValueEx(hKey, _T("Directory"), NULL, &dwKeyDataType,
								(LPBYTE) &szData, &dwDataBufSize) == ERROR_SUCCESS)
						{
							switch ( dwKeyDataType )
							{
								case REG_SZ:
									dir = CString(szData);
									break;
							}
						}
					}
				}
				else 
				{
					TCHAR szData[256];
					DWORD dwKeyDataType;
					DWORD dwDataBufSize = 256;
					if (RegQueryValueEx(hKey, _T("Directory"), NULL, &dwKeyDataType,
							(LPBYTE) &szData, &dwDataBufSize) == ERROR_SUCCESS)
					{
						switch ( dwKeyDataType )
						{
							case REG_SZ:
								dir = CString(szData);
								break;
						}
					}
				}
			}
			else 
			{
				TCHAR szData[256];
				DWORD dwKeyDataType;
				DWORD dwDataBufSize = 256;
				if (RegQueryValueEx(hKey, _T("Directory"), NULL, &dwKeyDataType,
						(LPBYTE) &szData, &dwDataBufSize) == ERROR_SUCCESS)
				{
					switch ( dwKeyDataType )
					{
						case REG_SZ:
							dir = CString(szData);
							break;
					}
				}
			}
		}
		else
		{
			dir = _T("C:\\Program Files\\Sony\\Community Place Browser");
		}
	}
	else
	{
		dir = _T("C:\\Sony\\Community Place Browser");
	}
	return dir;
};

BOOL Vscp::GetBumps(LPCTSTR world)
{
	CString linestr;
	BOOL bumps = TRUE;
	CStdioFile wrl;
	CFileStatus status;
	if(CFile::GetStatus(world, status))
	{
		wrl.Open(world, CFile::modeRead);
		CString collisionSound;
		while(wrl.ReadString(linestr))
		{
			if (linestr.Find("collisionSound") != -1) 
			{
				if (linestr.Find("TRUE") != -1)
					bumps = FALSE;
				else if (linestr.Find("FALSE") != -1)
					bumps = TRUE;
			}
			else
				bumps = TRUE;
		}
		wrl.Close();
	}
	return bumps;
};

int Vscp::SetBumps(LPCTSTR world, BOOL noMore)
{
	CString linestr;
	std::vector<CString> content;
	int val;
	BOOL anySonyProto = FALSE;
	BOOL changed = FALSE;
	CStdioFile wrl;
	CFileStatus status;
	if(CFile::GetStatus(world, status))
	{
		if (status.m_attribute & CFile::readOnly)
			return val = -3;
		if (wrl.Open(world, CFile::modeRead))
		{
			CString collisionSound;
			try
			{
				while(wrl.ReadString(linestr))
				{
					if (linestr.Find("PROTO Sony_WorldInfo") != -1)
						anySonyProto = TRUE;
					if (linestr.Find("collisionSound") != -1)
					{
						collisionSound = linestr;
						if (noMore == FALSE)
							collisionSound.Replace("TRUE", "FALSE");
						else
							collisionSound.Replace("FALSE", "TRUE");
						if (linestr != collisionSound)
						{
							changed = TRUE;
							linestr = collisionSound;
						}
					}
					content.push_back(linestr);
				}
				if (anySonyProto == FALSE)
				{
					content.insert(content.begin() + 1, "#-----------------------------------------------------------");
					content.insert(content.begin() + 2, "# Modified by SAPARiNoMoreBumps");
					content.insert(content.begin() + 3, "# Ver 1.0");
					content.insert(content.begin() + 4, "# http://barrarchiverio.7m.pl");
					content.insert(content.begin() + 5, "PROTO Sony_WorldInfo [");
					content.insert(content.begin() + 6, noMore == TRUE ? "  field        SFBool   collisionSound       TRUE" 
						: "  field        SFBool   collisionSound       FALSE");
					content.insert(content.begin() + 7, "] {}");
					content.insert(content.begin() + 8, "#-----------------------------------------------------------");
					changed = TRUE;
				}
				wrl.Close();
				if (changed == TRUE)
				{
					if (wrl.Open(world, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
					{
						CString contentString;
						for (int i = 0; i < content.size(); i++)
						{
							contentString += content[i];
							contentString += "\n";
						}
						wrl.WriteString(contentString);
						wrl.Close();
						val = 1;
						Vscp::writtenFiles++;
					}
					else
						val = -2;
				}
				else
					val = 1;
			}
			catch (CFileException* err)
			{
				if (err->m_cause == CFileException::diskFull)
					val = -4;
				if (err->m_cause == CFileException::accessDenied)
					val = -5;
				if (err->m_cause == CFileException::generic)
					val = -2;
			}
		}
		else
			val = -2;
	}
	else
		val = -1;
	return val;
};
