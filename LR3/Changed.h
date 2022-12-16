//
// Created by Евгений on 05.12.2022.
//
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <iterator>
#include <memory>
#ifndef PPVISLABA3_MATRIXFORM_H
#define PPVISLABA3_MATRIXFORM_H

template<typename Type>
class AdjacencyMatrix{
private:
    std::vector<std::vector<int>> matrix_content;
    std::vector<Type> vertexes_content;
public:
    class VertexIterator;
    class IncidentEdgeIterator;
    class IncidentVertexIterator;
    AdjacencyMatrix();
    AdjacencyMatrix(std::vector<Type> content, std::vector<std::vector<int>> init_matrix);
    AdjacencyMatrix(const AdjacencyMatrix &obj);
    ~AdjacencyMatrix();
    void clear();
    bool empty();
    bool EdgeCheck(int vertex_1,int vertex_2);
    bool VertexCheck(int vertex);
    class EdgeIterator;
    AdjacencyMatrix& operator=(AdjacencyMatrix obj){
        matrix_content = obj.matrix_content;
        vertexes_content = obj.vertexes_content;
        return *this;
    }
    bool operator==(AdjacencyMatrix &obj){
        if (matrix_content == obj.matrix_content){
            return true;
        } else
            return false;
    }
    bool operator!=(AdjacencyMatrix &obj){
        if (matrix_content == obj.matrix_content){
            return false;
        } else
            return true;
    }
    int size(){
        return matrix_content.size();
    }
    int EdgesNum(){
        int count = 0;
        for(auto & iter1 : matrix_content){
            for(int iter2 : iter1){
                if (iter2!= 0){
                    count++;
                }
            }
        }
        return count;
    }
    int PowerOfVertex(int vertex){
        int count = 0;
        for (int it1 = 0;it1<matrix_content.size();it1++){
            if (matrix_content[vertex][it1]>=1){
                count+=matrix_content[vertex][it1];
            }
            if (matrix_content[it1][vertex]>=1){
                count+=matrix_content[it1][vertex];
            }
        }
        return count;
    }
    int PowerOfEdge(int vertex1,int vertex2){
        return matrix_content[vertex1][vertex2];
    }
    void AddVertex(std::vector<int> newvertex, Type newcontent){
        matrix_content.push_back(newvertex);
        for(int it1 = 0;it1<matrix_content.size();it1++){
            matrix_content[it1].push_back(newvertex[it1]);
        }
        vertexes_content.push_back(newcontent);
    }
    void AddEdge(int vertex1,int vertex2,int num_1to2,int num_2to1){
        matrix_content[vertex1][vertex2] = num_1to2;
        matrix_content[vertex2][vertex1] = num_2to1;
    }
    void DeleteVertex(int vertex){
        matrix_content.erase(matrix_content.begin()+vertex);
        for (auto & it : matrix_content){
            it.erase(it.begin()+vertex);
        }
        vertexes_content.erase(vertexes_content.begin()+vertex);
    }
    void DeleteEdge(int vertex1, int vertex2){
        matrix_content[vertex1][vertex2] = 0;
        matrix_content[vertex2][vertex1] = 0;
    }
    Type GetVertex(int vertex){
        return vertexes_content[vertex];
    }
    VertexIterator begin(){
        return VertexIterator(0, this);
    }
    VertexIterator end(){
        return VertexIterator(vertexes_content.size(), this);
    }
    VertexIterator rbegin(){
        return VertexIterator(vertexes_content.size()-1, this);
    }
    VertexIterator rend(){
        return VertexIterator(-1, this);
    }
    EdgeIterator EdgeBegin(){
        std::pair<int,int> out;
        out.first = 0;
        out.second = 0;
        return EdgeIterator(this, out);
    }
    EdgeIterator EdgeEnd(){
        std::pair<int,int> out;
        out.first = vertexes_content.size()-1;
        out.second = vertexes_content.size()-1;
        return EdgeIterator(this, out);
    }
    EdgeIterator REdgeBegin(){
        std::pair<int,int> out;
        out.first = vertexes_content.size()-1;
        out.second = vertexes_content.size()-1;
        return EdgeIterator(this,out);
    }
    EdgeIterator REdgeEnd(){
        std::pair<int,int> out;
        out.first =0;
        out.second = 0;
        return EdgeIterator(this,out);
    }
    IncidentEdgeIterator IncEdgeBegin(){
        std::pair<int,int> out;
        out.first = 0;
        out.second = 0;
        return IncidentEdgeIterator(this,out);
    }
    IncidentEdgeIterator IncEdgeEnd(){
        std::pair<int,int> out;
        out.first = vertexes_content.size()-1;
        out.second = vertexes_content.size()-1;
        return IncidentEdgeIterator(this,out);
    }
    IncidentEdgeIterator RIncEdgeBegin(){
        std::pair<int,int> out;
        out.first = vertexes_content.size()-1;
        out.second = vertexes_content.size()-1;
        return IncidentEdgeIterator(this,out);
    }
    IncidentEdgeIterator RIncEdgeEnd(){
        std::pair<int,int> out;
        out.first = -1;
        out.second = -1;
        return IncidentEdgeIterator(this,out);
    }
    IncidentVertexIterator IncVertBegin(){
        return IncidentVertexIterator(0,this);
    }
    IncidentVertexIterator IncVertEnd(){
        return IncidentVertexIterator(vertexes_content.size(),this);
    }
    IncidentVertexIterator RIncVertBegin(){
        return IncidentVertexIterator(vertexes_content.size(),this);
    }
    IncidentVertexIterator RIncVertEnd(){
        return IncidentVertexIterator(-1,this);
    }
    class VertexIterator {
    private:
        int current;
        AdjacencyMatrix<Type>*obj;
    public:
        friend class AdjacencyMatrix;
        VertexIterator(){
            current = 0;
            obj = NULL;
        }
        VertexIterator(int curren, AdjacencyMatrix<Type> *ptr){
            current = curren;
            obj = ptr;
        }
        const VertexIterator &operator=(VertexIterator &object);
        VertexIterator& operator++(){
            current++;
            if (current < 0 || current>(*obj).size()){
                throw std::out_of_range("Index out of range");
            }
            return *this;
        }
        VertexIterator operator++(int){
            VertexIterator previous = (*this);
            current++;
            if (current < 0 || current>(*obj).size()){
                throw std::out_of_range("Index out of range");
            }
            return previous;
        }
        VertexIterator& operator--(){
            current--;
            if (current < -1 || current>(*obj).size()){
                throw std::out_of_range("Index out of range");
            }
            return *this;
        }
        VertexIterator operator--(int){
            VertexIterator previous = (*this);
            current--;
            if (current < -1 || current>(*obj).size()){
                throw std::out_of_range("Index out of range");
            }
            return previous;
        }
        bool operator!=(VertexIterator object){
            if (current!=object.current){
                return true;
            }
            else
                return false;
        }
        Type Current(){
            return (*obj).GetVertex(current);
        }
        void DeleteCurrent(){
            (*obj).DeleteVertex(current);
        }
        std::ostream &operator<<(std::ostream &output){
            output<<(*obj).GetVertex(current);
            return output;
        }
    };
    class EdgeIterator{
    private:
        std::pair<int,int> current;
        AdjacencyMatrix<Type>*obj;
    public:
        EdgeIterator(AdjacencyMatrix<Type>*something, std::pair<int,int> cur){
            current.first = cur.first;
            current.second = cur.second;
            obj = something;
        }
        const EdgeIterator &operator=(EdgeIterator &object){
            current.first = object.current.first;
            current.second = object.current.second;
            obj = object.obj;
            return *this;
        }
        EdgeIterator &operator++(){
            if (current.second!=(*obj).size()){
                current.second++;
            }
            else{
                current.second = 0;
                current.first++;
            }
            if (current.second>(*obj).size()  || current.first>(*obj).size()){
                throw std::out_of_range("Index out of range");
            }
            return *this;
        }
        EdgeIterator& operator--(){
            if (current.second>0){
                current.second--;
            }
            else{
                current.second = (*obj).size();
                current.first--;
            }
            if (current.second<0 || current.first<0){
                throw std::out_of_range("Index out of range");
            }
            return *this;
        }
        EdgeIterator operator++(int){
            EdgeIterator old = *this;
            if (current.second!=(*obj).size()-1){
                current.second++;
            }
            else{
                current.second = 0;
                current.first++;
            }
            if (current.second>(*obj).size()  || current.first>(*obj).size()){
                throw std::out_of_range("Index out of range");
            }
            return old;
        }
        EdgeIterator operator--(int){
            EdgeIterator old = *this;
            if (current.second>0){
                current.second--;
            }
            else{
                current.second = (*obj).size()-1;
                current.first--;
            }
            if (current.second<0  || current.first<0){
                throw std::out_of_range("Index out of range");
            }
            return old;
        }
        bool operator!=(EdgeIterator object){
            if (current.first == object.current.first && current.second == object.current.second && object.obj==obj){
                return false;
            }
            else
                return true;
        }
        int Current(){
            return (*obj).PowerOfEdge(current.first,current.second);
        }
        void DeleteCurrent(){
            (*obj).DeleteEdge(current.first,current.second);
        }
        std::ostream &operator<<(std::ostream &output){
            output<<(*obj).PowerOfEdge(current.first,current.second);
            return output;
        }
    };
    class IncidentEdgeIterator{
    private:
        std::pair<int,int> current;
        AdjacencyMatrix<Type>*obj;
    public:
        IncidentEdgeIterator(AdjacencyMatrix<Type>*something, std::pair<int,int> cur){
            current.first = cur.first;
            current.second = cur.second;
            obj =something;
        }
        IncidentEdgeIterator & operator = (IncidentEdgeIterator &object){
            current.first = object.current.first;
            current.second = object.current.second;
            obj = object.obj;
            return *this;
        }
        IncidentEdgeIterator &operator++(){
            for (int i=current.second;i<(*obj).size();i++){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return *this;
                }
            }
            for (int i = 0;i<=current.second;i++){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return *this;
                }
            }
            throw std::out_of_range("Unachivable vertex");

        }
        IncidentEdgeIterator operator++(int){
            IncidentEdgeIterator old = current;
            for (int i=current.second;i<(*obj).size();i++){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return *old;
                }
            }
            for (int i = 0;i<=current.second;i++){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return *old;
                }
            }
            throw std::out_of_range("Unachivable vertex");
        }
        IncidentEdgeIterator &operator--(){
            for (int i=current.second;i>=0;i--){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return *this;
                }
            }
            for (int i = (*obj).size();i>current.second;i++){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return *this;
                }
            }
            throw std::out_of_range("Unachivable vertex");
        }
        IncidentEdgeIterator &operator--(int){
            std::pair<int,int> old = current;
            for (int i=current.second;i>=0;i--){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return old;
                }
            }
            for (int i = (*obj).size();i>current.second;i++){
                if ((*obj).matrix_content[current.first][i]!=0){
                    current.second=i;
                    return old;
                }
            }
            throw std::out_of_range("Unachivable vertex");
        }
        int Current(){
            return (*obj).PowerOfEdge(current.first,current.second);
        }
        void DeleteCurrent(){
            (*obj).DeleteEdge(current.first,current.second);
        }
        bool operator!=(IncidentEdgeIterator object){
            if (current.first == object.current.first && current.second == object.current.second && object.obj==obj){
                return false;
            }
            else
                return true;
        }
        std::ostream &operator<<(std::ostream &output){
            output<<(*obj).PowerOfEdge(current.first,current.second);
            return output;
        }
    };
    class IncidentVertexIterator{
    private:
        int current;
        AdjacencyMatrix<Type>*obj;
    public:
        friend class AdjacencyMatrix;
        IncidentVertexIterator(){
            current = 0;
            obj = NULL;
        }
        IncidentVertexIterator(int curren, AdjacencyMatrix<Type> *ptr){
            current = curren;
            obj = ptr;
        }
        const IncidentVertexIterator & operator=(IncidentVertexIterator &object){
            current = object.current;
            obj = object.obj;
            return *this;
        }
        IncidentVertexIterator& operator++(){
            for(int i = current;i<(*obj).size();i++){
                if ((*obj)[i] != 0){
                    current=i;
                    return *this;
                }
            }
            for(int i = 0;i<current;i++){
                if ((*obj)[i] != 0){
                    current=i;
                    return *this;
                }
            }
            throw std::out_of_range("Unachivable vertex");
        }
        IncidentVertexIterator& operator--(){
            for(int i = current;i>=0;i--){
                if ((*obj)[i] != 0){
                    current=i;
                    return *this;
                }
            }
            for(int i = (*obj).size();i>current;i--){
                if ((*obj)[i] != 0){
                    current=i;
                    return *this;
                }
            }
            throw std::out_of_range("Unachievable vertex");
        }
        IncidentVertexIterator  operator++(int){
            int old = current;
            for(int i = current;i<(*obj).size();i++){
                if ((*obj)[i] != 0){
                    current=i;
                    return old;
                }
            }
            for(int i = 0;i<current;i++){
                if ((*obj)[i] != 0){
                    current=i;
                    return old;
                }
            }
            throw std::out_of_range("Unachivable vertex");
        }
        IncidentVertexIterator& operator--(int){
            int old = current;
            for(int i = current;i>=0;i--){
                if ((*obj)[i] != 0){
                    current=i;
                    return old;
                }
            }
            for(int i = (*obj).size();i>current;i--){
                if ((*obj)[i] != 0){
                    current=i;
                    return old;
                }
            }
            throw std::out_of_range("Unachivable vertex");
        }
        bool operator!=(IncidentVertexIterator object){
            if (current!=object.current){
                return true;
            }
            else
                return false;
        }
        Type Current(){
            return (*obj).GetVertex(current);
        }
        void DeleteCurrent(){
            (*obj).DeleteVertex(current);
        }
        std::ostream &operator<<(std::ostream &output){
            output<<(*obj).GetVertex(current);
            return output;
        }
    };
};
template<typename Type>
const AdjacencyMatrix<Type>::VertexIterator &
AdjacencyMatrix<Type>::VertexIterator::operator=(AdjacencyMatrix::VertexIterator &object) {
    current = object.current;
    obj = object.obj;
    return *this;
}

