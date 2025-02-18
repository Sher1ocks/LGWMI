//
//  LGWMI.hpp
//  LGWMI
//
//  Copyright © 2020 Le Bao Hiep. All rights reserved.
//

#ifndef _LGWMI_hpp
#define _LGWMI_hpp

#include <IOKit/acpi/IOACPIPlatformDevice.h>
#include "KeyImplementations.hpp"

#define WM_GET          1
#define WM_SET          2
#define WM_BATT_LIMIT   0x61
#define WM_FN_LOCK      0x407
#define WMBB_USB_CHARGE 0x10B
#define WMBB_BATT_LIMIT 0x10C

class LGWMI : public IOService {
    OSDeclareDefaultStructors(LGWMI)

    VirtualSMCAPI::Plugin vsmcPlugin {
        xStringify(PRODUCT_NAME),
        parseModuleVersion(xStringify(MODULE_VERSION)),
        VirtualSMCAPI::Version,
    };

public:
    IOService *probe(IOService *provider, SInt32 *score) override;
    bool start(IOService *provider) override;
    void setBatteryConservativeMode(bool state);
    void setFnLockMode(bool state);
    void setUSBChargeMode(bool state);

private:
    IOACPIPlatformDevice *mapDevice {nullptr};
    IONotifier *vsmcNotifier {nullptr};

    int lg_wmab(uint32_t method_id, uint32_t arg1, uint32_t arg2);
    int lg_wmbb(uint32_t method_id, uint32_t arg1, uint32_t arg2);

    void registerVSMC(void);
    static bool vsmcNotificationHandler(void *sensors, void *refCon, IOService *vsmc, IONotifier *notifier);
};

#endif //_LGWMI_hpp
