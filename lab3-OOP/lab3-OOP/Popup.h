#pragma once

#include <Wt/WJavaScript.h>
#include <Wt/WObject.h>
#include <Wt/WString.h>

class Popup : public Wt::WObject
{
public:
	Popup(const Wt::WString& message = "");

	static std::unique_ptr<Popup> createAlert(const Wt::WString& message = "");

	void setMessage(const Wt::WString& message);
	const Wt::WString& message() const { return message_; }

	Wt::JSlot show;

private:
	Wt::WString message_;
	void setJavaScript();
};

