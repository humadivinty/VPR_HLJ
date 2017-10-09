#ifndef VPR_SIGNALWAY_HLG_H
#define  VPR_SIGNALWAY_HLG_H
#include "CommonDef_VPR.h"

#ifdef    VPR_SIGNALWAY_HLJ_EXPORTS
//#define XLW_GZ_VFR_API extern "C" __declspec(dllexport)
#define XLW_VFR_API __stdcall
#else
//#define XLW_GZ_VFR_API extern "C" __declspec(dllimport)
#define XLW_VFR_API __stdcall
#endif

/*
1车牌识别控制接口
功能：获取车牌识别结果；
1.1资源初始化
函数描述
返回值	返回值类型	返回值说明
			int		0		    操作成功
						-100	    设备无响应
						-2000	其它错误
参数	出入	参数名称	类型	长度	含义

功能	申请足够的内存空间，保证后续运作
备注
*/
int XLW_VFR_API VLPR_Init();

/* 1.2释放资源
函数描述
返回值	返回值类型	返回值说明
			int	 	0		    操作成功
                        -100	    设备无响应
                        -2000	其它错误
参数	出入	参数名称	类型	长度	含义

功能	释放内存空间
备注	 */
int XLW_VFR_API VLPR_Deinit();

/* 1.3连接设备
函数描述
返回值	返回值类型	返回值说明
			int		>0	打开设备成功，返回值为设备句柄号
                        -100		设备无响应
                        -1000	传入参数错误
                        -1001	设备被占用
                        -1002	设备打开失败
                        -2000	其它错误
参数	出入	参数名称	类型	长度	含义
		输入	nType		int		4		连接方式：0=串口，1=网络连接
				sParas		char*	N		连接信息：-串口：填“串口号”
													例“COM1”
													-网络：填“网址，端口，用户名，密码”
													例“192.168.0.11,8000,admin,password”
功能	主机与设备建立连接
*/
int XLW_VFR_API VLPR_Login(int nType, char* sParas);

/* 1.4断开设备连接
函数描述
返回值	返回值 类型	返回值说明
int	 	0		    关闭设备成功
			-100	    设备无响应
			-1000	传入参数错误
			-2000	其它错误
参数	出入	参数名称	类型	长度	含义
		输入	nHandle		int 	4	设备句柄

功能	主机与设备断开连接
*/
int XLW_VFR_API VLPR_Logout(int nHandle);

/* 1.5设置识别结果回调
函数描述
参数	出入	参数名称	类型	长度	含义
输入	nHandle		int 	4	设备句柄
返回值	返回值类型	返回值说明
int	 		0		        操作成功
				-100	        设备无响应
				-1000	    传入参数错误
				-2000	    其它错误

pFunc	CBFun_RspRegResult 	4	识别结果回调函数NULL时，取消回调
pUser	void*		4	用户自定义数据

功能	获得识别结果触发回调函数
*/

int XLW_VFR_API VLPR_SetResultCallBack(int nHandle, CBFun_GetRegResult pFunc, void* pUser);

/* 1.6设置设备状态回调
函数描述
返回值	返回值类型	返回值说明
			int	 	0	操作成功
						-100	设备无响应
						-1000传入参数错误
						-2000其它错误
参数	出入	参数名称	类型	长度	含义
		输入	nHandle		int 	4	设备句柄
                nTimeInvl	    int		4	状态汇报时间间隔
				pFunc		CBFun_GetDevStatus	4	异常消息回调函数func=NULL时，取消回调
				pUser		void*	4	用户自定义数据
功能	设置回调，定时汇报设备运行状态或当设备发生异常时则立即回调
备注	参考CBFun_GetDevStatus
*/
int XLW_VFR_API VLPR_SetStatusCallBack(int nHandle, int nTimeInvl, CBFun_GetDevStatus pFunc, void* pUser);

/*
1.7手动触发抓拍
返回值	返回值类型	返回值说明
            Int	 	0	操作成功
                        -100	设备无响应
                        -1000传入参数错误
                        -2000其它错误

参数	出入	参数名称	类型	长度	含义
        输入	nHandle		int 	4	设备句柄

功能	手动触发抓拍识别，在识别回调函数中返回结果
*/
int XLW_VFR_API VLPR_ManualSnap(int nhandle);

/*
1.8获取设备状态
函数描述
返回值	返回值类型	返回值说明
            int	 	0		操作成功
                        -100	设备无响应
                        -1000	传入参数错误
                        -2000	其它错误

参数	出入	参数名称	        类型	长度	含义
        输入	nHandle		    int		4		设备句柄
        输出	pStatusCode	    int*	    4		设备状态错误码，0表示正常

版本功能	获取设备运行状态
*/
/*
1.12车牌识别接口错误码
错误码	错误描述
0		    正常
-100	    设备无响应
-1000	传入参数错误
-1001	设备被占用
-1002	打开失败
-2000	其他错误
-2000以上	预留
*/

int  XLW_VFR_API VLPR_GetStatus(int nHandle, int* pStatusCode);

/*
1.9获取错误码详细描述
函数描述
返回值	返回值类型	返回值说明
            Int	 	0	操作成功
                        -100	设备无响应
                        -1000传入参数错误
                        -2000其它错误
参数	出入	参数名称		类型	长度	含义
        输入	nStatusCode		 Int		4		错误码
        输出	sStatusMsg		 char*	N		错误码信息缓存地址
        输入	nStatusMsgLen	 Int		4		错误码信息缓存长度
功能	查询错误码详细描述
*/

int XLW_VFR_API VLPR_GetStatusMsg(int nStatusCode, char* sStatusMsg, int nStatusMsgLen);

/*
1.10获取设备版本信息
函数描述
返回值	返回值类型	返回值说明
            int	 	0	            操作成功
                        -100	        设备无响应
                        -1000       传入参数错误
                        -2000       其它错误
参数	出入	参数名称	类型	长度	含义
        输出	sVersion	char*	N	版本信息缓存地址
        输入	nVerLen		int 	4	版本信息缓存长度
功能	获取顶棚牌版本信息
*/

int XLW_VFR_API VLPR_GetVersion(char* sVersion, int nVerLen);

#endif