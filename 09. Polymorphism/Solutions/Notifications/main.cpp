#include <iostream>

#include "Device.h"
#include "FileNotification.h"
#include "ConsoleNotification.h"

int main() {
	Notification* n1 = new ConsoleNotification();
	Notification* n2 = new ConsoleNotification();
	Notification* n3 = new FileNotification("notif3.txt");

	Device d1("Samsung Galaxy Note 10.1 2014 Edition");
	Device d2("Nothing Phone 2");
	Device* d3 = new Device("Apple Macbook Pro M4");

	d1.attachChannel(n1);
	d2.attachChannel(n1);

	n1->notifyAll("This is the first notification\n");

	d2.attachChannel(n3);
	d1.attachChannel(n3);
	n3->notifyAll("This should be a file notification!");

	d3->attachChannel(n2);
	d1.attachChannel(n2);

	n2->notifyAll("This is for the console!\n");
	n2->notifyOne("Notifiying the heap device!\n", d3);

	delete d3;

	n2->notifyAll("This should notify only the Samsung Galaxy Note 10.1 2014 Edition\n");

	d3 = new Device("ThinkPad");
	d3->attachChannel(n2);
	d3->attachChannel(n2);
	d3->attachChannel(n2);

	try {
		d3->attachChannel(n2);
	}
	catch (...)
	{
		std::cout << "Should throw!\n";
	}

	delete n2;
	d3->attachChannel(n1);
	n1->notifyOne("Should work!\n", d3);
	d3->detachChannel(n1);
	d3->detachChannel(n3);
	
	n2 = new ConsoleNotification();
	d3->attachChannel(n2);
	n2->notifyOne("Showing notification from n2\n", d3);
	d3->detachChannel(n2);
	n2->notifyAll("Should not show anything!\n");

	delete d3;
	delete n1;
	delete n2;
	delete n3;
}