// clang -framework IOKit -framework Carbon BluetoothKeyboardEnhancer.c -o BluetoothKeyboardEnhancer
// ./BluetoothKeyboardEnhancer

#include <Carbon/Carbon.h>
#include <IOKit/hid/IOHIDManager.h>
#include <IOKit/hid/IOHIDValue.h>

void TriggerEscKey()
{
    CGEventRef event;
    event = CGEventCreateKeyboardEvent(NULL, kVK_Escape, true);
    CGEventPost(kCGSessionEventTap, event);
}

void TriggerEmojiPicker()
{
    CGEventRef keyboard_down_event = CGEventCreateKeyboardEvent(NULL, kVK_Space, true);
    CGEventRef keyboard_up_event = CGEventCreateKeyboardEvent(NULL, kVK_Space, false);

    CGEventSetFlags(keyboard_down_event, kCGEventFlagMaskCommand | kCGEventFlagMaskControl);
    CGEventSetFlags(keyboard_up_event, 0);

    CGEventPost(kCGHIDEventTap, keyboard_down_event);
    CGEventPost(kCGHIDEventTap, keyboard_up_event);

    CFRelease(keyboard_down_event);
    CFRelease(keyboard_up_event);
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
    static int ctrl_down, command_down;

    if (usage_page == kHIDPage_Consumer && usage == kHIDUsage_Csmr_ACHome && pressed == 1) {
        TriggerEscKey();
    }

    if (usage_page == kHIDPage_KeyboardOrKeypad && usage == 0xE0) {
        ctrl_down = pressed;
    }

    if (usage_page == kHIDPage_KeyboardOrKeypad && usage == 0xE3) {
        command_down = pressed;
    }

    if (ctrl_down && command_down && usage_page == kHIDPage_KeyboardOrKeypad && usage == -1 && pressed == 1103823438081) {
        TriggerEmojiPicker();
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
