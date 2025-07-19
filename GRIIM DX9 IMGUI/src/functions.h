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
    // Values
    extern heads head_selected = HEAD_1;
    extern int combobox = 0;
    extern int fFPS = 125;
    extern float fMapSize = 1.0f;
    extern float fFOV = 65.0f;
	extern float fFOVMin = 65.0f;
    extern bool bChat = true; // Killcam checkbox, 0 for off, 1 for on
	extern bool bMouseFix = true; // Mouse Fix checkbox, 0 for off, 1 for on
	extern int fBypassMouseInput = 0;
	extern float fMouseAccel = 0.0f; 
	extern float fYawSpeed = 0.0f; // Yaw Speed
	extern float fPitchSpeed = 0.0f; // Pitch Speed

	// Memory Addresses
	int mFOV = 0xAAC1F8; // FOV
    int mFOVMin = 0x88CB54; // FOV Min
    int mFPS = 0x1B90730; // FPS
    int mChat = 0xAA61C0; // Chat
	int mMapSize = 0x886E7C; // Map Size
	int mBypassMouseInput = 0xAB2B0C; // Mouse Bypass Input
	int mMouseAccel = 0xBC37E0; // Mouse Acceleration
	int mYawSpeed = 0xAB2B08; // Yaw Speed
	int mPitchSpeed = 0xAB2B14; // Pitch Speed



    // todo:
    // 0x886EBC compassMaxRange
    // 0x886EB8 compassRotation
    // 0x886E78 compassRadarUpdateTime
    // 0x886EE4 compassPlayerWidth
    // 0x886ED0 compassFriendlyWidth
    // 0x695D9D0 r_glow
    // 0xAAF7FC InnerFOV
    // 0xAAF7D4 left/right pov
    
    // Mouse Fix
    // 0xAB2B0C cl_bypassMouseInput 0
    // 0xBC37E0 cl_mouseAccel 0
    // 0xAB2B08 cl_yawspeed 0
	// 0xAB2B14 cl_pitchspeed 0






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

    void bypassMouseInput() {
        // cl_bypassMouseInput
        DWORD dwPointer = *(DWORD*)mBypassMouseInput;
        *(int*)(dwPointer + 0xC) = fBypassMouseInput;
    }

    void mouseAccel() {
        // cl_mouseAccel
        DWORD dwPointer = *(DWORD*)mMouseAccel;
        *(float*)(dwPointer + 0xC) = fMouseAccel;
    }

    void yawspeed() {
        // cl_yawspeed
        DWORD dwPointer = *(DWORD*)mYawSpeed;
        *(float*)(dwPointer + 0xC) = fYawSpeed;
    }

    void pitchspeed() {
        // cl_pitchspeed
        DWORD dwPointer = *(DWORD*)mYawSpeed;
        *(float*)(dwPointer + 0xC) = fYawSpeed;
    }

	void funMouseFix() {
        /*
        * < -noforcemaccel -noforcemparms > in launch options
            dword_B173DC = sub_5BDBD0((char)"m_pitch", 0.022, -1.0, 1.0, 1);
            dword_B173D4 = sub_5BDBD0((char)"m_yaw", 0.022, -1.0, 1.0, 1);
            dword_BC37D8 = sub_5BDBD0((char)"m_forward", 0.25, -1.0, 1.0, 1);
            dword_BC4488 = sub_5BDBD0((char)"m_side", 0.25, -1.0, 1.0, 1);
            dword_BC4490 = sub_5BDB40((char)"m_filter", 0, 1);
           */
        if (bMouseFix == true) {
            bypassMouseInput();
            mouseAccel();
            yawspeed();
            pitchspeed();
        }
	}

    void funFOV(){
        DWORD dwPointer = *(DWORD*)mFOV; // FOV
        *(float*)(dwPointer + 0xC) = fFOV; // Use fully qualified name
    }

    void funFOVMin() {
        DWORD dwPointer = *(DWORD*)mFOVMin; // FOV
        *(float*)(dwPointer + 0xC) = fFOVMin; // Use fully qualified name
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
