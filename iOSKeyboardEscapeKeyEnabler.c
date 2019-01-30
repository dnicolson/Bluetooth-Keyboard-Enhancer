// clang -framework IOKit -framework Carbon iOSKeyboardEscapeKeyEnabler.c -o iOSKeyboardEscapeKeyEnabler
// ./iOSKeyboardEscapeKeyEnabler

#include <Carbon/Carbon.h>
#include <IOKit/hid/IOHIDManager.h>
#include <IOKit/hid/IOHIDValue.h>

void TriggerEscKey()
{
    CGEventRef event;
    event = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)kVK_Escape, true);
    CGEventPost(kCGSessionEventTap, event);
}

CFMutableDictionaryRef CreateMatchingDictionary(UInt32 usage_page, UInt32 usage)
{
    CFMutableDictionaryRef dictionary = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFCopyStringDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    CFNumberRef page_number = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usage_page);
    CFDictionarySetValue(dictionary, CFSTR(kIOHIDDeviceUsagePageKey), page_number);
    CFRelease(page_number);

    CFNumberRef usage_number = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usage);
    CFDictionarySetValue(dictionary, CFSTR(kIOHIDDeviceUsageKey), usage_number);
    CFRelease(usage_number);

    return dictionary;
}

void HIDKeyboardCallback(void* context, IOReturn result, void* sender, IOHIDValueRef value)
{
    IOHIDElementRef elem = IOHIDValueGetElement(value);
    uint32_t usage_page = IOHIDElementGetUsagePage(elem);
    uint32_t usage = IOHIDElementGetUsage(elem);
    long pressed = IOHIDValueGetIntegerValue(value);

    if (usage_page == kHIDPage_Consumer && usage == kHIDUsage_Csmr_ACHome && pressed == 1) {
        TriggerEscKey();
    }
}

int main()
{
    IOHIDManagerRef hid_manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    CFMutableDictionaryRef matching_dictionary = CreateMatchingDictionary(kHIDPage_GenericDesktop, kHIDUsage_GD_Keyboard);
    IOHIDManagerSetDeviceMatching(hid_manager, matching_dictionary);
    IOHIDManagerRegisterInputValueCallback(hid_manager, HIDKeyboardCallback, NULL);
    IOHIDManagerScheduleWithRunLoop(hid_manager, CFRunLoopGetMain(), kCFRunLoopDefaultMode);
    IOHIDManagerOpen(hid_manager, kIOHIDOptionsTypeNone);
    CFRunLoopRun();
}
