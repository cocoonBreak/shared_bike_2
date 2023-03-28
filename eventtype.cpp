#include "eventtype.h"

static EErrorReason ERR[] = {
	{ERRC_SUCCESS, "ok."},
	{ERRC_INVALID_MSG, "Invalid message."},
	{ERRC_INVALID_DATA, "Invalid data."},
	{ERRC_METHOD_NOT_ALLOWED, "Method not allowed."},
	{ERRC_PROCCESS_FAILED, "Proccess failed."},
	{ERRC_BIKE_IS_TOOK, "Bike is took."},
	{ERRC_BIKE_IS_RUNNING, "Bike is running."},
	{ERRC_BIKE_IS_DAMAGED, "Bike is damaged."},
	{ERRC_NULL, "Undefined."}
};

const char* getReasonByErrorCode(i32 code)
{
	i32 i;
	for (i = 0; ERR[i] .code != ERRC_NULL; ++i) {
		if (ERR[i].code == code) return ERR[i].reason;
	}

	return ERR[i].reason;
}