#include "curving.h"

Curving::Curving(vector<double> data){
    m_confirm = false;
    m_originalGrades = data;
    m_curvedGrades = data;
    m_size = data.size();
}

// perform a linear curve on grades
void Curving::linCurve(double curve){
    for(int i = 0; i < m_size; i++)
        m_curvedGrades[i] = m_originalGrades[i] + curve;
    m_typeCurve = false;
}

// perform 10*sqrt(g) curve on grades
void Curving::rootCurve(){
    for(int i = 0; i < m_size; i++)
        m_curvedGrades[i] = 10*sqrt(m_originalGrades[i]);
    m_typeCurve = true;
}

// returns curved array of grades
vector<double> Curving::returnCurve() const {
    return m_curvedGrades;
}

// accept or deny changes to grades
void Curving::acceptChanges(){
    string s;
    if (m_typeCurve) // root curve
        s = "root curve";
    else
        s = "linear curve";

    string c;
    while(1){
        cout << "You performed a " << s << " on the grades\n"
                "Do you want to keep these changes? (Y or N)\n"
                "---------------------------------------------\n";
        cin >> c;
        if(c == "N" || c == "n" || c == "No" || c == "no"){
            m_curvedGrades = m_originalGrades;
            cout << "Your changes have not been saved\n";
            break;
        }
        else if(c == "Y" || c == "y" || c == "Yes" || c == "yes") {
            m_originalGrades = m_curvedGrades;
            cout << "Your changes have been saved\n";
            break;
        }
        else
            cout << "\nPlease enter Y for yes or N for no\n\n";
    }

}

int Curving::getMeanOrig(){
    int total = 0;
    for(int i = 0; i < m_size; i++)
        total += m_originalGrades[i];
    return total/m_size;
}

int Curving::getStdDevOrig(){
    int total = 0;
    int mean = getMeanOrig();
    for(int i = 0; i < m_size; i++)
        total += (mean - m_originalGrades[i]) * (mean - m_originalGrades[i]);
    return sqrt(total/m_size);
}

int Curving::getMeanCur(){
    int total = 0;
    for(int i = 0; i < m_size; i++)
        total += m_curvedGrades[i];
    return total/m_size;
}

int Curving::getStdDevCur(){
    int total = 0;
    int mean = getMeanCur();
    for(int i = 0; i < m_size; i++)
        total += (mean - m_curvedGrades[i]) * (mean - m_curvedGrades[i]);
    return sqrt(total/m_size);
}

// All-encompassing function to give the user options to do what they want with the data
void Curving::performCurve(){
    while(1){
        string s;
        cout << "The mean of the current grades is: " << getMeanOrig() << '\n';
        cout << "The standard deviation of the current grades is: " << getStdDevOrig() << '\n';
        while(1){
            cout << "What would you like to do with the grades?\n1: Perform a linear curve\n"
                    "2: Perform a root curve\n"
                    "3: Break from curving program\n"
                    "------------------------------------------\n";
            cin >> s;
            if(s == "1"){
                cout << "How much would you like to curve the grades?\n";
                double curve_num;
                while(1){
                    string curve_string;
                    cin >> curve_string;
                    istringstream iss;
                    iss.str(curve_string);
                    if(!(iss >> curve_num))
                        cout << "Please enter a valid number: ";
                    else
                        break;
                }
                linCurve(curve_num);
                break;
            }
            else if (s == "2"){
                rootCurve();
                break;
            }
            else if (s == "3"){
                cout << "Ending curving process...\n";
                return;
            }
            else
                cout << "Please enter 1 or 2 to perform a curve on the grades\n";
        }
        cout << "\nThe new mean of the grades is: " << getMeanCur() << '\n';
        cout << "The new standard deviation of the grades is: " << getStdDevCur() << '\n';
        acceptChanges();

        string c;
        cout << "\nWould you like to perform another curve? (Y to curve, anything else to break)\n"
                "-----------------------------------------------------------------------------\n";
        cin >> c;
        if(c != "Y" && c != "y" && c != "Yes" && c != "yes")
            break;
    }
}
