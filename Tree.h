#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <algorithm>

using namespace std;

class BST
{
private:
    string Country;
    int TotalCase;
    int TotalActive;
    int TotalRecovery;
    int TotalDeath;
    BST *left;
    BST *right;

public:
    BST();
    BST(const BST&);
    BST* Insert(BST*, BST);
    BST* Search(BST*, string);

    void Display(BST*);

    friend class Menu;
    friend void AddCountry(BST);
    friend string retString(BST*);
    friend std::istream& operator>>(std::istream&, BST&);
    friend std::ostream& operator<<( ostream &, BST&);
};

BST::BST()
{
    Country="";
    TotalCase=0;
    TotalActive=0;
    TotalRecovery=0;
    TotalDeath=0;
    left=NULL;
    right=NULL;
}

BST::BST(const BST& node)
{
    Country=node.Country;
    TotalCase=node.TotalCase;
    TotalActive=node.TotalActive;
    TotalRecovery=node.TotalRecovery;
    TotalDeath=node.TotalDeath;
    left=NULL;
    right=NULL;
}

BST* BST::Insert(BST* root,BST node)
{
    if(root==NULL)
    {
        return new BST(node);
    }
    if(node.Country>root->Country)
    {
        root->right=Insert(root->right,node);
    }
    else
    {
        root->left=Insert(root->left,node);
    }
    return root;
}

void BST::Display(BST* node)
{
    cout<<node->Country<<" "<<node->TotalCase<<" "<<node->TotalActive<<" "<<node->TotalRecovery<<" "<<node->TotalDeath<<endl;
}

BST* BST::Search(BST* root,string countryName)
{
    if(root==NULL)
    {
        return NULL;
    }
    else if(countryName<root->Country)
    {
        return Search(root->left,countryName);
    }
    else if(countryName>root->Country)
    {
        return Search(root->right,countryName);
    }
    else
        return root;
}


void AddCountry(BST nodeAdd)
{
    string line;
    ifstream file;
    file.open("CovidData.txt",ios::in);
    while(getline(file,line))//reading line by line
    {
        if(line.find(nodeAdd.Country) != std::string::npos)//if country to add is already present then return
        {
            cout<<"Data is already present for the country"<<endl;
            file.close();
            return;
        }
    }
    file.close();
    ofstream appendfile;
    appendfile.open("CovidData.txt",ios::app);
    appendfile<<'\n'<<nodeAdd;
    appendfile.close();
    cout<<"Country added successfully"<<endl;
}

string retString(BST* node) {//returns all the data as string in combined form for output in sfml
    string str = node->Country + "\nTotal Cases: " + to_string(node->TotalCase) + "\nTotal Active: " + to_string(node->TotalActive);
    str += "\nTotal Recovery: " + to_string(node->TotalRecovery) + "\nTotal Deaths: " + to_string(node->TotalDeath);
    return str;
}

std::istream& operator>>(std::istream& is, BST& tmp)//overloading of stream extraction operator so line by line data of file is stored as the data members of the user defined data type
{
    return is >> tmp.Country >> tmp.TotalCase >> tmp.TotalActive>> tmp.TotalRecovery>> tmp.TotalDeath;//serial data of file is stored in the members of the user defind data type
}

std::ostream& operator<<( ostream &output, BST &tmp) {//overloading to insert the data items of the user defined data type to the file
         output<<tmp.Country<<" "<<tmp.TotalCase<<" "<<tmp.TotalActive<<" "<<tmp.TotalRecovery<<" "<<tmp.TotalDeath;
         return output;
}

//function to update the file creates a temporary file copies the content of original file to temp file and removing the original file and renaming the
//temp file back to original file
void FileUpdate(string Find, BST *found)
{
    ifstream ofile;
    ofstream Temp_file("tempfile.txt",ios::out);
    string line;
    ofile.open("CovidData.txt",ios::in);
    while(getline(ofile,line))//reading line by line
    {
        if(line.find(Find) != std::string::npos)//finding the country to search if found then that line of the original file is replace by new data
        {
            Temp_file<<*found<<endl;
        }
        else//if not found then the original data is transferred to temp file
        {
            Temp_file<<line<<endl;
        }
    }
    ofile.close();
    Temp_file.close();
    if(remove("CovidData.txt"))
    {
        cout<<"removed"<<endl;
    }
    if(rename("tempfile.txt","CovidData.txt"))
    {
        cout<<"renamed"<<endl;
    }
}
