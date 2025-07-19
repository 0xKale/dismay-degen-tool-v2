#include <windows.h>
#include <shellapi.h>
#pragma once

enum heads {
    HEAD_1, // host
    HEAD_2, // friends
    HEAD_3, // kick tool
    HEAD_4, // ban tool
    HEAD_5, // console
    HEAD_6  // misc
};
// Memory Locations


namespace functions
{
    // Initial Values
    extern heads head_selected = HEAD_1;
    extern int combobox = 0;
    extern int fFPS = 125;
    extern float fMapSize = 1.0f;
    extern float fFOV = 65.0f;
    extern bool bChat = true; // Killcam checkbox, 0 for off, 1 for on

	// Memory Addresses
	int mFOV = 0xAAC1F8; // FOV
    int mFPS = 0x1B90730; // FPS
    int mChat = 0xAA61C0; // Chat
	int mMapSize = 0x886E7C; // Map Size

    //todo:
    //0x886EBC compassMaxRange
    //0x886EB8 compassRotation
    //0x886E78 compassRadarUpdateTime
    //0x886EE4 compassPlayerWidth
    //0x886ED0 compassFriendlyWidth



	// Handle Mouse Cursor
    inline void handleMouseCursor()
    {
        if (gui::open)
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDrawCursor = true;
            *reinterpret_cast<int**>(0x6427D3D) = nullptr; // Unhook mouse
        }
        else
        {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDrawCursor = false;
            *reinterpret_cast<int*>(0x6427D3D) = 1; // Release mouse
        }
    }

    void funFOV(){
        DWORD dwPointer = *(DWORD*)mFOV; // FOV
        *(float*)(dwPointer + 0xC) = fFOV; // Use fully qualified name
    }

	void funFPS()
	{
		DWORD dwPointer = *(DWORD*)mFPS; // FPS
		*(int*)(dwPointer + 0xC) = fFPS; // Set FPS
	}

	void funChat()
	{
		DWORD dwPointer = *(DWORD*)mChat; // Chat
		if (bChat == true)
		{
			*(int*)(dwPointer + 0xC) = 72000; // Enable Chat
		}
		else
		{
			*(int*)(dwPointer + 0xC) = 0; // Disable Chat
		}
	}

    void funMapSize()
    {
        DWORD dwPointer = *(DWORD*)mMapSize; 
        *(float*)(dwPointer + 0xC) = fMapSize;
    }



}
