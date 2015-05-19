// FunctionModule.h

#pragma once

#include "CP210xManufacturingDLL.h"

using namespace System;

namespace FunctionModule {

	public ref class ComPortDevice
	{
		// TODO: 在此处添加此类的方法。
	private:

		CP210x_STATUS nStatus;
		DWORD dwDeviceNum;
		
		array<char>^ chDevName;

		HKEY tmpKey, tmpSubKey, tmpPortKey;
		LPDCB dcbMasterInitState;

		static String^ strRegKeyEx = gcnew String("SYSTEM\\CurrentControlSet\\");
		static String^ strRegKeySub = gcnew String("Enum\\USB\\");
		static String^ strWantedKeyName = gcnew String("FriendlyName");

		static int RANDOM_RET_LENGTH = 0x400;

	public:

		HANDLE hDevHandle;
		array<String^>^ strDevList;
		array<byte>^ byRet;

		ComPortDevice(){

			nStatus = 0xFFFF;
			dwDeviceNum = 0;

			strDevList = gcnew array<String^>(CP210x_MAX_PRODUCT_STRLEN);
			chDevName = gcnew array<char>(CP210x_MAX_DEVICE_STRLEN);
			byRead = gcnew array<byte>(RANDOM_RET_LENGTH);

			hDevHandle = 0;
			dcbMasterInitState = new DCB;
		}

		CP210x_STATUS ComPort_GetDeviceList(){

			LPCSTR lpchRegString;
			DWORD dwType;
			DWORD dwLength = 0x64;

			array<Char>^ chSplit = gcnew array<Char>{'#', '#', '#'};

			cli::pin_ptr<DWORD> pdwDeviceNum = &dwDeviceNum; 
			cli::pin_ptr<char> pchDevName = &chDevName[0];
			cli::pin_ptr<HKEY> ptmpKey = &tmpKey;
			cli::pin_ptr<HKEY> ptmpSubKey = &tmpSubKey;
			cli::pin_ptr<HKEY> ptmpPortKey = &tmpPortKey;
			
			nStatus = CP210x_GetNumDevices(pdwDeviceNum);
			if(nStatus != CP210x_SUCCESS){
				return nStatus;
			}

			for(int i = 0; i < dwDeviceNum; i ++){
				nStatus = CP210x_GetProductString(i, pchDevName, CP210x_RETURN_FULL_PATH);
				if(nStatus != CP210x_SUCCESS){
					return nStatus;
				}
				strDevList[i] = String(pchDevName).ToString();

				lpchRegString = (LPCSTR)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strRegKeyEx);

				if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpchRegString, 0, KEY_ALL_ACCESS, ptmpKey)){
					lpchRegString = (LPCSTR)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strRegKeySub);

					if(ERROR_SUCCESS == RegOpenKey(tmpKey, lpchRegString, ptmpSubKey)){

						array<String^>^ strSplit = strDevList[i]->Split(chSplit);
						String^ strTmp = strSplit[1] + "\\\\" + strSplit[2];
						lpchRegString = (LPCSTR)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strTmp);

						if(ERROR_SUCCESS == RegOpenKey(tmpSubKey, lpchRegString, ptmpPortKey)){
							cli::pin_ptr<DWORD> pdwType = &dwType;
							cli::pin_ptr<DWORD> pdwLength = &dwLength;		
							lpchRegString = (LPCSTR)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strWantedKeyName);

