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
 * ����DLL���ԣ��ڿ���̨������
 * �ɹ����ø÷����������ǰSDK
 * �汾��Ϣ
 */
ARMOR_DEVICE_DRIVER_EXPORT 
void HS_Version();


// �����¼��л��ֱ�/Armro�Ļص�
// nMode = 1 ��Armor
// nMode = 2 ��Handle
ARMOR_DEVICE_DRIVER_EXPORT
void HS_ControllerModeChanged(void (*lpfnControllerModeChanged)(int nMode));



/**
 * ��ʼ������
 *
 * ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸��ʼ��ʧ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_InitArmor();



/**
 * ��ʼ���Ȳ�ģ��
 *
 * ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸��ʼ��ʧ��
 * 
 * ע����ʼ����ʱ����������ģ�鶼�ᱻ��ʼ��
 * �����߿�����HS_OpenDeviceDriver��ʱ��
 * �����Ƿ�����
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_InitLeg();

/**
 * ����UDP͸��ģʽ
 *
 * params:
 *   
 * 
 * ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸��ʼ��ʧ��
 *    2 ��������
 *    3 �豸��ʶ������
 *
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_EnablePassThroughMode(char deviceIdentifier[32], char IP[128], int Port, int RepeatNumber, int protocol);

/**
 * �����������豸
 * 
 * ����: 
 *  -> params:
	   deviceIdentifier [int] ֧�ֵ��豸��ʶ
 *   
 *     ����ֵ:
 *     0: �������κ��豸 [ȱʡ]
 *     1: �����豸
 *     2: �����豸
 *     4: �����豸
 * 
 *     �����Ҫͬʱ��������豸,ֻ��Ҫ�Ա�ʶ������|���㼴��
 *     ������Ҫ�������׺������豸,ֻ��Ҫ���� 1 | 4 = 5����
 *     5���ɡ�
 * 
 *  -> params:
 *     void (*fpResult)(bool, char*) [func*] ��ʼ���ɹ��ص�
 *     �ɹ�����true, ��������false �� errMsg
 *     
 *     �ò���ȱʡΪ0��˵��û�д���ص�����
 */
ARMOR_DEVICE_DRIVER_EXPORT
void HS_OpenDeviceDriver(int deviceIdentifier = 0, void (*fpResult)(bool bResult, char* errMsg) = 0);


/**.
 * �ͷ���Դ
 * 
 * ����
 * -> params:
 *    void(*fpResult)()  �ͷųɹ�����ûص�,
 *    �ڻص������п���ִ�йر���Դ��Ĳ���,�ص�
 *    δ����ǰ,�����ܱ�֤��Դ����ȫ�ͷš�
 */
ARMOR_DEVICE_DRIVER_EXPORT
void HS_ReleaseDeviceDriver(void(*fpResult)());


