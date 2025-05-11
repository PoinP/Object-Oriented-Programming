#pragma once

#include "SimpleString.h"

// Няма да имплементирам за:
// - SMS
// - Имейл
// - Push
// Защото са същите както при ConsoleNotification

class Notification
{
	friend class Device;
	static const uint8_t MAX_DEVICES = 5;

public:
	Notification() = default;
	virtual ~Notification() noexcept;

	void notifyAll(const SimpleString& message) const;
	void notifyOne(const SimpleString& message, const Device* device) const;

	bool canAttachDevice() const;
	void attachDevice(Device* device);
	void detachDevice(const Device* device);

	Notification(const Notification&) = delete;
	Notification& operator=(const Notification&) = delete;

protected:
	virtual void notify(const SimpleString& message, const Device* device) const = 0;

private:
	bool isAttachedTo(const Device* device) const;

private:
	uint8_t attachedDevices{};		// Initalize the value with 0 (the default value)
	Device* devices[MAX_DEVICES]{}; // Initalize the array with nullptr values
};