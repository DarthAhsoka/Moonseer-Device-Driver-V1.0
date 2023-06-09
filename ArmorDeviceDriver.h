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

#ifndef ARMOR_DEVICE_DRIVER
#define ARMOR_DEVICE_DRIVER

#define _DLL_ARMOR_DEVICE_DRIVER
#ifdef _DLL_ARMOR_DEVICE_DRIVER
#define ARMOR_DEVICE_DRIVER_EXPORT extern "C" __declspec(dllexport)
#else
#define ARMOR_DEVICE_DRIVER_INPORT __declspec(dllimport)
#endif

/////////////////////////////////// Type Definition ///////////////////////////////////
typedef unsigned char b8;
typedef unsigned long ulong;
/////////////////////////////////// Public API Declare ////////////////////////////////

/**
 * Unity3D/C#/Java Test
 * 用于DLL测试，在控制台程序中
 * 成功调用该方法会输出当前SDK
 * 版本信息
 */
ARMOR_DEVICE_DRIVER_EXPORT 
void HS_Version();


// 商汤奥嘉切换手柄/Armro的回调
// nMode = 1 是Armor
// nMode = 2 是Handle
ARMOR_DEVICE_DRIVER_EXPORT
void HS_ControllerModeChanged(void (*lpfnControllerModeChanged)(int nMode));



/**
 * 初始化盔甲
 *
 * 返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备初始化失败
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_InitArmor();



/**
 * 初始化腿部模块
 *
 * 返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备初始化失败
 * 
 * 注：初始化的时候左右两个模块都会被初始化
 * 开发者可以在HS_OpenDeviceDriver的时候
 * 决定是否启用
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_InitLeg();

/**
 * 开启UDP透传模式
 *
 * params:
 *   
 * 
 * 返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备初始化失败
 *    2 保留错误
 *    3 设备标识符错误
 *
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_EnablePassThroughMode(char deviceIdentifier[32], char IP[128], int Port, int RepeatNumber, int protocol);

/**
 * 搜索并启动设备
 * 
 * 参数: 
 *  -> params:
	   deviceIdentifier [int] 支持的设备标识
 *   
 *     参数值:
 *     0: 不驱动任何设备 [缺省]
 *     1: 盔甲设备
 *     2: 左腿设备
 *     4: 右腿设备
 * 
 *     如果需要同时开启多个设备,只需要对标识符进行|运算即可
 *     如我们要开启盔甲和右腿设备,只需要传入 1 | 4 = 5，传
 *     5即可。
 * 
 *  -> params:
 *     void (*fpResult)(bool, char*) [func*] 初始化成功回调
 *     成功返回true, 出错返回false 和 errMsg
 *     
 *     该参数缺省为0，说明没有传入回调函数
 */
ARMOR_DEVICE_DRIVER_EXPORT
void HS_OpenDeviceDriver(int deviceIdentifier = 0, void (*fpResult)(bool bResult, char* errMsg) = 0);


/**.
 * 释放资源
 * 
 * 参数
 * -> params:
 *    void(*fpResult)()  释放成功后调用回调,
 *    在回调函数中可以执行关闭资源后的操作,回调
 *    未返回前,并不能保证资源被完全释放。
 */
ARMOR_DEVICE_DRIVER_EXPORT
void HS_ReleaseDeviceDriver(void(*fpResult)());