/**
 * ���ÿ����ƶ�ģʽ
 * 
 * ����
 * -> params:
 *    pDeviceHandler [void*] �豸��ʶ��
 *    �����豸�����ɹ��󷵻ص��豸��ʶ��
 * 
 *    mode [int] ģʽ����
 *    1���������ģʽ
 * 
 *    2������λ��ģʽ
 * 
 * ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorDeviceMoveMode(int mode);


/**
 * �����Ȳ��ƶ�ģʽ
 *
 * ����
 * -> params:
 *    deviceIdentifier [int] �豸��ʶ��
 *    �豸��ʶ��,ȡֵ��
 *    2������
 *    4������
 *
 *    mode [int] ģʽ����
 *    1���������ģʽ
 *    2������λ��ģʽ
 *
 * ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegDeviceMoveMode(int deviceIdentifier , int mode);


/**
 * �����ز�ģ���������
 *
 * ����
 * -> params:
 *    nSamplingPrecision [int] ��������
 *    ϵͳȱʡ����Ϊ30
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetSamplingPrecision(int nSamplingPrecision);


/*
 * �����ز����״���ģʽ
 *
 * ����
 * -> params:
 *    TriggerMode [b8] ����ģʽ
 *    ϵͳȱʡ����Ϊ��Ե�������أ�����
 * 
 * TriggerMode��ֵΪ��
 *   1���ߵ�ƽˮƽ���� High Level Trigger
 *   2�����أ������أ����� Rising Edge Trigger
 * 
 * Ӱ�죺
 *   1���ز�������/�Ҳఴť
 *   2���ز�������/�Ҳ����
 * 
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorTriggerMode(int TriggerMode);


/**
 * ��ȡ�ز�ģ��״̬
 *
 *  ����
 * -> return: �ز������豸״̬
 *    0 ����
 *    1 ����
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_GetArmorStatus();

/**
 * ���ÿ��׵����ص�
 *
 * ����:
 * ->  params:
 *     lpFuncPowerChangedResult ����ָ��
 *	  
 * ->  ���� lpFuncPowerChangedResult ԭ��Ϊ
 *     void FuncPowerChangedResult(b8 power) 
 * 
 *   -> params:
 *	   changedMode [b8] �ϱ�������ģʽ
 *	   0: ÿ֡�ϴ�һ��
 *	   1: �ı��ʱ����ϴ� [ȱʡֵ]
 *	 
 * 
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorPowerChangedResult(void (*lpFuncPowerChangedResult)(b8 power), b8 changedMode = 1);


/**
 * �ز��豸�궨
 * 
 * ���øú�����,���ɼ��궨����,�ɼ��궨���ݵ�ʱ��
 * �����ڽ����ݽ��д�����ת��(���ٵ����ƶ�,����,����
 * ���û��ص�)
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_ArmorCalibration();


/**
 * ���ñ궨�ص�
 *
 * ����:
 * ->  params:
 *     lpFuncArmorCalibrationResult ����ָ��
 *
 * ->  ���� lpFuncArmorCalibrationResult ԭ��Ϊ
 *     void FuncArmorCalibrationResult()
 *     ���궨�����󴥷��÷��� 
 * 
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorCalibrationComplete(void (*lpFuncArmorCalibrationResult)());


/**
 * ���ÿ���ǰ���ƶ��ص�
 *
 * ����:
 * -> params:
 *    lpArmorForwardOrBackMove [Function] ����ǰ���ƶ��Ļص�����
 * 
 * ->   ���� lpArmorForwardOrBackMove ԭ��Ϊ
 *     void lpArmorForwardOrBackMove(double sine, double angle)
 *     �ú�����������:
 * 
 * ->  params:
 *     sine [double] ��ǰ�ƶ��Ƕȵ�����ֵ����ǰΪ��,���Ϊ��
 *	
 * ->  params
 *     angle [double] ��ǰ�ƶ��ǶȵĽǶ�ֵ����ǰΪ��,���Ϊ��
 *
 *
 *  ����
 * -> return: ������

 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorForwardOrBackMove(void (*lpArmorForwardOrBackMove)(double sine, double angle));


/**
 * ���ÿ��������ƶ��ص�
 *
 * ->  params:
 *     HS_SetArmorLeftOrRightMove [Function] ���������ƶ��Ļص�����
 *
 * ->   ���� lpArmorForwardOrBackMove ԭ��Ϊ
 *     void lpArmorForwardOrBackMove(double sine, double angle)
 *     �ú�����������:
 *
 * ->  params:
 *     sine [double] ��ǰ�ƶ��Ƕȵ�����ֵ����ǰΪ��,���Ϊ��
 *
 * ->  params
 *     angle [double] ��ǰ�ƶ��ǶȵĽǶ�ֵ����ǰΪ��,���Ϊ��
 *
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorLeftOrRightMove(void (*lpArmorLeftOrRightMove)(double sine, double angle));


/**
 * ���ÿ�����ఴť�¼��ص�
 *
 * ->  params:
 *     lpArmorLeftButtonStateChanged [Function] ���ÿ�����ఴť�¼��ص�
 *
 * ->   ���� lpArmorLeftButtonStateChanged ԭ��Ϊ
 *     void lpArmorLeftButtonStateChanged(bool state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [bool] stateΪtrue��ʱ��Ϊ����״̬
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorLeftButtonStateChanged(void (*lpArmorLeftButtonStateChanged)(bool state));


/**
 * ���ÿ����Ҳఴť�¼��ص�
 *
 * ->  params:
 *     lpArmorRightButtonStateChanged [Function] ���ÿ����Ҳఴť�¼��ص�
 *
 * ->  ���� lpArmorRightButtonStateChanged ԭ��Ϊ
 *     void lpArmorRightButtonStateChanged(bool state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [bool] state Ϊtrue ��ʱ��Ϊ����״̬
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorRightButtonStateChanged(void (*lpArmorRightButtonStateChanged)(bool state));



/**
 * ���ÿ����������¼��ص�
 *
 * ->  params:
 *     lpArmorLeftInfraredStateChanged [Function] ���ÿ����������¼��ص�
 *
 * ->  ���� lpArmorLeftInfraredStateChanged ԭ��Ϊ
 *     void lpArmorLeftInfraredStateChanged(bool state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [bool] state Ϊ true ��ʱ��Ϊ���ⴥ��״̬
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorLeftInfraredStateChanged(void (*lpArmorLeftInfraredStateChanged)(bool state));


/**
 * ���ÿ����Ҳ�����¼��ص�
 *
 * ->  params:
 *     lpArmorRightInfraredStateChanged [Function] ���ÿ����Ҳ�����¼��ص�
 *
 * ->  ���� lpArmorRightInfraredStateChanged ԭ��Ϊ
 *     void lpArmorRightInfraredStateChanged(bool state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [bool] state Ϊ true ��ʱ��Ϊ���ⴥ��״̬
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorRightInfraredStateChanged(void (*lpArmorRightInfraredStateChanged)(bool state));


/**
 * ���õ�ѹ״̬�ı��¼��ص�
 *
 * ->  params:
 *     lpArmorVoltageStateChanged [Function] ���ÿ��׵�ѹ�¼��ص�
 *
 * ->  ���� lpArmorVoltageStateChanged ԭ��Ϊ
 *     void lpArmorRightInfraredStateChanged(int state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [int] state Ϊ��ǰ�豸��ѹ״̬,����:
 *     0���͵�ѹ
 *     1������������ѹ
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorVoltageStateChanged(void (*lpArmorVoltageStateChanged)(int state));


/**
 * ���ó��״̬�ı��¼��ص�
 *
 * ->  params:
 *     lpArmorRechargingStateChanged [Function] ���ÿ��׳��״̬�¼��ص�
 *
 * ->  ���� lpArmorRechargingStateChanged ԭ��Ϊ
 *     void lpArmorRechargingStateChanged(int state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [int] state Ϊ���״̬������
 *     1: ���ڳ��
 *     2: δ���
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetArmorRechargingStateChanged(void (*lpArmorRechargingStateChanged)(int state));


/**
 * ����������̰�
 *
 * ����:
 * 
 * ->  parmas:
 *   
 *     deviceIdentifier [int] �豸��ʶ��
 *     1: �����豸
 *     2: �����豸
 *     4: �����豸
 * 
 * ->  params:
 *     w [b8]  �ϼ� [ȱʡ:KEY_W]
 *     a [b8]  ��� [ȱʡ:KEY_A]
 *     s [b8]  �¼� [ȱʡ:KEY_S]
 *     d [b8]  �Ҽ� [ȱʡ:KEY_D]
 * 
 * �󶨵�ֵ��windows�����¼������ascii��
 * ����A������65
 */
