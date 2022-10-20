#include "pch.h"
#include "Matrixx.h"

    vector<vector<int>> Table;

       /// Command for entering matrix from the file.
       /// @param file This represents name of the file with a matrix.
       /// @returns Nothing important.
    void MMM::Matrixx::enter(string file)
    {
        if (Table.size() != NULL)
        {
            vector<vector<int>> Null_Vector;
            Table = Null_Vector;
        }

        ifstream Table_Text(file);
        string Temp_Line;
        string Temp_Char;
        while (getline(Table_Text, Temp_Line))
        {
            stringstream S_TableText(Temp_Line);
            vector<int> Temp_Vector;

            while (getline(S_TableText, Temp_Char, ' '))
                Temp_Vector.push_back(stoi(Temp_Char));
            Table.push_back(Temp_Vector);
        }
        Table_Text.close();
    }
   
   ///Command for printing the matrix on the screen.
        /// @param No parameters.
        /// @returns Nothing important.
    void MMM::Matrixx::print()
    {
        cout << endl;
        for (int i = 0; i < Table.size(); i++)
        {
            for (int j = 0; j < Table[i].size(); j++)
                cout << Table[i][j] << " ";
            cout << endl;
        }
    }

    ///Command for incrementing matrix.
       /// @param No parameters.
       /// @returns Nothing important.
    void MMM::Matrixx::operator ++()
    {
        for (int i = 0; i < Table.size(); i++)
            ++Table[i][i];
    }

    ///Command for post - incrementing matrix.
        /// @param No parameters.
        /// @returns Nothing important.
    void MMM::Matrixx::operator ++(int)
    {
        for (int i = 0; i < Table.size(); i++)
            Table[i][i]++;
    }

    ///Command for decrementing matrix..
    /// @param No parameters.
    /// @returns Nothing important.
    void MMM::Matrixx::operator --()
    {
        for (int i = 0; i < Table.size(); i++)
            --Table[i][i];
    }

    /// Command for post-decrementing matrix.
    /// @param No parameters.
    /// @returns Nothing important.
    void MMM::Matrixx::operator --(int)
    {
        for (int i = 0; i < Table.size(); i++)
            Table[i][i]--;
    }

    /// Command for adding to the matrix the <radok> column, if a = 1, or the <radok> row.
    /// @param a represents the key for adding a coloumn.
    /// @param b represents the key for adding a row.
    /// @param radok represents the added line.
    /// @returns Nothing important.
    void MMM::Matrixx::add(bool a, bool b, vector<int> radok)
    {
        vector<int> Temp_Vector;
        if (a != 0)
        {
            if (b != 0)
                return;

            for (int i = 0; i < Table[0].size(); i++)
                Temp_Vector.push_back(0);

            while (radok.size() > Table.size())
                Table.push_back(Temp_Vector);

            while (radok.size() < Table.size())
                radok.push_back(0);

            for (int i = 0; i < Table.size(); i++)
                Table[i].push_back(radok[i]);
        }
        else
        {
            while (radok.size() > Table[0].size())
                for (int i = 0; i < Table.size(); i++)
                    Table[i].push_back(0);

            Table.push_back(radok);
        }
    }

    /// Command for deleting the last column, if a = 1, or the row from matrix.
    /// @param a represents the key for deleting a coloumn.
    /// @param b represents the key for deleting a row.
    /// @returns Nothing important.
    void MMM::Matrixx::del(bool a, bool b)
    {
        vector<int> Temp_Vector;
        if (a != 0)
        {
            if (b != 0)
                return;

            for (int i = 0; i < Table.size(); i++)
                Table[i].pop_back();
        }
        else
        {
            Table.pop_back();
        }
    }

    ///Command for extracting submatrix from the matrix.
       ///Which consists of original matrix's elements starting with element with coordinates x1 and y1,
        ///ending with x2, y2, and all elements between them.
        /// @param x1 is a row coordinate of the left extracted matrix's corner.
        /// @param y1 is a column coordinate of the left extracted matrix's corner.
        /// @param x2 is a row coordinate of the right extracted matrix's corner.
        /// @param y2 is a column coordinate of the right extracted matrix's corner.
         /// @returns Nothing important.
    void MMM::Matrixx::extract(int x1, int y1, int x2, int y2)
    {
        vector<vector<int>> Temp_Vector;
        vector<int> NullVector;

        for (int j = x1; j <= x2; j++)
            NullVector.push_back(0);

        for (int i = y1; i <= y2; i++)
            Temp_Vector.push_back(NullVector);

        for (int i = y1, q = 0; i <= y2; i++, q++)
            for (int j = x1, k = 0; j <= x2; j++, k++)
                Temp_Vector[q][k] = Table[i][j];

        Table = Temp_Vector;
    }

    ///Command for defining the type of matrix.
       /// @param No parameters.
       /// @returns string that consists of words defining the matrix's type.
    string MMM::Matrixx::type()
    {
        string Type = "The Matrix is ";
        int counter = 0, Square_Index = 0, k = 0, Diagonal_Index = 0, Identity_Index = 0;
        {
            if (Table.size() == Table[0].size())
            {
                Type += "Square "; counter++; Square_Index++;
            }
        }
        {
            if (Square_Index != 0)
            {
                k = 0;
                for (int i = 0; i < Table.size(); i++)
                    for (int j = 0; j < Table[0].size(); j++)
                        if ((i != j) && (Table[i][j] != 0))
                        {
                            k = 1;  break;
                        }
                if (k == 0)
                {
                    Type += "Diagonal "; counter++; Diagonal_Index++;
                }
            }
        }
        {
            if (Diagonal_Index != 0)
            {
                k = 0;
                for (int i = 0; i < Table.size(); i++)
                    for (int j = 0; j < Table[0].size(); j++)
                        if (Table[i][j] != 0)
                        {
                            k = 1;  break;
                        }
                if (k == 0)
                {
                    Type += "Zero "; counter++;
                }
            }
        }
        {
            if (Diagonal_Index != 0)
            {
                k = 0;
                for (int i = 0; i < Table.size(); i++)
                    for (int j = 0; j < Table[0].size(); j++)
                    {
                        if ((i == j) && (Table[i][j] != 1))
                        {
                            k = 1;  break;
                        }
                        if ((i != j) && (Table[i][j] != 0))
                        {
                            k = 1;  break;
                        }
                    }
                if (k == 0)
                {
                    Type += "Identity "; counter++; Identity_Index++;
                }
            }
        }
        {
            if (Square_Index != 0)
            {
                k = 0;
                for (int i = 0; i < Table.size(); i++)
                    for (int j = i; j < Table[0].size(); j++)
                        if (Table[i][j] != Table[j][i])
                        {
                            k = 1; break;
                        }
                if (k == 0)
                {
                    Type += "Symmetric "; counter++;
                }
            }
        }
        {
            if ((Square_Index != 0) && (Identity_Index == 0))
            {
                k = 0;
                for (int i = 0; i < Table.size(); i++)
                    for (int j = 0; j < i; j++)
                        if (Table[i][j] != 0)
                        {
                            k = 1;  break;
                        }
                if (k == 0)
                {
                    Type += "Upper triangular "; counter++;
                }
            }
        }
        {
            if ((Square_Index != 0) && (Identity_Index == 0))
            {
                k = 0;
                for (int i = 0; i < Table.size(); i++)
                    for (int j = i + 1; j < Table.size(); j++)
                        if (Table[i][j] != 0)
                        {
                            k = 1;  break;
                        }
                if (k == 0)
                {
                    Type += "Lower triangular "; counter++;
                }
            }
        }

        return Type;
    }

    /// Command for transponating matrix.
    /// @param No parameters.
    /// @returns Nothing important.
    void MMM::Matrixx::trans()
    {
        vector<vector<int>> Temp_Vector;
        vector<int> NullVector;

        int k = 0;

        if (Table.size() < Table[0].size())
        {
            for (int j = 0; j < Table[0].size(); j++)
                NullVector.push_back(0);

            while (Table.size()!=Table[0].size())
                Table.push_back(NullVector);

            k = 1;
        }

        if (Table.size() > Table[0].size())
        {
            while (Table.size() > Table[0].size())
                for (int i = 0; i < Table.size(); i++)
                Table[i].push_back(0);

            k = 2;
        }

        Temp_Vector = Table;

        for (int i = 0; i < Table.size(); i++)
            for (int j = 0; j < Table[0].size(); j++)
                Temp_Vector[i][j] = Table[j][i];

        if (k == 1)
        {               
            for (int i = 0; i < Table.size(); i++)
                for (int j = 0; j < Table[0].size() - 1; j++)
                    Temp_Vector[i].pop_back();
        }
        if (k == 2)
        {
            Temp_Vector.pop_back();
        }

        Table = Temp_Vector;
    }

    vector<vector<int>> MMM::Matrixx::vector_return()
    {
        vector<vector<int>> Temp_Vector;
        vector<int> NullVector;

        for (int j = 0; j < Table[0].size(); j++)
            NullVector.push_back(0);

        for (int i = 0; i < Table.size(); i++)
            Temp_Vector.push_back(NullVector);

        for (int i = 0; i < Table.size(); i++)
            for (int j = 0; j < Table[0].size(); j++)
                Temp_Vector[i][j] = Table[i][j];

        return Temp_Vector;
    }


    void MMM::Matrixx::operator +(Matrixx m2)
     {
         vector<vector<int>> Table2;
         vector<int> NullVector;
         Table2 = m2.vector_return();

         // Трэба перанесьці нфармацыю з m2 у Table2

         if (Table.size() < Table2.size())
         {
             for (int j = 0; j < Table[0].size(); j++)
                 NullVector.push_back(0);

             while (Table.size() < Table2.size())
                 Table.push_back(NullVector);
         }
         else
         {
             if (Table.size() > Table2.size())
             {
                 for (int j = 0; j < Table2[0].size(); j++)
                     NullVector.push_back(0);

                 while (Table.size() > Table2.size())
                     Table2.push_back(NullVector);
             }
         }

         if (Table[0].size() < Table2[0].size())
         {
             while (Table[Table.size() - 1].size() < Table2[0].size())
                 for (int i = 0; i < Table.size(); i++)
                     Table[i].push_back(0);
         }
         else
         {
             if (Table[0].size() > Table2[0].size())
             {
                 while (Table2[Table2.size() - 1].size() < Table[0].size())
                     for (int i = 0; i < Table2.size(); i++)
                         Table2[i].push_back(0);
             }
         }

         for (int i = 0; i < Table.size(); i++)
             for (int j = 0; j < Table[0].size(); j++)
                 Table[i][j] += Table2[i][j];

         
     }
