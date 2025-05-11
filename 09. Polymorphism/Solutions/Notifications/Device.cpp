#include <fstream>
#include <iostream>

#include "Device.h"

uint64_t Device::nextId = 1;

Device::Device(const SimpleString& model)
    : id(nextId), model(model)
{
    // If the object is created successfully, increment nextId
    nextId++;
}

Device::Device(const Device& other)
    : id(nextId), model(other.model)
{
    for (uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        Notification* channel = other.channels[i];
        if (channel != nullptr && channel->canAttachDevice())
        {
            channel->attachDevice(this);
            channels[i] = channel;
        }
    }
}

Device::~Device()
{
    for (uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        if (channels[i] != nullptr)
        {
            channels[i]->detachDevice(this);
        }
    }
}

uint64_t Device::getId() const
{
    return id;
}

const SimpleString& Device::getModel() const
{
    return model;
}

void Device::attachChannel(Notification* channel)
{
    if (!canAttachChannel())
        throw std::invalid_argument("Can not attach any more channels to this device!");

    if (isAttachedTo(channel))
        return;

    for (uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        if (channels[i] == nullptr)
        {
            channels[i] = channel;
            channels[i]->attachDevice(this);
            break;
        }
    }

    attachedChannels += 1;
}

void Device::detachChannel(Notification* channel)
{
    for (uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        if (channels[i] == channel)
        {
            Notification* toDetach = channels[i];
            channels[i] = nullptr;

            toDetach->detachDevice(this);
            attachedChannels -= 1;
            return;
        }
    }
}

void Device::sendConsoleMessage(const SimpleString& message)
{
    std::cout << "A message from " << model << ": " << message;
}

void Device::sendFileMessage(const SimpleString& message, const SimpleString& filePath, bool shouldAppend)
{
    int mode = shouldAppend ? std::ios::app : std::ios::trunc;
    std::ofstream outStream(filePath.getCString(), mode);

    if (!outStream)
        throw std::invalid_argument("Couldn't open file for writing!");

    outStream << "A message from " << model << ": " << message;
}

bool Device::isAttachedTo(Notification* channel)
{
    for (uint8_t i = 0; i < MAX_CHANNELS; i++)
    {
        if (channels[i] == channel)
            return true;
    }   

    return false;
}

bool Device::canAttachChannel() const
{
    return attachedChannels < MAX_CHANNELS;
}
