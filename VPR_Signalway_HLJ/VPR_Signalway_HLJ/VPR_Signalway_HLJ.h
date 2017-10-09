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
1����ʶ����ƽӿ�
���ܣ���ȡ����ʶ������
1.1��Դ��ʼ��
��������
����ֵ	����ֵ����	����ֵ˵��
			int		0		    �����ɹ�
						-100	    �豸����Ӧ
						-2000	��������
����	����	��������	����	����	����

����	�����㹻���ڴ�ռ䣬��֤��������
��ע
*/
int XLW_VFR_API VLPR_Init();

/* 1.2�ͷ���Դ
��������
����ֵ	����ֵ����	����ֵ˵��
			int	 	0		    �����ɹ�
                        -100	    �豸����Ӧ
                        -2000	��������
����	����	��������	����	����	����

����	�ͷ��ڴ�ռ�
��ע	 */
int XLW_VFR_API VLPR_Deinit();

/* 1.3�����豸
��������
����ֵ	����ֵ����	����ֵ˵��
			int		>0	���豸�ɹ�������ֵΪ�豸�����
                        -100		�豸����Ӧ
                        -1000	�����������
                        -1001	�豸��ռ��
                        -1002	�豸��ʧ��
                        -2000	��������
����	����	��������	����	����	����
		����	nType		int		4		���ӷ�ʽ��0=���ڣ�1=��������
				sParas		char*	N		������Ϣ��-���ڣ�����ںš�
													����COM1��
													-���磺���ַ���˿ڣ��û��������롱
													����192.168.0.11,8000,admin,password��
����	�������豸��������
*/
int XLW_VFR_API VLPR_Login(int nType, char* sParas);

/* 1.4�Ͽ��豸����
��������
����ֵ	����ֵ ����	����ֵ˵��
int	 	0		    �ر��豸�ɹ�
			-100	    �豸����Ӧ
			-1000	�����������
			-2000	��������
����	����	��������	����	����	����
		����	nHandle		int 	4	�豸���

����	�������豸�Ͽ�����
*/
int XLW_VFR_API VLPR_Logout(int nHandle);

/* 1.5����ʶ�����ص�
��������
����	����	��������	����	����	����
����	nHandle		int 	4	�豸���
����ֵ	����ֵ����	����ֵ˵��
int	 		0		        �����ɹ�
				-100	        �豸����Ӧ
				-1000	    �����������
				-2000	    ��������

pFunc	CBFun_RspRegResult 	4	ʶ�����ص�����NULLʱ��ȡ���ص�
pUser	void*		4	�û��Զ�������

����	���ʶ���������ص�����
*/

int XLW_VFR_API VLPR_SetResultCallBack(int nHandle, CBFun_GetRegResult pFunc, void* pUser);

/* 1.6�����豸״̬�ص�
��������
����ֵ	����ֵ����	����ֵ˵��
			int	 	0	�����ɹ�
						-100	�豸����Ӧ
						-1000�����������
						-2000��������
����	����	��������	����	����	����
		����	nHandle		int 	4	�豸���
                nTimeInvl	    int		4	״̬�㱨ʱ����
				pFunc		CBFun_GetDevStatus	4	�쳣��Ϣ�ص�����func=NULLʱ��ȡ���ص�
				pUser		void*	4	�û��Զ�������
����	���ûص�����ʱ�㱨�豸����״̬���豸�����쳣ʱ�������ص�
��ע	�ο�CBFun_GetDevStatus
*/
int XLW_VFR_API VLPR_SetStatusCallBack(int nHandle, int nTimeInvl, CBFun_GetDevStatus pFunc, void* pUser);

/*
1.7�ֶ�����ץ��
����ֵ	����ֵ����	����ֵ˵��
            Int	 	0	�����ɹ�
                        -100	�豸����Ӧ
                        -1000�����������
                        -2000��������

����	����	��������	����	����	����
        ����	nHandle		int 	4	�豸���

����	�ֶ�����ץ��ʶ����ʶ��ص������з��ؽ��
*/
int XLW_VFR_API VLPR_ManualSnap(int nhandle);

/*
1.8��ȡ�豸״̬
��������
����ֵ	����ֵ����	����ֵ˵��
            int	 	0		�����ɹ�
                        -100	�豸����Ӧ
                        -1000	�����������
                        -2000	��������

����	����	��������	        ����	����	����
        ����	nHandle		    int		4		�豸���
        ���	pStatusCode	    int*	    4		�豸״̬�����룬0��ʾ����

�汾����	��ȡ�豸����״̬
*/
/*
1.12����ʶ��ӿڴ�����
������	��������
0		    ����
-100	    �豸����Ӧ
-1000	�����������
-1001	�豸��ռ��
-1002	��ʧ��
-2000	��������
-2000����	Ԥ��
*/

int  XLW_VFR_API VLPR_GetStatus(int nHandle, int* pStatusCode);

/*
1.9��ȡ��������ϸ����
��������
����ֵ	����ֵ����	����ֵ˵��
            Int	 	0	�����ɹ�
                        -100	�豸����Ӧ
                        -1000�����������
                        -2000��������
����	����	��������		����	����	����
        ����	nStatusCode		 Int		4		������
        ���	sStatusMsg		 char*	N		��������Ϣ�����ַ
        ����	nStatusMsgLen	 Int		4		��������Ϣ���泤��
����	��ѯ��������ϸ����
*/

int XLW_VFR_API VLPR_GetStatusMsg(int nStatusCode, char* sStatusMsg, int nStatusMsgLen);

/*
1.10��ȡ�豸�汾��Ϣ
��������
����ֵ	����ֵ����	����ֵ˵��
            int	 	0	            �����ɹ�
                        -100	        �豸����Ӧ
                        -1000       �����������
                        -2000       ��������
����	����	��������	����	����	����
        ���	sVersion	char*	N	�汾��Ϣ�����ַ
        ����	nVerLen		int 	4	�汾��Ϣ���泤��
����	��ȡ�����ư汾��Ϣ
*/

int XLW_VFR_API VLPR_GetVersion(char* sVersion, int nVerLen);

#endif