///\file
///INPUT_ENCODING ANSI CP1251
/**
*    \brief ������������ ���� � ��������� ���� "����� ������"
*    \author Admin (�������� �.�.)
*    \version 1.0
*    \date 11.09.2022
*    \warning ������� � ������ ����� �������� 1.5.3. ������������ ������ 1.1 �� �������� �������� �����
*
*    ���������� ���� "����� ������" �� ����� �++. ������ ���� �������� � ���� ����������� �������� �������, ������ � �.�.
*/
#pragma once
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
class Cube;
std::istream& operator>>(std::istream& is, Cube& cube);
std::ostream& operator>>(std::ostream& os, const Cube& cube);
class Cube
{
private:
	/**
	*   \brief Edge ������ ����
	*   \author Admin (�������� �.�.)
	*   \date 04.09.2022.
	*   \warning ������ Edge ������ � ����� Cube. ����������� ������� private.
	*
	*   
	*/
	class Edge 
	{
	private:
		/**
	*   \brief cells ������ �����
	*   \author Admin (�������� �.�.)
	*   \date 04.09.2022.
	*   \warning ������ cells ������ � ����� Edge. ����������� ������� private.
	*
	*	������ ����� ������
	*/
		std::vector<char> cells;
	public:
		/**
	*   ����������� �������� �����
	*	\param data ����� ������, ������� ������ ����� ������ ����� ��������
	*/
		Edge(std::vector<char> data);
		/**
	*   ����������� ����������� �����
	*	\param other ������ �� ����� �� ������� �������� 
	*/
		Edge(const Edge& other);
		/**
	*   �������� ��������� 
	* \param other ������ �� ����� � ������� ����������
	*/
		bool operator ==(const Edge& other); 
		/**   �������� ��������� 
	* \param other ������ �� ����� � ������� ����������
	*/
		bool operator !=(const Edge& other); 
		/**
	*   ������ 
	*	���� ������ ������ ������
	*/
		std::vector<char> getCells(); 
		std::vector<char> getCells() const;
		/**
	*   ������
	*	\param ����� ������ ������� ����
	*/
		char getOneCell(int counter); 
		/**
	*   ������ ���� ������
	*	\param ������ ������ ������
	*/
		void setCells(const std::vector<char> & data);
		/**
	*   ������ ������� ������
	*	\param ������ ������ ������
	*/
		void setTopRove(const std::vector<char>& data); 
		/**
	*   ������ ������ ������
	*	\param ������ ������ ������
	*/
		void setBotRove(const std::vector<char>& data); 
		/**
	*   ������ ������ �������
	*	\param ������ ������ ������
	*/
		void setLeftColumn(const std::vector<char>& data); 
		/**
	*   ������ ������� �������
	*/
		void setRightColumn(const std::vector<char>& data); 
		/**
	*   ������ ������� ������
	*/
		std::vector<char> getTopRove();
		/**
	*   ������ ������ ������
	*/
		std::vector<char> getBotRove(); 
		/**
	*   ������ ������ �������
	*/
		std::vector<char> getLeftColumn(); 
		/**
	*   ������ ������� �������
	*/
		std::vector<char> getRightColumn(); 
		/**
	*   ������������ �� ������� ������� ������
	*/
		void rotateClocwise(); 
	};
	/**
	*   \brief edges �����
	*   \author Admin (�������� �.�.)
	*   \date 04.09.2022.
	*   \warning ������ edges ������ � ����� Cube. ����������� ������� private.
	*
	*	������ ��������� ������
	* 0- front, 1- back, 2- left, 3- right, 4- top, 5- bot.
	*/
	std::vector<Edge> edges;
	/**
	*   �������� ������ �����
	* \param other ������ �� ����� � ������� ����������
	*/
	friend std::istream& operator>>(std::istream& is, Cube& cube);
	/**
	*   �������� ������ ������
	* \param other ������ �� ����� � ������� ����������
	*/
	friend std::ostream& operator>>(std::ostream& os, const Cube& cube);
public:
	/**
	*   ����������� �������� ����
	*/
	Cube(); 
	/**
	*   ����������� ����������� �����
	*	\param other ������ �� ��� �� �������� ��������
	*/
	Cube(const Cube& other); 
	/**
	*   �������� ������������
	* \param other ������ �� ��� �������� �������� �����������
	*/
	void operator = (const Cube& other); 
	/**
	*   �������� ���������
	* \param other ������ �� ��� � ������� ����������
	*/
	bool operator ==(const Cube& other); 
	/**
	*   �������� ���������
	* \param other ������ �� ��� � ������� ����������
	*/
	bool operator !=(const Cube& other); 
	/**
	*   ������
	*	���� ������ ������ ���� ������
	*/
	std::vector<char> getCube(); 
	/**
	*   ������
	*	���� ������ ������ ���� ������
	*/
	std::vector<char> getCube() const; 
	/**
	*   ��������� ��� �� ������� ������� ������
	*	
	*/
	void loadCube(std::vector<char> data);
	/**
	*   ������������ ����������� ����� �� ������� �������
	*	
	*/
	void rotateClockwiseFrontEdge();
	/**
	*   ������������ ������ ����� �� ������� �������
	*
	*/
	void rotateClockwiseBackEdge();
	/**
	*   ������������ ����� ����� �� ������� �������
	*
	*/
	void rotateClockwiseLeftEdge();
	/**
	*   ������������ ������ ����� �� ������� �������
	*
	*/
	void rotateClockwiseRightEdge();
	/**
	*   ������������ ������� ����� �� ������� �������
	*
	*/
	void rotateClockwiseTopEdge();
	/**
	*   ������������ ������ ����� �� ������� �������
	*
	*/
	void rotateClockwiseBotEdge();
	/**
	*   ��������� ����������� ����
	*
	*/
	bool checkForWin(); 
};

