////////////////////////////////////////////////////////////////////////////////////////////////////////
// Part of Injectable Generic Camera System
// Copyright(c) 2017, Frans Bouma
// All rights reserved.
// https://github.com/FransBouma/InjectableGenericCameraSystem
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
//  * Redistributions of source code must retain the above copyright notice, this
//	  list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and / or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "InterceptorHelper.h"
#include "GameConstants.h"
#include "GameImageHooker.h"

using namespace std;

//--------------------------------------------------------------------------------------------------------------------------------
// external asm functions
extern "C" {
	void cameraAddressInterceptor();
	void cameraWriteInterceptor1();		// create as much interceptors for write interception as needed. In the example game, there are 4.
	void cameraWriteInterceptor2();
	void cameraWriteInterceptor3();
	void gamespeedAddressInterceptor();
	void fovInterceptor();
}

// external addresses used in asm.
extern "C" {
	// The continue address for continuing execution after camera values address interception. 
	LPBYTE _cameraStructInterceptionContinue = nullptr;
	// the continue address for continuing execution after interception of the first block of code which writes to the camera values. 
	LPBYTE _cameraWriteInterceptionContinue1 = nullptr;
	// the continue address for continuing execution after interception of the second block of code which writes to the camera values. 
	LPBYTE _cameraWriteInterceptionContinue2 = nullptr;
	// the continue address for continuing execution after interception of the third block of code which writes to the camera values. 
	LPBYTE _cameraWriteInterceptionContinue3 = nullptr;
	// the continue address for the continuing execution after interception of the gamespeed block of code. 
	LPBYTE _gamespeedInterceptionContinue = nullptr;
	// the continue address for the continuing execution after interception of the FoV block of code
	LPBYTE _fovInterceptorContinue = nullptr;
	// the base address of the host process. 
	LPBYTE _hostBaseAddress = nullptr;
}


namespace IGCS::GameSpecific::InterceptorHelper
{
	void setCameraStructInterceptorHook(LPBYTE hostImageAddress)
	{
		GameImageHooker::setHook(hostImageAddress, CAMERA_ADDRESS_INTERCEPT_START_OFFSET, CAMERA_ADDRESS_INTERCEPT_CONTINUE_OFFSET, &_cameraStructInterceptionContinue, &cameraAddressInterceptor);
	}


	void setFoVInterceptorHook(LPBYTE hostImageAddress)
	{
		_hostBaseAddress = hostImageAddress;
		GameImageHooker::setHook(hostImageAddress, FOV_INTERCEPT_START_OFFSET, FOV_INTERCEPT_CONTINUE_OFFSET, &_fovInterceptorContinue, &fovInterceptor);
	}


	void setTimestopInterceptorHook(LPBYTE hostImageAddress)
	{
		//GameImageHooker::setHook(hostImageAddress, GAMESPEED_ADDRESS_INTERCEPT_START_OFFSET, GAMESPEED_ADDRESS_INTERCEPT_CONTINUE_OFFSET, &_gamespeedInterceptionContinue, &gamespeedAddressInterceptor);
		//GameImageHooker::setHook(hostImageAddress, TOD_ADDRESS_INTERCEPT_START_OFFSET, TOD_ADDRESS_INTERCEPT_CONTINUE_OFFSET, &_todAddressInterceptorContinue, &todAddressInterceptor);
	}

}
