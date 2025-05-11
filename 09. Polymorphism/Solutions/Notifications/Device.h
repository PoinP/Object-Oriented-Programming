#pragma once

#include "Notification.h"

class Device
{
	static uint64_t nextId;
	const static uint8_t MAX_CHANNELS = 3;

public:
	Device(const SimpleString& model);
	Device(const Device& other);
	~Device();

	Device& operator=(const Device& other) = delete;

	uint64_t getId() const;
	const SimpleString& getModel() const;

	bool canAttachChannel() const;
	void attachChannel(Notification* channel);
	void detachChannel(Notification* channel);

	void sendConsoleMessage(const SimpleString& message);
	void sendFileMessage(const SimpleString& message, const SimpleString& filePath, bool shouldAppend = true);

private:
	bool isAttachedTo(Notification* channel);

private:
	const uint64_t id;
	SimpleString model;

	uint8_t attachedChannels{};				// Initalize the value to 0 (default value)
	Notification* channels[MAX_CHANNELS]{}; // Initalize the array with nullptr values
};