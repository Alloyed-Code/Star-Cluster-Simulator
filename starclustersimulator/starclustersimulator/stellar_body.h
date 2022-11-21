#pragma once

class stellar_body {
protected:
	double mass;
	double luminosity;
	int age;
	int current_age;
public:
	virtual void age_body() = 0;
};