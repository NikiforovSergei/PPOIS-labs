#include <fstream>
using namespace std;
/// <summary>
/// \brief class that implements the machine head
/// </summary>
class Head
{
private:
	/// <summary>
	/// \brief variable containing the current state of the head
	/// </summary>
	char curState;
	/// <summary>
	/// \brief variable containing the position of the symbol on which the head is currently located
	/// </summary>
	int position;
public:
	Head();
	~Head();
	Head(char, int);
	int GetCurPosition();
	void ChangeState(char);
	void Step(char);
	char GetCurState();
	/// <summary>
	/// \brief overloading the streaming output operator
	/// </summary>
	/// <param name="os"></param>
	/// <param name="hd"></param>
	/// <returns></returns>
	friend ostream& operator<<(ostream& os, const Head& hd)
	{
		return os << hd.curState << hd.position;
	}
};