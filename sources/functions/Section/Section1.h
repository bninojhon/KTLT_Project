#include <D:\Project_KTLT_C\sources\functions\Program.h>
#include <conio.h>

// Chạy chương trình cho section1 //
    void ProgramSection1(int subsection);

    void Control_DiemThi();
    void Control_CPA();
//
void ProgramSection1(int subsection){
    system("cls");
    Header();
    printf("\n");
    switch(subsection){
        case 0:
            Print_SV_bin();     /// đã được viết ở SV.h
        break;
        case 1: 
            Print_HP_bin();     // đã được viết ở HP.h
        break;
        case 2:
            Control_DiemThi();  /// ở Program.h
        break;
        case 3:
            Control_CPA();      // ở Program.h
        break;
        default:
        printf(BHCYN"SOMETHING WENT WRONG!!!" reset "\n");
    }
    printf(BHRED"Press to continue!!" reset);
    printf("\n");
    getch();
}