/**
 * 设置盔甲移动模式
 * 
 * 参数
 * -> params:
 *    pDeviceHandler [void*] 设备标识符
 *    创建设备驱动成功后返回的设备标识符
 * 
 *    mode [int] 模式参数
 *    1、虚拟键盘模式
 * 
 *    2、线性位移模式
 * 
 * 返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorDeviceMoveMode(int mode);


/**
 * 设置腿部移动模式
 *
 * 参数
 * -> params:
 *    deviceIdentifier [int] 设备标识符
 *    设备标识符,取值：
 *    2、左腿
 *    4、右腿
 *
 *    mode [int] 模式参数
 *    1、虚拟键盘模式
 *    2、线性位移模式
 *
 * 返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegDeviceMoveMode(int deviceIdentifier , int mode);


/**
 * 设置胸部模块采样精度
 *
 * 参数
 * -> params:
 *    nSamplingPrecision [int] 采样精度
 *    系统缺省参数为30
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetSamplingPrecision(int nSamplingPrecision);


/*
 * 设置胸部盔甲触发模式
 *
 * 参数
 * -> params:
 *    TriggerMode [b8] 触发模式
 *    系统缺省参数为边缘（上升沿）触发
 * 
 * TriggerMode的值为：
 *   1、高电平水平触发 High Level Trigger
 *   2、边沿（上升沿）触发 Rising Edge Trigger
 * 
 * 影响：
 *   1、胸部铠甲左/右侧按钮
 *   2、胸部铠甲左/右侧红外
 * 
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorTriggerMode(int TriggerMode);


/**
 * 获取胸部模块状态
 *
 *  返回
 * -> return: 胸部盔甲设备状态
 *    0 掉线
 *    1 在线
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_GetArmorStatus();

/**
 * 设置盔甲电量回调
 *
 * 参数:
 * ->  params:
 *     lpFuncPowerChangedResult 函数指针
 *	  
 * ->  函数 lpFuncPowerChangedResult 原型为
 *     void FuncPowerChangedResult(b8 power) 
 * 
 *   -> params:
 *	   changedMode [b8] 上报电量的模式
 *	   0: 每帧上传一次
 *	   1: 改变的时候才上传 [缺省值]
 *	 
 * 
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorPowerChangedResult(void (*lpFuncPowerChangedResult)(b8 power), b8 changedMode = 1);


/**
 * 胸部设备标定
 * 
 * 调用该函数后,将采集标定数据,采集标定数据的时候将
 * 不会在将数据进行处理和转发(不再调用移动,触摸,红外
 * 等用户回调)
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_ArmorCalibration();


/**
 * 设置标定回调
 *
 * 参数:
 * ->  params:
 *     lpFuncArmorCalibrationResult 函数指针
 *
 * ->  函数 lpFuncArmorCalibrationResult 原型为
 *     void FuncArmorCalibrationResult()
 *     当标定结束后触发该方法 
 * 
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorCalibrationComplete(void (*lpFuncArmorCalibrationResult)());


/**
 * 设置盔甲前后移动回调
 *
 * 参数:
 * -> params:
 *    lpArmorForwardOrBackMove [Function] 设置前后移动的回调函数
 * 
 * ->   函数 lpArmorForwardOrBackMove 原型为
 *     void lpArmorForwardOrBackMove(double sine, double angle)
 *     该函数参数如下:
 * 
 * ->  params:
 *     sine [double] 当前移动角度的正弦值，向前为正,向后为负
 *	
 * ->  params
 *     angle [double] 当前移动角度的角度值，向前为正,向后为负
 *
 *
 *  返回
 * -> return: 错误码

 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorForwardOrBackMove(void (*lpArmorForwardOrBackMove)(double sine, double angle));


/**
 * 设置盔甲左右移动回调
 *
 * ->  params:
 *     HS_SetArmorLeftOrRightMove [Function] 设置左右移动的回调函数
 *
 * ->   函数 lpArmorForwardOrBackMove 原型为
 *     void lpArmorForwardOrBackMove(double sine, double angle)
 *     该函数参数如下:
 *
 * ->  params:
 *     sine [double] 当前移动角度的正弦值，向前为正,向后为负
 *
 * ->  params
 *     angle [double] 当前移动角度的角度值，向前为正,向后为负
 *
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorLeftOrRightMove(void (*lpArmorLeftOrRightMove)(double sine, double angle));


/**
 * 设置盔甲左侧按钮事件回调
 *
 * ->  params:
 *     lpArmorLeftButtonStateChanged [Function] 设置盔甲左侧按钮事件回调
 *
 * ->   函数 lpArmorLeftButtonStateChanged 原型为
 *     void lpArmorLeftButtonStateChanged(bool state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [bool] state为true的时候为按下状态
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorLeftButtonStateChanged(void (*lpArmorLeftButtonStateChanged)(bool state));


/**
 * 设置盔甲右侧按钮事件回调
 *
 * ->  params:
 *     lpArmorRightButtonStateChanged [Function] 设置盔甲右侧按钮事件回调
 *
 * ->  函数 lpArmorRightButtonStateChanged 原型为
 *     void lpArmorRightButtonStateChanged(bool state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [bool] state 为true 的时候为按下状态
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorRightButtonStateChanged(void (*lpArmorRightButtonStateChanged)(bool state));



/**
 * 设置盔甲左侧红外事件回调
 *
 * ->  params:
 *     lpArmorLeftInfraredStateChanged [Function] 设置盔甲左侧红外事件回调
 *
 * ->  函数 lpArmorLeftInfraredStateChanged 原型为
 *     void lpArmorLeftInfraredStateChanged(bool state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [bool] state 为 true 的时候为红外触发状态
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorLeftInfraredStateChanged(void (*lpArmorLeftInfraredStateChanged)(bool state));


/**
 * 设置盔甲右侧红外事件回调
 *
 * ->  params:
 *     lpArmorRightInfraredStateChanged [Function] 设置盔甲右侧红外事件回调
 *
 * ->  函数 lpArmorRightInfraredStateChanged 原型为
 *     void lpArmorRightInfraredStateChanged(bool state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [bool] state 为 true 的时候为红外触发状态
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorRightInfraredStateChanged(void (*lpArmorRightInfraredStateChanged)(bool state));


/**
 * 设置电压状态改变事件回调
 *
 * ->  params:
 *     lpArmorVoltageStateChanged [Function] 设置盔甲电压事件回调
 *
 * ->  函数 lpArmorVoltageStateChanged 原型为
 *     void lpArmorRightInfraredStateChanged(int state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [int] state 为当前设备电压状态,其中:
 *     0：低电压
 *     1：正常工作电压
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorVoltageStateChanged(void (*lpArmorVoltageStateChanged)(int state));


/**
 * 设置充电状态改变事件回调
 *
 * ->  params:
 *     lpArmorRechargingStateChanged [Function] 设置盔甲充电状态事件回调
 *
 * ->  函数 lpArmorRechargingStateChanged 原型为
 *     void lpArmorRechargingStateChanged(int state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [int] state 为充电状态，其中
 *     1: 正在充电
 *     2: 未充电
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorRechargingStateChanged(void (*lpArmorRechargingStateChanged)(int state));


/**
 * 设置虚拟键盘绑定
 *
 * 参数:
 * 
 * ->  parmas:
 *   
 *     deviceIdentifier [int] 设备标识符
 *     1: 盔甲设备
 *     2: 左腿设备
 *     4: 右腿设备
 * 
 * ->  params:
 *     w [b8]  上键 [缺省:KEY_W]
 *     a [b8]  左键 [缺省:KEY_A]
 *     s [b8]  下键 [缺省:KEY_S]
 *     d [b8]  右键 [缺省:KEY_D]
 * 
 * 绑定的值是windows键盘事件里面的ascii码
 * 比如A键就是65
 */
