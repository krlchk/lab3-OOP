#include <iostream>
#include <locale.h>

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "Popup.h"
#include "Fraction.h"

std::string numberEditStyle = "width: 50px; margin: 0px 10px;";

class FractionApplication : public Wt::WApplication
{
public:
	FractionApplication(const Wt::WEnvironment&);

private:
	Wt::WLineEdit* num1Edit_;
	Wt::WLineEdit* den1Edit_;
	Wt::WLineEdit* num2Edit_;
	Wt::WLineEdit* den2Edit_;
	Wt::WText* result_;

	std::unique_ptr<Popup> alert_;

	void action(char);
};

FractionApplication::FractionApplication(const Wt::WEnvironment& env)
	: WApplication(env)
{
	setTitle("Actions with fractions");

	root()->addWidget(std::make_unique<Wt::WText>("The first fraction: "));

	num1Edit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	num1Edit_->setAttributeValue("type", "number");
	num1Edit_->setAttributeValue("style", numberEditStyle);
	num1Edit_->setFocus();

	root()->addWidget(std::make_unique<Wt::WText>(" / "));

	den1Edit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	den1Edit_->setAttributeValue("type", "number");
	den1Edit_->setAttributeValue("style", numberEditStyle);

	root()->addWidget(std::make_unique<Wt::WBreak>());

	root()->addWidget(std::make_unique<Wt::WText>("The second fraction: "));

	num2Edit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	num2Edit_->setAttributeValue("type", "number");
	num2Edit_->setAttributeValue("style", numberEditStyle);

	root()->addWidget(std::make_unique<Wt::WText>(" / "));

	den2Edit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
	den2Edit_->setAttributeValue("type", "number");
	den2Edit_->setAttributeValue("style", numberEditStyle);

	root()->addWidget(std::make_unique<Wt::WBreak>());

	auto buttonAddition = root()->addWidget(std::make_unique<Wt::WPushButton>("+"));
	buttonAddition->setMargin(5, Wt::Side::Left);
	buttonAddition->clicked().connect(this, [&]() { FractionApplication::action('+'); });

	auto buttonSubstruction = root()->addWidget(std::make_unique<Wt::WPushButton>("-"));
	buttonSubstruction->setMargin(5, Wt::Side::Left);
	buttonSubstruction->clicked().connect(this, [&]() { FractionApplication::action('-'); });

	auto buttonMultiplication = root()->addWidget(std::make_unique<Wt::WPushButton>("*"));
	buttonMultiplication->setMargin(5, Wt::Side::Left);
	buttonMultiplication->clicked().connect(this, [&]() { FractionApplication::action('*'); });

	auto buttonDivision = root()->addWidget(std::make_unique<Wt::WPushButton>("/"));
	buttonDivision->setMargin(5, Wt::Side::Left);
	buttonDivision->clicked().connect(this, [&]() { FractionApplication::action('/'); });

	root()->addWidget(std::make_unique<Wt::WBreak>());

	result_ = root()->addWidget(std::make_unique<Wt::WText>());

	alert_ = Popup::createAlert();
}

void FractionApplication::action(char operation)
{
	double n1 = 0, d1 = 0, n2 = 0, d2 = 0;
	try
	{
		n1 = std::stod(num1Edit_->text().toUTF8());
		d1 = std::stod(den1Edit_->text().toUTF8());
		n2 = std::stod(num2Edit_->text().toUTF8());
		d2 = std::stod(den2Edit_->text().toUTF8());
		Fraction f1 = Fraction(n1, d1);
		Fraction f2 = Fraction(n2, d2);
		switch (operation)
		{
		case '+':
			result_->setText("Result " + (f1 + f2).toString());
			break;
		case '-':
			result_->setText("Result " + (f1 - f2).toString());
			break;
		case '*':
			result_->setText("Result " + (f1 * f2).toString());
			break;
		case '/':
			result_->setText("Result " + (f1 / f2).toString());
			break;
		default:
			break;
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::string msg = "The numerator and denominator of both fractions must be whole numbers!";
		std::cerr << msg << std::endl;
		alert_->setMessage(msg);
		alert_->show.exec();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		alert_->setMessage(e.what());
		alert_->show.exec();
	}
}

int main()
{
	int argc = 8;
	char* argv[] = { (char*)".\\lab3-OOP.exe", (char*)"--docroot", (char*)".", (char*)"--http-port", (char*)"8080",(char*)"--http-address", (char*)"0.0.0.0", (char*)"%*" };
	return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
		return std::make_unique<FractionApplication>(env);
		});
}
