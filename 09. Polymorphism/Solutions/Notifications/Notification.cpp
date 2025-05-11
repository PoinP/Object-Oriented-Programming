#include <stdexcept>

#include "Device.h";
#include "Notification.h"

Notification::~Notification() noexcept
{
    for (uint8_t i = 0; i < MAX_DEVICES; i++)
    {
        if (devices[i] != nullptr)
            devices[i]->detachChannel(this);
    }
}

void Notification::notifyAll(const SimpleString& message) const
{
    for (uint8_t i = 0; i < MAX_DEVICES; i++)
    {
        if (devices[i] != nullptr)
            notify(message, devices[i]);
    }
}

void Notification::notifyOne(const SimpleString& message, const Device* device) const
{
    if (!isAttachedTo(device))
        throw std::invalid_argument("The notification is not attached to this device");

    notify(message, device);
}

bool Notification::canAttachDevice() const
{
    return attachedDevices < MAX_DEVICES;
}

void Notification::attachDevice(Device* device)
{
    if (!canAttachDevice())
        throw std::invalid_argument("Can not attach any more devices!");

    if (isAttachedTo(device))
        return;

    for (uint8_t i = 0; i < MAX_DEVICES; i++)
    {
        if (devices[i] == nullptr)
        {
            devices[i] = device;
            devices[i]->attachChannel(this);
            break;
        }
    }

    attachedDevices += 1;
}

void Notification::detachDevice(const Device* device)
{
    for (uint8_t i = 0; i < MAX_DEVICES; i++)
    {
        if (devices[i] == device)
        {
            Device* toDetach = devices[i];
            devices[i] = nullptr;

            toDetach->detachChannel(this);
            attachedDevices -= 1;
            return;
        }
    }
}

bool Notification::isAttachedTo(const Device* device) const
{
    for (uint8_t i = 0; i < MAX_DEVICES; i++) {
        if (devices[i] == device)
            return true;
    }

    return false;
}
