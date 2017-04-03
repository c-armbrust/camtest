#include <iostream>
#include <ueye.h>
#include <ueye_deprecated.h>

int main()
{
	INT ret;
	HIDS h = (HIDS)0;
	
	std::cout << "Init camera." << std::endl;
	ret = is_InitCamera(&h, NULL);
	if(ret != IS_SUCCESS) {
		std::cout << "is_InitCamera error." << std::endl;
		return 1;
	}

	CAMINFO camerainfo;
	ret = is_GetCameraInfo(h, &camerainfo);
	if(ret != IS_SUCCESS) {
		std::cout << "is_GetCameraInfo error." << std::endl;
		return 1;
	}

	SENSORINFO sensorinfo;
	ret = is_GetSensorInfo(h, &sensorinfo);
	if(ret != IS_SUCCESS) {
		std::cout << "is_GetSensorInfo error." << std::endl;
		return 1;
	}
	
	std::cout << "Sensor model " << sensorinfo.strSensorName << ". Camera serial no " << camerainfo.SerNo << ".\n";

	INT width = 0;
	INT height = 0;
	width = is_SetImageSize(h, IS_GET_IMAGE_SIZE_X, -1);
	height = is_SetImageSize(h, IS_GET_IMAGE_SIZE_Y, -1);
	std::cout << "Image size is " << width << "x" << height << "." << std::endl;

	std::cout << "Set color mode." << std::endl;
	ret = is_SetColorMode(h, IS_SET_CM_BAYER);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SetColorMode error." << std::endl;
		return 1;
	}

	INT nMinPixelClock=0, nMaxPixelClock=0;
	ret = is_GetPixelClockRange(h, &nMinPixelClock, &nMaxPixelClock);
	if(ret != IS_SUCCESS) {
		std::cout << "is_GetPixelClockRange error." << std::endl;
		return 1;
	}
	std::cout << "Pixelclock range " <<  nMinPixelClock << "-" << nMaxPixelClock << "."  << std::endl;
	std::cout << "Set Pixelclock to " << nMinPixelClock << "." <<  std::endl;
	ret = is_SetPixelClock(h, nMinPixelClock);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SetPixelClock error." << std::endl;
		return 1;
	}
	
	INT bpp = 8;
	INT id = 0;
	char* pmem = NULL;
	std::cout << "Allocate image memory." << std::endl;
	ret = is_AllocImageMem(h, width, height, bpp, &pmem, &id);
	if(ret != IS_SUCCESS) {
		std::cout << "is_AllocImageMem error." << std::endl;
		return 1;
	}

	std::cout << "Set image memory." << std::endl;
	ret = is_SetImageMem(h, pmem, id);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SetImageMem error." << std::endl;
		return 1;
	}

	std::cout << "Set image size." << std::endl;
	ret = is_SetImageSize(h, width, height);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SetImageSize error." << std::endl;
		return 1;
	}

	std::cout << "Set image position." << std::endl;
	ret = is_SetImagePos(h, 0, 0);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SetImagePos error." << std::endl;
		return 1;
	}	

	double dblMinFrameTime = 0.0, dblMaxFrameTime = 0.0, dblFrameTimeInterval = 0.0;
	double dblframerate = 0.0;
	ret = is_GetFrameTimeRange(h, &dblMinFrameTime, &dblMaxFrameTime, &dblFrameTimeInterval);
	if(ret != IS_SUCCESS) {
		std::cout << "is_GetFrameTimeRange error." << std::endl;
		return 1;
	}
	std::cout << "Frametime range " << dblMinFrameTime << "-" << dblMaxFrameTime << "." << std::endl;

	ret = is_SetFrameRate(h, IS_GET_FRAMERATE, & dblframerate);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SetFrameRate error." << std::endl;
		return 1;
	}
	std::cout << "Applied Framerate " << dblframerate << "." << std::endl;

	INT sleeptime = IS_WAIT;
	ret = is_FreezeVideo(h, sleeptime);
	if(ret != IS_SUCCESS) {
		std::cout << "is_FreezeVideo error." << std::endl;
		return 1;
	}

	double dblFps = 0.0;
	ret = is_GetFramesPerSecond(h, &dblFps);
	if(ret != IS_SUCCESS) {
		std::cout << "is_GetFramesPerSecond error." << std::endl;
		return 1;
	}
	std::cout << "Fps " << dblFps << "." << std::endl;
	
	static char szDefaultFilename[] = "image.bmp";
	char* filename = szDefaultFilename;
	ret = is_SaveImage(h, filename);
	if(ret != IS_SUCCESS) {
		std::cout << "is_SaveImage error." << std::endl;
		return 1;
	}
	
	ret = is_FreeImageMem(h, pmem, id);
	if(ret != IS_SUCCESS) {
		std::cout << "is_FreeImageMem error." << std::endl;
		return 1;
	}

	std::cout << "Exit board." << std::endl;
	ret = is_ExitBoard(h);
	if(ret != IS_SUCCESS) {
		std::cout << "is_ExitBoard error." << std::endl;
		return 1;
	}

    return 0;
}

