#pragma once

#include "standards.hpp"

enum HS_RUNNING_STATUS { HS_RUNNING_STATUS_CHECK_MONITORING_THREAD = 1, };

typedef int (__stdcall* _AhnHS_Callback_t)(long lCode, long lParamSize, void* pParam);

#define ANTICPX_TRANS_BUFFER_MAX	600

/* error-name-fetching */
namespace ahn
{
	std::string get_error_name(unsigned int error_code);
}

/* heartbeat errors */
#define ANTICPXSVR_BASECODE_ERROR							0xE9040000

#define ERROR_ANTICPXSVR_FILE_ACCESS_DENIED					(ANTICPXSVR_BASECODE_ERROR + 0x01)
#define ERROR_ANTICPXSVR_FILE_NOT_FOUND						(ANTICPXSVR_BASECODE_ERROR + 0x02)
#define ERROR_ANTICPXSVR_INVALID_PARAMETER					(ANTICPXSVR_BASECODE_ERROR + 0x03)
#define ERROR_ANTICPXSVR_BAD_FORMAT							(ANTICPXSVR_BASECODE_ERROR + 0x04)
#define ERROR_ANTICPXSVR_NOT_YET_RECEIVED_RESPONSE			(ANTICPXSVR_BASECODE_ERROR + 0x05)
#define ERROR_ANTICPXSVR_NO_WAITING							(ANTICPXSVR_BASECODE_ERROR + 0x06)
#define ERROR_ANTICPXSVR_NOT_ENOUGH_MEMORY					(ANTICPXSVR_BASECODE_ERROR + 0x07)
#define ERROR_ANTICPXSVR_BAD_MESSAGE						(ANTICPXSVR_BASECODE_ERROR + 0x08)
#define ERROR_ANTICPXSVR_REPLY_ATTACK						(ANTICPXSVR_BASECODE_ERROR + 0x09)
#define ERROR_ANTICPXSVR_HSHIELD_FILE_ATTACK				(ANTICPXSVR_BASECODE_ERROR + 0x0A)
#define ERROR_ANTICPXSVR_CLIENT_FILE_ATTACK					(ANTICPXSVR_BASECODE_ERROR + 0x0B)
#define ERROR_ANTICPXSVR_MEMORY_ATTACK						(ANTICPXSVR_BASECODE_ERROR + 0x0C)
#define ERROR_ANTICPXSVR_OLD_VERSION_CLIENT_EXPIRED			(ANTICPXSVR_BASECODE_ERROR + 0x0D)
#define ERROR_ANTICPXSVR_UNKNOWN_CLIENT						(ANTICPXSVR_BASECODE_ERROR + 0x0E)
#define ERROR_ANTICPXSVR_V3SENGINE_FILE_ATTACK				(ANTICPXSVR_BASECODE_ERROR + 0x0F)
#define ERROR_ANTICPXSVR_NANOENGINE_FILE_ATTACK				(ANTICPXSVR_BASECODE_ERROR + 0x10)
#define ERROR_ANTICPXSVR_INVALID_HACKSHIELD_VERSION			(ANTICPXSVR_BASECODE_ERROR + 0x11)
#define ERROR_ANTICPXSVR_INVALID_ENGINE_VERSION				(ANTICPXSVR_BASECODE_ERROR + 0x12)
#define ERROR_ANTICPXSVR_CREATE_SVROBJ_EXCEPTION			(ANTICPXSVR_BASECODE_ERROR + 0x13)
#define ERROR_ANTICPXSVR_MAKEREQ_EXCEPTION					(ANTICPXSVR_BASECODE_ERROR + 0x14)
#define ERROR_ANTICPXSVR_VERIFY_EXCEPTION					(ANTICPXSVR_BASECODE_ERROR + 0x15)
#define ERROR_ANTICPXSVR_TRACE_EXCEPTION					(ANTICPXSVR_BASECODE_ERROR + 0x16)
#define ERROR_ANTICPXSVR_CREATE_CLIENT_OBJECT_EXCEPTION		(ANTICPXSVR_BASECODE_ERROR + 0x17)
#define ERROR_ANTICPXSVR_ABNORMAL_HACKSHIELD_STATUS			(ANTICPXSVR_BASECODE_ERROR + 0x18)
#define ERROR_ANTICPXSVR_DETECT_CALLBACK_IS_NOTIFIED		(ANTICPXSVR_BASECODE_ERROR + 0x19)
#define ERROR_ANTICPXSVR_VERIFYEX_EXCEPTION					(ANTICPXSVR_BASECODE_ERROR + 0x1A)
#define ERROR_ANTICPXSVR_ABNORMAL_HACKSHIELD_XSTATUS		(ANTICPXSVR_BASECODE_ERROR + 0x1B)
#define ERROR_ANTICPXSVR_OLD_HACKSHIELD_VERSION				(ANTICPXSVR_BASECODE_ERROR + 0x1C)

#define ERROR_ANTICPXSVR_UNKNOWN							(ANTICPXSVR_BASECODE_ERROR + 0xFF)

