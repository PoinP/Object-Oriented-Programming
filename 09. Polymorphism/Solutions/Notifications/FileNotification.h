#pragma once

#include <fstream>
#include <stdexcept>

#include "Device.h"
#include "Notification.h"

class FileNotification : public Notification
{
public:
	FileNotification(const SimpleString filePath)
		: filePath(filePath)
	{
	}

protected:
	void notify(const SimpleString& message, const Device* device) const override
	{
		std::ofstream fileStream(filePath.getCString(), std::ios::app);

		if (!fileStream)
			throw std::invalid_argument("File could not be opened!");

		fileStream << device->getModel() << "[" << device->getId() << "]: " << message << std::endl;

		if (!fileStream)
			throw std::invalid_argument("An error has occured while writing to file!");
	}

private:
	SimpleString filePath;
};