// SPDX-License-Identifier: GPL-3.0-or-later
#include "fordlink/fordlink.h"
#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif
#if defined(__APPLE__) && TARGET_OS_IOS
#include "link/platform/apple/LinkPortableCore.c"
/* Xcode compiles one product-owned C translation unit for Ford-specific code. */
#include "network.c"
#include "module.c"
#include "identity.c"
#include "module_scan.c"
#include "signal.c"
#include "procedure.c"
#endif
const char *fordlink_product_name(void){return "FORDLink";}
const char *fordlink_brand_name(void){return "Ford";}
const char *fordlink_version(void){return FORDLINK_VERSION;}
