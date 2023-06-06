/***********************************************************************************
 * Copyright:   �Ϻ�����Ƽ����޹�˾
 * Created:     2022/09/20
 * Author: Darth.L
 * E-mail: 929204168@qq.com
 * 
 * Notice: Ϊ������C#��Unity3D��Ϸ����,ʹ��C-Style ���ʵ��
 *         ������з�����
 * 
 * Protocol: Bluetooth
 * 
 * History: 
 *        2022/09/20  Create
 * 
 * Version:
 *        4.0
 * 
 * SDK Download URL: 
 *
 **********************************************************************************/

#pragma once
//#define SOURCE_DATA
#ifndef MOONSEER_DEVICE_DRIVER
#define MOONSEER_DEVICE_DRIVER

#define _DLL_MOONSEER_DEVICE_DRIVER
#ifdef _DLL_MOONSEER_DEVICE_DRIVER
#define MOONSEER_DEVICE_DRIVER_EXPORT extern "C" __declspec(dllexport)
#else
#define MOONSEER_DEVICE_DRIVER_EXPORT __declspec(dllimport)
#endif


#include <functional>
/////////////////////////////////// Type Definition ///////////////////////////////////
typedef unsigned char b8;
typedef unsigned long ulong;


enum class DeviceEnum : b8
{
	Left_Handler = 0x02,
	Right_Handler = 0x03,
	Left_Leg = 0x04,
	Right_Leg = 0x05,
	Pistol = 0x06,
	Rifle = 0x07,
	Left_Bracelet = 0x08,
	Right_Bracelet = 0x09,
};


/////////////////////////////////// Public API Declare ////////////////////////////////
// ��ʼ���ص�
typedef std::function<void(bool result)> FuncInitResult;
// �豸ID�������ǵ�Pose
typedef std::function<void(int deviceEnumID, float pitch,float roll, float yaw)> FuncPose;
// ǹ�������
typedef std::function<void(int deviceEnumID, bool triggerScale)> FuncTrigger;
// ǹ�հ�
typedef std::function<void(int DeviceEnumID, bool grabState)> FuncGrabState;
// ǹ��˨
typedef std::function<void(int DeviceEnumID, bool Pullbolts)> FuncPullBolts;
// ǹ������
typedef std::function<void(int DeviceEnumID, bool reloadState)> FuncReloadState;
// �л�����ģʽ
typedef std::function<void(int DeviceEnumID, bool exchangeMode)> FuncExchangeMode;



// ��ʼ��,�ɹ�result����1��ʧ��result����0
// �첽����������ͨ���ص������ж��Ƿ��ʼ���ɹ�
MOONSEER_DEVICE_DRIVER_EXPORT void HS_Init();
// ��IMU��̬�ص�
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_IMUPose(FuncPose _funcPose);
// �󶨰������
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_Trigger(FuncTrigger _funcTrigger);
// ��ǹ�հ�
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_GrabState(FuncGrabState _funcGrabState, int mode);
// ��ǹ��˨
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_PullBolts(FuncPullBolts _funcPullBolts);
// ��ǹ������
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_ReloadState(FuncReloadState _funcReloadState);
// �л�����ģʽ
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_ExchangeMode(FuncExchangeMode _funcExchangeMode);
// �������ֻ���̬
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_RightBracelet_IMUPose(FuncPose _funcPose);
// �������ֻ���̬
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_LeftBracelet_IMUPose(FuncPose _funcPose);
#endif
