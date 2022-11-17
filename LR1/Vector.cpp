/*!
    \file
	\brief СРР-файл с описанием всех важнейших операций с классмо Vector
    \author Иван Титлов

    В файле есть код для всех начальных и важнейших операций для отедльно взятого вектора, будь-то задание координат, нахождение длины и проекций
*/

#include "Vector.h"
#include <cmath>
#include <iostream>

namespace std {

    Vector::Vector() {}
    /*!

	\brief Задаются значения координат начала и конца для вектора
    \author Иван Титлов
*/
    Vector::Vector(vector<double> start, vector<double> finish) {
        this->start.setX(start[0]);
        this->start.setY(start[1]);
        this->start.setZ(start[2]);

        this->finish.setX(finish[0]);
        this->finish.setY(finish[1]);
        this->finish.setZ(finish[2]);

        setCoordinatesOfVector();
    }
    /*!

       \brief Задаются значения проекции векторов на координантные прямые
       \author Иван Титлов
   */
    Vector::Vector(vector<double> coordinatesOfVector){
        this->coordinatesOfVector.setX(coordinatesOfVector[0]);

        this->coordinatesOfVector.setY(coordinatesOfVector[1]);


        this->coordinatesOfVector.setZ(coordinatesOfVector[2]);
    }
    /*!

        \brief Извлекаются координты начала вектора
        \author Иван Титлов
    */
    vector<double> Vector::getStart() const {
        vector<double> res {start.getX(),start.getY(), start.getZ()};
        return res;
    }
    /*!

        \brief Задаются координты начала вектора
        \author Иван Титлов
    */
    void Vector::setStart(vector<double> start) {
        this->start.setX(start[0]);
        this->start.setY(start[1]);
        this->start.setZ(start[2]);
    }
    /*!

        \brief Извлекаются координты конца вектора
        \author Иван Титлов
    */
    vector<double> Vector::getFinish() const {
        vector<double> res{finish.getX(), finish.getY(), finish.getZ()};
        return res;
    }
    /*!

        \brief Задаются координты конца вектора
        \author Иван Титлов
    */
    void Vector::setFinish(vector<double> finish) {
        this->finish.setX(finish[0]);
        this->finish.setY(finish[1]);
        this->finish.setZ(finish[2]);
    }
    /*!

        \brief Находится длина вектора
        \author Иван Титлов
    */
    double Vector::getLength()
    {
        return sqrt(pow(start.getX()-finish.getX(), 2) + pow(start.getY()-finish.getY(), 2) + pow(start.getZ()-finish.getZ(), 2));
    }

    Vector::~Vector() {}
    /*!

        \brief Действия для нахождения проекций вектора на координантые прямые
        \author Иван Титлов
    */
    const vector<double> Vector::getCoordinatesOfVector() const {
        Point coordinatesOfVector {finish.getX()-start.getX(), finish.getY()-start.getY(), finish.getZ()-start.getZ()};
        vector<double> res {coordinatesOfVector.getX(), coordinatesOfVector.getY(), coordinatesOfVector.getZ()};
        return res;
    }
    /*!

        \brief Нахожятся значения проекции векторов на координантные прямые без записи в вектор res
        \author Иван Титлов
    */
    const void Vector::setCoordinatesOfVector() {
        coordinatesOfVector={finish.getX()-start.getX(), finish.getY()-start.getY(), finish.getZ()-start.getZ()};
    }
    /*!

        \brief Выводится инофрмация о векторе
        \author Иван Титлов
    */

    string Vector::getInfo() {
        setCoordinatesOfVector();
        return "Start: (" + to_string(start.getX())+", " + to_string(start.getY())+", " + to_string(start.getZ())+")\n"+
                "Finish: (" + to_string(finish.getX())+", "+to_string(finish.getY())+", "+to_string(finish.getZ())+")\n"+
                "Coordinates of Vector: ("+ to_string(coordinatesOfVector.getX())+", "+to_string(coordinatesOfVector.getY())+", "+to_string(coordinatesOfVector.getZ())+" )\n"+
                "Length: "+ to_string(getLength())+"\n";
    }
    /*!

        \brief Подсчитываются значения для каждой из координат
        \author Иван Титлов
    */
    void Vector::setCoordinatesOfVector(vector<double> vectorCoordinates) {
        coordinatesOfVector.setX(vectorCoordinates[0]);
        coordinatesOfVector.setY(vectorCoordinates[1]);
        coordinatesOfVector.setZ(vectorCoordinates[2]);

    }

