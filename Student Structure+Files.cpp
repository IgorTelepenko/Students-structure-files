#include <iostream>
#include<cstring>
#include<fstream>
using namespace std;

ifstream file;
ofstream fout;

struct STUDENT
{
    char surname[20];
    char initial_name, initial_patronymic;
    int group_numb;
    int grades[5];

    void create(char surn[], char name_init, char patr_init, int group, int grade[])
    {

        for (int i = 0;i < strlen(surn);i++)
        {
            surname[i] = surn[i];
        }

        for (int i = strlen(surn);i < strlen(surname);i++)
        {
            surname[i] = NULL;
        }



        initial_name = name_init;
        initial_patronymic = patr_init;
        group_numb = group;

        for (int i = 0;i < 5;i++)
        {
            grades[i] = grade[i];
        }
    }

    char* readStudent()
    {
        int surn_len = strlen(surname);



        char* answer_full_name = new char[surn_len + 3];
        for (int i = surn_len + 3;i < strlen(answer_full_name);i++)
        {
            answer_full_name[i] = NULL;
        }

        for (int i = 0;i < surn_len;i++)
        {
            answer_full_name[i] = surname[i];
        }

        answer_full_name[surn_len] = 32;
        answer_full_name[surn_len + 1] = initial_name;
        answer_full_name[surn_len + 2] = initial_patronymic;

        return answer_full_name;
    }

    void update_group_and_grades(int new_gr, int new_grades[])
    {
        group_numb = new_gr;

        for (int i = 0;i < 5;i++)
        {
            grades[i] = new_grades[i];
        }
    }

    void to_annul()
    {
        for (int i = 0;i < 20;i++)
        {
            surname[i] = NULL;
        }
        initial_name = NULL;
        initial_patronymic = NULL;
        group_numb = NULL;
        for (int i = 0;i < 5;i++)
        {
            grades[i] = NULL;
        }
    }
};

void alph_sort(STUDENT st_arr[], int numb_of_st)
{
    for (int i = 0;i < numb_of_st - 1;i++)
    {
        for (int j = i; j < numb_of_st;j++)
        {
            if (strcmp(st_arr[i].surname, st_arr[j].surname) > 0)
            {
                swap(st_arr[i], st_arr[j]);
            }
        }
    }
}

int main()
{
    fout.open("Answ.txt", ios::out | ios::trunc); //очищення файлу для виведення результату
    fout.close();

    //file.open("Students.txt");
    file.open("Students2.txt");
    int numb_of_students;
    char numb_char;
    
    file.get(numb_char);
    numb_of_students = numb_char - '0';
    
    STUDENT* the_students = new STUDENT[numb_of_students];

    int const max_len_line = 20;
    char* help_char_line = new char[max_len_line];
    file.getline(help_char_line, max_len_line);
//зчитування студентів з файлу:
    for (int i = 0;i < numb_of_students;i++)
    {
        char temp_surname[20];        
        file.getline(temp_surname, 20);
               
        char name_letter_temp;        
        file.get(name_letter_temp);
        file.getline(help_char_line, max_len_line);

        char patronymic_lett_temp;        
        file.get(patronymic_lett_temp);
        file.getline(help_char_line, max_len_line);

        int temp_group;        
        file.get(numb_char);
        temp_group = numb_char - '0';
        file.getline(help_char_line, max_len_line);

        int temp_grades[5];
        int grades_ind = -1;
        
        for (int l = 0;l < 5;l++)
        {
            file.get(numb_char);
            
            if (numb_char != ' ')
            {
                grades_ind++;
                temp_grades[grades_ind] = numb_char - '0';
            }           
        }
        the_students[i].create(temp_surname, name_letter_temp, patronymic_lett_temp, temp_group, temp_grades);
        file.getline(help_char_line, max_len_line);
        
    }

//запуск сортування по прізвищам
    alph_sort(the_students, numb_of_students);

//вивід прізвищ і ініціалів студентів в файл, де студенти відсортовані в алфавітному порядку:
    fout.open("Answ.txt", ios::app);
    for (int i = 0;i < numb_of_students;i++)
    {
        char* the_full_name = the_students[i].readStudent();

        for (int l = 0;l < strlen(the_full_name);l++)
        {
            
            fout << the_full_name[l];            
        }        
        fout << endl;
    }
    fout.close();
    file.close();
    return 0;
}
