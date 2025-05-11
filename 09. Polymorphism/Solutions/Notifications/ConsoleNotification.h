#pragma once

#include <iostream>

#include "Device.h"
#include "Notification.h"

class ConsoleNotification : public Notification
{
protected:
	void notify(const SimpleString& message, const Device* device) const override
	{
		std::cout << device->getModel() << "[" << device->getId() << "]: " << message;
	}
};