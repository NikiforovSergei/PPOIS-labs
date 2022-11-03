#include "TimeManager.h"

InProgramTime::InProgramTime()
{
	hours = 12;
	minutes = 30;
}
void InProgramTime::ShowTime()
{
	if (minutes < 10)
	{
		std::cout << "Local time: " << hours << " : " << "0" << minutes << std::endl;
	}
	else
	{
		std::cout << "Local time: " << hours << " : " << minutes << std::endl;
	}
}

InProgramTime InProgramTime::operator+(float tickTime)
{
	int tickTimeFullHours = int(tickTime);
	int tickTimeInMinutes = (int)((tickTime - tickTimeFullHours) * 60);
	hours += tickTimeFullHours;
	if (minutes + tickTimeInMinutes >= 60)
	{
		minutes = (minutes + tickTimeInMinutes) % 60;
		hours++;
	}
	else
	{
		minutes += tickTimeInMinutes;
	}
	hours = (hours >= 24) ? hours - 24 : hours;
	return *this;
}

void TrainInTimeManipulator::ChangingConditionsOfTheTrain(Train* train)
{
	if (train->GetStatus() == InTheWay)
	{
		if (train->GetTimeToNextStation() > tickTime)
		{
			train->ChangeTimeToTheNextStation(tickTime);
		}
		else
		{
			train->numberOfCurrentStation++;
			Station* nextStation = (train->GetRoute()).GetStationsList()[train->numberOfCurrentStation];
			train->SetStatus(OnTheStation);
			train->SetLocation(nextStation);
			nextStation->DoTask(train);

		}
	}
	else if (train->GetStatus() == OnTheStation)
	{
		if (train->GetLocation() == (train->GetRoute()).GetTerminus())
		{
			train->SetStatus(Free);
			/*train->SetLocation(NULL);
			train->SetRoute(NULL);*/
			(train->GetLocation())->FullUnloading(train);
			train->numberOfCurrentStation = 0;
		}
		else if ((train->GetLocation())->GetTask() == "Temporary Stopping")
		{
			if (train->GetLocation()->SpendTimeOnStation())
			{
				train->SetStatus(InTheWay);
				train->SetTimeToTheNextStation(train->numberOfCurrentStation);
			}
		}
		else
		{
			train->SetStatus(InTheWay);
			train->SetTimeToTheNextStation(train->numberOfCurrentStation);
		}

	}
}