ARMOR_DEVICE_DRIVER_EXPORT
void HS_BindMoveVirtualKey(int deviceIdentifier,b8 w, b8 a, b8 s, b8 d);


/**
 * ������ָ����ز�ģ��
 *
 * ����:
 * ->    params:  MonitorIndexs [unsigned short]   �������
 *       Ŀǰ�������ֵ���£�
 *		 1������:    1
 *		 2������:    2
 *		 3������:    3
 *		 4������:    4
 *		 5������:    5
 *		 6������:    6
 *		 7������:    7
 *		 8������:    8
 *		 9������:    9
 *		 10������:   10
 *		 11������:   11
 *		 12������:   12
 *       
 * ->    params:  ÿ������Ķ�����ʱ��
 *       t1 ����1������Ķ�����ʱ��
 *       t2 ����2������Ķ�����ʱ��
 *       �Դ�����
 * 
 * ->    parmas: byteScale  [b8]
 *       ��ʱ�䱶��
 *       Ŀǰϵͳ��������Ϊ100ms��������Ϊ1��ʱ��,��ʱ��Ϊ
 *       T��max�� = 100ms * byteScale(1) * t(F)  t �ʣ� N | [0,F] }
 *		 T��min�� = 100ms * byteScale(1) * t(1)
 *       �����ʱ��Ϊ 1500ms,��С��ʱ��Ϊ100ms
 * 
 * @return true Ϊָ���·��ɹ�,false Ϊ�·�ʧ��
 * @note:
 *    ָ���·��ɹ���������λ����һ�����������У�
 *    ��������ָ�����λ��������
 */
ARMOR_DEVICE_DRIVER_EXPORT
bool HS_ArmorDeviceShake(unsigned short MonitorIndexs, b8 t1, b8 t2, b8 t3, b8 t4, b8 t5, b8 t6, b8 t7, b8 t8, b8 t9 ,
	            b8 t10, b8 t11, b8 t12, b8 byteScale = 100);


