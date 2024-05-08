
#include "shv.h"

VOID
ShvUnload (
    VOID
    )
{
   
    
    ShvOsRunCallbackOnProcessors(ShvVpUnloadCallback, NULL);

    ShvOsDebugPrint("The SHV has been uninstalled.\n");
}

INT32
ShvLoad (
    VOID
    )
{
    SHV_CALLBACK_CONTEXT callbackContext;

    callbackContext.Cr3 = __readcr3();
    callbackContext.FailureStatus = SHV_STATUS_SUCCESS;
    callbackContext.FailedCpu = -1;
    callbackContext.InitCount = 0;
    ShvOsRunCallbackOnProcessors(ShvVpLoadCallback, &callbackContext);

    
    if (callbackContext.InitCount != ShvOsGetActiveProcessorCount())
    {
        ShvOsDebugPrint("The SHV failed to initialize (0x%lX) Failed CPU: %d\n",
                        callbackContext.FailureStatus, callbackContext.FailedCpu);
        return callbackContext.FailureStatus;
    }

    ShvOsDebugPrint("The SHV has been installed.\n");
    return SHV_STATUS_SUCCESS;
}
