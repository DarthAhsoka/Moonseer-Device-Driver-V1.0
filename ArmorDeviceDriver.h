/***********************************************************************************
 * Copyright:   上海幻神科技有限公司
 * Created:     2022/09/20
 * Author: Darth.L
 * E-mail: 929204168@qq.com
 * 
 * Notice: 为了适配C#和Unity3D游戏引擎,使用C-Style 风格实现
 *         智能体感服驱动
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
// 初始化回调
typedef std::function<void(bool result)> FuncInitResult;
// 设备ID，陀螺仪的Pose
typedef std::function<void(int deviceEnumID, float pitch,float roll, float yaw)> FuncPose;
// 枪扳机操作
typedef std::function<void(int deviceEnumID, bool triggerScale)> FuncTrigger;
// 枪握把
typedef std::function<void(int DeviceEnumID, bool grabState)> FuncGrabState;
// 枪拉栓
typedef std::function<void(int DeviceEnumID, bool Pullbolts)> FuncPullBolts;
// 枪换弹夹
typedef std::function<void(int DeviceEnumID, bool reloadState)> FuncReloadState;
// 切换开火模式
typedef std::function<void(int DeviceEnumID, bool exchangeMode)> FuncExchangeMode;



// 初始化,成功result返回1，失败result返回0
// 异步函数，必须通过回调函数判断是否初始化成功
MOONSEER_DEVICE_DRIVER_EXPORT void HS_Init();
// 绑定IMU姿态回调
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_IMUPose(FuncPose _funcPose);
// 绑定扳机操作
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_Trigger(FuncTrigger _funcTrigger);
// 绑定枪握把
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_GrabState(FuncGrabState _funcGrabState, int mode);
// 绑定枪拉栓
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_PullBolts(FuncPullBolts _funcPullBolts);
// 绑定枪换弹夹
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_ReloadState(FuncReloadState _funcReloadState);
// 切换开火模式
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_ExchangeMode(FuncExchangeMode _funcExchangeMode);
// 绑定右手手环姿态
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_RightBracelet_IMUPose(FuncPose _funcPose);
// 绑定左手手环姿态
MOONSEER_DEVICE_DRIVER_EXPORT void SetEvent_LeftBracelet_IMUPose(FuncPose _funcPose);
#endif