/* service errors */
#define HS_ERR_OK										0x00000000
#define HS_ERR_UNKNOWN									0x00000001
#define HS_ERR_INVALID_PARAM							0x00000002
#define HS_ERR_NOT_INITIALIZED							0x00000003
#define HS_ERR_COMPATIBILITY_MODE_RUNNING				0x00000004
#define HS_ERR_ALREADY_UNINITIALIZED					0x00000005
#define HS_ERR_STRING_CONVERSION_FAILED					0x00000006
#define HS_ERR_EXCEPTION_RAISED							0x00000007

#define HS_ERR_INVALID_LICENSE							0x00000100
#define HS_ERR_INVALID_FILES							0x00000101
#define HS_ERR_INIT_DRV_FAILED							0x00000102
#define HS_ERR_ANOTHER_SERVICE_RUNNING					0x00000103
#define HS_ERR_ALREADY_INITIALIZED						0x00000104
#define HS_ERR_DEBUGGER_DETECT							0x00000105
#define HS_ERR_EXECUTABLE_FILE_CRACKED					0x00000106
#define HS_ERR_NEED_ADMIN_RIGHTS						0x00000107
#define HS_ERR_MODULE_INIT_FAILED						0x00000108

#define HS_ERR_START_ENGINE_FAILED						0x00000200
#define HS_ERR_ALREADY_SERVICE_RUNNING					0x00000201
#define HS_ERR_DRV_FILE_CREATE_FAILED					0x00000202
#define HS_ERR_REG_DRV_FILE_FAILED						0x00000203
#define HS_ERR_START_DRV_FAILED							0x00000204
#define HS_ERR_START_THREAD_FAILED						0x00000205
#define HS_ERR_ALREADY_GAME_STARTED						0x00000206
#define HS_ERR_VIRTUAL_MACHINE_DETECT					0x00000207

#define HS_ERR_SERVICE_NOT_RUNNING						0x00000301
#define HS_ERR_SERVICE_STILL_RUNNING					0x00000302
#define HS_ERR_ALREADY_EXISTED							0x00000303
#define HS_ERR_INVALID_DATA								0x00000304
#define HS_ERR_NOT_SUPPORTED							0x00000305

#define HS_ERR_NEED_UPDATE								0x00000401

#define HS_ERR_API_IS_HOOKED							0x00000501

#define HS_ERR_GET_SDKVERSION_FAILED					0x00000601

#define HS_ERR_LMP_START								0x00000701

#define HS_ERR_HSMS_WAIT_TIME_OUT						0x00000801
#define HS_ERR_HSMS_WAIT_FAILED							0x00000802
#define HS_ERR_HSMS_NOT_RUNNING							0x00000803

/*  callback errors */
#define AHNHS_ACTAPC_STATUS_HACKSHIELD_RUNNING			0x00010001

#define AHNHS_ACTAPC_DETECT_ALREADYHOOKED				0x00010101
#define AHNHS_ACTAPC_DETECT_AUTOMOUSE					0x00010102
#define AHNHS_ACTAPC_DETECT_AUTOMACRO					0x00010104
#define AHNHS_ACTAPC_DETECT_HOOKFUNCTION				0x00010301
#define AHNHS_ACTAPC_DETECT_DRIVERFAILED				0x00010302
#define AHNHS_ACTAPC_DETECT_SPEEDHACK					0x00010303
#define AHNHS_ACTAPC_DETECT_MESSAGEHOOK					0x00010306
#define AHNHS_ACTAPC_DETECT_KDTRACE						0x00010307
#define AHNHS_ACTAPC_DETECT_KDTRACE_CHANGED				0x00010308
#define AHNHS_ACTAPC_DETECT_SPEEDHACK_RATIO				0x0001030B
#define AHNHS_ENGINE_DETECT_GAME_HACK					0x00010501
#define AHNHS_ACTAPC_DETECT_MULTI_LOADING				0x00010504
#define AHNHS_ACTAPC_DETECT_ABNORMAL_MEMORY_ACCESS		0x00010601
#define AHNHS_ACTAPC_DETECT_MODULE_CHANGE				0x00010701
#define AHNHS_ACTAPC_DETECT_ENGINEFAILED				0x00010702
#define AHNHS_ACTAPC_DETECT_CODEMISMATCH				0x00010703
#define AHNHS_ACTAPC_DETECT_PROTECTSCREENFAILED			0x00010704
#define AHNHS_ACTAPC_DETECT_MEM_MODIFY_FROM_LMP			0x00010705
#define AHNHS_ACTAPC_DETECT_LMP_FAILED					0x00010706
#define AHNHS_ACTAPC_DETECT_RMEM_MODIFY_FROM_LMP		0x00010709
#define AHNHS_ACTAPC_DETECT_ABNORMAL_FUNCTION_CALL		0x00010801
#define AHNHS_ACTAPC_DETECT_ANTIFREESERVER				0x00010901
#define AHNHS_ACTAPC_DETECT_ABNORMAL_HACKSHIELD_STATUS	0x00010A01