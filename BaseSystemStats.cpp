#include <iostream>
#include <cmath>
#include <string>
#include <queue> 
#include <list>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

//Δήλωση γεννήτριας παραγωγής τυχαίων αριθμών
mt19937 mt(high_resolution_clock::now().time_since_epoch().count());

//Δήλωση struct και συνάρτησης που μετατρέπει τον αριθμό σε δεκαδικό ώστε η μία να "βλέπει" την άλλη
struct number;
size_t to_Decimal(number &n);

//Αναπαράσταση αριθμού
struct number
{
    int system; //Δήλωση συστήματος
    string num; //Δήλωση αριθμού ως αλφαριθμητικό

    //Υπερφόρτωση του τελεστή < για την ταξινόμηση κατά αύξουσα σειρά συμφωνα με το δεκαδικό σύστημα
    bool operator<(number &n)
    {
        return to_Decimal(*this) < to_Decimal(n);
    }
};

//Getter για αλλαγή αλφαριθμητικών σε αριθμούς
int get_Number_By_Character(char x)
{
    char ch[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int n[6] = {10, 11, 12, 13, 14, 15};
    int i;
    for (i = 0; i < 6; i++)
    {
        if (ch[i] == x)
        {
            break;
        }
    }
    if (i > 5)
    {
        return -1;
    }
    return n[i];
}

//Getter για αλλαγή αριθμών σε αλφαριθμητικά
char get_Character_By_Number(int num)
{
    char ch[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int n[6] = {10, 11, 12, 13, 14, 15};
    int i;
    for (i = 0; i < 6; i++)
    {
        if (n[i] == num)
        {
            break;
        }
    }
    if (i > 5)
    {
        return ' ';
    }
    return ch[i];
}

//Μετατροπή των αριθμών από οποιοδήποτε σύστημα στο δεκαδικό
size_t to_Decimal(number &n)
{
    size_t to_dec = 0;
    queue<char> digits; // Δήλωση ουράς

    // Εισαγωγή ψηφίων στην ουρά
    for (char &x : n.num)
    {
        digits.push(x);
    }

    int mul = pow(n.system, (n.num.length() - 1)); // Δύναμη του συστήματος ^ πόσο είναι το μήκος του αριθμού κάθε φορά

    while (!digits.empty()) //Όσο η ουρά δεν είναι άδεια
    {
        if (digits.front() >= 'A' && digits.front() <= 'F') //Αν υπάρχει χαρακτήρας
        {
            to_dec += mul * get_Number_By_Character(digits.front()); //τον μετατρέπει στον αντίστοιχο αριθμό και προσθέτει το γινόμενο του με την δύναμη στην μεταβλητη to_dec
        }
        else // αλλιώς
        {
            int queue_number = digits.front() - '0'; //μετατρέπει το ψηφίου σε αριθμό και
            to_dec += mul * queue_number;            // προσθέτει στο to_dec το γινόμενο της δύνμης με τον αριθμό
        }
        digits.pop();    //Αφαιρεί ένα στοιχείο από την ουρά
        mul /= n.system; //Κατεβαίνει κατά μία δύναμη
    }
    return to_dec;
}

//Παραγωγή τυχαίων αριθμών
number random_number()
{
    uniform_int_distribution<int> system(2, 16);
    int available_system = system(mt);
    int arithmetic_digit;
    number n;
    n.system = available_system;
    n.num = "";
    uniform_int_distribution<int> num(0, available_system - 1);

    //Παραγωγή αριθμού 8 ψηφίων
    for (int i = 0; i < 8; i++)
    {
        string digit = "";
        arithmetic_digit = num(mt);
        if (arithmetic_digit >= 10)
            digit += get_Character_By_Number(arithmetic_digit);
        else
            digit += to_string(arithmetic_digit);
        n.num += digit;
    }
    return n;
}

//Εμφάνιση λίστας αριθμών
void show_numbers(list<number> &n)
{
    cout << "-------------- Arithmoi --------------" << endl;
    int i = 1;
    for (auto &x : n)
    {
        cout << "\t" << i << ". Systhma: " << x.system << "\tArithmos: " << x.num << endl;
        i++;
    }
    cout << endl;
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now(); //Καταγραφή ώρας έναρξης του κώδικα

    long total_numbers;
    list<number> nums;
    size_t dec1;
    size_t dec2;
    size_t x1 = 0;
    double x2 = 0;
    double base;
    double m_o;
    double d;

    cout << "Dwse ena plithos arithmwn: ";
    cin >> total_numbers;
    cout << endl;

    for (int i = 0; i < total_numbers; i++)
    {
        nums.push_back(random_number());
        show_numbers(nums);
    }
    nums.sort();
    
    //Εύρεση μέσου όρου αριθμών
    for (auto &n : nums)
    {
        dec1 = to_Decimal(n);
        x1 += dec1;
    }
    m_o = (double)x1 / total_numbers;
    cout << "-------------- Mesos Oros Synolou Arithmwn --------------" << endl << endl << "\tO Mesos Oros twn arithmwn einai: " << m_o << endl << endl;

    //Tυπική απόκληση s=sqrt(Σ pow(xi-m_ox,2)/n)
    for (auto &n : nums)
    {
        dec2 = to_Decimal(n);
        base = (double)dec2 - m_o;
        x2 += pow(base, 2); //Σ pow(xi-m_ox,2)
    }
    x2/=total_numbers;
    d = sqrt(x2);
    cout << "-------------- Diaspora Synolou Arithmwn --------------" << endl << endl << "\tH diaspora toy synolou twn arithmwn mesw tou typou ths typikhs apoklishs einai: " << d << endl << endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now(); //Καταγραφή ώρας λήξης του κώδικα
    auto duration = duration_cast<microseconds>(t2 - t1).count();        //Διαφορά ώρας λήξης - ώρας έναρξης του κώδικα ώστε να βρούμε την ώρα που χρειάστηκε για να εκτελεστεί ο κώδικας σε  microseconds
    cout << "\tTime elapsed: " << duration << " microseconds or " << duration / 1000000.0 << " seconds" << endl;
}
