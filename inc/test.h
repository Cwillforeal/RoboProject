#include "main.h"
#include <fstream>

class TestOutput{
private:
	ofstream test_GPIO;

public:
	TestOutput(void);
	void On(void);
	void Off(void);
};