template<typename Type>
bool AdjacencyMatrix<Type>::VertexCheck(int vertex) {
    if (vertexes_content.size()<(vertex-1)){
        return true;
    }
    else
        return false;
}

template<typename Type>
bool AdjacencyMatrix<Type>::EdgeCheck(int vertex_1, int vertex_2) {
    if (((vertex_1>matrix_content.size()||vertex_2>matrix_content.size() ||(vertex_1>matrix_content.size()&&vertex_2>matrix_content.size()))>matrix_content.size())||((0 > vertex_1 || 0 > vertex_2 ||
                                                                                                                                                                       ((0 > vertex_1) && (0 > vertex_2))))){
        throw std::invalid_argument("Incorrect input");
    }
    if ((matrix_content[vertex_1][vertex_2] >= 1 && matrix_content[vertex_2][vertex_1]>=1)||(matrix_content[vertex_1][vertex_2] == 0 && matrix_content[vertex_2][vertex_1]>= 1)||(matrix_content[vertex_1][vertex_2] >= 1 && matrix_content[vertex_2][vertex_1]==0)){
        return true;
    }
    else
    {
        return false;
    }
}

template<typename Type>
bool AdjacencyMatrix<Type>::empty() {
    if (matrix_content.empty() && vertexes_content.empty()){
        return true;
    }
    else
        return false;
}

template<typename Type>
void AdjacencyMatrix<Type>::clear() {
    matrix_content.clear();
    vertexes_content.clear();
}

template<typename Type>
AdjacencyMatrix<Type>::~AdjacencyMatrix() {
    matrix_content.clear();
    vertexes_content.clear();
}

template<typename Type>
AdjacencyMatrix<Type>::AdjacencyMatrix(const AdjacencyMatrix &obj) {
    obj.matrix_content = matrix_content;
    obj.vertexes_content = vertexes_content;
}

template<typename Type>
AdjacencyMatrix<Type>::AdjacencyMatrix(std::vector<Type> content, std::vector<std::vector<int>> init_matrix) {
    for (int iter=0;iter<content.size();iter++){
        vertexes_content.push_back(content[iter]);
    }
    matrix_content = std::move(init_matrix);
}

template<typename Type>
AdjacencyMatrix<Type>::AdjacencyMatrix() {
    matrix_content.clear();
    vertexes_content.clear();
}

#endif //PPVISLABA3_MATRIXFORM_H
