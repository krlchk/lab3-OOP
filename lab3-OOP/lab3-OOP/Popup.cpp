#include "Popup.h"

Popup::Popup(const Wt::WString& message) : Wt::WObject(), message_(message)
{
	setJavaScript();
}

void Popup::setJavaScript()
{
	show.setJavaScript("function(){ alert('" + message_.narrow() + "'); }");
}

void Popup::setMessage(const Wt::WString& message)
{
	message_ = message;
	setJavaScript();
}

std::unique_ptr<Popup> Popup::createAlert(const Wt::WString& message)
{
	return std::make_unique<Popup>(message);
}