ARMOR_DEVICE_DRIVER_EXPORT
void HS_BindMoveVirtualKey(int deviceIdentifier,b8 w, b8 a, b8 s, b8 d);


/**
 * 发送震动指令给胸部模块
 *
 * 参数:
 * ->    params:  MonitorIndexs [unsigned short]   电机索引
 *       目前电机索引值如下：
 *		 1号马达:    1
 *		 2号马达:    2
 *		 3号马达:    3
 *		 4号马达:    4
 *		 5号马达:    5
 *		 6号马达:    6
 *		 7号马达:    7
 *		 8号马达:    8
 *		 9号马达:    9
 *		 10号马达:   10
 *		 11号马达:   11
 *		 12号马达:   12
 *       
 * ->    params:  每个马达的独立震动时间
 *       t1 就是1号马达的独立震动时间
 *       t2 就是2号马达的独立震动时间
 *       以此类推
 * 
 * ->    parmas: byteScale  [b8]
 *       震动时间倍数
 *       目前系统精度设置为100ms，当倍数为1的时候,震动时间为
 *       T（max） = 100ms * byteScale(1) * t(F)  t ∈｛ N | [0,F] }
 *		 T（min） = 100ms * byteScale(1) * t(1)
 *       最大震动时间为 1500ms,最小震动时间为100ms
 * 
 * @return true 为指令下发成功,false 为下发失败
 * @note:
 *    指令下发成功不代表下位机就一定能正常运行，
 *    仅仅代表指令从上位机发出。
 */
ARMOR_DEVICE_DRIVER_EXPORT
bool HS_ArmorDeviceShake(unsigned short MonitorIndexs, b8 t1, b8 t2, b8 t3, b8 t4, b8 t5, b8 t6, b8 t7, b8 t8, b8 t9 ,
	            b8 t10, b8 t11, b8 t12, b8 byteScale = 100);