    /*!

        \brief Действия для операции сложения
        \author Иван Титлов
        \param x, y, z
        \return res Значения суммы
    */
    const Vector Vector::operator+(const Vector &v1) {
        double x = v1.getFinish()[0]-v1.getStart()[0]+finish.getX();
        double y = v1.getFinish()[1]-v1.getStart()[1]+finish.getY();
        double z = v1.getFinish()[2]-v1.getStart()[2]+finish.getZ();
        setStart(v1.getStart());
        setFinish({x, y, z});
        Vector res = *this;
        return res;
    }
    /*!

         \brief Действия для операции вычитания
         \author Иван Титлов
         \param x, y, z
         \return res Значение разности
     */
    const Vector Vector::operator-(const Vector &v1) {
        double x = -(v1.getFinish()[0]-v1.getStart()[0])+finish.getX();
        double y = -(v1.getFinish()[1]-v1.getStart()[1])+finish.getY();
        double z = -(v1.getFinish()[2]-v1.getStart()[2])+finish.getZ();
        Vector res = *this;
        res.setStart(v1.getStart());
        res.setFinish({x, y, z});
        return res;
    }
    /*!

     \brief Действия для операции умножения векторов
     \author Иван Титлов
     \param x, y, z
     \return res Значение произведения
 */
    const Vector Vector::operator*(Vector v1) {
        double x = getCoordinatesOfVector()[1]*v1.getCoordinatesOfVector()[2]-getCoordinatesOfVector()[2]*v1.getCoordinatesOfVector()[1];

        double y = getCoordinatesOfVector()[2]*v1.getCoordinatesOfVector()[0]-getCoordinatesOfVector()[0]*v1.getCoordinatesOfVector()[2];

        double z= getCoordinatesOfVector()[0]*v1.getCoordinatesOfVector()[1]-getCoordinatesOfVector()[1]*v1.getCoordinatesOfVector()[0];

        Vector res = *this;
        res.setCoordinatesOfVector({x,y,z});
        return res;
    }
    /*!

     \brief Действия для операции умножения вектора на число
     \author Иван Титлов
     \param number
     \return res Значение произведения
 */
    const Vector Vector::operator*(const int number) {
        std::vector<double> finish {this->finish.getX(), this->finish.getY(),this->finish.getZ()};
        std::vector<double> start {this->start.getX(), this->start.getY(), this->start.getZ()};

        for(int i=0;i<finish.size(); i++){
            finish[i]*=number;
            start[i]*=number;
        }
        Vector res= *this;
        res.setStart(start);
        res.setFinish(finish);
        return res;
    }
    /*!

         \brief Действия для операции сложения
         \author Иван Титлов
         \param x, y, z
         \return res Значения суммы
     */
    Vector& operator+=(Vector &v1, const Vector &v2) {
        Vector res;
        double x = v1.getFinish()[0]-v1.getStart()[0]+v2.getFinish()[0];
        double y = v1.getFinish()[1]-v1.getStart()[1]+v2.getFinish()[1];
        double z = v1.getFinish()[2]-v1.getStart()[2]+v2.getFinish()[2];
        v1.setStart(v1.getStart());
        v1.setFinish({x, y, z});
        return v1;
    }
    /*!

        \brief Задаются значения проекции векторов на координантные прямые
        \author Иван Титлов
    */
    Vector &operator-=(Vector &v1, const Vector &v2) {
        double x = -(v1.getFinish()[0]-v1.getStart()[0])+v2.getFinish()[0];
        double y = -(v1.getFinish()[1]-v1.getStart()[1])+v2.getFinish()[1];
        double z = -(v1.getFinish()[2]-v1.getStart()[2])+v2.getFinish()[2];
        v1.setStart(v1.getStart());
        v1.setFinish({x, y, z});
        return v1;
    }
    /*!

        \brief Задаются значения проекции векторов на координантные прямые
        \author Иван Титлов
    */
    Vector &operator*=(Vector &v1, const Vector &v2) {
        Vector res;
        double x = v1.getCoordinatesOfVector()[1]*v2.getCoordinatesOfVector()[2]-v1.getCoordinatesOfVector()[2]*v2.getCoordinatesOfVector()[1];

        double y = v1.getCoordinatesOfVector()[2]*v2.getCoordinatesOfVector()[0]-v1.getCoordinatesOfVector()[0]*v2.getCoordinatesOfVector()[2];

        double z = v1.getCoordinatesOfVector()[0]*v2.getCoordinatesOfVector()[1]-v1.getCoordinatesOfVector()[1]*v2.getCoordinatesOfVector()[0];

        v1.setCoordinatesOfVector({x,y,z});
        return v1;
    }
    /*!

        \brief Задаются значения проекции векторов на координантные прямые
        \author Иван Титлов
    */
    Vector &operator*=(Vector &v, const int &number) {
        v.setStart({v.getStart()[0]*number, v.getStart()[1]*number, v.getStart()[2]*number});
        v.setFinish({v.getFinish()[0]*number, v.getFinish()[1]*number, v.getFinish()[2]*number});
        return v;
    }
    /*!

        \brief Задаются значения проекции векторов на координантные прямые
        \author Иван Титлов
    */
    const double Vector::operator^(Vector v1) {
        double chisl = (getCoordinatesOfVector()[0]*v1.getCoordinatesOfVector()[0]+getCoordinatesOfVector()[1]*v1.getCoordinatesOfVector()[1]+getCoordinatesOfVector()[2]*v1.getCoordinatesOfVector()[2]);
        double znam = (getLength()*v1.getLength());
        return chisl/znam;
    }


} // std