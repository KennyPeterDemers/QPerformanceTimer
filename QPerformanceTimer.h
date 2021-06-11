// Example:
//
//
//	SomeFunction()
//	{
//		... some code...
//
//		int elapsedTime;
//		{	// start of the block we want to monitor
//			// constructor starts the timer - destructor stops timer
//			QPerformanceTimer(elapsedTime);
//
//			... some lengthy process...
//
//		}	// end of block, elapsed time is recorded in elapsedTime
//
//		printf("Time = %d microseconds", elapsedTime);
//	}
//
#pragma once

class QPerformanceTimer
{
public:
	QPerformanceTimer(int& MicroSeconds) : m_Output(MicroSeconds) {
		::QueryPerformanceCounter(&m_Start);
	}

	~QPerformanceTimer(void) {
		if (m_Start.QuadPart == 0) {
			m_Output = -1;		// system doesn't support performance counter
			return;
		}
		LARGE_INTEGER stop;
		LARGE_INTEGER freq;
		::QueryPerformanceCounter(&stop);
		::QueryPerformanceFrequency(&freq);

		// get the ellapsed time in ticks
		stop.QuadPart -= m_Start.QuadPart;
		// convert it to micro seconds
		stop.QuadPart *= 1000000;
		stop.QuadPart /= freq.QuadPart;

		if (stop.HighPart != 0) {
			m_Output = -1;
		} else {
			m_Output = stop.LowPart;
		}
	}
protected:
	LARGE_INTEGER m_Start;
	int& m_Output;
};