/**
 * �Ȳ��豸�궨
 *
 * ���øú�����,���ɼ��궨����,�ɼ��궨���ݵ�ʱ��
 * �����ڽ����ݽ��д�����ת��(���ٵ����ƶ�,����,����
 * ���û��ص�)
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 *    2 �豸δ���ã����HS_OpenDeviceDriver��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_LegCalibration();



/**
 * �����Ȳ��궨�ص�
 *
 * ����:
 * ->  params:
 *     lpFuncLegCalibrationResult ����ָ��
 *
 * ->  ���� lpFuncLegCalibrationResult ԭ��Ϊ
 *     void lpFuncLegCalibrationResult()
 *     ���궨�����󴥷��÷���
 *
 * ->  params:
 *     deviceIdentifier [int] �豸��ʶ��
 *     �豸��ʶ��,ȡֵ��
 *     2������
 *     4������
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegCalibrationComplete(void (*lpFuncLegCalibrationResult)(), int deviceIdentifier);


/**
 * �����Ȳ�ģ������ص�
 *
 * ����:
 * ->  params:
 *     lpFuncLegResult ����ָ��
 *
 * ->  ���� lpFuncLegPowerChangedResult ԭ��Ϊ
 *     void lpFuncLegPowerChangedResult(int identifier, b8 power)
 *	   ���� 
 *     power [b8]  ���صĵ���
 *
 * 
 *   -> params:
 *     identifier [int] �豸��ʶ��
 *     2:����ģ������ϴ�
 *     4:����ģ������ϴ�
 * 
 *   -> params:
 *	   changedMode [b8] �ϱ�������ģʽ
 *	   0: ÿ֡�ϴ�һ��
 *	   1: �ı��ʱ����ϴ� [ȱʡֵ]
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 *    2 �豸��ʶ�����豸������)
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegPowerChangedResult(void (*lpFuncLegPowerChangedResult)(b8 power), int identifier, b8 changedMode = 1);


/**
 * ���õ�ѹ״̬�ı��¼��ص�
 *
 * ->  params:
 *     lpLegVoltageStateChanged [Function] �����Ȳ���ѹ�ı��¼�
 *
 * ->  ���� lpLegVoltageStateChanged ԭ��Ϊ
 *     void lpLegVoltageStateChanged(int state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [int] state Ϊ��ǰ�豸��ѹ״̬,����:
 *     0���͵�ѹ
 *     1������������ѹ
 * 
 * -> params:
 *     identifier [int] �豸��ʶ��
 *     2:����ģ���ѹ״̬�ϴ�
 *     4:����ģ���ѹ״̬�ϴ�
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegVoltageStateChanged(void (*lpLegVoltageStateChanged)(int state), int identifier);

/**
 * ���ó��״̬�ı��¼��ص�
 *
 * ->  params:
 *     lpLegRechargingStateChanged [Function] ���ÿ��׳��״̬�¼��ص�
 *
 * ->  ���� lpArmorRechargingStateChanged ԭ��Ϊ
 *     void lpArmorRechargingStateChanged(int state)
 *     �ú�����������:
 *
 * ->  params:
 *     state [int] state Ϊ���״̬������
 *     1: ���ڳ��
 *     2: δ���
 * 
 * -> params:
 *     identifier [int] �豸��ʶ��
 *     2:����ģ���ѹ״̬�ϴ�
 *     4:����ģ���ѹ״̬�ϴ�
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegRechargingStateChanged(void (*lpLegRechargingStateChanged)(int state), int identifier);



/**
 * �����Ȳ�ģ��ǰ���ƶ��ص�
 *
 * ����:
 * -> params:
 *    lpLegForwardOrBackMove [Function] ����ǰ���ƶ��Ļص�����
 *
 * ->   ���� lpLegForwardOrBackMove ԭ��Ϊ
 *     void lpLegForwardOrBackMove(double sine, double angle)
 *     �ú�����������:
 *
 * ->  params:
 *     sine [double] ��ǰ�ƶ��Ƕȵ�����ֵ����ǰΪ��,���Ϊ��
 *
 * ->  params
 *     angle [double] ��ǰ�ƶ��ǶȵĽǶ�ֵ����ǰΪ��,���Ϊ��
 *
 * 
 * 
 * -> params:
 *    deviceIdentifier [int] �豸��ʶ��
 *    �豸��ʶ��,ȡֵ��
 *    2������
 *    4������
 *
 *  ����
 * -> return: ������
 *
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegForwardOrBackMove(void (*lpLegForwardOrBackMove)(double sine, double angle), int deviceIdentifier);


/**
 * �����Ȳ�ģ�������ƶ��ص�
 *
 * ->  params:
 *     lpLegLeftOrRightMove [Function] ���������ƶ��Ļص�����
 *
 * ->   ���� lpLegLeftOrRightMove ԭ��Ϊ
 *     void lpLegLeftOrRightMove(double sine, double angle)
 *     �ú�����������:
 *
 * ->  params:
 *     sine [double] ��ǰ�ƶ��Ƕȵ�����ֵ����ǰΪ��,���Ϊ��
 *
 * ->  params
 *     angle [double] ��ǰ�ƶ��ǶȵĽǶ�ֵ����ǰΪ��,���Ϊ��
 *
 *
 *
 *  ����
 * -> return: ������
 *    0 �޴���
 *    1 �豸δ��ʼ��
 */
ARMOR_DEVICE_DRIVER_EXPORT
int HS_SetLegLeftOrRightMove(void (*lpLegLeftOrRightMove)(double sine, double angle), int deviceIdentifier);


#endif