/**
 * 腿部设备标定
 *
 * 调用该函数后,将采集标定数据,采集标定数据的时候将
 * 不会在将数据进行处理和转发(不再调用移动,触摸,红外
 * 等用户回调)
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 *    2 设备未启用（检查HS_OpenDeviceDriver）
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_LegCalibration();



/**
 * 设置腿部标定回调
 *
 * 参数:
 * ->  params:
 *     lpFuncLegCalibrationResult 函数指针
 *
 * ->  函数 lpFuncLegCalibrationResult 原型为
 *     void lpFuncLegCalibrationResult()
 *     当标定结束后触发该方法
 *
 * ->  params:
 *     deviceIdentifier [int] 设备标识符
 *     设备标识符,取值：
 *     2、左腿
 *     4、右腿
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegCalibrationComplete(void (*lpFuncLegCalibrationResult)(), int deviceIdentifier);


/**
 * 设置腿部模块电量回调
 *
 * 参数:
 * ->  params:
 *     lpFuncLegResult 函数指针
 *
 * ->  函数 lpFuncLegPowerChangedResult 原型为
 *     void lpFuncLegPowerChangedResult(int identifier, b8 power)
 *	   参数 
 *     power [b8]  返回的电量
 *
 * 
 *   -> params:
 *     identifier [int] 设备标识符
 *     2:左腿模块电量上传
 *     4:右腿模块电量上传
 * 
 *   -> params:
 *	   changedMode [b8] 上报电量的模式
 *	   0: 每帧上传一次
 *	   1: 改变的时候才上传 [缺省值]
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 *    2 设备标识错误（设备不存在)
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegPowerChangedResult(void (*lpFuncLegPowerChangedResult)(b8 power), int identifier, b8 changedMode = 1);


/**
 * 设置电压状态改变事件回调
 *
 * ->  params:
 *     lpLegVoltageStateChanged [Function] 设置腿部电压改变事件
 *
 * ->  函数 lpLegVoltageStateChanged 原型为
 *     void lpLegVoltageStateChanged(int state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [int] state 为当前设备电压状态,其中:
 *     0：低电压
 *     1：正常工作电压
 * 
 * -> params:
 *     identifier [int] 设备标识符
 *     2:左腿模块电压状态上传
 *     4:右腿模块电压状态上传
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegVoltageStateChanged(void (*lpLegVoltageStateChanged)(int state), int identifier);

/**
 * 设置充电状态改变事件回调
 *
 * ->  params:
 *     lpLegRechargingStateChanged [Function] 设置盔甲充电状态事件回调
 *
 * ->  函数 lpArmorRechargingStateChanged 原型为
 *     void lpArmorRechargingStateChanged(int state)
 *     该函数参数如下:
 *
 * ->  params:
 *     state [int] state 为充电状态，其中
 *     1: 正在充电
 *     2: 未充电
 * 
 * -> params:
 *     identifier [int] 设备标识符
 *     2:左腿模块电压状态上传
 *     4:右腿模块电压状态上传
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegRechargingStateChanged(void (*lpLegRechargingStateChanged)(int state), int identifier);



/**
 * 设置腿部模块前后移动回调
 *
 * 参数:
 * -> params:
 *    lpLegForwardOrBackMove [Function] 设置前后移动的回调函数
 *
 * ->   函数 lpLegForwardOrBackMove 原型为
 *     void lpLegForwardOrBackMove(double sine, double angle)
 *     该函数参数如下:
 *
 * ->  params:
 *     sine [double] 当前移动角度的正弦值，向前为正,向后为负
 *
 * ->  params
 *     angle [double] 当前移动角度的角度值，向前为正,向后为负
 *
 * 
 * 
 * -> params:
 *    deviceIdentifier [int] 设备标识符
 *    设备标识符,取值：
 *    2、左腿
 *    4、右腿
 *
 *  返回
 * -> return: 错误码
 *
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegForwardOrBackMove(void (*lpLegForwardOrBackMove)(double sine, double angle), int deviceIdentifier);


/**
 * 设置腿部模块左右移动回调
 *
 * ->  params:
 *     lpLegLeftOrRightMove [Function] 设置左右移动的回调函数
 *
 * ->   函数 lpLegLeftOrRightMove 原型为
 *     void lpLegLeftOrRightMove(double sine, double angle)
 *     该函数参数如下:
 *
 * ->  params:
 *     sine [double] 当前移动角度的正弦值，向前为正,向后为负
 *
 * ->  params
 *     angle [double] 当前移动角度的角度值，向前为正,向后为负
 *
 *
 *
 *  返回
 * -> return: 错误码
 *    0 无错误
 *    1 设备未初始化
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegLeftOrRightMove(void (*lpLegLeftOrRightMove)(double sine, double angle), int deviceIdentifier);


#endif
