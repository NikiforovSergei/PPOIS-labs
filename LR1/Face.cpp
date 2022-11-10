#include "Face.h"
#include <vector>

Face::Face()
{
	index = 0;
	naighbor = {	{"topFace", 0},
					{"bottomFace", 0},
					{"leftFace", 0},
					{"rightFace", 0}
	};

}

Face::Face(int valueIndex, vector<vector<int>> &valueVertical, vector<vector<int>> &valueHorizontal)
{
	index = valueIndex;
	if (index == 0)
	{
		naighbor = { {"topFace", 1},
					 {"bottomFace", 3},
					 {"leftFace", 4},
					 {"rightFace", 5}
		};
	}
	if (index == 1)
	{
		naighbor = { {"topFace", 2},
					 {"bottomFace", 0},
					 {"leftFace", 4},
					 {"rightFace", 5}
		};
	}
	if (index == 2)
	{
		naighbor = { {"topFace", 3},
					 {"bottomFace", 1},
					 {"leftFace", 5},
					 {"rightFace", 4}
		};
	}
	if (index == 3)
	{
		naighbor = { {"topFace", 0},
					 {"bottomFace", 2},
					 {"leftFace", 4},
					 {"rightFace", 5}
		};
	}
	if (index == 4)
	{
		naighbor = { {"topFace", 1},
					 {"bottomFace", 3},
					 {"leftFace", 2},
					 {"rightFace", 0}
		};
	}
	if (index == 5)
	{
		naighbor = { {"topFace", 1},
					 {"bottomFace", 3},
					 {"leftFace", 0},
					 {"rightFace", 2}
		};
	}

	vertical = valueVertical;
	horizontal = valueHorizontal;

}