							if(ERROR_SUCCESS == RegQueryValueEx(tmpPortKey, lpchRegString, NULL, pdwType, (LPBYTE)pchDevName, pdwLength)){
								strDevList[i] = String(pchDevName).ToString();
							}
							RegCloseKey(tmpPortKey);
						}
						RegCloseKey(tmpSubKey);
					}
					RegCloseKey(tmpKey);
				}
				
				
			}
			return nStatus;

		}

		CP210x_STATUS ComPort_Open(String^ strComName){

			array<Char>^ chSplit = gcnew array<Char>{'(', ')'};
			
			array<String^>^ strTmp = strComName->Split(chSplit);

			String^ strComNum = "\\\\.\\" + strTmp[1];

			char* ch = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(strComNum);
			
			hDevHandle = CreateFile((LPCSTR)ch,
				GENERIC_READ | GENERIC_WRITE,
				0,
				0,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
				0);

			if (hDevHandle == INVALID_HANDLE_VALUE){
				return CP210x_INVALID_HANDLE;
			}else{
				return CP210x_SUCCESS;
			}
			
		}

		CP210x_STATUS ComPort_Purging(){
			
			cli::pin_ptr<DCB> pdcbMasterInitState = &(*dcbMasterInitState);

			if(0 != PurgeComm(hDevHandle,
				PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
			{
				if(0 != GetCommState(hDevHandle, pdcbMasterInitState)){
					return CP210x_SUCCESS;
				}
			}
			return CP210x_DEVICE_IO_FAILED;	
			
		}

		CP210x_STATUS ComPort_Write(String^ strCmd){

			DWORD dwWritten = 0x10;
			DWORD length = strCmd->Length / 2;
			array<byte>^ byCmd = gcnew array<byte>(length);
			for(int i = 0, j = 0; j < length; j ++){
				byCmd[j] = Convert::ToByte(strCmd->Substring(i, 2), 16);
				i += 2;
			}

			nStatus = ComPort_Purging();
			if(CP210x_SUCCESS != nStatus){
				return nStatus;
			}

			LPOVERLAPPED o= new OVERLAPPED;
			cli::pin_ptr<OVERLAPPED> po = &(*o);
			cli::pin_ptr<byte> pbyCmd = &byCmd[0];
			cli::pin_ptr<DWORD> pdwWritten = &dwWritten;
			o->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			o->Offset = 0;
			o->OffsetHigh = 0;
			if (!WriteFile(hDevHandle, (LPCVOID)pbyCmd, length, pdwWritten, po))
			{
				DWORD err = GetLastError();
				if (err == ERROR_IO_PENDING)
					if (WaitForSingleObject(o->hEvent, INFINITE) == WAIT_OBJECT_0)
						if (GetOverlappedResult(hDevHandle, po, pdwWritten, FALSE))
							nStatus = CP210x_SUCCESS;
			}
			else
				nStatus = CP210x_SUCCESS;
			if (dwWritten != length)
				nStatus = CP210x_DEVICE_IO_FAILED;
			CloseHandle(o->hEvent);
		
			return nStatus;
		}

		bool ComPort_Read(int nLength){

			bool bRet = false;
			DWORD dwRead;
			DWORD dwLength = nLength;

			LPOVERLAPPED o= new OVERLAPPED;
			cli::pin_ptr<OVERLAPPED> po = &(*o);
			cli::pin_ptr<byte> pbyRead = &byRead[0];
			cli::pin_ptr<DWORD> pdwRead = &dwRead;
			o->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			o->Offset = 0;
			o->OffsetHigh = 0;
			if (!ReadFile(hDevHandle, pbyRead, dwLength, pdwRead, po))
			{
				DWORD err = GetLastError();
				if (err == ERROR_IO_PENDING)
					if (WaitForSingleObject(o->hEvent, 1000) == WAIT_OBJECT_0)
						bRet = true;
					GetOverlappedResult(hDevHandle, po, pdwRead, FALSE);
							
			}else
				bRet = true;			
				
			CloseHandle(o->hEvent);

			return bRet;

		}


	public ref class DataProcess{
	
	public:

		
		String^ strHeadType;

	public:

		DataProcess(){
			strHeadType = gcnew String("");
		}

		void RetDataProcess(array<byte>^ byRet){
			strHeadType = Convert::ToString(byRet[0], 16) + Convert::ToString(byRet[1], 16);

		}
	};

	};
}
