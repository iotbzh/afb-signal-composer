/*
 * Copyright (C) 2015, 2016 "IoT.bzh"
 * Author "Romain Forlot" <romain.forlot@iot.bzh>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#pragma once

#include <map>
#include <string>
#include <vector>
#include <ctl-config.h>

class bindingApp;

class Signal
{
private:
	std::string id_;
	std::vector<std::string> signalSigList_;
	long long int timestamp_;
	double value_;
	std::map<long long int, double> history_; ///< history_ - Hold signal value history in map with <timestamp, value>
	double frequency_;
	std::string unit_;
	CtlActionT* onReceived_;
	std::vector<Signal*> Observers_;

	void attach(Signal *obs);
	int recursionCheck(const std::string& origId);

public:
	Signal(const std::string& id, std::vector<std::string>& sources, const std::string& unit, double frequency, CtlActionT* onReceived);
	explicit operator bool() const;
	bool operator==(const Signal& other) const;
	bool operator==(const std::string& aName) const;

	const std::string id() const;
	json_object* toJSON() const;

	void update(long long int timestamp, double value);
	int onReceivedCB(json_object *queryJ);
	void attachToSourceSignals(bindingApp& bApp);
	void notify();

	//virtual double average() const;
	//virtual double min() const;
	//virtual double max() const;
	//double lastValue() const;
	int recursionCheck();
};