#include <iostream>
#include <time.h>
#include "clui.h"
using namespace std;
void work_with_cursor(){
    int row = get_window_rows();
    int column = get_window_cols();

    cursor_to_pos(row / 2 , column /2);

    change_color_rgb(237, 237, 14);
    cout<<"Please enter your age:"<<endl;
    
    reset_color();
    cursor_to_pos(row / 2 + 1 , column /2);
    int age =0;
    change_color_rgb(237, 66, 14);

    cin>>age;
    reset_color();
    delay(2000);
    clear_screen();
    cursor_to_pos(row/2 , column /2);
    cout<<"Hello world!"<<endl;
    // cout<<"Row:"<<row<<endl;
    // cout<<"Column:"<<column<<endl;
    // cout<<"Hello World, I'm programmer"<<endl;
}

int main(){
    work_with_cursor();


    getch();
    return 0;
}